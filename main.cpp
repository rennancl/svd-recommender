#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>
#include <cmath> 
#include "model.h"
#define MODEL_DIMENTIONS 30
#define LEARNING_RATE .002
#define MIN_ERROR 0.1
#define EPOCHS 50

using namespace std;

int main(int argc, char *argv[])
{ 
    string ratings_filename = argv[1];
    string targets_filename = argv[2];

    vector<array<int, 4>> ratings = process_inputs(ratings_filename);
    vector<array<int, 4>> targets = process_inputs(targets_filename);

    Matrix matrix(get_matrix_dimentions(ratings));
    matrix.create_matrix();
    matrix.fill_matrix(ratings);

    Model model(matrix.dimentions, MODEL_DIMENTIONS, LEARNING_RATE, ratings);
    model.create_pq_matrix();
    model.fill_pq_matrix(); 
    model.stochastic_gradient_descent();
    model.get_prediction(targets_filename);

    return 0;
}

