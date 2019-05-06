#include "model.h"
using namespace std;

Model::Model(std::pair<int, int> dimentions, std::vector<array<int, 5>> train){
    this->model_dimentions = MODEL_DIMENTIONS;
    this->learning_rate = LEARNING_RATE;
    this->train = train;
    this->p_dimentions.first = dimentions.first;
    this->p_dimentions.second = model_dimentions;
    this->q_dimentions.first = model_dimentions;
    this->q_dimentions.second = dimentions.second;
    this->mean_users = new int[dimentions.first + 1];
    this->mean_items = new int[dimentions.second +1 ];
    this->users_num_edges = new int[dimentions.first + 1];
    this->items_num_edges = new int[dimentions.second + 1];
    this->user_bias = new float[dimentions.first + 1];
    this->item_bias = new float[dimentions.second + 1];
    p_matrix = new Matrix(p_dimentions);
    q_matrix = new Matrix(q_dimentions);
}

void Model::create_pq_matrix(){
    this->q_matrix->create_matrix();
    this->p_matrix->create_matrix();
}

void Model::fill_pq_matrix(){
    this->q_matrix->fill_ones();
    this->p_matrix->fill_ones();
}


Matrix Model::getq_matrix(){
    return *q_matrix;
}

Matrix Model::getp_matrix(){
    return *p_matrix;
}

void Model::print_csv_line(int user, int item, float prediction){
    cout << "u" << user << ":" << item << "," << prediction << endl;
}
void Model::get_prediction(string filename){
    ifstream file;
    file.open(filename);
    string line;
    float prediction;
    cout << "UserId:ItemId" << "," << "Prediction" << endl;
    while(getline(file,line)){
            string work_line = line;
            string delimiter = ":";
            int user = atoi(work_line.substr(1, work_line.find(delimiter)-1).c_str());

            work_line = line;
            delimiter = ":";
            string delimiter2 = ",";
            int item = atoi(work_line.substr( work_line.find(delimiter)+2, work_line.find(delimiter2)).c_str());

            if(user == 0 and item == 0) continue;

            prediction =  get_value_product(user,item);
            if(prediction > 10){
                prediction = 10;
            }
            if(items_num_edges[item] == 0 && users_num_edges[user] == 0){
                prediction = this->mean;
            }
            if(items_num_edges[item] != 0 && users_num_edges[user] == 0){
                prediction = (float)mean_items[item]/(float)items_num_edges[item];
            }
            if(items_num_edges[item] == 0 && users_num_edges[user] != 0){
                prediction = (float)mean_users[user]/(float)users_num_edges[user];
            }
            float u_bias = 0.0;
            if(items_num_edges[item] != 0 && users_num_edges[user] != 0){
                u_bias = user_bias[user]/(float)users_num_edges[user];
                u_bias = u_bias/BIAS_DIVISOR;
            }
            float i_bias = 0.0;
            if(items_num_edges[item] != 0 && users_num_edges[user] != 0){
                i_bias = item_bias[item]/(float)items_num_edges[item];
                i_bias = i_bias/BIAS_DIVISOR;
            }
            cout << line << "," << prediction + u_bias + i_bias<<endl;
            
        }   

    file.close();
    return;
}

float Model::get_value_product(int user, int item){
    float value = 0;
    for(int j = 0; j < this->model_dimentions; j++){
        value += p_matrix->matrix[user][j] * q_matrix->matrix[j][item];
    }
    return value;
}

void Model::update_matrix(int user, int item, float error){
    for(int j = 0; j < this->model_dimentions; j++){
        this->p_matrix->matrix[user][j] = this->p_matrix->matrix[user][j]+ (this->q_matrix->matrix[j][item] * 2 * learning_rate * error);
        this->q_matrix->matrix[j][item] = this->q_matrix->matrix[j][item]+ (this->p_matrix->matrix[user][j] * 2 * learning_rate * error);
    }
}

void Model::get_mean(){
    int sum = 0;
    for(int i = 0; i < this->p_dimentions.first + 1; i++)
    {
        mean_users[i] = 0;
        users_num_edges[i] = 0;
        user_bias[i] = 0.0; 
    }

    for(int i = 0; i <  this->q_dimentions.second + 1; i++)
    {
        mean_items[i] = 0;
        items_num_edges[i] = 0;
        item_bias[i] = 0.0; 
    }

    for(unsigned i = 0; i < this->train.size(); i++){
        sum += this->train[i][2];
    }
    this->mean = (float)sum/(float)this->train.size();
        
    for(unsigned i = 0; i < this->train.size(); i++){
        int user = this->train[i][0];
        int item = this->train[i][1];
        int rate = this->train[i][2];
        mean_items[item] += rate;
        items_num_edges[item]++;
        mean_users[user] += rate;
        users_num_edges[user]++;
        user_bias[user] += this->mean - rate;
        item_bias[item] += this->mean - rate;
    }
}

void Model::stochastic_gradient_descent(){
    int user;
    int item;
    float rate;
    float error;
    for(unsigned j = 0; j < EPOCHS; j++){
        for(unsigned i = 0; i < this->train.size(); i++){
            user = this->train[i][0];
            item = this->train[i][1];
            rate = this->train[i][2];
            error = (float)rate - get_value_product(user,item);
            update_matrix(user, item, error);
        }
    }
}