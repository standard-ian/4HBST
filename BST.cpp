/*
Ian Leuty CS 163 8/10/2024 Program 4 ileuty@pdx.edu

This file contains the implementation of the BST member functions. 
The member functions must include:

    1. [] Constructor 
    2. [] Add new Animal 
    3. [] Diplay all in sorted order by name & breed
    4. [] Remove an animal by name and breed
    5. [] Retrieve and animal by name and breed
    6. [] Display all animals matching another field 
    7. [] Return the tree height
*/

#include "BST.h"

//constructor
BST::BST(){
    root = nullptr;
}

//destructor
BST::~BST(){
    removeAll(root);
}

//call the add function to traverse the table to the correct point and add
bool BST::add(rabbitIO &newRabbit){
    return add(newRabbit, root);
}

//call the ordered display function, return number displayed 
int BST::orderedDisplay(){
    if(!root) return 0;
    return orderedDisplay(root);
}

//if the table is empty return 0 otherwise return the state of removal w/ recursive function
bool BST::remove(char name[], char breed[]){
    if(!root) return false;
    return remove(name, breed, root);
}

//call the retrive function, return number retrieved
int BST::retrieve(char name[], char breed[], rabbitIO rabbit[]){
    if(!root) return 0;
    int matches{0};
    return retrieve(name, breed, rabbit, matches, root);
}

//call the function to display in order rabbits of matching size, return number displayed 
int BST::sizeOrderedDisplay(char size[]){
    if(!root) return 0;
    return sizeOrderedDisplay(size, root);
}

//call the recursive function to get the height and return it
int BST::height(){
    if(!root) return 0;
    return height(root);
}

///////////RECURSIVE & UTILITY////////////////

//post order recursive destuctor
void BST::removeAll(node *&root){
    if(!root) return;
    removeAll(root -> left);
    removeAll(root -> right);
    delete root;
    root = nullptr;
    return;
}

/*
pre order traversal to add
if the breeds are the same, continue to a leaf based on the value of the name
otherwise, continue to a leaf based on the value of the breed
or until the breed is the same
*/
bool BST::add(rabbitIO &newRabbit, node *&root){
    if(!root){
        root = new node;
        root -> left = root -> right = nullptr;
        if(!root -> animal.copy(newRabbit)) return false;
        return true;
    }
    if(root -> animal.compareBreed(newRabbit.breed)  == 0 && 
       root -> animal.compareName(newRabbit.name) < 0)
        return add(newRabbit, root -> left);
    if(root -> animal.compareBreed(newRabbit.breed) < 0)
        return add(newRabbit, root -> left);
    return add(newRabbit, root -> right);
}

//in order traversal to display
int BST::orderedDisplay(node *root){
    if(!root) return 0;
    int count = orderedDisplay(root -> left);
    std::cout << std::endl;
    root -> animal.display();
    ++count;
    count += orderedDisplay(root -> right);
    return count;
}

//traverse to find a match, then deal with re-connecting and or finding ios
bool BST::remove(char name[], char breed[], node *&root){
    if(!root) return 0; //no BST, return
    if(root -> animal.compareBreed(breed) == 0 && 
       root -> animal.compareName(name) == 0){
        if(root -> left == nullptr && root -> right == nullptr){ //if root is a leaf
            delete root; //delete it
            root = nullptr; //set to null
        }
        else if(!root -> left && root -> right){ //if left is null, but not right
            node *hold{root -> right}; //hold the node thats not null (right)
            delete root; //delete the match
            root = hold; //assign the match's pointer to the right (non null) node
        }
        else if(!root -> right && root -> left){ //opposite scenario
            node *hold{root -> left}; //hold the node that's not null (left)
            delete root; //delete
            root = hold; //reassign
        }
        else{
            removeIOS(root -> right, root);
        }
    return 1;
    }
    if(root -> animal.compareBreed(breed)  == 0 && 
       root -> animal.compareName(name) < 0)
        return remove(name, breed, root -> left);
    if(root -> animal.compareBreed(breed) < 0)
        return remove(name, breed, root -> left);
    return remove(name, breed, root -> right);
}


//pre order to find matching rabbits and retrieve them, return number of matches
int BST::retrieve(char name[], char breed[], rabbitIO rabbit[], int &matches, node *root){
    if(!root) return 0;
    if(root -> animal.compareBreed(breed) == 0 && 
       root -> animal.compareName(name) == 0){
        root -> animal.retrieveIO(rabbit[matches]);
        ++matches;
        return retrieve(name, breed, rabbit, matches, root -> left) + 
               retrieve(name, breed, rabbit, matches, root -> right) + 1;
    }
    if(root -> animal.compareBreed(breed)  == 0 && 
       root -> animal.compareName(name) < 0)
        return retrieve(name, breed, rabbit, matches, root -> left);
    if(root -> animal.compareBreed(breed) < 0)
        return retrieve(name, breed, rabbit, matches, root -> left);
    return retrieve(name, breed, rabbit, matches, root -> right);
}

//in order traversal to display, but only do so if value for size matches.
int BST::sizeOrderedDisplay(char size[], node *root){
    if(!root) return 0;
    int count = sizeOrderedDisplay(size, root -> left);
    if(root -> animal.compareSize(size) == 0){
        std::cout << std::endl;
        root -> animal.display();
        ++count;
    }
    count += sizeOrderedDisplay(size, root -> right);
    return count;
}

//post order to get height
int BST::height(node *root){
    if(!root) return 0;
    return std::max(height(root -> left), height(root -> right)) + 1;
}

/*
traverse left subtree to find the ios, carrying pointer to the node it's replacing.
when found, copy it's data to the node being replaces and delete it.
*/
void BST::removeIOS(node *&root, node *&dest){
    if(!root -> left){
        dest -> animal.move(root -> animal);
        node *hold = root -> right;
        delete root;
        root = hold;
        return;
    }
    removeIOS(root -> left, dest);
}
