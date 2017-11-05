#include <iostream>
#include <fstream>

using namespace std;

int main(){

  ifstream ip("data.csv");

  if(!ip.is_open()) std::cout << "ERROR: File Open" << '\n';

  string timestamp;
  string roll;


  while(ip.good()){

    getline(ip,timestamp,',');
    getline(ip,roll,',');

    cout << "Timestamp: "<<timestamp<< " "<<lastname << '\n';
    cout << "Pushups: "<<roll << '\n';
  }

  ip.close();
}
