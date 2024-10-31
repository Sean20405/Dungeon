# include "Dungeon.h"

Dungeon::Dungeon(){ }

void Dungeon::createPlayer(){
    string name;
    cout << "\nType in your name: ";
    cin >> name;
    string occupation;
    cout << "\nChoose your occupation:\n";
    cout << "A. Shadow Warrior (with much HP and Def)\n";
    cout << "B. Dark Sorcerer (with powerful skill and ultimate)\n";
    cout << "C. Divine Archer (with high normal attack)\n";
    while(true){
        cout << "> ";
        cin >> occupation;
        if(occupation == "A" || occupation == "a"){
            player = new Warrior(name);
            break;
        }
        else if(occupation == "B" || occupation == "b"){
            player = new Magician(name);
            break;
        }
        else if(occupation == "C" || occupation == "c"){
            player = new Archer(name);
            break;
        }
        else cout << "Invalid action. Please choose from A to C.\n";
    }
    player->setCurrentRoom(rooms[0]);
    player->setPreviousRoom(NULL);
}

void Dungeon::createMap(){
    mapSize = 9;
    RoomRecord roomRecord[mapSize] = {
        [0] = {
                .type = "Empty",
                .up = 1, .down = -1, .left = -1, .right = 2},
        [1] = {
                .type = "Monster",
                .up = 7, .down = 0, .left = 3, .right = 4},
        [2] = {
                .type = "Monster",
                .up = -1, .down = -1, .left = 0, .right = 5},
        [3] = {
                .type = "Monster",
                .up = 6, .down = -1, .left = -1, .right = 1},
        [4] = {
                .type = "Merchant",
                .up = -1, .down = -1, .left = 1, .right = -1},
        [5] = {
                .type = "Monster",
                .up = -1, .down = -1, .left = 2, .right = -1},
        [6] = {
                .type = "Mystery",
                .up = -1, .down = 3, .left = -1, .right = -1},
        [7] = {
                .type = "Empty",
                .up = 8, .down = 1, .left = -1, .right = -1},
        [8] = {
                .type = "Boss",
                .up = -1, .down = 7, .left = -1, .right = -1},
    };

    /* Create Rooms */
    for(int i=0; i<mapSize; i++){
        vector<Object*> tmp;
        if(roomRecord[i].type == "Empty"){
            rooms.push_back(new Room(0, i, tmp));
        }
        if(roomRecord[i].type == "Monster"){
            tmp.push_back(new Monster("Monster", 600, 100, 25));
            /* Create item dropped while defeating the monster */
            if(i == 3) tmp.push_back(new Item("Sword", "Weapon", "Warrior", 0, 50, 0, 0));
            else if(i == 1) tmp.push_back(new Item("Wand", "Weapon", "Magician", 0, 75, 0, 0));
            else if(i == 5) tmp.push_back(new Item("Arrow", "Weapon", "Archer", 0, 75, 0, 0));
            rooms.push_back(new Room(0, i, tmp));
        }
        else if(roomRecord[i].type == "Merchant"){
            vector<Item> commodity;
            commodity.push_back(Item("Abyssal Sword", "Weapon", "Warrior", 0, 200, 0, 150));
            commodity.push_back(Item("Void Staff", "Weapon", "Magician", 0, 450, 0, 150));
            commodity.push_back(Item("Starfall Arrow", "Weapon", "Archer", 0, 375, 0, 150));
            commodity.push_back(Item("Spirit Visage", "Weapom", "Everyone", 1000, 0, 150, 150));
            commodity.push_back(Item("Health Potion", "Item", "Everyone", 500, 0, 0, 100));
            tmp.push_back(new NPC("Merchant", commodity));
            rooms.push_back(new Room(0, i, tmp));
        }
        else if(roomRecord[i].type == "Mystery"){
            vector<Item> commodity;
            commodity.push_back(Item("Voidreaper", "Weapon", "Everyone", 0, 1000000, 0, 0));
            tmp.push_back(new NPC("Mystery", commodity));
            rooms.push_back(new Room(0, i, tmp));
        }
        else if(roomRecord[i].type == "Boss"){
            vector<Object*> tmp;
            tmp.push_back(new Monster("boss", 2000, 500, 100));
            rooms.push_back(new Room(1, 8, tmp));
        }
    }

    /* Link Rooms */
    for(int i=0; i<mapSize; i++){
        if(roomRecord[i].up != -1) rooms[i]->setUpRoom(rooms[roomRecord[i].up]);
        else rooms[i]->setUpRoom(NULL);
        if(roomRecord[i].down != -1) rooms[i]->setDownRoom(rooms[roomRecord[i].down]);
        else rooms[i]->setDownRoom(NULL);
        if(roomRecord[i].left != -1) rooms[i]->setLeftRoom(rooms[roomRecord[i].left]);
        else rooms[i]->setLeftRoom(NULL);
        if(roomRecord[i].right != -1) rooms[i]->setRightRoom(rooms[roomRecord[i].right]);
        else rooms[i]->setRightRoom(NULL);
    }
}

void Dungeon::printMap(){
    int currentRoom = player->getCurrentRoom()->getIndex();
    cout << "            +-----+                           \n";
    cout << "            |  " << ((currentRoom == 8) ? "*" : "8") << "  |                           \n";
    cout << "            +-----+                           \n";
    cout << "               |                              \n";
    cout << "+-----+     +-----+                           \n";
    cout << "|  " << ((currentRoom == 6) ? "*" : "6") << "  |     |  " << ((currentRoom == 7) ? "*" : "7") << "  |\n";
    cout << "+-----+     +-----+                           \n";
    cout << "   |           |                              \n";
    cout << "+-----+     +-----+     +-----+               \n";
    cout << "|  " << ((currentRoom == 3) ? "*" : "3") << "  |-----|  " << ((currentRoom == 1) ? "*" : "1") << "  |-----|  " << ((currentRoom == 4) ? "*" : "4") << "  |\n";
    cout << "+-----+     +-----+     +-----+               \n";
    cout << "               |                              \n";
    cout << "            +-----+     +-----+     +-----+   \n";
    cout << "            |  " << ((currentRoom == 0) ? "*" : "0") << "  |-----|  " << ((currentRoom == 2) ? "*" : "2") << "  |-----|  " << ((currentRoom == 5) ? "*" : "5") << "  |\n";
    cout << "            +-----+     +-----+     +-----+   \n";
}

bool Dungeon::handleMovement(){
    cout << "\nWhere do you want to go?\nA. Go up\nB. Go down\nC. Go left\nD. Go right\nE. Back to menu\n";
    string direction;
    while(true){
        cout << "> "; 
        cin >> direction;
        Room* currentRoom = player->getCurrentRoom();
        if(direction == "A" || direction == "a"){
            Room* upRoom = currentRoom->getUpRoom();
            if(upRoom == NULL) cout << "[System] Oops. There is only endless abyss. Please Choose another direction.\n";
            else{
                player->changeRoom(upRoom);
                return 1;
            }
        }
        else if(direction == "B" || direction == "b"){
            Room* downRoom = currentRoom->getDownRoom();
            if(downRoom == NULL) cout << "[System] Oops. There is only endless abyss. Please Choose another direction.\n";
            else{
                player->changeRoom(downRoom);
                return 1;
            }
        }
        else if(direction == "C" || direction == "c"){
            Room* leftRoom = currentRoom->getLeftRoom();
            if(leftRoom == NULL) cout << "[System] Oops. There is only endless abyss. Please Choose another direction.\n";
            else {
                player->changeRoom(leftRoom);
                return 1;
            }
        }
        else if(direction == "D" || direction == "d"){
            Room* rightRoom = currentRoom->getRightRoom();
            if(rightRoom == NULL) cout << "[System] Oops. There are only endless abyss. Please Choose another direction.\n";
            else{
                player->changeRoom(rightRoom);
                return 1;
            }
        }
        else if(direction == "E" || direction == "e"){
            return 0;
        }
        else cout << "[System] Invalid operation. Please choose from A to E.\n";
    }
}

bool Dungeon::handleEvent(Object* obj){
    if(obj->getTag() == "Monster"){
        string choice;
        cout << "\nYou encounter " << obj->getName() << ". Do you want to start a fight? (Y/N): ";
        while(true){
            cin >> choice;
            if(choice == "Y" || choice == "y"){
                if(obj->triggerEvent(player)){
                    player->setMoney(player->getMoney() + obj->getMoney());
                    cout << "[System] You earn " << obj->getMoney() << " dallars from " << obj->getName() << ".\n";
                    player->getCurrentRoom()->popObject();
                }
                return 1;
            }
            else if(choice == "N" || choice == "n"){
                player->setCurrentRoom(player->getPreviousRoom());
                cout << "\n[Room " << player->getCurrentRoom()->getIndex() << "]\n";
                return 0;
            }
            else cout << "[System] Invalid action. Please choose Y or N. (Y/N): ";
        }
        
    }
    else if(obj->getTag() == "Weapon"){
        cout << "\nYou find a weapon, " << obj->getName() << ". Do you want to pick up? (Y/N): ";
        string choice;
        while(true){
            cin >> choice;
            if(choice == "Y" || choice == "y"){
                obj->triggerEvent(player);
                player->getCurrentRoom()->popObject();
                return 1;
            }
            else if(choice == "N" || choice == "n"){
                return 1;
            }
            else cout << "[System] Invalid action. Please choose Y or N. (Y/N): ";
        }
    }
    else if(obj->getTag() == "Player"){
        obj->triggerEvent(player);
        return 1;
    }
    else if(obj->getTag() == "NPC"){
        obj->triggerEvent(player);
        return 1;
    }
    return 1;
}

void Dungeon::startGame(){
    cout << " ______     ______     ______     __  __     ______    \n";
    cout << "/\\  ___\\   /\\  __ \\   /\\  ___\\   /\\ \\/\\ \\   /\\  ___\\   \n";
    cout << "\\ \\ \\____  \\ \\ \\/\\ \\  \\ \\  __\\   \\ \\ \\_\\ \\  \\ \\___  \\  \n";
    cout << " \\ \\_____\\  \\ \\_____\\  \\ \\_____\\  \\ \\_____\\  \\/\\_____\\ \n";
    cout << "  \\/_____/   \\/_____/   \\/_____/   \\/_____/   \\/_____/ \n";
    cout << "\n[System] Welcome to COEUS, a world of darkness and despair.\n";
    cout << "[System] There, the only law is strength and wisdom.\n";
    cout << "[System] Will you rise to the top, or be swallowed by the abyss? It's all up to you.\n";
    cout << "[System] Now let's start. Bless you.\n";
    createMap();
    createPlayer();
}

void Dungeon::chooseAction(){
    cout << "\nWhat do you want to do?\n";
    cout << "A. Move\n";
    cout << "B. Check Status\n";
    cout << "C. Open Backpack\n";
    cout << "D. Check Map\n";
    cout << "E. Save Record\n";
    string action;
    while(true){
        cout << "> ";
        cin >> action;
        /* Move */
        if(action == "A" || action == "a"){
            if(handleMovement()){
                int size = player->getCurrentRoom()->getObjects().size();
                for(int i=0; i<size; i++){
                    if(!handleEvent(player->getCurrentRoom()->getObjects()[0])) break;
                }
            }
            return;
        }
        /* Check player status */
        else if(action == "B" || action == "b"){
            handleEvent(player);
            return;
        }
        /* Open backpack */
        else if(action == "C" || action == "c"){
            cout << "\nYour backpack: ";
            if(!player->listInventory(" ")) return;
            cout << "\n\nDo you want to use item? What do you want to use?\n";
            player->listInventory("\n");
            cout << player->getInventory().size() + 1 << ". No. Back to the last menu.\n";
            string suse;
            int iuse;
            while(true){
                cout << "> ";
                cin >> suse;
                if(all_of(suse.begin(), suse.end(), ::isdigit)){
                    iuse = stoi(suse);
                }
                else{
                    cout << "[System] Invalid action. Please choose from 1 to " << player->getInventory().size() << ".\n";
                    continue;
                }
                iuse--;
                if(iuse >= 0 && iuse < player->getInventory().size()){
                    player->useItem(player->getInventory()[iuse]);
                    return;
                }
                else if(iuse == player->getInventory().size()){
                    return;
                }
                else cout << "[System] Invalid action. Please choose 1 to " << player->getInventory().size() << '\n';
            }
        }
        /* Print map */
        else if(action == "D" || action == "d"){
            printMap();
            return;
        }
        /* Save record */
        else if(action == "E" || action == "e"){
            saveRecord();
            return;
        }
        else if(action == "mysterygift"){
            cout << "\nCongratulations, you find the mystery of Mystery. Here are gift for you.\n";
            player->addItem(new Item("Voidreaper", "Weapon", "Everyone", 0, 1000000, 0, 0));
            return;
        }
        else cout << "[System] Invalid action. Please choose A to E.\n";
    }
}

bool Dungeon::checkGameLogic(){
    if(player->checkIsDead()){
        cout << "You're dead...\n";
        return 0;
    }
    else if(player->getCurrentRoom()->getIsExit()){
        cout << "\nCongratulations! You overcome all the obstacles and successfully see the brightness of sun!\n";
        return 0;
    }
    return 1;
}

void Dungeon::saveRecord(){
    /* Read */
    ifstream f("record.json");
    json record = json::parse(f);

    bool userExist = 0;
    for(int i=0; i<record.size(); i++){
        if(record[i]["name"] == player->getName()){
            /* save player */
            json& user = record[i];
            user["player"]["currenthp"] = player->getCurrentHp();
            user["player"]["currentroom"] = player->getCurrentRoom()->getIndex();
            user["player"]["money"] = player->getMoney();
            user["player"]["occupation"] = player->getOccupation();
            if(player->getWeapon() != NULL) user["player"]["weapon"] = player->getWeapon()->getName();
            
            int inventorySize = player->getInventory().size();
            json json_inventory = json::array();
            for(int j=0; j<inventorySize; j++){
                
                json_inventory.emplace_back(player->getInventory()[j]->getName());
            }
            user["player"]["inventory"] = json_inventory;

            /* save room */
            for(int j=0; j<mapSize; j++){
                json json_object = json::array();
                int objectSize = rooms[j]->getObjects().size();
                for(int k=0; k<objectSize; k++){
                    json_object.emplace_back(rooms[j]->getObjects()[k]->getName());
                }
                user["room"][j] = {"Object", json_object};
            }
            userExist = 1;
            break;
        }
    }

    if(!userExist){
        /* save player */
        int inventorySize = player->getInventory().size();
        json json_inventory = json::array();
        for(int j=0; j<inventorySize; j++){
            json_inventory.emplace_back(player->getInventory()[j]->getName());
        }
        json newPlayer = {
            {"currenthp", player->getCurrentHp()},
            {"money", player->getMoney()},
            {"currentroom", player->getCurrentRoom()->getIndex()},
            {"occupation", player->getOccupation()},
            {"inventory", json_inventory}
        };
        if(player->getWeapon() != NULL) newPlayer["weapon"] = player->getWeapon()->getName();
        
        /* save room */
        json newRooms = json::array();
        for(int j=0; j<mapSize; j++){
            json json_object = json::array();
            int objectSize = rooms[j]->getObjects().size();
            for(int k=0; k<objectSize; k++){
                json_object.emplace_back(rooms[j]->getObjects()[k]->getName());
            }
            json newRoom = {{"Object", json_object}};
            newRooms.emplace_back(newRoom);
        }

        json user = {
            {"name", player->getName()},
            {"player", newPlayer},
            {"room", newRooms},
        };
        record.emplace_back(user);
    }

    /* Write */
    ofstream o("record.json");
    o << setw(4) << record << endl;
    cout << "Your record has been saved.";
    exit(1);
}

void Dungeon::loadRecord(){
    /* Read */
    ifstream f("record.json");
    json record = json::parse(f);
    json user;

    /* check user */
    cout << "\nWhat's your name?\n";
    string name;
    while(true){
        cout << "> ";
        cin >> name;
        bool userExist = 0;
        for(int i=0; i<record.size(); i++){
            if(name == record[i]["name"]){
                user = record[i];
                userExist = 1;
                break;
            }
        }
        if(userExist) break;
        if(!userExist) cout << "Can't find your record. Please check whether your name is correct.\n";
    }

    /* load room */
    json recordRoom = user["room"];
    mapSize = 9;
    RoomRecord roomRecord[mapSize] = {
        [0] = {
                .up = 1, .down = -1, .left = -1, .right = 2},
        [1] = {
                .up = 7, .down = 0, .left = 3, .right = 4},
        [2] = {
                .up = -1, .down = -1, .left = 0, .right = 5},
        [3] = {
                .up = 6, .down = -1, .left = -1, .right = 1},
        [4] = {
                .up = -1, .down = -1, .left = 1, .right = -1},
        [5] = {
                .up = -1, .down = -1, .left = 2, .right = -1},
        [6] = {
                .up = -1, .down = 3, .left = -1, .right = -1},
        [7] = {
                .up = 8, .down = 1, .left = -1, .right = -1},
        [8] = {
                .up = -1, .down = 7, .left = -1, .right = -1},
    };

    /* Create Rooms */
    for(int i=0; i<mapSize; i++){
        vector<Object*> tmp;
        json object = recordRoom[i]["object"];
        if(object.empty()){
            rooms.push_back(new Room(0, i, tmp));
        }
        else{
            int objectSize = object.size();
            for(int j=0; j<objectSize; j++){
                if(object[j] == "Boss"){
                    tmp.push_back(new Monster("boss", 2000, 500, 100));
                    rooms.push_back(new Room(1, 8, tmp));
                    break;
                }
                if(object[j] == "Monster") tmp.push_back(new Monster("monster", 600, 100, 25));
                if(object[j] == "Sword") tmp.push_back(new Item("Sword", "Weapon", "Warrior", 0, 50, 0, 0));
                if(object[j] == "Wand") tmp.push_back(new Item("Wand", "Weapon", "Magician", 0, 75, 0, 0));
                if(object[j] == "Arror") tmp.push_back(new Item("Arrow", "Weapon", "Archer", 0, 75, 0, 0));
                if(object[j] == "Merchant"){
                    vector<Item> commodity;
                    commodity.push_back(Item("Abyssal Sword", "Weapon", "Warrior", 0, 200, 0, 150));
                    commodity.push_back(Item("Void Staff", "Weapon", "Magician", 0, 450, 0, 150));
                    commodity.push_back(Item("Starfall Arrow", "Weapon", "Archer", 0, 375, 0, 150));
                    commodity.push_back(Item("Spirit Visage", "Weapom", "Everyone", 1000, 0, 150, 150));
                    commodity.push_back(Item("Health Potion", "Item", "Everyone", 500, 0, 0, 100));
                    tmp.push_back(new NPC("Merchant", commodity));
                    break;
                }
                if(object[j] == "Mystery"){
                    vector<Item> commodity;
                    commodity.push_back(Item("Voidreaper", "Weapon", "Everyone", 0, 1000000, 0, 0));
                    tmp.push_back(new NPC("Mystery", commodity));
                }
                rooms.push_back(new Room(0, i, tmp));
            }
        }
    }

    /* Link Rooms */
    for(int i=0; i<mapSize; i++){
        if(roomRecord[i].up != -1) rooms[i]->setUpRoom(rooms[roomRecord[i].up]);
        else rooms[i]->setUpRoom(NULL);
        if(roomRecord[i].down != -1) rooms[i]->setDownRoom(rooms[roomRecord[i].down]);
        else rooms[i]->setDownRoom(NULL);
        if(roomRecord[i].left != -1) rooms[i]->setLeftRoom(rooms[roomRecord[i].left]);
        else rooms[i]->setLeftRoom(NULL);
        if(roomRecord[i].right != -1) rooms[i]->setRightRoom(rooms[roomRecord[i].right]);
        else rooms[i]->setRightRoom(NULL);
    }

    /* load player */
    json recordPlayer = user["player"];
    if(recordPlayer["occupation"] == "Warrior"){
        player = new Warrior(name);
    }
    else if(user["player"]["occupation"] == "Magician"){
        player = new Magician(name);
    }
    else if(user["player"]["occupation"] == "Archer"){
        player = new Archer(name);
    }
    else cout << "No corresponding occupation.\n";
    player->setCurrentHp(recordPlayer["currenthp"]);
    player->setCurrentRoom(rooms[recordPlayer["currentroom"]]);
    player->setPreviousRoom(NULL);
    player->setMoney(recordPlayer["money"]);
    if(recordPlayer.find("weapon") != recordPlayer.end()){
        Item* weapon;
        if(recordPlayer["weapon"] == "Sword"){
            weapon = new Item("Sword", "Weapon", "Warrior", 0, 50, 0, 0);
        }
        else if(recordPlayer["weapon"] == "Wand"){
            weapon = new Item("Wand", "Weapon", "Magician", 0, 75, 0, 0);
        }
        else if(recordPlayer["weapon"] == "Arrow"){
            weapon = new Item("Arrow", "Weapon", "Archer", 0, 75, 0, 0);
        }
        else if(recordPlayer["weapon"] == "Abyssal Sword"){
            weapon = new Item("Abyssal Sword", "Weapon", "Warrior", 0, 200, 0, 150);
        }
        else if(recordPlayer["weapon"] == "Void Staff"){
            weapon = new Item("Void Staff", "Weapon", "Magician", 0, 450, 0, 150);
        }
        else if(recordPlayer["weapon"] == "Starfall Arrow"){
            weapon = new Item("Starfall Arrow", "Weapon", "Archer", 0, 375, 0, 150);
        }
        else if(recordPlayer["weapon"] == "Spirit Visage"){
            weapon = new Item("Spirit Visage", "Weapom", "Everyone", 1000, 0, 150, 150);
        }
        else if(recordPlayer["weapon"] == "Voidreaper"){
            weapon = new Item("Voidreaper", "Weapon", "Everyone", 0, 1000000, 0, 0);
        }
        else cout << "No corresponding weapon\n";
        weapon->triggerEvent(player);
    }
    vector<Item*> inventory;
    for(int i=0; i<recordPlayer["inventory"].size(); i++){
        if(recordPlayer["inventory"][i] == "Health Potion"){
            inventory.push_back(new Item("Health Potion", "Item", "Everyone", 500, 0, 0, 100));
        }
    }
    player->setInventory(inventory);
}

void Dungeon::runDungeon(){
    cout << "What do you want to do?\n";
    cout << "1. Create a new game.\n";
    cout << "2. Load previous record.\n";
    string choice;
    while(true){
        cout << "> ";
        cin >> choice;
        if(choice == "1"){
            startGame();
            break;
        }
        else if(choice == "2"){
            loadRecord();
            break;
        }
        else cout << "Invalid action. Please choose 1 or 2.\n";
    }
    while(checkGameLogic()){
        chooseAction();
    }
    system("PAUSE");
}

int Dungeon::getMapSize(){
    return mapSize;
}