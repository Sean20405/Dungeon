# ifndef PLAYER_H_INCLUDED
# define PLAYER_H_INCLUDED
 
# include <iostream>
# include <string>
# include <vector>
# include "GameCharacter.h"
# include "Item.h"
# include "Room.h"

using namespace std;

class Item;

class Player: public GameCharacter
{
private:
    Room* currentRoom;
    Room* previousRoom;
    vector<Item*> inventory;
    Item* weapon;
    string occupation;
    int skillCD, ultCD;
public:
    Player();
    Player(string, int, int, int, string, int, int);
    void addItem(Item*);
    void useItem(Item*);
    bool listInventory(string);
    void increaseStates(int, int, int);
    void heal(int);
    void changeRoom(Room*);

    virtual void skill(GameCharacter*) = 0;
    virtual void ultimate(GameCharacter*) = 0;

    /* Virtual function in Player: Show the status of player. */
    bool triggerEvent(Object*);

    /* Set & Get function*/
    void setCurrentRoom(Room*);
    void setPreviousRoom(Room*);
    void setInventory(vector<Item*>);
    void setWeapon(Item*);
    void setOccupation(string);
    void setSkillCD(int);
    void setUltCD(int);
    Room* getCurrentRoom();
    Room* getPreviousRoom();
    vector<Item*> getInventory();
    string getOccupation();
    Item* getWeapon();
    int getSkillCD();
    int getUltCD();
};
# endif // PLAYER_H_INCLUDED