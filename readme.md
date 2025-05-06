# Final Exam: TimedSharedPtr Library Documentation

---

## 1. Overview

**TimedSharedPtr** is a C++ smart‐pointer template that combines:  
- **Shared ownership** semantics (like `std::shared_ptr`)  
- **Time‐based expiration** of the managed object  

Key features:  
- Heap‐allocated **control block** tracking pointer, ref-count, creation time, expiry duration  
- Copy/move constructors & assignments with correct ref-count management  
- `get()`, `expired()`, `reset()` and boolean-conversion  
- Automatic deletion of managed object & control block when ref-count → 0 or time expires  

---

## 2. Requirements

- **C++17** (or later)  
- `<chrono>` for timing  
- `<thread>` (for tests/demo)  
- **doctest** (or other unit-test framework)  

---

## 3. Architecture Diagram

```
+----------------------------------------------------+
|                    Client Code                     |
|  ┌──────────────────────────────────────────────┐  |
|  | TimedSharedPtr<Node> myNode(new Node(7),100)|  |
|  | TimedSharedPtr<Node> other = myNode;        |  |
|  | …                                           |  |
|  └──────────────────────────────────────────────┘  |
+                         │                          +
                          ▼
+----------------------------------------------------+
|                 TimedSharedPtr<T>                  |
|  ┌──────────────────────────────────────────────┐  |
|  | - _ctrl: ControlTimedSharedPtr*            |  |
|  | + get(), expired(), reset(), use_count()   |  |
|  | + operator*, operator->, operator bool()   |  |
|  └──────────────────────────────────────────────┘  |
+                         │                          +
                          ▼
+----------------------------------------------------+
|             ControlTimedSharedPtr (heap)           |
|  ┌──────────────────────────────────────────────┐  |
|  | - ptr: void*                                 │  |
|  | - myUseCount: long                           │  |
|  | - startTime: clockTime                       │  |
|  | - expiry: milliSeconds                       │  |
|  | + ctor(p,expiry)                             │  |
|  | + ~dtor()  // logs “end:” time               │  |
|  └──────────────────────────────────────────────┘  |
+                         │                          +
                          ▼
+----------------------------------------------------+
|                Raw Object (Client’s T*)            |
+----------------------------------------------------+
```

---

## 4. Class Diagram

```
┌───────────────────────────┐           ┌────────────────────────────┐
│  TimedSharedPtr<T>        │           │  ControlTimedSharedPtr     │
│───────────────────────────│           │────────────────────────────│
│ - _ctrl: ControlTimed…*   │ owns →    │ - ptr: void*               │
│ + TimedSharedPtr(raw, ms) │           │ - myUseCount: long         │
│ + TimedSharedPtr(raw)     │           │ - startTime: clockTime     │
│ + copy/move ctors/assign  │           │ - expiry: milliSeconds     │
│ + ~TimedSharedPtr()       │           │ + ctor(p, expiry)          │
│ + get(): T*               │           │ + ~ControlTimed…()         │
│ + expired(): bool         │           └────────────────────────────┘
│ + reset(ms) / reset(ptr)  │
│ + use_count(): long       │
│ + operator*, operator->   │
│ + operator bool(): bool   │
└───────────────────────────┘
```

---

## 5. Sequence Diagram (Pointer Lifespan)

```
Client            TimedSharedPtr           ControlBlock            Managed Object
  │                     │                         │                          │
  │ new Node(7)         │                         │                          │
  │────────────────────▶│ ctor(raw,100ms)         │                          │
  │                     ├────────────────────────▶│ allocate ControlBlock   │
  │                     │                         ├─ ptr = raw             │
  │                     │                         ├─ myUseCount = 1        │
  │                     │                         ├─ startTime = now       │
  │                     │                         └─ expiry = 100ms        │
  │                     │                         │                          │
  │ copy             ┌──┴───┐                      │                          │
  │ of TimedSharedPtr│      │                      │                          │
  │─────────────────▶│ copy │                      │                          │
  │                  │ ctor │ increments myUseCount=2                        │
  │                  └──────┘                      │                          │
  │                     │                         │                          │
  │ get() at t=50ms     │                         │                          │
  │────────────────────▶│                    elapsed = 50ms                 │
  │                     │                         └─ returns raw pointer    │
  │                     │                         │                          │
  │ sleep 75ms         │                         │                          │
  │──────────────────────────────────────────────▶│ elapsed = 125ms           │
  │ get() at t=125ms   │                         └─ expired → nullptr       │
  │────────────────────▶│ get() returns nullptr                            │
  │                     │                         │                          │
  │ both ptrs destroyed ─────────────────────────▶│ myUseCount-- (→1, then 0)│
  │                     │                         ├─ delete raw object      │
  │                     │                         └─ delete ControlBlock    │
```

---

## 6. Build & Test

```bash
# Compile library + smoke tests + doctest
g++ -std=c++17 TimedSharedPtr_full_test.cpp -o full_test -pthread

# Run demo & unit tests in one:
./full_test
```

*End of Documentation*  
