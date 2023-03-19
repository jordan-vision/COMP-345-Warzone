#include "CommandProcessing.h"
#include "GameEngine.h"
#include <iostream> 
using std:: endl; 
using std:: cout;
using std:: cin;
#include <fstream> 
#include <string>
using std:: ifstream;
//                                          COMMAND CLASS SECTION   


Command:: Command(){
    commandName = "";
    effect = "";
}

Command:: Command(string commandName){
    this->commandName = commandName; 
}

Command:: Command(string commandName, string effect){
    this->commandName = commandName;
    this->effect = effect;
}

Command:: Command(const Command& copy){
    this->commandName = copy.commandName;
    this->effect = copy.effect;
}

string Command:: getCommandName(){
    return commandName;
}

string Command:: getCommandEffect(){
    return effect;
}

void Command:: setCommandName(string name){
    this->commandName = name;
}

void Command:: setCommandEffect(string effect){
    this->effect = effect;
}

ostream& operator <<(ostream& output, Command& command){
   return output<<command.commandName<<endl;
}

Command& Command:: operator=(const Command& rhs){
    this->commandName = rhs.commandName; 
    this->effect = rhs.effect;
    return *this; 
}



void Command:: saveEffect(string effect){

    if (effect.substr(0,7) == "loadmap"){
        this->setCommandEffect("map loaded");

    } else if (effect.substr(0,9) == "addplayer") {
        this->setCommandEffect("players added");

    } else if (effect == "validatemap"){
        this->setCommandEffect("map validated");

    } else if (effect == "gamestart"){
        this->setCommandEffect("starting game");

    } else if (effect == "replay"){
        this->setCommandEffect("replaying game");

    } else if (effect == "quit"){
        this->setCommandEffect("exiting program");
    }
     Notify(this);
    }
 

string Command::stringToLog() {

    return "Command's Effect: ...";
}

Command:: ~Command(){}


//                                      COMMAND PROCESSOR CLASS SECTION 

CommandProcessor:: CommandProcessor(){
    commandList = vector <Command*> ();
}

CommandProcessor:: CommandProcessor(const CommandProcessor& copy){
    commandList = vector <Command*> ();
    for(auto it : copy.commandList){
        commandList.push_back(new Command (*it));
    }
}

CommandProcessor& CommandProcessor:: operator = (const CommandProcessor& rhs){
    commandList = vector <Command*> ();
    for(auto it : rhs.commandList){
        commandList.push_back(new Command (*it));
    }
    return *this;
}

ostream& operator <<(ostream& output, CommandProcessor& command){
    return output<<"Command Processor"<<endl;
}

void CommandProcessor::saveCommand(Command* command) {
    //cout<<"Saving command \" "<<command->getCommandName()<<" \"
    cout<<"Command saved"<<endl;
    commandList.push_back(command);
    cout<<"Currently in command list: \n\n";
    int lineNumber = 1;
    for (auto it: commandList){
        cout<<lineNumber<<": "<<*it;
        ++lineNumber;
    }
    Notify(this);
}

Command* CommandProcessor:: readCommand(){
    string command;
    cout<<"\n*** Reading Command ***\nEnter your command: ";
    getline(cin, command);
    
    cout<<"Validating command\n";
    if (!validate(command)) {
        cout<<"\nError. Command not valid.";
        return NULL;
    }

    cout<<"command is valid. Saving command\n";
    Command* newCommand = new Command(command);
    saveCommand(newCommand);
    return newCommand;
}

Command* CommandProcessor:: getCommand(){
    cout<<"\nGetting command "<<endl;
    Command* newCommand = readCommand();
    return newCommand;
}

bool CommandProcessor:: validate(string command){
    State *nextState = GameEngine::getGameLoop()->getCurrentState()->executeCommand(command);
    return (nextState != NULL);
}

string CommandProcessor::stringToLog() {

    return "Command: ...";
}

CommandProcessor:: ~CommandProcessor(){
    for(auto it: commandList){
        delete it; 
        it = nullptr; 
    }
}


//                      FILE LINE READER CLASS SECTION 

FileLineReader:: FileLineReader(){}

FileLineReader:: FileLineReader(const FileLineReader& copy){}

FileLineReader&  FileLineReader :: operator =(FileLineReader& rhs) {return *this;}

ostream& operator << (ostream& output, const FileLineReader& reader){
    return cout<<"This is a file line reader object"<<endl;
}


vector <Command*> FileLineReader:: readLineFromFile(string fileName){
    //static int count = 1; 
    string commandString;
    vector <Command*> commandsFromFile; 
    ifstream inputFile;
    inputFile.open(fileName);
    if(!inputFile){
        cout<<"\nError. Commands file does not exist."<<endl;
        return commandsFromFile;
    }
    while(getline(inputFile, commandString)){
        //cout<<"Reading command line "<<count<<" : "<<commandString<<"\n";
        Command* lineCommand = new Command(commandString);
        commandsFromFile.push_back(lineCommand);
       // ++count;
    }
    return commandsFromFile;
   
}

FileLineReader:: ~FileLineReader(){}



//                  FILE COMMAND PROCESSOR ADAPTER CLASS SECTION

FileCommandProcessorAdapter:: FileCommandProcessorAdapter(){
    flr = nullptr;
}

FileCommandProcessorAdapter& FileCommandProcessorAdapter:: operator =(FileCommandProcessorAdapter& rhs){
    this->flr = rhs.flr;
    return *this;
}

FileCommandProcessorAdapter:: FileCommandProcessorAdapter(const FileCommandProcessorAdapter& copy){
    this->flr = copy.flr;
}

ostream& operator <<(ostream& output, FileCommandProcessorAdapter& adapter){
    return output<<"\nThis is a file command processor adapter object"<<endl;
}

void FileCommandProcessorAdapter:: readCommand(string fileName){
    vector <Command*> readCommands = flr->readLineFromFile(fileName);

    // after validate method has been implemented, call it here on the command returned from above to check it 
    // if (validate(command))
    // then continue to save command function 
    int count = 1;
    for (auto it: readCommands){
        cout<<"\nReading command line "<<count<<" : "<<*it;
        saveCommand(it);
        ++count;
    }
}

FileCommandProcessorAdapter:: ~FileCommandProcessorAdapter(){
    delete flr;
    flr = nullptr;
}