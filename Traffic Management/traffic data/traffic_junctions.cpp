#include <iostream>
#include <fstream>

using namespace std;
class traffic_junctions
{
 public:
    int ID;
    float x_coordinate,y_coordinate;
};
int main()
{
  traffic_junctions obj;
  ofstream fout;
  fout.open("traffic_junctions.dat", ios::app|ios::binary);
  while(1){
  cout << "junction_id: ";
  cin >> obj.ID;
  if(obj.ID == -1)
  {
    break;
  }
  cout << "location..\n\tx:";
  cin >> obj.x_coordinate;
  cout << "\ty:";
  cin >> obj.y_coordinate;
  cout<<"____________________________________________" <<endl;
  fout.write((char*)&obj,sizeof(obj));
  }
  fout.close();
  return 0;
}
