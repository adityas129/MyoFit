#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(){

    ifstream ip("orientationEuler-1509784830 - 5.csv");



    int count;
    ip >> count;
    cout << count ;
    cout << count;
    string roll;
    int number_of_lines = 0;


    if(!ip.is_open()) std::cout << "ERROR: File Open" << '\n';


    while (ip.good()){
      getline(ip, roll,',');
      cout << roll;
      number_of_lines ++;

    }




    int total_number = number_of_lines - 1;
    float arrayofrolls[total_number];


    ip.close();
  }
