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

GameEngine:: reset();

    string answer;
    cout<<"\nIf you want to enter commands to the console, type \"-console\". Otherwise, type \"-file <filename>\" to read commands from the file."<<endl;
    getline(cin, answer);

    // Letting the user use commands by console 
    if (answer.substr(0, answer.find(" ")) == "-console"){
        cout<<"\nUser has chosen to use commands through the console."<<endl;
        CommandProcessor* console = new CommandProcessor();
        console->getCommand();
        console->getCommand();

    } else {
        string fileName = answer.substr(answer.find("<") + 1, answer.size() - (answer.find("<")+2));
        cout<<"\nUser has chosen to read commands from file \""<<fileName<<"\""<<endl;
        ifstream input;
        input.open(fileName);
        FileCommandProcessorAdapter* fileCommand = new FileCommandProcessorAdapter();
        cout<<"Beginnning to read from file:\n"<<endl;

        // Reading from the commands.txt file 
        fileCommand->readCommand(fileName);
        cout<<"\nEnd of file reached."<<endl;

    } 

    
}

