#include<bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()

using namespace std;
#define int long long
mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

int Random(int l,int r) {
    return l + (rng()%(r-l+1));
}

void generateAndSaveTestCase(int testCaseNumber) {

    // Create a filename for the test case
    ostringstream filenameStream;
    filenameStream << "test_case--------" << setw(3) << setfill('0') << testCaseNumber << ".txt";
    string filename = filenameStream.str();

    // Open the file for writing
    ofstream outputFile(filename);

    if (!outputFile.is_open()) {
        cerr << "Error: Unable to open file " << filename << " for writing." << endl;
        return;
    }

    const int N = 1e5;
    int n = N ;
    // Save the test case to the file
    int start_val = 1, end_val = 1e9;
    outputFile << n << endl;
    for (int i =0;i<n;i++){
        outputFile<< Random(start_val , end_val) <<" ";
    }

    // Close the file
    outputFile.close();

    cout << "Test case " << testCaseNumber << " saved to " << filename << endl;
}

signed main() {
    int numTestCases = 5; // Change this to the number of test cases you want

    // Seed the random number generator
    srand(time(nullptr));

    // Generate and save test cases
    for (int i = 1; i <= numTestCases; ++i) {
        generateAndSaveTestCase(i);
    }

}
