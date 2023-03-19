#include "CommandProcessing.h"
#include <iostream>
using std:: cout; 
using std:: endl;
using std:: cin; 
#include <string>
using namespace std;
#include <fstream> 
using std:: ifstream;

int main(){

    string answer;
    cout<<"\nIf you want to enter commands to the console, type \"-console\". Otherwise, type \"-file <filename>\" to read commands from the file."<<endl;
    getline(cin, answer);

    if (answer.substr(0, answer.find(" ")) == "-console"){
        cout<<"\nUser has chosen to use commands through the console."<<endl;
    } else {
        string fileName = answer.substr(answer.find("<") + 1, answer.size() - (answer.find("<")+2));
        cout<<"\nUser has chosen to read commands from file \""<<fileName<<"\""<<endl;
        ifstream input;
        input.open(fileName);
        FileCommandProcessorAdapter* fileCommand = new FileCommandProcessorAdapter();
        cout<<"Beginnning to read from file: "<<endl;

        // Reading the first line from the commands.txt file 
        fileCommand->readCommand(fileName);
        // Reading the second line from the commands.txt file 
        fileCommand->readCommand(fileName);
        // Reading the third line from the commands.txt file 
        fileCommand->readCommand(fileName);
        // Reading the fourth line from the commands.txt file
        fileCommand->readCommand(fileName);
        // Reading the fifth line from the commands.txt file 
        fileCommand->readCommand(fileName);
        // Reading the sixth line from the commands.txt file 
        fileCommand->readCommand(fileName);
        // Reading the seventh line from the commands.txt file 
        fileCommand->readCommand(fileName);
        // Reading the eighth line from the commands.txt file
        fileCommand->readCommand(fileName);
        // Reading the ninth line from the commands.txt file
        fileCommand->readCommand(fileName);
        // Reading the tenth line from the commands.txt file
        fileCommand->readCommand(fileName);

        cout<<"\nEnd of file reached."<<endl;

    } 

    
}

