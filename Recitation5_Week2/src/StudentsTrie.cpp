/* @Author
Student Name: Salih Karabulut
Student ID : 150180044
Date: 28/12/2021 */
#include <fstream>
#include <iostream>

#include "StudentsTrie.h"

using namespace std;

TrieNode::TrieNode (const char& digit){
   this->digit = digit;
   for(int i=0; i<MAX_CHILDREN; children[i++] = NULL); 
};
// Construct a StudentsTrie using the records in 'file_name' 
StudentsTrie::StudentsTrie ( const string& file_name  ) { 
    ifstream student_ids_file ( file_name );   // ifstream object for input file
    string current_student_id;

    root = new TrieNode('r');

    if( student_ids_file.is_open() ) {
        for(int i=1; student_ids_file >> current_student_id; i++ ) {
           insert_id(current_student_id); // YOU HAVE TO IMPLEMENT insert_id() METHOD
        }
        student_ids_file.close();
    }
    else {
        cout << "File: " << file_name << " could NOT be opened!!";
        exit(1);
    }

    student_ids_file.close();
};

// Insert a student ID into the StudentsTrie 
void StudentsTrie::insert_id ( const string& student_id ) {
   // IMPLEMENT THIS METHOD
   //cout << "I have to implement insert_id() method" << endl;
   TrieNode* traverse = this->root;       //traverse node
   int i = 0;                       
   while (i<9)                  //traverse till student_id[i] becomes null
   {
      if (!traverse->children[(student_id[i]-'0')])   //if the node does not exist
      {
         TrieNode* new_node = new TrieNode(student_id[i]);   //create new node
         traverse->children[(student_id[i]-'0')] = new_node;   //link to the trie
      }
      traverse = traverse->children[(student_id[i]-'0')];   //if the node exist go next node
      i++;                                               //increment i by 1
   }
}; 

// Print Student IDs in Trie in ascending order 
void StudentsTrie::print_trie(){
   // IMPLEMENT THIS METHOD
   ///cout << "I have to implement print_trie() method" << endl;
   string st_id = "\0";          //create a string to hold numbers
   print_num(this->root,st_id);  //call the print num function
   
};

void StudentsTrie::print_num( TrieNode* home, string s_id){

   if (home->digit=='r')   //if it is the root
   {
      s_id.push_back(' '); //push empty space 
   }else{
      s_id.push_back(home->digit);  //if it is a digit push into the string
   }
   bool flag = false;               //created a flag to understand when to print
   for (int i = 0; i < 10; i++)     //search children array
   {
      if (home->children[i])        //if its not null
      {
         flag = true;               //set flag true(it means we have still node to go)
         print_num(home->children[i], s_id); //call this function recursively
      }
   }   
   if(!flag){                       //if flag is false (if the children array all null then, it is time to print)
      cout<<s_id;                   //print the string
   }
};

// StudentsTrie Destructor
StudentsTrie::~StudentsTrie() {
   for (int i=0; i < MAX_CHILDREN; i++){
      if( root->children[i] ) delete root->children[i];
   };
};

