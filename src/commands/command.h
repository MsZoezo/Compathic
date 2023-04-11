//
// Created by zoezo on 4/11/23.
//

#ifndef COMPATHIC_COMMAND_H
#define COMPATHIC_COMMAND_H

#include <dpp/dpp.h>

class Command {
protected:
    dpp::slashcommand* command;
    dpp::cluster *bot;

public:
    Command(dpp::cluster *bot);

    dpp::slashcommand* getSlashCommand() const;

    virtual void run(const dpp::slashcommand_t &event) = 0;
};

#endif //COMPATHIC_COMMAND_H
