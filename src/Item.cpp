# include "Item.h"

Item::Item(){ }

Item::Item(string name, string tag, string target, int hp, int atk, int def, int money)
    : Object(name, tag){
    this->target = target;
    this->hp = hp;
    this->atk = atk;
    this->def = def;
    setMoney(money);
}

bool Item::triggerEvent(Object* objPlayer){
    Player* player = dynamic_cast<Player*>(objPlayer);
    player->addItem(this);
    return 0;
}

void Item::setHp(int hp){
    this->hp = hp;
}
void Item::setAtk(int atk){
    this->atk = atk;
}
void Item::setDef(int def){
    this->def = def;
}
void Item::setTarget(string target){
    this->target = target;
}

int Item::getHp(){
    return hp;
}
int Item::getAtk(){
    return atk;
}
int Item::getDef(){
    return def;
}
string Item::getTarget(){
    return target;
}