# ifndef OCCUPATION_H_INCLUDED
# define OCCUPATION_H_INCLUDED

# include <iostream>
# include <string>
# include <vector>
# include <stdlib.h>
# include <time.h>
# include "Player.h"
# include "GameCharacter.h"

class Warrior: public Player{
public:
    Warrior();
    Warrior(string);

    /* increase atk & dizziness */
    void skill(GameCharacter*);
    /* execute while under 30% */
    void ultimate(GameCharacter*);
};
class Magician: public Player{
public:
    Magician();
    Magician(string);

    /* heal */
    void skill(GameCharacter*);
    /* power the atk */
    void ultimate(GameCharacter*);
};
class Archer: public Player{
public:
    Archer();
    Archer(string);

    /* penetrate the def */
    void skill(GameCharacter*);
    /* randomly rapid shooting */
    void ultimate(GameCharacter*);
};

# endif // OCCUPATION_H_INCLUDED