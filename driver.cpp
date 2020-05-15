//Imports
//#include "processor.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <numeric>
#include <algorithm>
#include "./libs/eigen-3.3.7/Eigen/Core"
#include "./libs/eigen-3.3.7/Eigen/EigenValues"

//Functions
double str_to_double(const std::string &str){
    std::stringstream ss(str);
    double d;
    ss >> d;
    return d;
}

void load_file(std::vector<std::string> &locations, std::vector<double> &january, std::vector<double> &july){
    std::ifstream infile("./2018-AvgRainfall_mm_.csv");

    std::string line;
    //std::stringstream ss;

    if(!infile.is_open()){
        std::cout << "[ERROR] Could not open file!\n";
        exit(0);
    }

    
    while(getline(infile, line)){
        if(line.find('#') != line.npos)
            continue;

        int next_del = 0;
        locations.push_back(line.substr(next_del, line.find(',')));
        next_del = line.find(',') + 1;
        january.push_back(str_to_double(line.substr(next_del, line.find(',', next_del))));
        next_del = line.find(',', next_del) + 1;
        july.push_back(str_to_double(line.substr(next_del, line.find(',', next_del))));
    }

    infile.close();
}

template<typename T>
void print_vector(const std::vector<T> &vec, const std::string &id_str){
    std::cout << id_str << ": "; 
    for (auto i = vec.begin(); i != vec.end();){
        std::cout << *i;
        if(++i != vec.end())
            std::cout << ", ";
    }
    std::cout << std::endl;
}

void normalize_by_mean(std::vector<double> &vec){
    double mean = std::accumulate(vec.begin(), vec.end(), (double) 0)/(double) vec.size();

    auto normalizer = [mean](double &d){d -= mean;};

    std::for_each(vec.begin(), vec.end(), normalizer);
}

//Main
int main(int argc, char *argv[]){

    std::vector<std::string> locations;
    std::vector<double> january;
    std::vector<double> july;

    //Load in the data
    load_file(locations, january, july);

    //Normalize the data points
    normalize_by_mean(january);
    normalize_by_mean(july);

    //Create the covariance matrix
    Eigen::MatrixXd covariance(2, 64); //(2 by 64 matrix)
    
    //Populate covariance matrix with all values jan & jul
    for(int i = 0; i < 64; i++){
        covariance(0, i) = january[i];
        covariance(1, i) = july[i];
    }

    //Accumulation Stage
    covariance *= covariance.transpose();

    //Divide by N-1 to get covariance
    covariance /= (january.size()-1);

    //Find the eigenvalues and eigen vector
    Eigen::EigenSolver<Eigen::MatrixXd> es(covariance);

    //Find the total variance
    double total_variance = es.eigenvalues().real()[0] + es.eigenvalues().real()[1];


    //Print Out for Questions:
    std::cout << "-------------------------------------------------------------------\n";
    std::cout << "Answers to questions 1 -> 5\n";
    std::cout << "-------------------------------------------------------------------\n";

    std::cout << "The eigenvalues for the principal components 1 and 2 are:\n\n";
    std::cout << "Eigen Value for PC 1: " << es.eigenvalues().real()[0] << std::endl;
    std::cout << "Eigen Value for PC 2: " << es.eigenvalues().real()[1] << std::endl;
    std::cout << "-------------------------------------------------------------------\n";

    std::cout << "The eigenvectors for the principal components 1 and 2 are:\n\n";
    std::cout << "Eigen Vector for PC 1 (january, july): " << es.eigenvectors().real()(0, 0) << ", " << es.eigenvectors().real()(1, 0) << std::endl;
    std::cout << "Eigen Vector for PC 2 (january, july): " << es.eigenvectors().real()(0, 1) << ", " << es.eigenvectors().real()(1, 1) << std::endl;
    std::cout << "-------------------------------------------------------------------\n";

    std::cout << "The covariance matrix is:\n\n";
    std::cout << covariance << std::endl;
    std::cout << "-------------------------------------------------------------------\n";

    std::cout << "The total variance is:\n\n";
    std::cout << total_variance << std::endl;
    std::cout << "-------------------------------------------------------------------\n";

    std::cout << "Proportion of total variance accounted for by principle component:\n\n";
    std::cout << "PC 1: " << (es.eigenvalues().real()[0]/total_variance)*100 << "%" << std::endl;
    std::cout << "PC 2: " << (es.eigenvalues().real()[1]/total_variance)*100 << "%" << std::endl;
    std::cout << "-------------------------------------------------------------------\n";



}