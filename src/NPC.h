# ifndef NPC_H_INCLUDED
# define NPC_H_INCLUDED

# include <iostream>
# include <string>
# include <vector>
# include <algorithm>
# include "GameCharacter.h"
# include "Player.h"
# include "Item.h"

using namespace std;

class NPC: public GameCharacter
{
private:
    vector<Item> commodity;
public:
    NPC();
    NPC(string, vector<Item>);
    /*print all the Item in this NPC*/
    void listCommodity();

    /* Virtual function in NPC: deal with the transaction */
    bool triggerEvent(Object*);

    /* Set & Get function*/
    void setCommodity(vector<Item>);
    vector<Item> getCommodity();
};


# endif // NPC_H_INCLUDED
