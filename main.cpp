#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <stdexcept>
#include <iostream>
#include <iomanip>

std::vector<std::vector<int>> read_file();
std::vector<std::vector<int>> add_matrices(std::vector<std::vector<int>> matrix_1, std::vector<std::vector<int>>  matrix_2, int matrix_size);
void print_matrix(std::vector<std::vector<int>> matrix, int matrix_size);
std::vector<std::vector<int>> multiply_matrices(std::vector<std::vector<int>> matrix_1, std::vector<std::vector<int>>  matrix_2, int matrix_size);
void get_matrix_diagonal_sums(std::vector<std::vector<int>> matrix, int matrix_size);
std::vector<std::vector<int>> swap_rows(std::vector<std::vector<int>> matrix, int index_1, int index_2);
std::vector<std::vector<int>> swap_cols(std::vector<std::vector<int>> matrix, int col_1, int col_2);



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

    std::cout << "Matrix A\n";
    print_matrix(matrix_a, matrix_size);
    std::cout << "\n";

    std::cout << "Matrix B\n";
    print_matrix(matrix_b, matrix_size);
    std::cout << "\n";

    std::cout << "A + B\n";
    print_matrix(add_matrices(matrix_a, matrix_b, matrix_size), matrix_size);
    std::cout << "\n";

    std::cout << "A * B\n";
    print_matrix(multiply_matrices(matrix_a, matrix_b, matrix_size), matrix_size);
    std::cout << "\n";

    std::cout << "Diagonal sums for Matrix A:\n";
    get_matrix_diagonal_sums(matrix_a, matrix_size);
    std::cout << "\n";

    std::cout << "Problem 5 - Rows 0 and 2 Swapped\n";
    print_matrix(swap_rows(matrix_a, 0, 2),matrix_size); // Not entirely sure if I was supposed to get user input for this :(
    std::cout << "\n";

    std::cout << "Problem 6 - Columns 0 and 2 Swapped\n";
    print_matrix(swap_cols(matrix_a, 0, 2),matrix_size);
    std::cout << "\n";


    




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

std::vector<std::vector<int>>  multiply_matrices(std::vector<std::vector<int>> matrix_1, std::vector<std::vector<int>>  matrix_2, int matrix_size){
    /*Takes two matrices and returns the product of them*/
    std::vector<std::vector<int>>  new_matrix(matrix_size, std::vector<int>(matrix_size,0));

    for(int row = 0; row < matrix_size; row++){ // row and column will be relative to matrix_1
        for(int col = 0; col < matrix_size; col ++){
            for(int k = 0; k < matrix_size; k++){
                new_matrix[row][col] += matrix_1[row][k] * matrix_2[k][col];
            }
        }
    }
    return new_matrix;
}

void get_matrix_diagonal_sums(std::vector<std::vector<int>> matrix, int matrix_size){
    // finds sum of main diagonal (top left to bottom right)
    int main_diagonal = 0;
    for(int row = 0; row < matrix_size; row++){
        int col = row;
        main_diagonal += matrix[row][col];
    }

    //finds sum of secondary diagonal (top right to bottom left)
    int secondary_diagonal = 0;
    for(int row = matrix_size - 1; row >= 0; row--){
        int col = (matrix_size - 1) - row;
        secondary_diagonal += matrix[row][col];
    }

    std::cout << std::fixed << std::setprecision(1) << "Main diagonal sum: " << main_diagonal << "\n"; 
    std::cout << std::fixed << std::setprecision(1) << "Secondary diagonal sum: " << secondary_diagonal << "\n"; 
}

std::vector<std::vector<int>> swap_rows(std::vector<std::vector<int>> matrix, int index_1, int index_2){
    if (index_1 >= 0 && index_1 < matrix.size()){
        if(index_2 >= 0 && index_2 < matrix.size()){
            std::swap(matrix[index_1], matrix[index_2]);
        }
        else{
            throw std::invalid_argument("row index not in range");
        }
    }
    else{
        throw std::invalid_argument("row index not in range");
    }
    return matrix;
}

std::vector<std::vector<int>> swap_cols(std::vector<std::vector<int>> matrix, int col_1, int col_2){
    // create an identity matrix
    std::vector<std::vector<int>> identity_matrix(matrix.size(), std::vector<int>(matrix.size(), 0));
    for (int i = 0; i < matrix.size(); ++i) {
        identity_matrix[i][i] = 1;
    }

    if (col_1 >= 0 && col_1 < matrix.size()){
        if(col_2 >= 0 && col_2 < matrix.size()){
            std::swap(identity_matrix[col_1], identity_matrix[col_2]);
        }
        else{
            throw std::invalid_argument("col index not in range");
        }
    }
    else{
        throw std::invalid_argument("col index not in range");
    }

    return multiply_matrices(matrix, identity_matrix, matrix.size());
}