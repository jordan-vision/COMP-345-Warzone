#pragma once
#include <vector>
#include "LoggingObserver.h"
class FileLineReader;


//                      COMMAND CLASS SECTION 
class Command : public ILoggable, public Subject {
    public:
        void saveEffect(string effect);        
        virtual string stringToLog() override;

        string getCommandName();                  
        string getCommandEffect();                  
        void setCommandName(string name);           
        void setCommandEffect(string effect);       

        Command();         
        Command(string commandName);      
        Command(string commandName, string effect);    

        Command(const Command& copy);           

        ~Command();         

        friend ostream& operator <<(ostream& output, Command& command);       
        Command& operator =(const Command& rhs);             


    protected:
        string commandName; 
        string effect; 

};


//                  COMMAND PROCESSOR CLASS SECTION 
class CommandProcessor : public ILoggable, public Subject {
    public:
        void saveCommand(Command* command);     
        virtual string stringToLog() override;     

        Command* getCommand();              
        bool validate(string command);        

        void tournamentMode(string command);

        CommandProcessor();     

        CommandProcessor(const CommandProcessor& copy);     

        ~CommandProcessor();        

        friend ostream& operator <<(ostream& output, CommandProcessor& processor);     
        CommandProcessor& operator =(const CommandProcessor& rhs);      


    protected:
        virtual Command* readCommand();        
        vector <Command*> commandList;
};


//                      File LINE READER CLASS SECTION 
class FileLineReader {
    public: 
        vector <Command*> readLineFromFile(string file);     

        FileLineReader();          

        ~FileLineReader();          
        FileLineReader(const FileLineReader& copy);         

        friend ostream& operator << (ostream& output, FileLineReader& reader);          
        FileLineReader& operator = (FileLineReader& rhs);           
};



//                   FILE COMMAND PROCESSOR ADAPTER CLASS SECTION 
class FileCommandProcessorAdapter : public CommandProcessor {
    private:
        int lineNumber;
        string fileName;
        vector<Command*> commandList;

    public: 
        FileCommandProcessorAdapter();
        FileCommandProcessorAdapter(string theFileName);
        FileCommandProcessorAdapter(const FileCommandProcessorAdapter& copy);           

        string getFileName();         
        FileLineReader* getflr();
        void setFileName(string theFileName);
        void setFlr(FileLineReader* theflr); 

        Command* getCommandAt(int i);
        bool isEntireFileRead();

        ~FileCommandProcessorAdapter();        

        friend ostream& operator <<(ostream& output, FileCommandProcessorAdapter& object);        
        FileCommandProcessorAdapter& operator = (FileCommandProcessorAdapter& rhs);         

    protected: 
        Command* readCommand();
        FileLineReader* flr;      
};

//                  HELPER FUNCTIONS
string getFirstWord(string command);