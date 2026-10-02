#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

int main(){
    // gets file name
    std::string file_name;
    std::cout << "Enter the file name: ";
    std::cin >> file_name;
    std::ifstream my_file(file_name);

    // Check if the file opened successfully
    if (!my_file.is_open()) {
        std::cerr << "Error: Could not open the file" << std::endl;
        return 1;
    }

    // reads the file and populates a 2d array
    int number_of_rows;
    std::vector<std::vector<int>> matrix;
    std::string line;

    my_file >> number_of_rows; // reads the first row which should be the number of rows
    my_file.ignore(); // skips the newline character

    // reads the input file and populates the matrix
    while (std::getline(my_file, line)) {
        std::istringstream ss(line);
        std::vector<int> row;
        int value;

        // Extract individual numbers from the current line
        while (ss >> value) {
            row.push_back(value);
        }

        // Only add non-empty rows to the matrix
        if (!row.empty()) {
            matrix.push_back(row);
        }

        std::cout << row[0] <<" ";
    }

    

    return 0;
}