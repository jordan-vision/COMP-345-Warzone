#pragma once
#include "LoggingObserver.h"

class Command : public ILoggable, Subject {
    public:
        void saveEffect();
        virtual string stringToLog() override;

};

class CommandProcessor : public ILoggable, Subject {
    public:
        void saveCommand();
        virtual string stringToLog() override;
};

class FileCommandProcessorAdapter {

};
