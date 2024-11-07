/*
Ian Leuty CS 163 8/10/2024 Program 4 ileuty@pdx.edu

This file contains the interface for the BST class. 
Assume all animal contestants will be of the same species
The member functions must include:

    1. [] Constructor 
    2. [] Add new Animal 
    3. [] Diplay all in sorted order by name 
    4. [] Dispay all in sorted order by breed
    4. [] Remove an animal by name and breed
    5. [] Retrieve and animal by name and breed
    6. [] Display all animals matching another field 
    7. [] Return the tree height
    8. [] Destructor 
*/

#include "rabbit.h"

//node struct
struct node{
    rabbit animal;
    node *right;
    node *left;
};


//BST class
class BST{
    public:
        BST();
        ~BST();

        bool add(rabbitIO &newRabbit);
        int orderedDisplay();
        bool remove(char name[], char breed[]);
        int retrieve(char name[], char breed[], rabbitIO rabbit[]);
        int sizeOrderedDisplay(char size[]);
        int height();

    private: 
        node *root;
        
        void removeAll(node *&root);
        bool add(rabbitIO &newRabbit, node *&root);
        int orderedDisplay(node *root);
        bool remove(char name[], char breed[], node *&root);
        int retrieve(char name[], char breed[], rabbitIO rabbit[], int &matches, node *root);
        int sizeOrderedDisplay(char size[], node *root);
        int height(node *root);
        void removeIOS(node *&root, node *&removed);
};
