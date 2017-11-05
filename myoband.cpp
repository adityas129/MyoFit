#include <iostream>
#include <fstream>

using namespace std;

int main(){


  ifstream ip("orientationEuler-1509784830 - 5.csv");

  try
 {
   throw 0;
 }
 catch (int e)
 {
   cout << "An exception occurred. Exception Nr. " << 0 << '\n';
 }

  if(!ip.is_open()) std::cout << "ERROR: File Open" << '\n';

  string timestamp;
  string roll;
  int size = 0;





    while(ip.good()){
    size++;

    getline(ip,timestamp,',');
    getline(ip,roll,',');


    //cout << "Timestamp: "<<timestamp<< " "<<timestamp << '\n';
  //  cout << "Pushups: "<<roll << '\n';

  }
  char ** timestamparray;
  char ** rollarray;
  for (int i = 0; i < size; i++){
    rollarray[i] = &roll[i];

    cout  <<  & rollarray[i];
  }


  ip.close();


}
