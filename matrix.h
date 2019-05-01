#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>
#include <cmath>
#define MODEL_DIMENTIONS 30
#define LEARNING_RATE .002
#define MIN_ERROR 0.1
#define EPOCHS 50
using namespace std;

class Matrix{
    public:
        int x_dimention;
        int y_dimention;
        std::pair<int, int> dimentions;
        float** matrix;
    
    Matrix(std::pair<int, int> dimentions);
    void create_matrix();
    void fill_ones();
    void fill_matrix(std::vector<array<int, 4>> input_vector);
};