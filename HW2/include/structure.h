/* @Author
Student Name: Salih Karabulut
Student ID : 150180044
Date: 30/12/2021 */

#pragma once

using namespace std;

class City
{
    public:
        City* left_hw = NULL;                                       //left child (left highway)
        City* right_hw = NULL;                                      //right child (right highway)
        City* next = NULL;                                          //next (for city list)
        

        City* par = NULL;                                           //hold the parent city
        char way = '\0';                                            //hold the way that which highway it is coming from. 'L' if it is left, 'R' if it is right

        string city_name = "\0";                                    //city name  
        int left_dist = 0;                                          //distance of left highway
        int right_dist = 0;                                         //distance of right highway
        int d_f_h = 0;                                              //distance from home
};


class Friend
{
    public:
        City* home = NULL;                                          //root of tree
        City* list_head = NULL;                                     //head of list

        // ~Friend();
        void add_to_map(string, string, int);                       //adding new roads to map
        City* search_City(string);                                  //search for a city in the map                
        void prune(City*, int);                                     //prune function
        void print_pre_order(City*);                                //print preorder 

        void addToList(City*);                                      //to construct city list
};
