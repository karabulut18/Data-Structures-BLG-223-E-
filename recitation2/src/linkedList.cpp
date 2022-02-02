/* @Author 
Student Name: Salih Karabulut
Student ID : 150180044
Date: 26/10/2021*/

#include <iostream>
#include <stdio.h>

#include "../include/linkedList.h"

using namespace std;

void LinkedList::reorderList(){

    Node* start = head;
    bool sorted = false;
/* 
    int listSize = 0;
    while(start)
    {
        listSize++;
        start = start->next;
    }
*/
    bool notSorted = true;
    while (!sorted)
    {
        notSorted = false;
        start = head;
        Node* temp = start;
        while ((start->next))
        {
            if (start->letter > start->next->letter)
            {
                notSorted = true;
                if (start == head)
                {
                    temp = start->next;
                    start->next = temp->next;
                    temp->next = start;
                    head = temp;
                }
                else 
                {
                    temp = start->next;
                    start->next = temp->next;
                    Node* previous = head;
                    while(previous->next != start)
                    {
                        previous = previous->next;
                    }
                    temp->next = start;
                    previous->next =temp;
                }
                sorted = false;
            }
            else 
            {
                start = start->next;
            }
        }
        if (notSorted == false) {sorted = true;}
    }
};

void LinkedList::removeDublicates(){
    Node* trace = head;
    Node* temp;
    while (trace->next)
    {
        while(trace->letter == trace->next->letter){
            temp= trace->next->next;
            delete trace->next;
            trace->next=temp;
        }
        trace = trace->next;
    }
};

void LinkedList::reverseList(){
    Node* start = head;

    bool sorted = false;
    int listSize = 0;
    while(start)
    {
        listSize++;
        start = start->next;
    }

    bool notSorted = true;
    while (!sorted)
    {
        notSorted = false;
        start = head;
        Node* temp = start;
        while ((start->next))
        {
            if (start->letter < start->next->letter)
            {
                notSorted = true;
                if (start == head)
                {
                    temp = start->next;
                    start->next = temp->next;
                    temp->next = start;
                    head = temp;
                }
                else 
                {
                    temp = start->next;
                    start->next = temp->next;
                    Node* previous = head;
                    while(previous->next != start)
                    {
                        previous = previous->next;
                    }
                    temp->next = start;
                    previous->next =temp;
                }
                sorted = false;
            }
            else 
            {
                start = start->next;
            }
        }
        if (notSorted == false) {sorted = true;}
    }
};

void LinkedList::printList(){
    Node* temp = head;
    while(temp != NULL){
        cout<<temp->letter<<" ";
        temp = temp->next;
    }
    cout<<endl;
};

void LinkedList::add_node(char a){
    Node* new_node= new Node;
    new_node->letter = a;

    if(head==NULL){                                   
        head = new_node;
        tail = new_node;
    }
    else if(tail!=NULL){
        tail->next=new_node;
        tail = new_node;
    }
}
