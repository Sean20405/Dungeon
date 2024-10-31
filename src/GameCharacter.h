# ifndef GAMECHARACTER_H_INCLUDED
# define GAMECHARACTER_H_INCLUDED

# include <iostream>
# include <string>
# include "Object.h"

using namespace std;

class GameCharacter: public Object
{
private:
    string name;
    int maxHp;
    int currentHp;
    int atk;
    int def;
public:
    GameCharacter();
    GameCharacter(string, string, int, int, int);
    bool checkIsDead();
    void takeDamage(int);

    /* Set & Get function*/
    void setMaxHp(int);
    void setCurrentHp(int);
    void setAtk(int);
    void setDef(int);
    int getMaxHp();
    int getCurrentHp();
    int getAtk();
    int getDef();
};

# endif // GAMECHARACTER_H_INCLUDED
