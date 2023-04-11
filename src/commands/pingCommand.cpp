//
// Created by zoezo on 4/11/23.
//

#include "pingCommand.h"

PingCommand::PingCommand(dpp::cluster *bot): Command(bot) {
    this->command = new dpp::slashcommand("ping", "Ping pong!", bot->me.id);
}

void PingCommand::run(const dpp::slashcommand_t &event) {
    event.reply("Pong!");
}