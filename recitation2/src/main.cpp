/* @Author 
Student Name: Salih Karabulut
Student ID : 150180044
Date: 26/10/2021*/

#include <iostream> 
#include <stdlib.h>
#include <fstream>

#include "../include/linkedList.h"

using namespace std;

int main(int argc, char* argv[]) {
	system("clear");// make this line as comment if you are compiling on Linux or Mac
	//system("cls"); // make this line as comment if you are compiling on Windows
    
    LinkedList newLinkedList;

    ifstream thefile (argv[1]);      

    if(!thefile.is_open()){
        cout<<"file couldn't open"<<endl;
    }
    
    string new_letter;                      //adding new letter
    while ( getline(thefile, new_letter) )
    {
        newLinkedList.add_node(new_letter[0]);
    }
    thefile.close();
    

    cout<<"Readed letters in linked list: ";
    newLinkedList.printList();

    newLinkedList.reorderList();
    cout<<"After reordering: ";
    newLinkedList.printList();

    newLinkedList.removeDublicates();
    cout<<"After removing dublicates: ";
    newLinkedList.printList();
   
    newLinkedList.reverseList();
    cout<<"Reversed list: ";
    newLinkedList.printList();
   

    return EXIT_SUCCESS;
}