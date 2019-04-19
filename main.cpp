#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>

using namespace std;
#define KDIMENTIONS 30
#define LEARNING_RATE 0.1 

class Matrix{
    public:
        int x_dimention;
        int y_dimention;
        pair<int, int> dimentions;
        int** matrix;

    Matrix(pair<int, int> dimentions){
        this->dimentions = dimentions;
        this->x_dimention = dimentions.first;
        this->y_dimention = dimentions.second;
    }

    void create_matrix(){
        this->matrix = new int*[x_dimention + 1];
        for (int i = 0; i < x_dimention + 1; i++)
        {
            this->matrix[i] = new int[y_dimention + 1];
        }
    }

    void fill_matrix(vector<tuple<int, int, int, int>> input_vector){
        for(unsigned i = 0; i < input_vector.size(); i++){
            this->matrix[get<0>(input_vector[i])][get<1>(input_vector[i])] = get<2>(input_vector[i]);
        }
    }
};

class Model{
    public:
        pair<int, int> p_dimentions;
        pair<int, int> q_dimentions;
        float learning_rate;
        Matrix* p_matrix;
        Matrix* q_matrix;
    
    Model(pair<int, int> dimentions, int knumber, int learning_rate){
        this->learning_rate = learning_rate;
        this->p_dimentions.first = dimentions.first;
        this->p_dimentions.second = knumber;
        this->q_dimentions.first = knumber;
        this->q_dimentions.second = dimentions.second;
        p_matrix = new Matrix(p_dimentions);
        q_matrix = new Matrix(q_dimentions);
    }

    void create_pq_matrix(){
        this->q_matrix->create_matrix();
        this->p_matrix->create_matrix();
    }

    Matrix getq_matrix(){
        return *q_matrix;
    }
    void stochastic_gradient_descent(){
        bool converged = false;
        while(1){    
            converged = true;
            if(converged) break;
        }
    }
};

pair<int,int> get_matrix_dimentions(vector<tuple<int, int, int, int>> vetor){
    pair<int,int> max_values;
    int max_user = 0;
    int max_item = 0;

    for(unsigned i = 0; i < vetor.size(); i++){
        if(get<0>(vetor[i]) > max_user){
            max_user = get<0>(vetor[i]);
        }    
    }

    for(unsigned i = 0; i < vetor.size(); i++){
        if(get<1>(vetor[i]) > max_item){
            max_item = get<1>(vetor[i]);
        }    
    }

    max_values.first = max_user;
    max_values.second = max_item;
    return max_values;
}

vector<tuple<int, int, int, int>> process_inputs(string filename){
    ifstream file;
    file.open(filename);
    string line;

    std::vector<tuple<int, int, int, int>> inputs;
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
            inputs.push_back(make_tuple(user, item, rating, timestamp));
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
            inputs.push_back(make_tuple(user, item, rating, timestamp));
        }
    }

    file.close();
    return inputs;
}

int main(int argc, char *argv[])
{ 
    string ratings_filename = argv[1];
    string targets_filename = argv[2];

    vector<tuple<int, int, int, int>> ratings = process_inputs(ratings_filename);
    vector<tuple<int, int, int, int>> targets = process_inputs(targets_filename);

    Matrix matrix(get_matrix_dimentions(ratings));
    matrix.create_matrix();
    matrix.fill_matrix(ratings);

    Model model(matrix.dimentions, KDIMENTIONS, LEARNING_RATE);
    model.create_pq_matrix();

    // iterate throug q matriz to check if it was created
    for(int i =0; i < KDIMENTIONS; i++){
        for(int j = 0; j < matrix.dimentions.second; j++)
        {
            int a = model.getq_matrix().matrix[i][j];
        }
    }
    return 0;
}