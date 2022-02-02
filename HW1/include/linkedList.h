/* @Author 
Student Name: Salih Karabulut
Student ID : 150180044
Date: 10/11/2021*/

#ifndef _H
#define _H

#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

class materialNode{
    public:
        char id;
        int weight ;
        materialNode* next;

};

class wagonNode{
    public:
        int wagonId = 1;                            //the wagon id is 1 for the head
        materialNode* material= NULL;
        wagonNode* next = NULL;
};

class Train{  

    wagonNode* head;
    
    public:
        void create();
        void addMaterial(char,int);
        void deleteFromWagon(char, int); 
        void printWagon();                          //Prints wagon info
        void addWagon();
        void RemoveWagon();

};

#endif