# ifndef ITEM_H_INCLUDED
# define ITEM_H_INCLUDED

# include <iostream>
# include <string>
# include <vector>
# include "Object.h"
# include "Player.h"

using namespace std;

class Player;

class Item: public Object
{
private:
    string target;
    int hp;
    int atk;
    int def;
public:
    Item();
    Item(string, string, string, int, int, int, int);

    /* Virtual function in Item: pick up action & update player's status */
    bool triggerEvent(Object*);

    /* Set & Get function*/
    void setHp(int);
    void setAtk(int);
    void setDef(int);
    void setTarget(string);
    int getHp();
    int getAtk();
    int getDef();
    string getTarget();
};

# endif // ITEM_H_INCLUDED
