
#include <iostream>
#include <fstream>

using namespace std;

int main(){

  ifstream ip("orientationEuler-1509785084 - 3.csv");


  if(!ip.is_open()) std::cout << "ERROR: File Open" << '\n';
  //ip.ignore ( std::numeric_limits<stream::ip>::max(), '\n' );


  string timestamp;
  string roll;
  string pitch;
  string yaw;
  int counter =0;
  double temp = 0;
  double prev_value=0;

  getline(ip,timestamp,',');
  getline(ip,roll,',');
  getline(ip,pitch,',');
  getline(ip,yaw,'\n');

  while(ip.good()){

        getline(ip,timestamp,',');
        getline(ip,roll,',');
        getline(ip,pitch,',');
        getline(ip,yaw,'\n');




        //std::cout << "timestamp: "<<timestamp<< '\n';
        //std::cout << "roll: "<<roll << '\n';
        //std::cout << "pitch: "<<pitch << '\n';
        //std::cout << "yaw: "<<yaw << '\n';
        cout << "prev_value start"<< prev_value<< endl;
        cout << "temp start"<< temp<<endl;
        cout << "counter start" << counter<< endl;

        temp = std::stod(roll);

        if (prev_value >= 1.0){
          if (temp < 1.0){
            counter = counter + 1;
          }

          }
          prev_value = temp;
          cout << "prev_value end"<< prev_value<< endl;
          cout << "temp end"<< temp<<endl;
          cout << "counter end" << counter<< endl;




}
cout << "Number of pushups completed is " << counter << endl;
ip.close();

}
