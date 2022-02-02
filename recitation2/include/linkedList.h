/* @Author 
Student Name: Salih Karabulut
Student ID : 150180044
Date: 26/10/2021*/

#ifndef _H
#define _H

#include <iostream>
#include <stdio.h>

using namespace std;


class Node{
    public:
        char letter;
        Node* next= NULL;
};


class LinkedList{

    Node* head= NULL;
    Node* tail= NULL;

    public:
       
        void reorderList();
        void removeDublicates();
        void reverseList();
        void printList();

        void add_node(char);
};

#endif