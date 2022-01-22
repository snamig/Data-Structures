/*
@Author
Student name: Namig Samadov
Student ID: 150190912'
Date: 12.10.2021
*/
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

    //In the code below, we can see the initialization of 
    //capacity and the process of populating the player list
    if (Team::capacity == 0){
        Team::capacity += 3;
        Team::player_list = new Player[capacity];
        Team::current_size = 0;
    }
    //In the code below, we checked whether the capacity is
    //full or not and if it is full, we have doubled its previous
    //size
    else if (Team::capacity - Team::current_size == 0){
        Team::capacity *= 2;
        Player* tempArr = new Player[capacity];

        for (int i = 0; i < current_size; i++){
            tempArr[i] = player_list[i];
        }
        delete[] player_list;

        //On the code above we created a temporary array that
        //holds player class and used for making changes on the
        //player list
        player_list = tempArr;
    }

    
    Player* newPlayer = new Player(name, number, age, goals, assists, matches);
    Team::player_list[current_size] = *newPlayer;
    Team::current_size++;
    
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