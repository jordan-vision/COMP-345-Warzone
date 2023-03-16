#pragma once
#include <vector>
#include "LoggingObserver.h"
class FileLineReader;

class Command : public ILoggable, Subject {
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

class CommandProcessor : public ILoggable, Subject {
    public:
        void saveCommand(Command* command);     
        virtual string stringToLog() override;     

        Command* getCommand();              
        //void saveEffect();
        bool validate();        



        CommandProcessor();     

        CommandProcessor(const CommandProcessor& copy);     

        ~CommandProcessor();        

        friend ostream& operator <<(ostream& output, CommandProcessor& processor);     
        CommandProcessor& operator =(const CommandProcessor& rhs);      


    protected:
        Command* readCommand();        
        vector <Command*> commandList;
};


class FileLineReader {
    public: 
        Command* readLineFromFile(string file);     

        FileLineReader();          

        ~FileLineReader();          
        FileLineReader(const FileLineReader& copy);         

        friend ostream& operator << (ostream& output, FileLineReader& reader);          
        FileLineReader& operator = (FileLineReader& rhs);           
};



class FileCommandProcessorAdapter : public CommandProcessor {
    public: 
        FileCommandProcessorAdapter();         
        FileCommandProcessorAdapter(const FileCommandProcessorAdapter& copy);           

        string getFileName();         
        FileLineReader* getflr();   
        void setFlr(FileLineReader* flr);      
        void setFileName();           

        ~FileCommandProcessorAdapter();        

        friend ostream& operator <<(ostream& output, FileCommandProcessorAdapter& object);        
        FileCommandProcessorAdapter& operator = (FileCommandProcessorAdapter& rhs);        

        void readCommand(string fileName); 

    protected: 
        FileLineReader* flr;

};