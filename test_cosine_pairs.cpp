#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <cmath>
#include <vector>

using namespace std;

// Function to compute the magnitude (Euclidean norm) of a vector
double computeMagnitude(const vector<double>& vec) {
    double sumSquares = 0.0;
    for (double x : vec) {
        sumSquares += x * x;
    }
    return sqrt(sumSquares);
}

// Function to compute the cosine angle between two vectors
double computeCosineAngle(const vector<double>& a, const vector<double>& b) {
    double dot = 0.0;
    for (size_t i = 0; i < a.size(); i++) {
        dot += a[i] * b[i];
    }
    double magA = computeMagnitude(a);
    double magB = computeMagnitude(b);
    double cosVal = dot / (magA * magB);
    if (cosVal > 1.0) cosVal = 1.0;
    if (cosVal < -1.0) cosVal = -1.0;
    return acos(cosVal);
}

TEST_CASE("Compute Magnitude") {
    vector<double> vec = {3.0, 4.0};
    double mag = computeMagnitude(vec);
    CHECK(mag == doctest::Approx(5.0));
}

TEST_CASE("Compute Cosine Angle") {
    vector<double> v1 = {1, 0};
    vector<double> v2 = {0, 1};
    // Expected angle is 90 degrees = pi/2 radians
    double angle = computeCosineAngle(v1, v2);
    CHECK(angle == doctest::Approx(M_PI / 2).epsilon(0.001));

    vector<double> v3 = {1, 1};
    angle = computeCosineAngle(v1, v3);
    // Expected angle is 45 degrees = pi/4 radians
    CHECK(angle == doctest::Approx(M_PI / 4).epsilon(0.001));
}
