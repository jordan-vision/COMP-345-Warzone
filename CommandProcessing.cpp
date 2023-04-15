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



// The string effect is the command name that is passed to this function as a parameter 
// This command name (string effect) is then set to be the effect of this command
void Command:: saveEffect(string effect){
    this->setCommandEffect(getFirstWord(effect));
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


// This saves the command object which is passed in the vector list of command objects 
// which the commandprocessor object possesses 

void CommandProcessor::saveCommand(Command* command) {
    //cout<<"Saving command \" "<<command->getCommandName()<<" \"
    commandList.push_back(command);
    cout<<"\nCommand list: \n";
    int lineNumber = 1;
    for (auto it: commandList){
        cout<<lineNumber<<": "<<*it;
        ++lineNumber;
    }
    cout<<"\n";
    Notify(this);
}


// This function allows the command processor object to read user input 
// This function then saves the command by first checking if it's valid or not 
// Then, it saves the effect 

Command* CommandProcessor:: readCommand(){
    string command;
    cout<<"\n*** Reading Command ***\nEnter your command: ";
    getline(cin, command);
    Command* newCommand = new Command(command);

    // Start tournament mode
    if (!GameEngine::instance()->hasGameStarted() && getFirstWord(command) == "tournament") {
        startTournamentMode(command);
        return NULL;
    }
    
    // If command is invalid, an error message will be saved as its effect
    if (!validate(command)) {
        cout<<"Command not valid\n";
        newCommand->saveEffect("error");
        cout<<newCommand->getCommandEffect();
        return NULL;
    }
    cout<<"Command is valid, command saved\n";
    newCommand->saveEffect(command);
    saveCommand(newCommand);
        
    return newCommand;
}


// This function calls the readCommand function
Command* CommandProcessor:: getCommand(){
    Command* newCommand = readCommand();
    return newCommand;
}


// This validates the command string passed which is the name of the command object 
bool CommandProcessor:: validate(string command){
    State *nextState = GameEngine::instance()->getGameLoop()->getCurrentState()->executeCommand(getFirstWord(command));
    return (nextState != NULL);
}

 void CommandProcessor::startTournamentMode(string command) {
     // Get all parameters as strings
    string maps = copyInBetweenAngleBrackets("-M ", command);
    string players = copyInBetweenAngleBrackets("-P ", command);
    string games = copyInBetweenAngleBrackets("-G ", command);
    string turns = copyInBetweenAngleBrackets("-D ", command);

    // If some parameters are absent, print error message
    if (maps == "" || players == "" || games == "" || turns == "") {
        cerr << "Please write the tournament settings in the following format:" << endl;
        cerr << "tournament -M <listofmapfiles> -P <listofplayerstrategies> -G <numberofgames> -D <maxnumberofturns>" << endl;
        return;
    }

    // Get maps as a 5-array of strings
    string* mapArray = splitByCommas(maps, 5);
    if (mapArray == NULL) {
        cerr << "Too many maps. Please enter 5 maps at most." << endl;
        return;
    }

    // Get player strategies as a 4-array of strings
    string* playerStringArray = splitByCommas(players, 4);
    if (playerStringArray == NULL || playerStringArray[1] == "") {
        cerr << "Inappropriate amount of players. Please enter 2 players at least and 4 at most." << endl;
        delete[] mapArray;
        return;
    }

    // Make player strategies a 4-array of Player objects, return an error if the string is not the name of a strategy
    Player** playerArray = new Player*[4];
    string playerNames[4] = { "Afaf", "Ally", "Parker", "Victoria" };
    for (int i = 0; i < 4; i++) {
        if (playerStringArray[i] == "") {
            break;
        } 
        else if (playerStringArray[i] == "Aggressive") { // Make aggressive player
            Player* player = new Player(playerNames[i]);
            player->setStrategy(new AggressivePlayerStrategy(player));
            playerArray[i] = player;
        }
        else if (playerStringArray[i] == "Benevolent") { // Make benevolent player
            Player* player = new Player(playerNames[i]);
            player->setStrategy(new BenevolentPlayerStrategy(player));
            playerArray[i] = player;
        }
        else if (playerStringArray[i] == "Neutral") { // Make netral player
            Player* player = new Player(playerNames[i]);
            player->setStrategy(new NeutralPlayerStrategy(player));
            playerArray[i] = player;
        }
        else if (playerStringArray[i] == "Cheater") { // Make cheater player
            Player* player = new Player(playerNames[i]);
            player->setStrategy(new CheaterPlayerStrategy(player));
            playerArray[i] = player;
        }
        else {
            cerr << "Error: please enter valid strategies in the -P parameter. The alid strategies are \"Aggressive\", \"Benevolent\", \"Neutral\" and \"Cheater\"";
            delete[] mapArray;
            delete[] playerStringArray;
            delete[] playerArray;
            return;
        }
    }


    // Tournament command has been validated, now make the tournament
    cout << "Command valid. Creating tournament";
    // Tournament::newTournament(mapArray, playerArray, games, turns);
    return;
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



// reads line from file 
// This method is called by another function to read the lines form the file

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


// The readCommand is used to read and then save both the effect and command
// The command is saved in the vector list 
Command* FileCommandProcessorAdapter:: readCommand(){
    Command* newCommand = commandList[lineNumber];
    string commandString = newCommand->getCommandName();
    cout<<"\nLine "<<lineNumber + 1<<" : "<< commandString;
    ++lineNumber;
   
    // Start tournament mode
    if (!GameEngine::instance()->hasGameStarted() && getFirstWord(commandString) == "tournament") {
        startTournamentMode(commandString);
        return NULL;
    }

    if (!validate(commandString)) {
        cout << "\nError. Command not valid.";
        newCommand->saveEffect("error");
        return NULL;
    }

    cout << ". Command is valid\n";
    newCommand->saveEffect(commandString);
    saveCommand(newCommand);
    return newCommand;
}

FileCommandProcessorAdapter:: ~FileCommandProcessorAdapter(){
    delete flr;
    flr = nullptr;
}

// In here we are separating the command string to just take the keyword
// the game engine checks if the current state allows for this command to be executed
string getFirstWord(string command) {
    string firstWord;
    if (command.find(" ")) {
        firstWord = command.substr(0, command.find(" "));
    }
    else {
        firstWord = command;
    }
    return firstWord;
}

string copyInBetweenAngleBrackets(string prefix, string command) {
    string result = "";
    int i = command.find(prefix + "<");

    if (i == string::npos) {
        return result;
    }

    i += prefix.length() + 1;
    char currentChar = command[i];

    while (currentChar != '>' && i < command.length()) {
        i++;
        result += currentChar;
        currentChar = command[i];
    } if (i >= command.length()) {
        return "";
    }
    return result;
}

string* splitByCommas(string input, int size) {
    int position = 0, i = 0;
    string tempInput = input;
    string* splitValues = new string[5];
    position = tempInput.find(", ");

    while (i < size) {
        if (position == string::npos) {
            splitValues[i] = tempInput;
            break;
        }
        splitValues[i] = tempInput.substr(0, position);
        tempInput.erase(0, position + 2);
        position = tempInput.find(", ");
        i++;
    }

    if (i >= size) {
        delete[] splitValues;
        splitValues = NULL;
    }
    return splitValues;
}