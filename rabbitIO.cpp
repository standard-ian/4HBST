/*
Ian Leuty CS 163 8/10/2024 Program 4 ileuty@pdx.edu

This file contains the implementation of the rabbitIO struct 
The data members are:
    char name [WORD];
    char breed [WORD];
    char bunDesc [PHRASE];
    char hdlrDesc [PHRASE];
    char size [WORD];
    int pose;
    char fur [WORD];

*/

#include "rabbit.h"
using namespace std;

//make a rabbit with cin
void rabbitIO::make(){
    cout << "Enter the name of a rabbit.\n>";
    read(name, WORD);
    cout << "Enter the breed.\n>";
    read(breed, WORD);
    cout << "Enter a description of the rabbit.\n>";
    read(bunDesc, PHRASE);
    cout << "Enter a description of the handler.\n>";
    read(hdlrDesc, PHRASE);
    cout << "Enter the size classification of the rabbit. (i.e. fryer, roaster, etc)\n>";
    read(size, WORD);
    cout << "Rate the rabbits pose. (1-10)\n>";
    cin >> pose;
    cin.ignore(100, '\n');
    cout << "Enter the color of the rabbit's fur.\n>";
    read(fur, WORD);
}

//display a rabbit from the IO version of rabbit
void rabbitIO::display(){
    cout << "\033[4m" << "Breed:" << "\033[0m" << ' ' << breed << endl
         << "\033[4m" << "Contestant:" << "\033[0m" << ' ' << name << endl 
         << "\033[4m" << "About the bunny:" << "\033[0m" << endl
         << bunDesc << endl
         << "\033[4m" << "About the handler:" << "\033[0m" << endl
         << hdlrDesc << endl
         << "\033[4m" << "Physical attributes of rabbit:" << "\033[0m" << endl
         << size << " with " << fur << " fur." << endl
         << "\033[4m" << "Pose Rating:" << "\033[0m" << ' ' << pose << endl;
}

//statically read in chars
void rabbitIO::read(char chars[], const int SIZE){ 
    cin.get(chars, SIZE, '\n');
    while(cin.peek() != '\n'){
        cin.ignore(100, '\n');
        cout << endl << "Enter less than " << SIZE << " characters" << endl;
        cin.get(chars, SIZE, '\n');
    }
    cin.ignore(100, '\n');
}

//load a single rabbit line
bool rabbitIO::load(ifstream &filein){
    if(!readFile(filein, name, WORD, '|')) return false;
    if(!readFile(filein, breed, WORD, '|')) return false;
    if(!readFile(filein, bunDesc, PHRASE, '|')) return false;
    if(!readFile(filein, hdlrDesc, PHRASE, '|')) return false;
    if(!readFile(filein, size, WORD, '|')) return false;
    filein >> pose;
    filein.ignore(100, '|');
    if(!readFile(filein, fur, WORD, '\n')) return false;
    filein.peek();
    if(filein.eof()) return false; //return 0 if end of file
    return true; //else return success state
}

//load a single char token 
bool rabbitIO::readFile(ifstream &filein, char chars[], const int SIZE, char delim){
    filein.get(chars, SIZE, delim);
    if(filein.peek() != delim)
        return false;
    filein.ignore(100, delim);
    return true;
}
