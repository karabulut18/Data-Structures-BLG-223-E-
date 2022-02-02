/* @Author 
Student Name: Salih Karabulut
Student ID : 150180044
Date: 12/10/2021*/


#include "../include/team.h"

using namespace std;

Team::Team(){};
string Team::getName() { return name; };
int Team::getCurrentSize() { return current_size; };
int Team::getId() { return id; };
int Team::getCapacity() { return capacity; };
Player *Team::getPlayer(int number)
{
    for (int i = 0; i < current_size; i++)
    {
        if (player_list[i].getNumber() == number)
            return &player_list[i];
    }
    return nullptr;
};
Player *Team::getPlayerList()
{
    return player_list;
};
void Team::setName(string new_name) { name = new_name; };
void Team::setId(int newId) { id = newId; };
void Team::listPlayers()
{
    cout << "Number"
         << " Name"
         << " Age"
         << " #Goals"
         << " #Assists"
         << " #Matches" << endl;
    ;
    for (int i = 0; i < current_size; i++)
    {
        cout << player_list[i].getNumber() << " - ";
        cout << player_list[i].getName() << " - ";
        cout << player_list[i].getAge() << " - ";
        cout << player_list[i].getGoalNumber() << " - ";
        cout << player_list[i].getAssistNumber() << " - ";
        cout << player_list[i].getMatchNumber() << endl;
    }
};
void Team::addPlayer(int number, string name, int age, int goals, int assists, int matches)
{
    // *********************Fill this method
    bool flag = this->checkNumber(number);
    if (this->capacity == 0 && !flag)                //if the capacity is 0, increased by 3
    {
        capacity = capacity+3 ;
        Player* P1 = new Player[capacity]; //create a new player list
        P1[current_size].setNumber(number);
        P1[current_size].setName(name);
        P1[current_size].setMatchNumber(matches);
        P1[current_size].setGoalNumber(goals);
        P1[current_size].setAssistNumber(assists);
        P1[current_size].setAge(age);
        
        current_size++;
        delete [] this->player_list; 
        this->player_list = P1;
        return;
    }
    else if(this->current_size==this->capacity-1 && !flag){  // if the team list is full then, capacity should doubled
        capacity = capacity+capacity;
        Player* P1 = new Player[capacity]; // the new player list created
        int i=0;         
        for (i; i < current_size; i++)      
        {
            P1[i].setNumber(this->player_list[i].getNumber());
            P1[i].setName(this->player_list[i].getName());
            P1[i].setMatchNumber(this->player_list[i].getMatchNumber());
            P1[i].setGoalNumber(this->player_list[i].getGoalNumber());
            P1[i].setAssistNumber(this->player_list[i].getAssistNumber());
            P1[i].setAge(this->player_list[i].getAge());
        }
        // P1[current_size].Player(number,name,age,goals,assists,matches);//new player added
        P1[i].setNumber(number);
        P1[i].setName(name);
        P1[i].setMatchNumber(matches);
        P1[i].setGoalNumber(goals);
        P1[i].setAssistNumber(assists);
        P1[i].setAge(age);
        
        current_size++;
        delete [] this->player_list;                 //old list deleted
        this->player_list = P1;                      // assigned to new list 
        return;
    }
    else if(!flag){                                            //if there is space, the new player added
        player_list[current_size].setNumber(number);
        player_list[current_size].setName(name);
        player_list[current_size].setMatchNumber(matches);
        player_list[current_size].setGoalNumber(goals);
        player_list[current_size].setAssistNumber(assists);
        player_list[current_size].setAge(age);
        current_size++;
    }
   return;
};

bool Team::checkNumber(int number)
{
     for (int i = 0; i < current_size; i++)
    {
        if (player_list[i].getNumber() == number)
            return true;
    }
    return false;
}