# include "Room.h"

Room::Room(){ }

Room::Room(bool isExit, int index, vector<Object*> objects){
    this->isExit = isExit;
    this->index = index;
    this->objects = objects;
}

bool Room::popObject(){
    objects.erase(objects.begin());
    return 0;
}

void Room::setUpRoom(Room* upRoom){
    this->upRoom = upRoom;
}
void Room::setDownRoom(Room* downRoom){
    this->downRoom = downRoom;
}
void Room::setLeftRoom(Room* leftRoom){
    this->leftRoom = leftRoom;
}
void Room::setRightRoom(Room* rightRoom){
    this->rightRoom = rightRoom;
}
void Room::setIsExit(bool isExit){
    this->isExit = isExit;
}
void Room::setIndex(int index){
    this->index = index;
}
void Room::setObjects(vector<Object*> objects){
    this->objects = objects;
}

Room* Room::getUpRoom(){
    return upRoom;
}
Room* Room::getDownRoom(){
    return downRoom;
}
Room* Room::getLeftRoom(){
    return leftRoom;
}
Room* Room::getRightRoom(){
    return rightRoom;
}
bool Room::getIsExit(){
    return isExit;
}
int Room::getIndex(){
    return index;
}
vector<Object*> Room::getObjects(){
    return objects;
}
