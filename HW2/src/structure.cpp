/* @Author
Student Name: Salih Karabulut
Student ID : 150180044
Date: 30/12/2021 */

#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <iomanip>
#include <string.h>

#include "../include/structure.h"

void Friend::add_to_map(string source, string target, int dist){
    
    City* new_source_City = new City;                                               //creating source city
    new_source_City->city_name.append(source);                                      //adding city number to city name

    City* new_target_City = new City;                                               //creating target city
    new_target_City->city_name.append(target);                                      //adding target city number to target city name
    
    if (this->home==NULL)                                                           //if the map is empty add first city and target city
    {
        this->home = new_source_City;
        new_source_City->left_dist = dist;
        new_source_City->left_hw = new_target_City;
        //this->home->next = new_target_City;                                       //fill the city list
        this->addToList(new_source_City);                                           //add to list
        this->addToList(new_target_City);           
    }
    else
    {
        City* temp;

        temp = this->search_City(new_source_City->city_name);
        if (temp == NULL)
        {
            cout<<"Map is wrong"<<endl;
            cout<<new_source_City->city_name<<endl;
        }
        else
        {
            City* temp_target = this->search_City(new_target_City->city_name);

            if (temp_target == NULL)                                                //if the target city is not on the map
            {
                if (temp->left_hw == NULL)
                {
                    temp->left_hw = new_target_City;                                //if the left highway is null add there first
                    temp->left_dist = dist;                                         //set distance
                    //temp->next = new_target_City;                                 //fill the city list
                }
                else
                {
                    temp->right_hw = new_target_City;                               //if left highway is not null, add to right highway
                    temp->right_dist = dist;                                        //set distance
                    //temp->next = new_target_City;                                 //fill the city list
                }
                this->addToList(new_target_City);                                   //add to list

            }else                                                                   //if the target city is already added
            {
                if (temp->left_hw == NULL)
                {
                    temp->left_hw = temp_target;                                    //if the left highway is null add there first
                    temp->left_dist = dist;                                         //set distance
                }
                else
                {
                    temp->right_hw = temp_target;                                   //if left highway is not null, add to right highway
                    temp->right_dist = dist;                                        //set distance
                }   
                delete new_target_City;                                             //and delete new created one
            }  
            delete new_source_City;                                                 //delete the source city
        }       
    }
}

City* Friend::search_City(string city_name){                                        //return the wanted city or return null
    
    City* traverse  = this->list_head;                                              //traverse the city list
    bool found = false;
    while ((traverse&& !(found)))
    {
        if(!traverse->city_name.compare(city_name)){                                //if the city found send the node
            found = true;   
        }else
        {
            traverse = traverse->next;                                              // else move traverse
        }
    }
    return traverse;                                                                //if the city found return city, if it couldnt be found return null
}

void Friend::prune(City* current, int disFromHome){
    
    int d_f_h_right = disFromHome;                                                  //temp right distance from gome variable

    bool flag = true;

    if (current->left_hw)                                                           //if current left is not null
    {
        disFromHome = current->left_dist + disFromHome;                             //add left distance to distance from home variable 
        if (current->left_hw->par == NULL)                                          //if left city parent pointer is null then, it mean thi is the first time we came here
        {
            current->left_hw->par = current;                                        //set parent node
            current->left_hw->way = 'L';                                            //set parent node's way
            current->left_hw->d_f_h = disFromHome;                                  //set dist from home 
        }
        else if (current->left_hw->d_f_h > disFromHome)                             //if it is not null then its the second time we came here and check which connection is closest
        {                                                                           //if the new connection is closest set the values
            if(current->left_hw->par == current){}                                    //if the parent is same with current, dont delete child(do nothing) **this line forgetten before submitting the hw
            else{
                if (current->left_hw->way == 'L')                                       //if its coming from left highway
                {
                    current->left_hw->par->left_hw = NULL;                              //set the previous parent left connection to null
                    current->left_hw->par = current;                                    //set new parent
                }else if (current->left_hw->way == 'R')                                 //if its coming from right highway
                {
                    current->left_hw->par->right_hw = NULL;                             //set the previous parent right connection to null
                    current->left_hw->par = current;                                    //set new parent
                    current->left_hw->way = 'L';                                        //change the way of parent
                }
            }
            current->left_hw->d_f_h = disFromHome;                                  //set the distance
        }
        else
        {
            current->left_hw = NULL;
            flag = false;
        }

        if (flag)
        {
            prune(current->left_hw, disFromHome);                                   //call the function recursively
        }
    }

    if (current->right_hw)                                                          //if current right is not null
    {
        d_f_h_right = current->right_dist + d_f_h_right;                            //add right distance to distance from home variable 
        if (current->right_hw->par == NULL)                                         //if right city parent pointer is null then, it mean thi is the first time we came here
        {
            current->right_hw->par = current;                                       //set parent node
            current->right_hw->way = 'R';                                           //set parent node's way
            current->right_hw->d_f_h = d_f_h_right;                                 //set dist from home 
        }
        else if (current->right_hw->d_f_h > d_f_h_right)                            //if it is not null then its the second time we came here and check which connection is closest
        {                                                                           //if the new connection is closest set the values
            if(current->right_hw->par == current){}                                   //if the parent is same with current, dont delete child(do nothing)
            else{
                if (current->right_hw->way == 'L')                                      //if its coming from left highway
                {
                    current->right_hw->par->left_hw = NULL;                             //set the previous parent left connection to null
                    current->right_hw->way = 'R';                                       //change the way of parent
                    current->right_hw->par = current;                                   //set new parent
                }else if (current->right_hw->way == 'R')                                //if its coming from right highway
                {
                    current->right_hw->par->right_hw = NULL;                            //set the previous parent right connection to null
                    current->right_hw->par = current;                                   //set new parent
                }
            }
            current->right_hw->d_f_h = d_f_h_right;                                 //set the distance
        }
        else
        {
            current->right_hw = NULL;
            return;
        }
        prune(current->right_hw, d_f_h_right);                                      //call the function recursively
    }   
}

void Friend::print_pre_order(City* node){

    if (!node)
    {
        return;
    }else
    {
        cout<<node->city_name<<" ";                                                      //print the name of the city
        this->print_pre_order(node->left_hw);                                       //go left child
        this->print_pre_order(node->right_hw);                                      //go right child
    }
}

void Friend::addToList(City* new_node){                                             //add to city list
    City* traverse = this->list_head;

    if (!this->list_head)                                                           //add begining of the list if the head is null
    {
        this->list_head = new_node;
    }else{
        while (traverse->next)                                                      //else add to end of list
        {
            traverse = traverse->next;
        }
        traverse->next = new_node;
    }   
}
