# ifndef DUNGEON_H_INCLUDED
# define DUNGEON_H_INCLUDED

# include <iostream>
# include <string>
# include <vector>
# include <exception>
# include <fstream>
# include "Player.h"
# include "Occupation.h"
# include "Item.h"
# include "Monster.h"
# include "NPC.h"
# include "Room.h"
# include "nlohmann/json.hpp"

using namespace std;
using json = nlohmann::json;

class Dungeon{
private:
    Player* player;
    vector<Room*> rooms;
    int mapSize;
public:
    Dungeon();
    
    /* Create a new player, and give him/her basic status */
    void createPlayer();

    /* Create a map, which include several different rooms */
    void createMap();

    void printMap();
    
    /* Deal with player's moveing action */
    bool handleMovement();

    /* Deal with player's iteraction with objects in that room */
    bool handleEvent(Object*);

    /* Deal with all game initial setting, including create player, create map etc */
    void startGame();

    /* Deal with the player's action including showing the action list
       that player can do at that room and dealing with player's input */
    void chooseAction();

    /* Check whether the game should end or not,
       including player victory, or he/she dead */
    bool checkGameLogic();

    void saveRecord();
    void loadRecord();

    /* Deal with the whole game process */
    void runDungeon();
    
    int getMapSize();
};


# endif // DUNGEON_H_INCLUDED
