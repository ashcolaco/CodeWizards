#define SERVER_PROTOCOL " ftp://ADMIN:aDmIn@"
#define SERVER_IP "192.168.225.124"
#define SERVER_port ":2121"
#define NULL "\0"
#define junctions "traffic_junctions.dat"
#define init_veh "veh_data"
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <fstream>
#include <math.h>

using namespace std;

namespace data_transfer
{
    void upload(const char* FILENAME)
    {
        char _EXEC[50] = "curl -T ";
        strcat(_EXEC, FILENAME);
        strcat(_EXEC, SERVER_PROTOCOL);
        strcat(_EXEC, SERVER_IP);
        strcat(_EXEC, SERVER_port);
        system(_EXEC);
    }

    void download(const char* FILENAME)
    {
        char _EXEC[50] = "curl -O ";
        strcat(_EXEC, SERVER_PROTOCOL);
        strcat(_EXEC, SERVER_IP);
        strcat(_EXEC, SERVER_port);
        strcat(_EXEC, "/");
        strcat(_EXEC, FILENAME);
        system(_EXEC);
    }
}


class
{
public:
    char vehicle_id[17];
    bool STATUS;
    float x_coordinate, y_coordinate;

    void _initialize()
    {
        char temp[30];
        ifstream r_object;
        r_object.open(init_veh, ios::in);
        r_object.getline(temp, 15);

        if(strcmp(temp, "-1") == 0)
        {
            vehicle_id[0] = '\0';
            STATUS = false;
            x_coordinate = y_coordinate = -1;
        }
        else
        {
            strcpy(vehicle_id, temp);

            r_object.getline(temp,15);
            x_coordinate = atof(temp);

            r_object.getline(temp,15);
            y_coordinate = atof(temp);

            STATUS= true;
        }
        r_object.close();
    }



}CONV_to_OBJECT;


class traffic_junctions
{
 public:
    int ID;
    float x_coordinate,y_coordinate;
};

float coordinate_distance(traffic_junctions jn)
{
    return (sqrt(pow(jn.x_coordinate - CONV_to_OBJECT.x_coordinate,2) + pow(jn.y_coordinate - CONV_to_OBJECT.y_coordinate,2)));
}

traffic_junctions nearest_jn;


float min_dist()
{
    traffic_junctions jn;
    ifstream r_object;
    r_object.open(junctions,ios::in|ios::binary);
    float min_dist=99999;
    float dist;
    while(r_object.read((char*)&jn, sizeof(jn)))
    {
        dist=coordinate_distance(jn);

        if(dist<min_dist)
        {
            min_dist = dist;
            nearest_jn = jn;
        }
    }
    r_object.close();
    return min_dist;
}

void ping_raspberryid(traffic_junctions jn, bool active)
{
    ofstream w_object("signals");
    if(active)
        w_object << jn.ID;
    else
        w_object << -1;
}
