#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>

using namespace std;
#define KDIMENTIONS 30
// string -> tuple<int, int, int>

pair<int,int> max_user_item(vector<tuple<int, int, int, int>> vetor){
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
int** create_matrix(pair<int,int> dimentions){
    int** matrix = new int*[dimentions.first + 1];
    for (int i = 0; i < dimentions.first + 1; i++)
    {
        matrix[i] = new int[dimentions.second + 1];
    }
    return matrix;
}

int** fill_matrix(vector<tuple<int, int, int, int>> input_vector, pair<int,int> dimentions){

    int** matrix = create_matrix(dimentions);
    for(unsigned i = 0; i < input_vector.size(); i++){
        matrix[get<0>(input_vector[i])][get<1>(input_vector[i])] = get<2>(input_vector[i]);
    }
    return matrix;
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

void create_predictions_file(int predictions){
    cout << predictions << endl;
    return;
}

pair<int**, int**> stochastic_gradient_descent(int **matrix,pair<int,int> dimentions, int k){
    pair<int**, int**> matrixes;
    
    pair<int, int> p_dimentions;
    pair<int, int> q_dimentions;

    p_dimentions.first = dimentions.first;
    p_dimentions.second = k;

    q_dimentions.first = k;
    q_dimentions.second = dimentions.second;

    int **p_matrix  = create_matrix(p_dimentions);
    int **q_matrix  = create_matrix(q_dimentions);
    
    bool converged = false;
    while(1){    
        converged = true;
        if(converged) break;
    }

    matrixes.first = p_matrix;
    matrixes.second = q_matrix;
    return matrixes;
}

int main(int argc, char *argv[])
{ 
    string ratings_filename = argv[1];
    string targets_filename = argv[2];

    vector<tuple<int, int, int, int>> ratings= process_inputs(ratings_filename);
    vector<tuple<int, int, int, int>> targets= process_inputs(targets_filename);

    pair<int,int> dimentions = max_user_item(ratings);
    int** matrix = fill_matrix(ratings, dimentions);

    int** p_matrix;
    int** q_matrix;
    pair<int**, int**> pqmatrix;

    pqmatrix = stochastic_gradient_descent(matrix,dimentions,KDIMENTIONS);
    p_matrix = pqmatrix.first;
    q_matrix = pqmatrix.second;
    
    // iterate throug p matriz to check if it was created
    for(int i =0; i < dimentions.first; i++){
        for(int j = 0; j < KDIMENTIONS; j++)
        {
            int a = p_matrix[i][j];
        }
    }

    // iterate throug q matriz to check if it was created
    for(int i =0; i < KDIMENTIONS; i++){
        for(int j = 0; j < dimentions.second; j++)
        {
            int a = q_matrix[i][j];
        }
    }
    create_predictions_file(1);
    return 0;
}