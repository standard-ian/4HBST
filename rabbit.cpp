/*
Ian Leuty CS 163 8/10/2024 Program 4 ileuty@pdx.edu

This file contains the implementation of the rabbit sublcass 
Data members are:
        char *name;
        char *breed;
        char *bunDesc;
        char *hdlrDesc;
        char *size;
        int pose;
        char *fur;
*/

#include "rabbit.h"
using namespace std;

//constructor
rabbit::rabbit(){
    name = nullptr;
    breed = nullptr;
    bunDesc = nullptr;
    hdlrDesc = nullptr;
    size = nullptr;
    fur = nullptr;
    pose = 0;
}


//copy
bool rabbit::copy(rabbitIO &toAdd){
    if(name || breed || bunDesc || hdlrDesc || size || fur) return false;
    dyCopy(toAdd.name, name);
    dyCopy(toAdd.breed, breed);
    dyCopy(toAdd.bunDesc, bunDesc);
    dyCopy(toAdd.hdlrDesc, hdlrDesc);
    dyCopy(toAdd.size, size);
    dyCopy(toAdd.fur, fur);
    pose = toAdd.pose;
    return true;
}

//copy between rabbit objects
void rabbit::move(rabbit &source){
    strcpy(name, source.name);
    strcpy(breed, source.breed);
    strcpy(bunDesc, source.bunDesc);
    strcpy(hdlrDesc, source.hdlrDesc);
    strcpy(size, source.size);
    pose = source.pose;
    strcpy(fur, source.fur);
}

//implicit destructor
rabbit::~rabbit(){
    delete [] name;
    delete [] breed;
    delete [] bunDesc;
    delete [] hdlrDesc;
    delete [] size;
    delete [] fur;
    pose = 0;
    name = nullptr;
    breed = nullptr;
    bunDesc = nullptr;
    hdlrDesc = nullptr;
    size = nullptr;
    fur = nullptr;
}

//explicit destructor, remove a rabbit
bool rabbit::remove(){
    delete [] name;
    delete [] breed;
    delete [] bunDesc;
    delete [] hdlrDesc;
    delete [] size;
    delete [] fur;
    pose = 0;
    name = nullptr;
    breed = nullptr;
    bunDesc = nullptr;
    hdlrDesc = nullptr;
    size = nullptr;
    fur = nullptr;
    return true;
}

//display a rabbit
bool rabbit::display(){
    if(!name || !breed) return false;
    cout << "\033[4m" << "Breed:" << "\033[0m" << ' ' << breed << endl
         << "\033[4m" << "Contestant:" << "\033[0m" << ' ' << name << endl 
         << "\033[4m" << "About the bunny:" << "\033[0m" << endl
         << bunDesc << endl
         << "\033[4m" << "About the handler:" << "\033[0m" << endl
         << hdlrDesc << endl
         << "\033[4m" << "Physical attributes of rabbit:" << "\033[0m" << endl
         << size << " with " << fur << " fur." << endl
         << "\033[4m" << "Pose Rating:" << "\033[0m" << ' ' << pose << endl;
    return true;
}


//return true if rabbit matches name given
int rabbit::compareSize(char size[]){
    return strcmp(size, this -> size);
}

//return strcmp results for incoming rabbit by breed
int rabbit::compareBreed(char breed[]){
    return strcmp(breed, this -> breed);
}

//return strcmp results for incoming rabbit by breed
int rabbit::compareName(char name[]){
    return strcmp(name, this -> name);
}

//copy static temp array into dynamic
void rabbit::dyCopy(char source[], char *&dest){
    dest = new char[strlen(source) + 1];
    strcpy(dest, source);
}

//copies a class object out to a rabbit IO struct
void rabbit::retrieveIO(rabbitIO &dest){
    strcpy(dest.name, name);
    strcpy(dest.breed, breed);
    strcpy(dest.bunDesc, bunDesc);
    strcpy(dest.hdlrDesc, hdlrDesc);
    strcpy(dest.size, size);
    dest.pose = pose;
    strcpy(dest.fur, fur);
}
