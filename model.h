#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>
#include <cmath>
#include "matrix.h"
#define MODEL_DIMENTIONS 30
#define LEARNING_RATE .002
#define EPOCHS 80
#define BIAS_DIVISOR 5
using namespace std;

class Model{
    public:
        std::pair<int, int> p_dimentions;
        std::pair<int, int> q_dimentions;
        int model_dimentions;
        float learning_rate;
        float mean;
        std::vector<array<int, 5>> train;
        std::vector<array<int, 5>> test;
        std::vector<array<int, 5>> target;

        Matrix* p_matrix;
        Matrix* q_matrix;
        int* mean_users;
        int* mean_items;
        int* users_num_edges;
        int* items_num_edges;
        float* user_bias;
        float* item_bias;
    
    Model(std::pair<int, int> dimentions, std::vector<array<int, 5>> train);

    void create_pq_matrix();

    void fill_pq_matrix();

    Matrix getq_matrix();
    
    Matrix getp_matrix();

    //this function get the global item rating mean
    void get_mean();

    void print_csv_line(int user, int item, float prediction);

    //this function gets the file output and process all pairs to predict genarating the submission file
    void get_prediction(string filename);

    //used to generate the prediction, computing the dot product os two vectors
    float get_value_product(int user, int item);

    //function used to update both user and item matrixes
    void update_matrix(int user, int item, float error);

    //this is the fuction to train the model
    void stochastic_gradient_descent();
};