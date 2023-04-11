//
// Created by zoezo on 4/8/23.
//

#ifndef COMPATHIC_COMMANDHANDLER_H
#define COMPATHIC_COMMANDHANDLER_H

#include <map>
#include <string>
#include "commands/command.h"
#include <dpp/dpp.h>

class CommandHandler {
private:
    std::map<std::string, Command*> commands;
public:
    CommandHandler* addCommand(Command *command);
    void runCommand(const dpp::slashcommand_t &event);
};


#endif //COMPATHIC_COMMANDHANDLER_H
