# include "Monster.h"

Monster::Monster(){ }

Monster::Monster(string name, int hp, int atk, int def)
    : GameCharacter(name, "Monster", hp, atk, def){
    setMoney(20);
}

bool Monster::triggerEvent(Object* objPlayer){
    cout << "[System] You start a fight with " << getName() << '\n';
    Player* player = dynamic_cast<Player*>(objPlayer);
    int round = -1, skillCD = 0, ultCD = 0;
    while(true){
        round++;

        /* Print fight info. */
        cout << '\n';
        cout << player->getName() << ": " << player->getCurrentHp() << "/" << player->getMaxHp() << '\n';
        cout << this->getName() << ": " << this->getCurrentHp() << "/" << this->getMaxHp() << '\n';

        /* Monster attack */
        if(round % 2){
            player->takeDamage(this->getAtk());
            cout << "\nYou take " << this->getAtk() - player->getDef() << " points of demage.\n";
        }
        /* Player attack */
        else{
            cout << "\nWhat do you want to use\n";
            cout << "A. Normal attack\n";
            cout << "B. Skill (" << skillCD << "/" << player->getSkillCD() << ")\n";
            cout << "C. Ultimate (" << ultCD << "/" << player->getUltCD() << ")\n";
            if(skillCD > 0) skillCD--;
            if(ultCD > 0) ultCD--;
            string attackType;
            cout << "> ";
            cin >> attackType;
            if(attackType == "A" || attackType == "a"){
                this->takeDamage(player->getAtk());
                cout << '\n' << this->getName() << " take " << player->getAtk() - this->getDef() << " points of demage.\n";
            }
            else if(attackType == "B" || attackType == "b"){
                if(skillCD == 0){
                    player->skill(this);
                    if(player->getOccupation() == "Warrior") round--; // dizziness
                    skillCD = player->getSkillCD();
                }
                else{
                    cout << "Your skill is still in CD.\n";
                    round--;
                    skillCD++;
                    continue;
                }
            }
            else if(attackType == "C" || attackType == "c"){
                if(ultCD == 0){
                    player->ultimate(this);
                    ultCD = player->getUltCD();
                }
                else{
                    cout << "Your Ultimate is still in CD.\n";
                    round--;
                    ultCD++;
                    continue;
                }
            }
            else{
                cout << "[System] Invalid Action. Please choose A, B, or C.\n";
                round--;
                continue;
            }
        }
        if(player->checkIsDead()){
            return 0;
        }
        else if(this->checkIsDead()){
            cout << "\n[System] You killed " << this->getName() << "!\n";
            return 1;
        }
    }
}