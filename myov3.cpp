#include <iostream>
#include <fstream>

using namespace std;

int main(){

  ifstream ip("orientationEuler-1509784830 - 5.csv");

  if(!ip.is_open()) std::cout << "ERROR: File Open" << '\n';

  string timestamp;
  string roll;
  int i = 0;
  int size;
  char *array= new char[size];



  while(ip.good()){

    getline(ip,timestamp,',');
    getline(ip,roll,',');
    array[i]= atof(getline(ip,roll,','));
    i++;
  }



  ip.close();
}
