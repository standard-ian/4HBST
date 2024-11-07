/*
Ian Leuty CS 163 8/10/2024 Program 4 ileuty@pdx.edu

This file contains the interface for the animal subclass
Assume the animals are rabbits 
An animal contestant need the following data:
    1. name
    2. breed 
    3. animal description
    4. handler description
    5. size category (fryer, roaster, stewer...)
    6. posing (1-10)
    5. fur color
*/

#include <iostream>
#include <cstring>
#include <cctype>
#include <cmath>
#include <vector>
#include <fstream>

#ifndef RABBIT
#define RABBIT

const int WORD {61};
const int PHRASE {501};
const int RETRIEVAL {20};

struct rabbitIO{
    void make();
    void display();
    void read(char chars[], const int SIZE);
    bool load(std::ifstream &filein);
    bool readFile(std::ifstream &filein, char chars[], const int SIZE, char delim);

    char name [WORD];
    char breed [WORD];
    char bunDesc [PHRASE];
    char hdlrDesc [PHRASE];
    char size [WORD];
    int pose;
    char fur [WORD];
};

class rabbit{
    public:
        rabbit();
        ~rabbit();
        bool copy(rabbitIO &toAdd);
        void move(rabbit &source);
        bool remove();
        bool display();
        int compareSize(char size[]);
        int compareBreed(char breed[]);
        int compareName(char name[]);
        void retrieveIO(rabbitIO &dest);

    private:
        void dyCopy(char chars[], char *&dest);
        char *name;
        char *breed;
        char *bunDesc;
        char *hdlrDesc;
        char *size;
        int pose;
        char *fur;
};
#endif
