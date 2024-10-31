# include "NPC.h"

NPC::NPC(){}

NPC::NPC(string name, vector<Item> commodity)
    : GameCharacter(name, "NPC", 100000, 100000, 100000){
    this->commodity = commodity;
}

void NPC::listCommodity(){
    int i = 0;
    for(; i<commodity.size(); i++){
        cout << i+1 << ". " << commodity[i].getName() << " $" << commodity[i].getMoney() << "    ";
    }
    cout << i+1 << ". " << "I don't want anything.\n";
    return;
}

bool NPC::triggerEvent(Object* objPlayer){
    Player* player = dynamic_cast<Player*>(objPlayer);
    if(getName() == "Merchant"){
        cout << "\n[System] You meet a merchant.\n";
        cout << "[Merchant] What do you want to buy, " << player->getName() << "?\n";
        cout << "[Merchant] Notice: you can just buy one item.\n";
        listCommodity();
        string schoice;
        int ichoice;
        while(true){
            cout << "> ";
            cin >> schoice;
            if(all_of(schoice.begin(), schoice.end(), ::isdigit)){
                ichoice = stoi(schoice);
            }
            else{
                cout << "[System] Invalid action. Please choose from 1 to " << commodity.size()+1 << ".\n";
                continue;
            }
            ichoice--;
            if(ichoice >= 0 && ichoice < commodity.size()){
                int playerMoney = player->getMoney();
                int commodityMoney = commodity[ichoice].getMoney();
                if(playerMoney >= commodityMoney){
                    player->setMoney(playerMoney - commodityMoney);
                    commodity[ichoice].triggerEvent(objPlayer);
                    return 0;
                }
                else{
                    cout << "[Merchant] You don't have enough money.\n";
                    cout << "[Merchant] Do you want to continue? (Y/N): ";
                    string YN;
                    while(true){
                        cin >> YN;
                        if(YN == "Y" || YN == "y"){
                            listCommodity();
                            break;
                        }
                        else if(YN == "N" || YN == "n"){
                            return 0;
                        }
                        else cout << "[System] Invalid action. Please choose Y or N. (Y/N): ";
                    }
                }
            }
            else if(ichoice == commodity.size()) return 0;
            else cout << "[System] Invalid action. Please choose from 1 to " << commodity.size()+1 << ".\n";
        }
    }
    else if(this->getName() == "Mystery"){
        cout << "[System] You meet Mystery, the most mysterious thing in COEUS\n";
        cout << "[Mystery] S2hvb3Iga2h1ciwgTCBrZHloIGpsaXcgaXJ1IGJyeC4gV2JzaCAicGJ2d2h1YmpsaXciLiBCcnggemxvbyBqaHcgbHFmdWhnbGVvaCBkZWxvbHdiIDopCg==\n";
        return 0;
    }
}

void NPC::setCommodity(vector<Item> commodity){
    this->commodity = commodity;
}
vector<Item> NPC::getCommodity(){
    return commodity;
}