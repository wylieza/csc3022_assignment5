//Imports
//#include "processor.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

//Functions
double str_to_double(std::string str){
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


//Main
int main(int argc, char *argv[]){

    std::vector<std::string> locations;
    std::vector<double> january;
    std::vector<double> july;

    load_file(locations, january, july);
    print_vector(locations, "Locations");
    print_vector(january, "January");
    print_vector(july, "July");


}