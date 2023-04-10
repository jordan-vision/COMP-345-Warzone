#include "CommandProcessing.h"
#include "GameEngine.h"
#include <iostream>
using std:: cout; 
using std:: endl;
using std:: cin; 
#include <string>
using namespace std;
#include <fstream> 
using std:: ifstream;

int main(){

GameEngine:: instance()->reset();

    string answer;
    cout<<"\nIf you want to enter commands to the console, type \"-console\". Otherwise, type \"-file <filename>\" to read commands from the file."<<endl;
    getline(cin, answer);

    // Letting the user use commands by console 
    if (answer.substr(0, answer.find(" ")) == "-console"){
        bool answer = true;
        cout<<"\nUser has chosen to use commands through the console."<<endl;

        // The object "console" accesses the getCommand function 
        CommandProcessor* console = new CommandProcessor();


        // This while loop lets the getCommand function loop till the game is over
        while(!GameEngine:: instance()->getIsGameOver()){

            // The getCommand function asks the user for the commands
            Command* command = console->getCommand();
            
            // Making sure command object is not null S
            if (command != NULL){
            // cout<<"\n COMMAND EFFECT: "<<command->getCommandEffect()<<endl;
            GameEngine::instance()->transition(command->getCommandEffect());
            }
        }


    // The user chooses for the commands to be read from the commands.txt file
    } else {
        
        // Here we are taking only the file name from the command string that the user inputs 
        // by extracting only what's inside the < > brackets
        string fileName = answer.substr(answer.find_first_of("<")+1, answer.find_last_of(">") - answer.find_first_of("<")-1);
        cout<<"\nUser has chosen to read commands from file \""<<fileName<<"\""<<endl;
        ifstream input;
        input.open(fileName);

        // The fileCommand object calls the getCommand function 
        FileCommandProcessorAdapter* fileCommand = new FileCommandProcessorAdapter(fileName);
        cout<<"Reading from file:\n"<<endl;

        // Reading from the commands.txt file 
        while (!fileCommand->isEntireFileRead()) {
            Command* commandFromFile = fileCommand->getCommand();
            GameEngine::instance()->transition(commandFromFile->getCommandEffect());
        }
        cout<<"\nEnd of file reached."<<endl;

    } 

    
}

