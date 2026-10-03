#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <stdexcept>

std::vector<std::vector<int>> read_file();
std::vector<std::vector<int>> add_matrices(std::vector<std::vector<int>> matrix_1, std::vector<std::vector<int>>  matrix_2, int matrix_size);
void print_matrix(std::vector<std::vector<int>> matrix, int matrix_size);



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

    std::vector<std::vector<int>> matrix_a(matrix_size, std::vector<int>(matrix_size));
    std::vector<std::vector<int>> matrix_b(matrix_size, std::vector<int>(matrix_size));
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

    print_matrix(add_matrices(matrix_a, matrix_b, matrix_size), matrix_size);

    return 0;
}

std::vector<std::vector<int>>  add_matrices(std::vector<std::vector<int>> matrix_1, std::vector<std::vector<int>>  matrix_2, int matrix_size){
    /*Takes two matrices and returns the sum of them*/
    std::vector<std::vector<int>>  new_matrix(matrix_size, std::vector<int>(matrix_size,0));

    for(int row = 0; row < matrix_size; row++){
        for(int col = 0; col < matrix_size; col ++){
            new_matrix[row][col] = matrix_1[row][col] + matrix_2[row][col];
        }
    }
    return new_matrix;
}

void print_matrix(std::vector<std::vector<int>> matrix, int matrix_size){
    /*iterates through a 2d vector array and prints the array out*/
        for (int i = 0; i < matrix_size; ++i) {
            for (int j = 0; j < matrix_size; ++j) {
                std::cout << matrix[i][j] << " ";
        }
        std::cout << "\n";
    }
}