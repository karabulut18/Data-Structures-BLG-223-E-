#include <iostream>
#include <stdio.h>
#include <string.h>

#include "linkedList.h"

/* @Author 
Student Name: Salih Karabulut
Student ID : 150180044
Date: 10/11/2021*/

#include <iostream>
#include <stdio.h>
#include <string.h>

#include "../include/linkedList.h"

using namespace std;

void Train::create(){
    head = NULL;
}; 

void Train::addMaterial(char material, int weight){
        //FILL THIS FUNCTION ACCORDINGLY
    if(!head){                                                              //if there is no wagon 
        wagonNode* newhead = new wagonNode();
        this->head = newhead;
    }

    wagonNode* traverse = head;
    bool flag_not_added = true;
    bool go_next_wagon = false;

    while (traverse && flag_not_added)                                      //should check for appropriate place for material
    {   
        if(traverse->material==NULL){                                       // if there is no material, add one
            materialNode* newmater = new materialNode();
            newmater->id = material;
            newmater->weight = 0;
            newmater->next=NULL;
            traverse->material = newmater;

        }
        materialNode* traverMat = traverse->material;                       //traverse node for the material nodes
        materialNode* traverPreMat = traverse->material;                    //previous of the traverse node for the material nodes that is going to be added
        go_next_wagon = false;                                              // set this false again
        while (traverMat && !go_next_wagon)                                 // if it should go to next wagon 
        {
            if( material <= traverMat->id && flag_not_added){
                if(traverMat->id==material){                                // the materialnode exists
                    if(traverMat->weight<2000){                             // if there is a space
                        int empty_space = 2000 - traverMat->weight;     
                        if (empty_space>=weight) {                          // if there is still material to add
                            traverMat->weight += weight;
                            flag_not_added = false;                         //leavae the func
                        }
                        else{                                               //if not, leave the func
                            flag_not_added = false;
                            traverMat->weight = 2000;
                            this->addMaterial(material, (weight-empty_space));
                        }
                    }else{   
                        //flag_not_added = true;
                        go_next_wagon = true;                               //go next wagon if the material node is full
                    }
                }
                else{                                                       //the materialnode does not exist
                    materialNode* new_mater = new materialNode();
                    new_mater->id = material;
                    new_mater->weight = 0;
                    if (traverMat==traverPreMat){   
                        traverse->material = new_mater;
                        new_mater->next = traverMat;
                    }
                    else{
                        new_mater->next = traverMat;
                        traverPreMat->next=new_mater;
                    }
                    
                    if(weight>2000){                                        // if it excees the capacity                     
                        new_mater->weight = 2000;
                        this->addMaterial(material,(weight-2000));
                        flag_not_added = false;
                    }
                    else{                                                   // if it is not
                        new_mater->weight = weight;
                        flag_not_added = false;
                    }
                }    
            }
            else if(traverMat->next==NULL && flag_not_added){               //if the materialnode suppose to be added to back of to list
                    
                materialNode* new_mater = new materialNode();
                new_mater->id= material;
                new_mater->next = NULL;
                new_mater->weight = 0;
                traverMat->next = new_mater;

                if(weight>2000){                                            // if it excees the capacity
                    new_mater->weight = 2000;
                    this->addMaterial(material,(weight-2000));
                    flag_not_added = false;
                }
                else{                                                       // if it is not
                    new_mater->weight = weight;
                    flag_not_added = false;
                    break;
                }
            }
            traverPreMat = traverMat;
            traverMat = traverMat->next;
        }
        traverse = traverse->next;
    }

    if(flag_not_added){                                                     //and finally if there is no space in any wagon, then add wagon
        this->addWagon();

        this->addMaterial(material,weight);
        flag_not_added = false;
    }
    
}; 


void Train::deleteFromWagon(char material, int weight){
        //FILL THIS FUNCTION ACCORDINGLY
        wagonNode* del_tra = head;                                              //traverse pointer for delete func

        while (del_tra->next)                                                   //go to the last wagon
        {
            del_tra = del_tra->next; 
        }

        materialNode* del_tra_mat;
        materialNode* del_tra_mat_pre ;

        bool deleted = false;

        while (!deleted) // loop until deleted
        {
            del_tra_mat = del_tra->material;
            del_tra_mat_pre = del_tra->material;

            while (del_tra_mat && !deleted)
            {
                if (del_tra_mat == del_tra_mat_pre && del_tra_mat->id == material) // if its the first material
                {
                   int a = del_tra_mat->weight;                                 // record the weight
                   if(weight>=a){                                               // if the amount that neeeded to be unloaded is larger than tha amount that exists
                       del_tra->material= del_tra_mat->next;                    // since we are at the begining of the list, arrange the order accordingly
                       delete del_tra_mat;                                      //delete the material node
                       this->RemoveWagon();
                       if(weight>a){                                            // if the wait that wanted to unloaded is larger than the weight that wagon has
                           deleteFromWagon(material, (weight-a));               // send the remaining amount that needed to be unloaded
                       }
                       deleted = true;                                          // and change the deleted flag to true
                   }
                   else{
                       del_tra_mat->weight -= weight;                           // if the amount that needed to be unloaded is smaller than the amount that exists, delete 
                       deleted = true;                                          // change the flag
                   }
                }
                else if((del_tra_mat != del_tra_mat_pre) && del_tra_mat->id == material){        // if it after the first material node
                                
                   int a = del_tra_mat->weight;
                   if(weight >= del_tra_mat->weight){
                       del_tra_mat_pre->next = del_tra_mat->next;
                       delete del_tra_mat;
                       //this->RemoveWagon();
                       if(weight>a){
                           deleteFromWagon(material, (weight-a));               // send it back to delete remaining amount
                       }
                       deleted = true;
                   }
                   else{
                       del_tra_mat->weight =  (a - weight);
                       deleted = true;
                   }
                }else{
                    del_tra_mat_pre  = del_tra_mat;                             // increment the traverse material pointers: set pre to traverse
                    del_tra_mat = del_tra_mat->next;                            // set traverse to next
                    deleted = false;                                            //delted false
                }
            }
            wagonNode* temp1 = head;
            if(!deleted){                                                       //if it's deleted don't go loop
                while (! (temp1->next == del_tra) )                             // find the previous wagon 
                {
                    temp1 = temp1->next;
                }
                del_tra = temp1;                                                // set it as new delete traverse pointer
            }
        }     
};  


void Train::printWagon(){
    wagonNode* tempWagon = head;

    if(tempWagon == NULL){
            cout<<"Train is empty!!!"<<endl;
            return;
    }

    while(tempWagon != NULL){
        materialNode* tempMat = tempWagon->material;
        cout<<tempWagon->wagonId<<". Wagon:"<<endl; 
        while (tempMat != NULL){
            cout<<tempMat->id<<": "<<tempMat->weight<<"KG, "; 
            tempMat = tempMat->next;  
        }
        cout<<endl; 
        tempWagon = tempWagon->next;
    }
    cout<<endl;
}; 


void Train::addWagon(){ 

    wagonNode* new_wagon = new wagonNode();
    
    wagonNode* traverse = this->head;

    while (traverse->next)
    {
        traverse = traverse->next;
    }
    
    traverse->next = new_wagon;
    new_wagon->next = NULL;
    new_wagon->wagonId= traverse->wagonId+1;                        //if (this == head) than next wagon id is 2 and goes like that 
};

void Train::RemoveWagon(){
    
    if (!head->material){                                           //if the head materaial is null then, make head NULL to clear 
        head = NULL;
    }
    else{
        wagonNode* temp = head;                                     
        wagonNode* prev= head;
        while(temp->next){                                          //search for the last wagon
            prev = temp;                                            //set previous
            temp = temp->next;
        }
        if(!temp->material && !(temp == head)){                     //if the material node is empty then
            delete temp;                                            //delete that wagon
            prev->next = NULL;                                      //set previous next to NULL
        }    
    }
};

void Train::create(){
    head = NULL;
}; 

void Train::addMaterial(char material, int weight){
        //FILL THIS FUNCTION ACCORDINGLY
}; 


void Train::deleteFromWagon(char material, int weight){
        //FILL THIS FUNCTION ACCORDINGLY
};  


void Train::printWagon(){
    wagonNode* tempWagon = head;

    if(tempWagon == NULL){
            cout<<"Train is empty!!!"<<endl;
            return;
    }

    while(tempWagon != NULL){
        materialNode* tempMat = tempWagon->material;
        cout<<tempWagon->wagonId<<". Wagon:"<<endl; 
        while (tempMat != NULL){
            cout<<tempMat->id<<": "<<tempMat->weight<<"KG, "; 
            tempMat = tempMat->next;  
        }
        cout<<endl; 
        tempWagon = tempWagon->next;
    }
    cout<<endl;
}; 