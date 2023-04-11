//
// Created by zoezo on 4/11/23.
//
#include "command.h"

dpp::slashcommand* Command::getSlashCommand() const {
    return this->command;
}

Command::Command(dpp::cluster *bot): bot(bot) {}
