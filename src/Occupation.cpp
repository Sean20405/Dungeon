# include "Occupation.h"

Warrior::Warrior(){}
Warrior::Warrior(string name)
    : Player(name, 1500, 100, 50, "Warrior", 1, 3){}
void Warrior::skill(GameCharacter* monster){
    cout << "\nYou use Empowered Strike!\n";
    monster->takeDamage(getAtk() + 50);
    cout << monster->getName() << " take " << getAtk() + 50 - monster->getDef() << " points of demage.\n";
    cout << "And " << monster->getName() << " was dizzy. You can continue attack.\n";
}
void Warrior::ultimate(GameCharacter* monster){
    cout << "\nYou use Demonic Decapitation!\n";
    if(monster->getCurrentHp() <= monster->getMaxHp() * 0.3){
        monster->setCurrentHp(-1);
        cout << "You slay " << monster->getName() << ".\n";
    }
    else{
        monster->takeDamage(getAtk());
        cout << monster->getName() << " take " << getAtk() * 2 - monster->getDef() << " points of demage.\n";
    }
}

Magician::Magician(){}
Magician::Magician(string name)
    : Player(name, 1400, 100, 0, "Magician", 2, 4){}
void Magician::skill(GameCharacter* monster){
    cout << "\nYou use Last Embrace!\n";
    cout << "You heal 500.\n";
    heal(500);
}
void Magician::ultimate(GameCharacter* monster){
    cout << "\nYou use Death's Embrace\n";
    monster->takeDamage(getAtk()*15);
    cout << monster->getName() << " take " << getAtk() * 15 - monster->getDef() << " points of demage.\n";
}

Archer::Archer(){}
Archer::Archer(string name)
    : Player(name, 1300, 250, 25, "Archer", 2, 5){}
void Archer::skill(GameCharacter* monster){
    cout << "\nYou use Celestial Piercer!\n";
    monster->takeDamage(getAtk() + monster->getDef());
    cout << monster->getName() << " take " << getAtk() << " points of demage.\n";
}
void Archer::ultimate(GameCharacter* monster){
    cout << "\nYou use Divine Judgement!\n";
    srand(time(NULL));
    int times = rand() % 4 + 3;
    while(times--){
        monster->takeDamage(getAtk());
        cout << monster->getName() << " take " << getAtk() - monster->getDef() << " points of demage.\n";
    }
}