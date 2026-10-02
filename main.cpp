#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

std::vector<std::vector<int>> read_file();



int main(){
    // gets file name
    std::string file_name;
    std::cout << "Enter the file name: ";
    std::cin >> file_name;
    std::ifstream my_file(file_name);

    // Check if the file opened successfully
    if (!my_file.is_open()) {
        throw std::runtime_error("Error: Could not open the file");    
    }

    // initializes variables
    int matrix_size;
    my_file >> matrix_size; // reads the first row which should be the number of rows
    my_file.ignore(); // skips the newline character

    int matrix_a[matrix_size][matrix_size];
    int matrix_b[matrix_size][matrix_size];
    std::string line;

    // reads the input file and populates the matrix
    int row_index = 0;
    while (std::getline(my_file, line)) {
        std::istringstream ss(line);
        int col_index = 0;
        int value;

        // Extract individual numbers from the current line
        int col_counter = 0;
        while (ss >> value && col_index < matrix_size) {
            
            if (row_index < matrix_size){
                matrix_a[row_index][col_index] = value;
            }
            else{
                matrix_b[row_index % matrix_size][col_index] = value;
            }
            col_index ++ ;
        }
        row_index ++;


    }

    for (int i = 0; i < matrix_size; ++i) {
        for (int j = 0; j < matrix_size; ++j) {
            std::cout << matrix_a[i][j] << " ";
        }
        std::cout << "\n";
    }

        for (int i = 0; i < matrix_size; ++i) {
        for (int j = 0; j < matrix_size; ++j) {
            std::cout << matrix_b[i][j] << " ";
        }
        std::cout << "\n";
    }

    return 0;
}

