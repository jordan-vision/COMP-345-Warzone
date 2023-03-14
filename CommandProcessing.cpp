#include "CommandProcessing.h"

void Command::saveEffect() {

    Notify(this);
};

string Command::stringToLog() {

    return "Command's Effect: ...";
};

void CommandProcessor::saveCommand() {

    Notify(this);
};

string CommandProcessor::stringToLog() {

    return "Command: ...";
};