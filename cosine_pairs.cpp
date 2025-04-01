#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>

using namespace std;

// Structure to hold a pair of vector indices and their cosine angle
struct PairDistance {
    int index1;
    int index2;
    double angle; // angle in radians between vectors
};

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
    // Compute cosine similarity and clamp to [-1, 1] to avoid domain errors with acos
    double cosVal = dot / (magA * magB);
    if (cosVal > 1.0) cosVal = 1.0;
    if (cosVal < -1.0) cosVal = -1.0;
    // Angle in radians between the two vectors
    return acos(cosVal);
}

int main(int argc, char* argv[]) {
    // Check if filename is provided as command-line argument
    if (argc < 2) {
        cout << "Usage: " << argv[0] << " <input_file>\n";
        return 1;
    }
    
    ifstream infile(argv[1]);
    if (!infile) {
        cerr << "Error opening file: " << argv[1] << "\n";
        return 1;
    }
    
    vector<vector<double>> vectors;
    string line;
    // Read each line from the file
    while(getline(infile, line)) {
        if (line.empty()) continue;
        istringstream iss(line);
        vector<double> vec;
        double value;
        // Read all doubles from the line into the vector
        while (iss >> value) {
            vec.push_back(value);
        }
        if (!vec.empty()) {
            vectors.push_back(vec);
        }
    }
    infile.close();
    
    // There must be at least two vectors to compare
    if (vectors.size() < 2) {
        cout << "Need at least two vectors to compute pairwise distances.\n";
        return 1;
    }
    
    // Ensure all vectors are of the same dimension
    size_t dimension = vectors[0].size();
    for (size_t i = 1; i < vectors.size(); i++) {
        if (vectors[i].size() != dimension) {
            cerr << "Error: Not all vectors have the same dimension.\n";
            return 1;
        }
    }
    
    // Compute cosine angles for every unique pair of vectors
    vector<PairDistance> distances;
    for (size_t i = 0; i < vectors.size(); i++) {
        for (size_t j = i + 1; j < vectors.size(); j++) {
            double angle = computeCosineAngle(vectors[i], vectors[j]);
            distances.push_back({static_cast<int>(i), static_cast<int>(j), angle});
        }
    }
    
    // Sort pairs by cosine angle (smallest angle first means the vectors are closest)
    sort(distances.begin(), distances.end(), [](const PairDistance& a, const PairDistance& b) {
        return a.angle < b.angle;
    });
    
    // Output the sorted pairwise cosine angles with 4-decimal precision
    cout << fixed << setprecision(4);
    for (const auto& pd : distances) {
        cout << "Vectors (" << pd.index1 << ", " << pd.index2 << ") - Angle: " << pd.angle << " radians" << endl;
    }
    
    return 0;
}
