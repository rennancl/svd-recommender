#include "matrix.h"
using namespace std;

Matrix::Matrix(std::pair<int, int> dimentions){
    this->dimentions = dimentions;
    this->x_dimention = dimentions.first;
    this->y_dimention = dimentions.second;
}

void Matrix::create_matrix(){
this->matrix = new float*[x_dimention + 1];
for (int i = 0; i < x_dimention + 1; i++)
    {
        this->matrix[i] = new float[y_dimention + 1];
    }
}

void Matrix::fill_ones(){
    for(int i = 0; i < x_dimention + 1; i++)
    {
        for(int j = 0; j < y_dimention + 1; j++)
        {
            matrix[i][j] = 1.0;
        }
        
    }
}

void Matrix::fill_matrix(std::vector<array<int, 4>> input_vector){
    for(unsigned i = 0; i < input_vector.size(); i++){
        this->matrix[get<0>(input_vector[i])][get<1>(input_vector[i])] = (float)get<2>(input_vector[i]);
    }
}