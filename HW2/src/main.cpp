/* @Author
Student Name: Salih Karabulut
Student ID : 150180044
Date: 30/12/2021 */
//I changed the "run" line in calico file as
//run: g++ -Wall -Werror src/main.cpp src/structure.cpp -I include -o blg223e_hw2

#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <iomanip>
#include <string.h>

#include "../include/structure.h"

using namespace std;

string findMeetingPoint(Friend,Friend);                                             //find meeting city and return

int main(int argc, char* argv[]){
    
    system("clear");                                                                //clear command 

    Friend f1, f2; 

    string map1 = argv[1];
    string map2 = argv[2];
        
    ifstream fileone;
    fileone.open(map1,ifstream::in);
    if (!fileone.is_open()) {
        cerr<<"file couldnt be opened"<<endl;
        exit(1);
    }

    string temp;                                                                    //hold chararchter temp
    string source_city;                                                             //source city number
    string dest_city;                                                               //destination city number
    int dist;                                                                       //distance between cities                  
    int flag = 0;                                                                   //flag for deciding source, target city or distance
    
    while (fileone>>temp)                                                           //read from file
    {
        if (flag == 0)                                                              //and flag is zero then its source city number
        {
            source_city = temp;     
            flag = 1;                                                               //set flag 1
        }
        else if(flag == 1){                                                         //if flag 1 then, temp is target city number
            dest_city = temp;
            flag = 2;                                                               //set flag is 2
        }
        else                                                                        //if flag is 2 then, temp is the distance
        {
            dist = temp[0] - 48;                                                    //set distance
            if (temp[1]){ dist = (temp[1]- 48); dist = dist + 10*(temp[0] - 48);}   //if distance has two digit
            
            flag = 0;                                                               //set flag zero again, for next roads
            f1.add_to_map(source_city, dest_city, dist);                            //add to the map 
        }
    }
    fileone.close();                                                                //close the file

    ifstream filetwo;
    filetwo.open(map2,ifstream::in);
    if (!filetwo.is_open()) {
        cerr<<"file couldnt be opened"<<endl;
        exit(1);
    }

    while (filetwo>>temp)                                                           //read from file
    {
        if (flag == 0)                                                              //and flag is zero then its source city number
        {
            source_city = temp;     
            flag = 1;                                                               //set flag 1
        }
        else if(flag == 1){                                                         //if flag 1 then, temp is target city number
            dest_city = temp;
            flag = 2;                                                               //set flag is 2
        }
        else                                                                        //if flag is 2 then, temp is the distance
        {
            dist = temp[0] - 48;                                                    //set distance
            if (temp[1]){ dist = temp[1]-48; dist = dist + 10*(temp[0] - 48);}      //if distance has two digit 
            
            flag = 0;                                                               //set flag zero again, for next roads
            f2.add_to_map(source_city,dest_city,dist);                              //add to the map 
        }
    }
    filetwo.close();                                                                //close the file

    int i = 0;
    f1.prune(f1.home,i);
    f2.prune(f2.home,i);

    cout<<"FRIEND-1: ";                                                             //print the map for friend 1
    f1.print_pre_order(f1.home);
    cout<<endl;

    cout<<"FRIEND-2: ";                                                             //print the map for friend 2
    f2.print_pre_order(f2.home);
    cout<<endl;

    string meCity = findMeetingPoint(f1,f2);                                        //print meeting point
    cout<<"MEETING POINT: "<<meCity<<endl;

    cout<<"TOTAL DURATION COST: "<<(f1.search_City(meCity)->d_f_h + f2.search_City(meCity)->d_f_h)<<endl; //print total duration cost    
    return EXIT_SUCCESS;
}

string findMeetingPoint(Friend friend1, Friend friend2){
    string meetingCity = "\0";                                                      //meeting city
    int distance = 0;                                                               //total duration cost
    bool flag = false;                                                              //flag for the setting meeting city for the first time

    City* traverse = friend1.list_head;                                             //traverse the first city list
    City* temp = NULL;                                                              //find that city in the second map list

    while (traverse)                                                                //while traverse not null
    {
        temp = friend2.search_City(traverse->city_name);                            //search the same city in the map two
        if (temp)                                                                   //if there
        {
            if ((temp->d_f_h + traverse->d_f_h)<distance)                           //and total duration cost is smaller than already held 
            {
                meetingCity = temp->city_name;                                      //update meeting city
                distance = (temp->d_f_h + traverse->d_f_h);                         //and total duration cost
            }else if(!flag){                                                        //if total duration cost is bigger than already held but its first time
                meetingCity = temp->city_name;                                      //set the meeting city 
                distance = (temp->d_f_h + traverse->d_f_h);                         //and total duration cost
                flag = true;                                                        //set the flag
            }
        }                                                                           //if city is not on the second map list do nothing
        traverse = traverse->next;                                                  //move the traverse node
    }
    return meetingCity;                                                             //finally return meeting city
};       
