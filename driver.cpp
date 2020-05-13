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
    double mean = std::accumulate(vec.begin(), vec.end(), 0)/(double) vec.size();

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

    //View loaded data
    print_vector(locations, "Locations");
    print_vector(january, "January");
    print_vector(july, "July");

    //Normalize the data points
    normalize_by_mean(january);
    normalize_by_mean(july);

    //Print out normalized vectors
    std::cout << "Jan:" << std::endl;
    for (auto i = january.begin(); i < january.end(); ++i)
        std::cout << ", " << *i;
    std::cout << std::endl;

    std::cout << "Jul:" << std::endl;
    for (auto i = july.begin(); i < july.end(); ++i)
        std::cout << ", " << *i;
    std::cout << std::endl;


    //Create the covariance matrix
    //ROW x COL
    Eigen::MatrixXd covariance(2, 64); //(2 by 64 matrix)
    //Eigen::MatrixXd covariance(64, 2); //(64 by 2 matrix)
    
    for(int i = 0; i < 64; i++){
        covariance(0, i) = january[i];
        covariance(1, i) = july[i];
    }

    //Calculate Covariance Manually
    std::vector<std::vector<double>> covarianceV({{0,0}, {0,0}});
    for (auto i = 0; i < january.size(); ++i){
        covarianceV[0][0] += january[i]*january[i];
        covarianceV[0][1] += january[i]*july[i];
        covarianceV[1][1] += july[i]*july[i];
        covarianceV[1][0] = covarianceV[0][1];
    }
    //Print results
    std::cout << "Vector calculation:\n" << covarianceV[0][0] << " " << covarianceV[0][1] << std::endl << covarianceV[1][0] << " " << covarianceV[1][1] << std::endl;


    //Print out created matrix
    //std::cout << "Loaded data:\n" << covariance << std::endl;

    //Accumulation Stage
    covariance *= covariance.transpose();

    //Print out covariance matrix
    std::cout << "Accumulation Result:\n" << covariance << std::endl;

    covariance /= (january.size()-1);

    //Print out normalized covariance matrix
    std::cout << "Normalized Covariance:\n" << covariance << std::endl;

    //Find the eigenvalues and eigen vector
    Eigen::EigenSolver<Eigen::MatrixXd> es(covariance);

    std::cout << "Eigen Values:\n" << es.eigenvalues() << std::endl;
    std::cout << "Eigen Vectors:\n" << es.eigenvectors() << std::endl;

}