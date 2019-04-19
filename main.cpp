#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>

using namespace std;

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
            max_item = get<0>(vetor[i]);
            cout << max_item  << endl;
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

    vector<tuple<int, int, int, int>> ratings= process_inputs(ratings_filename);
    vector<tuple<int, int, int, int>> targets= process_inputs(targets_filename);

    pair<int,int> max_values = max_user_item(ratings);

    int** user_item_matrix = new int*[max_values.first + 1];
    for (int i = 0; i < max_values.first + 1; i++)
    {
        user_item_matrix[i] = new int[max_values.second];
        for (int j = 0; j < max_values.first; j++)
        {
            user_item_matrix[i][j] = 0;
        }
    }
    for(unsigned i = 0; i < ratings.size(); i++){
        // user_item_matrix[get<0>(ratings[i])][get<1>(ratings[i])] = get<2>(ratings[i]);
    }

    return 0;
}
// for(unsigned i = 0; i < ratings.size(); i++){
//     cout << get<0>(ratings[i]) << "-" << get<1>(ratings[i]) <<  "-"  << get<2>(ratings[i]) <<  "-"  << get<3>(ratings[i]) << endl;    
// }

// for(unsigned i = 0; i < targets.size(); i++){
//     cout << get<0>(targets[i]) << "-" << get<1>(targets[i]) << endl;    
// }