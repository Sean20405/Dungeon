# include "GameCharacter.h"

GameCharacter::GameCharacter(){ }

GameCharacter::GameCharacter(string name, string tag, int hp, int atk, int def)
    : Object(name, tag){
    this->maxHp = hp;
    this->currentHp = hp;
    this->atk = atk;
    this->def = def;
}

bool GameCharacter::checkIsDead(){
    if(currentHp <= 0) return 1;
    else return 0;
}

void GameCharacter::takeDamage(int dmg){
    if(dmg < def) return;
    else currentHp -= dmg - def;
}

void GameCharacter::setMaxHp(int maxHp){
    this->maxHp = maxHp;
}
void GameCharacter::setCurrentHp(int currentHp){
    this->currentHp = currentHp;
}
void GameCharacter::setAtk(int atk){
    this->atk = atk;
}
void GameCharacter::setDef(int def){
    this->def = def;
}

int GameCharacter::getMaxHp(){
    return maxHp;
}
int GameCharacter::getCurrentHp(){
    return currentHp;
}
int GameCharacter::getAtk(){
    return atk;
}
int GameCharacter::getDef(){
    return def;
}