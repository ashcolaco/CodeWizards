#include <iostream>
#include "utilities.cpp"

using namespace std;

void update_info()
{
    data_transfer::download(init_veh);
    CONV_to_OBJECT._initialize();
}
int main()
{
    do
    {
        update_info();

        system("sleep 5");
    }while(!CONV_to_OBJECT.STATUS);

    float min_dist_old, min_dist_new;
    do
    {

    ping_raspberryid(nearest_jn,false);

    min_dist_old=min_dist();

    system("sleep 10");

    update_info();

     min_dist_new = min_dist();
    }while( min_dist_old > min_dist_new );

    ping_raspberryid(nearest_jn, true);

    return 0;
}
