#include <iostream>
#include <fstream>

using namespace std;

int main(){

  ifstream ip("orientationEuler-1509784830 - 5.csv");

  if(!ip.is_open()) std::cout << "ERROR: File Open" << '\n';

  string timestamp;
  string roll;


  while(ip.good()){

    getline(ip,timestamp,',');
    getline(ip,roll,',');

    cout << "Timestamp: "<<timestamp<< " "<<timestamp << '\n';
    cout << "Pushups: "<<roll << '\n';
  }

  ip.close();
}
