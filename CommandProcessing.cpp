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
        this->setCommandEffect("loadmap");

    } else if (effect.substr(0,9) == "addplayer") {
        this->setCommandEffect("addplayer");

    } else if (effect == "validatemap"){
        this->setCommandEffect("validatemap");

    } else if (effect == "gamestart"){
        this->setCommandEffect("gamestart");

    } else if (effect == "replay"){
        this->setCommandEffect("replay");

    } else if (effect == "quit"){
        this->setCommandEffect("quit");

    } else if (effect == "error") {
        this->setCommandEffect("error");
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
    cout<<"\nCurrently in command list: \n";
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
    string first = command.substr(0, command.find(" "));
    // string validateString = "validatemap";

    Command* newCommand = new Command(command);
    cout<<"\nValidating command...\n";

    if (!validate(first)) {
        cout<<"NOT A COMMAND\n";
        newCommand->saveEffect("error");
        cout<<newCommand->getCommandEffect();
        return NULL;
    }
    cout<<"Command is valid. Saving command\n";
    newCommand->saveEffect(command);
    saveCommand(newCommand);
        
    return newCommand;
}

Command* CommandProcessor:: getCommand(){
    cout<<"Getting command "<<endl;
    Command* newCommand = readCommand();
    return newCommand;
}

bool CommandProcessor:: validate(string command){
    string firstWord = command + " ";
    firstWord = firstWord.substr(0, command.find(" "));
    State *nextState = GameEngine::getGameLoop()->getCurrentState()->executeCommand(command);
    State *nextState = GameEngine::getGameLoop()->getCurrentState()->executeCommand(firstWord);
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

FileCommandProcessorAdapter:: FileCommandProcessorAdapter(){}

FileCommandProcessorAdapter::FileCommandProcessorAdapter(string theFileName) {
    flr = new FileLineReader();
    lineNumber = 0;
    fileName = theFileName;
    commandList = flr->readLineFromFile(theFileName);
}

FileCommandProcessorAdapter& FileCommandProcessorAdapter:: operator =(FileCommandProcessorAdapter& rhs){
    this->flr = rhs.flr;
    this->lineNumber = rhs.lineNumber;
    this->fileName = rhs.fileName;
    this->commandList = rhs.commandList;
    return *this;
}

FileCommandProcessorAdapter:: FileCommandProcessorAdapter(const FileCommandProcessorAdapter& copy){
    this->flr = copy.flr;
}

string FileCommandProcessorAdapter::getFileName() {
    return fileName;
}
FileLineReader *FileCommandProcessorAdapter::getflr() {
    return flr;
}
void FileCommandProcessorAdapter::setFileName(string theFileName) {
    fileName = theFileName;
}
void FileCommandProcessorAdapter::setFlr(FileLineReader* theflr) {
    flr = theflr;
}

Command* FileCommandProcessorAdapter::getCommandAt(int i) {
    return commandList[i];
}

bool FileCommandProcessorAdapter::isEntireFileRead() {
    return (lineNumber >= commandList.size());
}

ostream& operator <<(ostream& output, FileCommandProcessorAdapter& adapter){
    return output<<"\nThis is a file command processor adapter object"<<endl;
}

Command* FileCommandProcessorAdapter:: readCommand(){
    Command* newCommand = commandList[lineNumber];
    string commandString = newCommand->getCommandName();
    cout<<"\nReading command line "<<lineNumber + 1<<" : "<< commandString;
    ++lineNumber;

    cout << "Validating command\n";
    if (!validate(commandString)) {
        cout << "\nError. Command not valid.";
        return NULL;
    }

    cout << "command is valid. Saving command\n";
    saveCommand(newCommand);
    return newCommand;
}

FileCommandProcessorAdapter:: ~FileCommandProcessorAdapter(){
    delete flr;
    flr = nullptr;
}