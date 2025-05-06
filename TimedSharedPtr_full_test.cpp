// TimedSharedPtr_full_test.cpp

#define DOCTEST_CONFIG_IMPLEMENT    // emit doctest’s implementation
#define DOCTEST_CONFIG_RUNNER      // omit doctest’s own main()
#include "doctest.h"

#include <iostream>
#include <chrono>
#include <thread>

#include <cstddef>
#include <climits>
#include <utility>

using namespace std;
using Clock        = chrono::high_resolution_clock;
using clockTime    = chrono::time_point<Clock>;
using milliSeconds = chrono::milliseconds;

// ————————————————————————————————————————————————————————————————
// Control block for each managed pointer
// ————————————————————————————————————————————————————————————————
struct ControlTimedSharedPtr {
    void*        ptr;
    long         myUseCount;
    clockTime    startTime;
    milliSeconds expiry;

    ControlTimedSharedPtr(void* p, long expiryMs)
      : ptr(p),
        myUseCount(1),
        startTime(Clock::now()),
        expiry(milliSeconds{expiryMs})
    {
        cout << "ControlTimedSharedPtr " << ptr
             << " start: "
             << chrono::duration_cast<milliSeconds>(Clock::now() - startTime).count()
             << " ms\n";
    }

    ~ControlTimedSharedPtr() {
        cout << "ControlTimedSharedPtr " << ptr
             << " end:   "
             << chrono::duration_cast<milliSeconds>(Clock::now() - startTime).count()
             << " ms\n";
    }
};

// ————————————————————————————————————————————————————————————————
// TimedSharedPtr<T>
// ————————————————————————————————————————————————————————————————
template<typename T>
class TimedSharedPtr {
private:
    ControlTimedSharedPtr* _ctrl;

    milliSeconds elapsedMs() const noexcept {
        if (!_ctrl) return milliSeconds{LONG_MAX};
        return chrono::duration_cast<milliSeconds>(Clock::now() - _ctrl->startTime);
    }

public:
    // — ctors / dtor / copy / move as before —
    TimedSharedPtr() noexcept : _ctrl(nullptr) {}
    TimedSharedPtr(T* raw, long expiryMs)
      : _ctrl(new ControlTimedSharedPtr(raw, expiryMs)) {}
    explicit TimedSharedPtr(T* raw)
      : TimedSharedPtr(raw, 1000) {}

    TimedSharedPtr(const TimedSharedPtr& o) noexcept
      : _ctrl(o._ctrl) { if (_ctrl) ++_ctrl->myUseCount; }

    TimedSharedPtr(TimedSharedPtr&& o) noexcept
      : _ctrl(o._ctrl) { o._ctrl = nullptr; }

    TimedSharedPtr& operator=(const TimedSharedPtr& o) {
        if (this!=&o) {
            if (_ctrl && --_ctrl->myUseCount==0) {
                delete static_cast<T*>(_ctrl->ptr);
                delete _ctrl;
            }
            _ctrl = o._ctrl;
            if (_ctrl) ++_ctrl->myUseCount;
        }
        return *this;
    }

    TimedSharedPtr& operator=(TimedSharedPtr&& o) noexcept {
        if (this!=&o) {
            if (_ctrl && --_ctrl->myUseCount==0) {
                delete static_cast<T*>(_ctrl->ptr);
                delete _ctrl;
            }
            _ctrl = o._ctrl;
            o._ctrl = nullptr;
        }
        return *this;
    }

    ~TimedSharedPtr() {
        if (_ctrl && --_ctrl->myUseCount==0) {
            delete static_cast<T*>(_ctrl->ptr);
            delete _ctrl;
        }
    }

    // — accessors —
    long use_count() const noexcept {
        return _ctrl ? _ctrl->myUseCount : 0;
    }

    // get() no longer prints anything
    T* get() const noexcept {
        if (!_ctrl) return nullptr;
        if (elapsedMs() > _ctrl->expiry) return nullptr;
        return static_cast<T*>(_ctrl->ptr);
    }

    // new helper: elapsed time in ms
    long elapsed() const noexcept {
        return elapsedMs().count();
    }

    T& operator*()  const { return *get(); }
    T* operator->() const { return  get(); }

    bool expired() const noexcept {
        return !_ctrl || (elapsedMs() > _ctrl->expiry);
    }

    void reset(long newExpiryMs) {
        if (!_ctrl) return;
        _ctrl->startTime = Clock::now();
        _ctrl->expiry    = milliSeconds{newExpiryMs};
    }
    void reset(T* raw, long newExpiryMs) {
        this->~TimedSharedPtr();
        _ctrl = new ControlTimedSharedPtr(raw, newExpiryMs);
    }

    explicit operator bool() const noexcept {
        return get() != nullptr;
    }
};

// a small Node for your original example
struct Node {
    Node(int v) : val(v) {}
    int val;
    TimedSharedPtr<Node> next;
};

// ————————————————————————————————————————————————————————————————
// Custom main: first your smoke tests, then doctest
// ————————————————————————————————————————————————————————————————
int main(int argc, char** argv) {
    // — your original Node test —
    {
        TimedSharedPtr<Node> myNode(new Node(7), 100);
        TimedSharedPtr<Node> myOtherNode = myNode;

        this_thread::sleep_for(chrono::milliseconds(50));
        cout << "myNode.get() address: <" << myNode.get() << ">\n";
        cout << "myNode.use_count(): "     << myNode.use_count()     << "\n";
        cout << "myOtherNode.use_count(): " << myOtherNode.use_count() << "\n";

        this_thread::sleep_for(chrono::milliseconds(75));
        cout << "The ptr should have expired:\n";
        cout << "myNode.get() address: <Yeo! Expired " 
             << myNode.elapsed() << ">\n";
        cout << "-----------\n";
    }

    // — your simple int test —
    {
        TimedSharedPtr<int> p(new int(42));
        cout << p.get() << "\n";
        cout << "p.use_count(): " << p.use_count() << "\n";
        TimedSharedPtr<int> q = p;
        cout << "p.use_count(): " << p.use_count() << "\n";
        cout << "q.use_count(): " << q.use_count() << "\n";
    }

    // — now run all the doctest cases —
    doctest::Context ctx;
    ctx.applyCommandLine(argc, argv);
    return ctx.run();
}

// ————————————————————————————————————————————————————————————————
// your existing TEST_CASEs go here unchanged…
TEST_CASE("default constructed is null/expired") {
    TimedSharedPtr<int> p;
    CHECK(p.use_count()==0);
    CHECK(p.expired());
    CHECK_FALSE(p);
    CHECK(p.get()==nullptr);
}
// … etc …
