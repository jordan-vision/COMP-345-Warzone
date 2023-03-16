#pragma once
#include <list>
#include <string>
using namespace std;

class ILoggable {

    public:
        ~ILoggable();
        virtual string stringToLog() =0;
};

class Observer {
    
    public:
        ~Observer();
        virtual void Update(ILoggable* log) =0;
    protected:
        Observer();
};

class LogObserver : public Observer {

    public:
        LogObserver();
        ~LogObserver();
        virtual void Update(ILoggable* log) override;
};

class Subject {
    
    public:
        virtual void Attach(Observer* o);
        virtual void Detach(Observer* o);
        virtual void Notify(ILoggable* log);
        Subject();
        ~Subject();
    private:
        list<Observer*> *_observers;
};