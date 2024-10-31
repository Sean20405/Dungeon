# include "Player.h"

Player::Player(){ }
Player::Player(string name, int hp, int atk, int def, string occupation, int skillCD, int ultCD)
    : GameCharacter(name, "Player", hp, atk, def){
    weapon = NULL;
    this->occupation = occupation;
    this->skillCD = skillCD;
    this->ultCD = ultCD;
    setMoney(100);
}

void Player::addItem(Item* item){
    /* Equip item */
    if(item->getTag() == "Weapon"){
        cout << "You equipped with " << item->getName() << ".\n";
        if(this->occupation == item->getTarget() || item->getTarget() == "Everyone"){
            if(weapon != NULL){
                if(weapon->getTarget() == this->occupation || weapon->getTarget() == "Everyone"){
                    increaseStates(-weapon->getHp(), -weapon->getAtk(), -weapon->getDef());
                }
                else{
                    increaseStates(-weapon->getHp()*0.4, -weapon->getAtk()*0.4, -weapon->getDef()*0.4);
                }
            }
            cout << "This weapon is specially for you.\n";
            increaseStates(item->getHp(), item->getAtk(), item->getDef());
            weapon = item;
        }
        else{
            if(weapon != NULL){
                if(weapon->getTarget() == this->occupation || weapon->getTarget() == "Everyone"){
                    increaseStates(-weapon->getHp(), -weapon->getAtk(), -weapon->getDef());
                }
                else{
                    increaseStates(-weapon->getHp()*0.4, -weapon->getAtk()*0.4, -weapon->getDef()*0.4);
                }
            }
            cout << "This weapon is not for you. You can just abtain some of its ability.\n";
            increaseStates(item->getHp()*0.4, item->getAtk()*0.4, item->getDef()*0.4);
            weapon = item;
        }
    }

    /* Add item into inventory */
    else if(item->getTag() == "Item"){
        inventory.push_back(item);
    }
}

void Player::useItem(Item* item){
    if(item->getName() == "Health Potion"){
        heal(item->getHp());
    }
}

bool Player::listInventory(string space){
    if(inventory.empty()){
        cout << "<EMPTY>\n";
        return 0;
    }
    for(int i=0; i<inventory.size(); i++){
        cout << i+1 << ". " << inventory[i]->getName() << space;
    }
    return 1;
}

void Player::increaseStates(int hp, int atk, int def){
    /* Decrease */
    if(hp < 0 || atk < 0 || def < 0){
        setCurrentHp(getCurrentHp() + hp);
        setMaxHp(getMaxHp() + hp);
        setAtk(getAtk() + atk);
        setDef(getDef() + def);
    }
    else{
        int weaponHp = (weapon == NULL) ? 0 : weapon->getHp();
        int weaponAtk = (weapon == NULL) ? 0 : weapon->getAtk();
        int weaponDef = (weapon == NULL) ? 0 : weapon->getDef();
        if(weapon != NULL && weapon->getTarget() != occupation){
            weaponHp *= 0.4;
            weaponAtk *= 0.4;
            weaponDef *= 0.4;
        }
        cout << "[HP] " << getCurrentHp() + weaponHp << "/" << getMaxHp() << " -> ";
        setCurrentHp(getCurrentHp() + hp);
        setMaxHp(getMaxHp() + hp);
        cout << getCurrentHp() << "/" << getMaxHp() << '\n';
        cout << "[ATK] " << getAtk() + weaponAtk << " -> ";
        setAtk(getAtk() + atk);
        cout << getAtk() << '\n';
        cout << "[DEF] " << getDef() + weaponDef << " -> ";
        setDef(getDef() + def);
        cout << getDef() << '\n';
    }
}

void Player::heal(int hp){
    if(getCurrentHp() + hp < getMaxHp()){
        cout << "[HP]: " << getCurrentHp() << "/" << getMaxHp() << " -> ";
        setCurrentHp(getCurrentHp() + hp);
        cout << getCurrentHp() << "/" << getMaxHp() << '\n';
    }
    else{
        cout << "[HP]: " << getCurrentHp() << "/" << getMaxHp() << " -> ";
        setCurrentHp(getMaxHp());
        cout << getCurrentHp() << "/" << getMaxHp() << '\n';
    }
}

void Player::changeRoom(Room* room){
    previousRoom = currentRoom;
    currentRoom = room;
    cout << "\n[Room " << currentRoom->getIndex() << "]" << '\n';
}

bool Player::triggerEvent(Object* obj){
    cout << "\n[" <<  getName() << "'s Status]\n";
    cout << "> HP: " << getCurrentHp() << "/" << getMaxHp() << '\n';
    cout << "> ATK: " << getAtk() << '\n';
    cout << "> DEF: " << getDef() << '\n';
    cout << "> MONEY: " << getMoney() << '\n';
    cout << "> WEAPON: ";
    if(weapon != NULL) cout << weapon->getName() << '\n';
    else cout << "*You don't have any weapon.*\n";
    return 0;
}

void Player::setCurrentRoom(Room* currentRoom){
    this->currentRoom = currentRoom;
}
void Player::setPreviousRoom(Room* previousRoom){
    this->previousRoom = previousRoom;
}
void Player::setInventory(vector<Item*> package){
    this->inventory = package;
}
void Player::setOccupation(string occupation){
    this->occupation = occupation;
}
void Player::setWeapon(Item* weapon){
    this->weapon = weapon;
}
void Player::setSkillCD(int skillCC){
    this->skillCD = skillCD;
}
void Player::setUltCD(int ultCD){
    this->ultCD = ultCD;
}
Room* Player::getCurrentRoom(){
    return currentRoom;
}
Room* Player::getPreviousRoom(){
    return previousRoom;
}
vector<Item*> Player::getInventory(){
    return inventory;
}
string Player::getOccupation(){
    return occupation;
}
Item* Player::getWeapon(){
    return weapon;
}
int Player::getSkillCD(){
    return skillCD;
}
int Player::getUltCD(){
    return ultCD;
}