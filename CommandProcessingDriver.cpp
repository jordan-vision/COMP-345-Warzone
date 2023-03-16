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
    cout<<"If you want to enter commands to the console, type \"-console\". Otherwise, type \"-file <filename>\" to read commands from the file."<<endl;
    getline(cin, answer);

    if (answer.substr(0, answer.find(" ")) == "-console"){
        cout<<"User has chosen to use commands through the console."<<endl;
    } else {
        string fileName = answer.substr(answer.find("<") + 1, answer.size() - (answer.find("<")+2));
        cout<<"User has chosen to read commands from file \""<<fileName<<"\""<<endl;
        ifstream input;
        input.open(fileName);
        FileCommandProcessorAdapter* fileCommand = new FileCommandProcessorAdapter();
        cout<<"Beginnning reading from file: "<<endl;
        fileCommand->readCommand(fileName);
    } 

    
}

