
#include <iostream>


#define pid "13"
#include "utilities.cpp"
using namespace std;

bool update()
{

    data_transfer::download("signal");
    ifstream r_object("signal");
    char test[5];
    r_object >> test;

    if(strcpy(test, pid)==0)
    {
        return true;
    }
    else
        return false;
}

void emergency_green()
{
    while(update())
    {
        cout<< "colour = green\n";
        system("sleep 1");
    }
}
int main()
{
   while(true)
   {
       for(int i=0; i<5; ++i)
       {
           cout << "colour = red" <<endl;
           if(update())
           {
               emergency_green();
           }
           system("sleep 1");
       }

       for(int i=0; i<3; ++i)
       {
           cout << "colour = yellow"<<endl;
           if(update())
           {
               emergency_green();
           }
           system("sleep 1");
       }

       for(int i=0; i<4; ++i)
       {
           cout <<" colour = green" <<endl;
           if(update())
           {
               emergency_green();
           }
           system("sleep 1");
       }

   }

}
