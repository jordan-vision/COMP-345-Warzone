#pragma once
#include <list>
#include <string>
using namespace std;

class ILoggable {

    public:
        ~ILoggable();
        //ILoggable(const ILoggable &ilog);                               // Copy Constructor
        //ILoggable& operator =(const ILoggable &ilog);                   // Assignment Operator
        //friend ostream& operator <<(ostream& out, const ILoggable* ilog); // Stream Operator
        virtual string stringToLog() =0;
};

class Observer {
    
    public:
        ~Observer();
        Observer& operator =(const Observer &observer);                   // Assignment Operator
        friend ostream& operator <<(ostream& out, const Observer* observer); // Stream Operator
        virtual void Update(ILoggable* log) =0;
    protected:
        Observer();
};

class LogObserver : public Observer {

    public:
        LogObserver();
        ~LogObserver();
        LogObserver(const LogObserver &logobserver);                               // Copy Constructor
        LogObserver& operator =(const LogObserver &logobserver);                   // Assignment Operator
        friend ostream& operator <<(ostream& out, const LogObserver* logobserver); // Stream Operator
        virtual void Update(ILoggable* log) override;
};

class Subject {
    
    public:
        virtual void Attach(Observer* o);
        virtual void Detach(Observer* o);
        virtual void Notify(ILoggable* log);
        Subject();
        ~Subject();
        Subject(const Subject &subject);                                   // Copy Constructor
        Subject& operator =(const Subject &subject);                       // Assignment Operator
        friend ostream& operator <<(ostream& out, const Subject* subject); // Stream Operator
    private:
        list<Observer*> *_observers;
};