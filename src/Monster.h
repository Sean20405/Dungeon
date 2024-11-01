# ifndef ENEMY_H_INCLUDED
# define ENEMY_H_INCLUDED

# include <iostream>
# include <string>
# include <vector>
# include "GameCharacter.h"
# include "Player.h"

using namespace std;

class Player;

class Monster: public GameCharacter
{
private:
public:
    Monster();
    Monster(string, int, int, int);

    /* Virtual function in Monster: deal with the combat system */
    bool triggerEvent(Object*);
};


# endif // ENEMY_H_INCLUDED
