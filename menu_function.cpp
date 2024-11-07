/*
Ian Leuty CS 163 8/10/2024 Program 4 ileuty@pdx.edu
*/

using namespace std;
#include "BST.h"


//repeat stuff function
bool again(){
    char again{'\0'};
    cout << endl << "Again? [y/n]\n>";
    cin >> again;
    cin.ignore(100, '\n');
    if(toupper(again) == 'Y')
        return true;
    return false;
}

//menu 
void testMenu(BST &rabbits){
    int choice{};
    cout << endl << "Shell for testing.\n" << endl;

    while(choice != 7){ //7 will quit, no switch case needed
        cout << endl << "Choose from one of the following options:\n\n"
             << "1. Add a new rabbit" << endl
             << "2. Display rabbits" << endl
             << "3. Retrieve rabbit with matching name and breed" << endl
             << "4. Remove a rabbit" << endl
             << "5. Current height of the BST" << endl
             << "6. Load rabbits from data file" << endl
             << "7. Quit" << endl
             << '>';
        cin >> choice;

        while(cin.fail() ||
              choice < 1 ||
              choice > 7){ //error check menu selection
            cin.clear();
            cin.ignore(100, '\n');
            cout << endl << "Please make a numeric selection between 1 and 7.\n>";
            cin >> choice;
        }
        cin.ignore(100, '\n');

        switch(choice){
            
            //add rabbits
            case 1:{
                do{
                    cout << endl;
                    rabbitIO freshBun;
                    freshBun.make();
                    if(!rabbits.add(freshBun))
                        cout << endl << "Operation Failed: Error adding rabbit." << endl;
                }while(again());
            }
            break;
            
            //display rabbits
            case 2:{
                int subChoice{0};
                while(subChoice!= 3){
                    cout << endl << "How would you like to display the rabbits?" << endl
                         << "1. Alphabetically by name and breed" << endl
                         << "2. Display all rabbits of a particular size category" << endl
                         << "3. Return to main menu" << endl
                         << '>';
                    cin >> subChoice;

                    while(cin.fail() ||
                          subChoice < 1 ||
                          subChoice > 3){ //error check menu selection
                        cin.clear();
                        cin.ignore(100, '\n');
                        cout << endl << "Please make a numeric selection between 1 and 3.\n>";
                        cin >> subChoice ;
                    }
                    cin.ignore(100, '\n');

                    switch(subChoice){
                        
                        //display in order name
                        case 1:{
                            int displayed{rabbits.orderedDisplay()};
                            if(displayed > 0) 
                                cout << endl << displayed << " rabbits were displayed." << endl;
                            else 
                                cout << endl << "Operation Failed: No rabbits in the table." << endl;
                        }
                        break;
                        
                        //display all with matching size
                        case 2:{
                            do{
                                char size[WORD];
                                rabbitIO io;
                                cout << endl << "Enter a rabbit size (i.e. Giant, Large, Fryer, etc..) to see"
                                     << " lagomorphs of equal magnitude in this competition." << endl;
                                io.read(size, WORD);
                                int displayed{rabbits.sizeOrderedDisplay(size)};
                                if(displayed > 0) 
                                    cout << endl << displayed << " rabbits of '"
                                         << size << "' size were displayed." << endl;
                                else 
                                    cout << endl << "Operation Failed: No rabbits in the table of '"
                                         << size << "' size." << endl;
                            }while(again());
                        }
                        break;

                    }
                }
            }
            break;

            //retrieve rabbit
            case 3:{
                do{
                    char name[WORD];
                    char breed[WORD];
                    rabbitIO io[10];
                    cout << endl << "Enter the name of a rabbit to retrive.\n>";
                    io[0].read(name, WORD);
                    cout << endl << "Enter the breed.\n>";
                    io[0].read(breed, WORD);
                    int retrieved{rabbits.retrieve(name, breed, io)};
                    if(retrieved > 0){
                        cout << endl << retrieved << " matching rabbit(s) found in the table and retrived locally:" << endl;
                        for(int i = 0; i < retrieved; ++i){
                            cout << endl;
                            io[i].display();
                        }
                    }
                    else
                        cout << endl << "Operation Failed: No " << breed 
                             << "s in the table by the name of " << name << endl;

                }while(again());
            }
            break;

            //remove rabbit
            case 4:{
                do{
                    char name[WORD];
                    char breed[WORD];
                    rabbitIO io;
                    cout << endl << "Enter the name of a rabbit to remove.\n>";
                    io.read(name, WORD);
                    cout << endl << "Enter the breed.\n>";
                    io.read(breed, WORD);
                    if(rabbits.remove(name, breed))
                        cout << endl << name << " the " 
                             << breed << " was found in the table and removed." << endl;
                    else 
                        cout << endl << "Operation Failed: No " << breed 
                             << "s in the table by the name of " << name << endl;
                }while(again());
            }
            break;

            //height & tree analysis
            case 5:{
                int height{rabbits.height()};
                //int nodes{rabbits.countNodes()};
                if(height > 0)
                    cout << endl << "The height of the table is: " 
                         << height;
                else 
                    cout << endl << "Operation Failed: No rabbits in the table." << endl;
            }
            break;
            
            //load a test file in through rabbitIO objects and the same add function
            case 6:{
                char filename[WORD];
                rabbitIO io;
                ifstream filein;
                int count{0};
                cout << endl << "Enter the name of the file.\n>";
                io.read(filename, WORD); 
                filein.open(filename);
                if(!filein) 
                    cout << endl << "Operation Failed: " << filename 
                         << " could not be opened." << endl;
                else{
                    filein.peek();
                    bool fileCheck{!filein.eof()};
                    if(!fileCheck) //error if file was opened but is empty
                        cout << endl << "Operation Failed: " << filename 
                             << " was opened but contained no items." << endl;
                    while(fileCheck){ //while !eof
                        rabbitIO freshBun; //create a new rabbit 
                        fileCheck = freshBun.load(filein); //read into it from the file
                        if(!rabbits.add(freshBun)) 
                            cout << endl << "Operation failed: Could not load from file " 
                                 << filename << '.' << endl;
                        ++count;
                    }
                    cout << endl << count << " rabbits were added to the table." << endl;
                }
            }
            break;
        }
    }
}
