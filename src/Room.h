# ifndef ROOM_H_INCLUDED
# define ROOM_H_INCLUDED
 
# include <iostream>
# include <string>
# include <vector>
# include "Object.h"

using namespace std;

class Room
{
private:
    Room* upRoom;
    Room* downRoom;
    Room* leftRoom;
    Room* rightRoom;
    bool isExit;
    int index;
    vector<Object*> objects; /*contain 1 or multiple objects, including monster, npc, etc*/
public:
    Room();
    Room(bool, int, vector<Object*>);
    /* pop out the specific object, used when the interaction is done */
    bool popObject();

    /* Set & Get function*/
    void setUpRoom(Room*);
    void setDownRoom(Room*);
    void setLeftRoom(Room*);
    void setRightRoom(Room*);
    void setIsExit(bool);
    void setIndex(int);
    void setObjects(vector<Object*>);
    Room* getUpRoom();
    Room* getDownRoom();
    Room* getLeftRoom();
    Room* getRightRoom();
    bool getIsExit();
    int getIndex();
    vector<Object*> getObjects();
    
};

struct RoomRecord{
    string type;
    int up, down, left, right;
};

# endif // ROOM_H_INCLUDED