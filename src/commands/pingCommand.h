//
// Created by zoezo on 4/11/23.
//

#ifndef COMPATHIC_PINGCOMMAND_H
#define COMPATHIC_PINGCOMMAND_H

#include "command.h"
#include <dpp/dpp.h>

class PingCommand : public Command {
public:
    PingCommand(dpp::cluster *bot);

    void run(const dpp::slashcommand_t &event);
};


#endif //COMPATHIC_PINGCOMMAND_H
