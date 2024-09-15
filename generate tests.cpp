#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()

using namespace std;

// Function to generate and save a single test case to a text file
void generateAndSaveTestCase(int testCaseNumber) {
    // Generate your test case here
    // For example, generating a random integer between 1 and 100
    int testCase = rand() % 30 + 1;

    // Create a filename for the test case
    ostringstream filenameStream;
    filenameStream << "test_case__" << setw(3) << setfill('0') << testCaseNumber << ".txt";
    string filename = filenameStream.str();

    // Open the file for writing
    ofstream outputFile(filename);

    if (!outputFile.is_open()) {
        cerr << "Error: Unable to open file " << filename << " for writing." << endl;
        return;
    }

    // Save the test case to the file
    outputFile << testCase << endl;
    for (int i =0;i<testCase;i++){
        outputFile<< testCase+rand()%30<<" ";
    }

    // Close the file
    outputFile.close();

    cout << "Test case " << testCaseNumber << " saved to " << filename << endl;
}

int main() {
    int numTestCases = 10; // Change this to the number of test cases you want

    // Seed the random number generator
    srand(time(nullptr));

    // Generate and save test cases
    for (int i = 1; i <= numTestCases; ++i) {
        generateAndSaveTestCase(i);
    }

    return 0;
}
