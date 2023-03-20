#include "LoggingObserver.h"
#include <fstream>

// THE FOLLOWING CODE IS COMMENTED OUT BECAUSE IT WAS INTERFERRING WITH ISSUES IN OTHER FILES

// LogObserver::LogObserver() {

// };


// /***************** ILOGGABLE COPY CONSTRUCTOR *****************/
// LogObserver::LogObserver(const LogObserver &logobserver) {

// };

/**************** SUBJECT ASSIGNMENT OPERATOR ***************/
// LogObserver& LogObserver::operator =(const LogObserver &logobserver) {

//     return *this;
// };

/***************** SUBJECT STREAM OPERATOR *****************/
// ostream& operator<<(std::ostream& out, const LogObserver& logobserver) {

//     out << "LogObserver";                              
//     return out; 
// }

// Observer::Observer() {

// };

/***************** Observer COPY CONSTRUCTOR *****************/
// Observer::Observer(const Observer &observer) {

// };

/**************** Observer ASSIGNMENT OPERATOR ***************/
// Observer& Observer::operator =(const Observer &observer) {

//     return *this;
// };

// /***************** Observer STREAM OPERATOR *****************/
// ostream& operator<<(std::ostream& out, const Observer& observer) {

//     out << "OBSERVER";                                  
//     return out; 
// }

/***************** SUBJECT COPY CONSTRUCTOR *****************/
// Subject::Subject(const Subject &subject) {

// };

// /**************** SUBJECT ASSIGNMENT OPERATOR ***************/
// Subject& Subject::operator =(const Subject &subject) {

//     return *this;
// };

/**************** SUBJECT ASSIGNMENT OPERATOR ***************/
// ILoggable& ILoggable::operator =(const ILoggable &ilog) {

//     return *this;
// };

// /***************** SUBJECT STREAM OPERATOR *****************/
// ostream& operator<<(std::ostream& out, const ILoggable& ilog) {

//     out << "ILOGGABLE";                              
//     return out; 
// }


LogObserver::~LogObserver() {

};

// LogObserver Update - prints stringToLog whenever update is called to .txt
void LogObserver::Update(ILoggable* log) {

    ofstream output;

    output.open("gamelog.txt");
    output << log->stringToLog();
    output.close();
};

// Observer destructor
Observer::~Observer() {

};


// Subject constructor creates new list of observers
Subject::Subject() {
    _observers = new list<Observer*>;
};

// Subject destructor
Subject::~Subject() {
    delete _observers;
};


/***************** SUBJECT STREAM OPERATOR *****************/
ostream& operator<<(std::ostream& out, const Subject& subject) {

    out << "SUBJECT";                              
    return out; 
}

// Used to attach an observer
void Subject::Attach(Observer* o) {
    _observers->push_back(o);
};

// Used to detach an observer
void Subject::Detach(Observer* o) {
    _observers->remove(o);
};

// Notify function that updates all observers
void Subject::Notify(ILoggable* log) {

    list<Observer *>::iterator i = _observers->begin();

    for (; i != _observers->end(); ++i)
        (*i)->Update(log);
};

// ILoggable destructor
ILoggable::~ILoggable() {

};
