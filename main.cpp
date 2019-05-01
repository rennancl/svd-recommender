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

// class Matrix{
//     public:
//         int x_dimention;
//         int y_dimention;
//         pair<int, int> dimentions;
//         float** matrix;

//     Matrix(pair<int, int> dimentions){
//         this->dimentions = dimentions;
//         this->x_dimention = dimentions.first;
//         this->y_dimention = dimentions.second;
//     }

//     void create_matrix(){
//     this->matrix = new float*[x_dimention + 1];
//     for (int i = 0; i < x_dimention + 1; i++)
//         {
//             this->matrix[i] = new float[y_dimention + 1];
//         }
//     }

//     void fill_ones(){
//         for(int i = 0; i < x_dimention + 1; i++)
//         {
//             for(int j = 0; j < y_dimention + 1; j++)
//             {
//                 matrix[i][j] = 1.0;
//             }
            
//         }
//     }

//     void fill_matrix(vector<array<int, 4>> input_vector){
//         for(unsigned i = 0; i < input_vector.size(); i++){
//             this->matrix[get<0>(input_vector[i])][get<1>(input_vector[i])] = (float)get<2>(input_vector[i]);
//         }
//     }

// };

// class Model{
//     public:
//         pair<int, int> p_dimentions;
//         pair<int, int> q_dimentions;
//         int model_dimentions;
//         float learning_rate;
//         vector<array<int, 4>> train;
//         vector<array<int, 4>> test;
//         vector<array<int, 4>> target;

//         Matrix* p_matrix;
//         Matrix* q_matrix;
    
//     Model(pair<int, int> dimentions, int model_dimentions, float learning_rate, vector<array<int, 4>> train, vector<array<int, 4>>  target){
//         this->model_dimentions = model_dimentions;
//         this->learning_rate = learning_rate;
//         this->train = train;
//         this->p_dimentions.first = dimentions.first;
//         this->p_dimentions.second = model_dimentions;
//         this->q_dimentions.first = model_dimentions;
//         this->q_dimentions.second = dimentions.second;
//         p_matrix = new Matrix(p_dimentions);
//         q_matrix = new Matrix(q_dimentions);
//     }

//     void create_pq_matrix(){
//         this->q_matrix->create_matrix();
//         this->p_matrix->create_matrix();
//     }

//     void fill_pq_matrix(){
//         this->q_matrix->fill_ones();
//         this->p_matrix->fill_ones();
//     }


//     Matrix getq_matrix(){
//         return *q_matrix;
//     }
    
//     Matrix getp_matrix(){
//         return *p_matrix;
//     }

//     void print_csv_line(int user, int item, float prediction){
//         cout << "u" << user << ":" << item << "," << prediction << endl;
//     }
//     void get_prediction(string filename){
//         ifstream file;
//         file.open(filename);
//         string line;
//         float prediction;
//         cout << "User:Item" << "," << "Prediction" << endl;
//         while(getline(file,line)){
//                 string work_line = line;
//                 string delimiter = ":";
//                 int user = atoi(work_line.substr(1, work_line.find(delimiter)-1).c_str());

//                 work_line = line;
//                 delimiter = ":";
//                 string delimiter2 = ",";
//                 int item = atoi(work_line.substr( work_line.find(delimiter)+2, work_line.find(delimiter2)).c_str());

//                 int rating = 0;
//                 int timestamp = 0;
//                 if(user == 0 and item == 0) continue;
//                 prediction =  get_value_product(user,item);
//                 cout << line << "," << prediction<< endl;
//             }   

//         file.close();
//         return;
//     }

//     float get_value_product(int user, int item){
//         float value = 0;
//         for(int j = 0; j < this->model_dimentions; j++){
//             value += p_matrix->matrix[user][j] * q_matrix->matrix[j][item];
//         }
//         return value;
//     }

//     void update_matrix(int user, int item, float error){
//         for(int j = 0; j < this->model_dimentions; j++){
//             this->p_matrix->matrix[user][j] = this->p_matrix->matrix[user][j]+ (this->q_matrix->matrix[j][item] * 2 * learning_rate * error);
//             this->q_matrix->matrix[j][item] = this->q_matrix->matrix[j][item]+ (this->p_matrix->matrix[user][j] * 2 * learning_rate * error);
//         }
//     }

//     // void stochastic_gradient_descent(){
//     //     int user;
//     //     int item;
//     //     float rate;
//     //     float error;
//     //     while(1){
//     //         for(unsigned i = 0; i < this->train.size(); i++){
//     //             user = this->train[i][0];
//     //             item = this->train[i][1];
//     //             rate = this->train[i][2];
//     //             error = (float)rate - get_value_product(user,item);
//     //             update_matrix(user, item, error);
//     //         }
//     //         if(abs(error) < MIN_ERROR) break;
//     //     }
//     // }

//     void stochastic_gradient_descent(){
//         int user;
//         int item;
//         float rate;
//         float error;
//         for(unsigned j = 0; j < EPOCHS; j++){
//             for(unsigned i = 0; i < this->train.size(); i++){
//                 user = this->train[i][0];
//                 item = this->train[i][1];
//                 rate = this->train[i][2];
//                 error = (float)rate - get_value_product(user,item);
//                 update_matrix(user, item, error);
//             }
//         }
//     }
// };

int max_in_vector(vector<array<int, 4>> vetor,unsigned const int index){
    int max_value = 0;
    for(unsigned i = 0; i < vetor.size(); i++){
        if(vetor[i][index] > max_value){
            max_value = vetor[i][index];
        }    
    }
    return max_value;
}

pair<int,int> get_matrix_dimentions(vector<array<int, 4>> vetor){
    pair<int,int> max_values;
    max_values.first = max_in_vector(vetor, 0);
    max_values.second = max_in_vector(vetor, 1);
    return max_values;
}

vector<array<int, 4>> process_inputs(string filename){
    ifstream file;
    file.open(filename);
    string line;

    std::vector<array<int, 4>> inputs;
    while(getline(file,line)){
        if (line.find(",") != std::string::npos){
            string work_line = line;
            string delimiter = ":";
            int user = atoi(work_line.substr(1, work_line.find(delimiter)-1).c_str());

            work_line = line;
            delimiter = ":";
            string delimiter2 = ",";
            int item = atoi(work_line.substr( work_line.find(delimiter)+2, work_line.find(delimiter2)).c_str());

            work_line = line;
            delimiter = ",";
            work_line = work_line.substr(work_line.find(delimiter)+1, -1);
            int rating = atoi(work_line.substr(0, work_line.find(delimiter)).c_str());

            work_line = line;
            delimiter = ",";
            work_line = work_line.substr(work_line.find(delimiter)+1, -1);
            int timestamp = atoi(work_line.substr(work_line.find(delimiter)+1, -1).c_str());
            if(user == 0 and item == 0) continue;
            inputs.push_back({user, item, rating, timestamp});
        }
        else{
            string work_line = line;
            string delimiter = ":";
            int user = atoi(work_line.substr(1, work_line.find(delimiter)-1).c_str());

            work_line = line;
            delimiter = ":";
            string delimiter2 = ",";
            int item = atoi(work_line.substr( work_line.find(delimiter)+2, work_line.find(delimiter2)).c_str());

            int rating = 0;
            int timestamp = 0;
            if(user == 0 and item == 0) continue;
            inputs.push_back({user, item, rating, timestamp});
        }
    }

    file.close();
    return inputs;
}

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

