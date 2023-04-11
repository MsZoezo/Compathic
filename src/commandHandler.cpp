//
// Created by zoezo on 4/8/23.
//

#include "commandHandler.h"

#include <map>

CommandHandler* CommandHandler::addCommand(Command *command) {
    // TODO: check if command with name already exists
    this->commands.emplace(command->getSlashCommand()->name, command);

    return this;
}

void CommandHandler::runCommand(const dpp::slashcommand_t &event) {
    std::string name = event.command.get_command_name();

    if(this->commands.count(name) == 0) {
        event.reply("Oopsie woopsie unknown command?");
        return;
    }

    Command *command = this->commands[name];

    command->run(event);
}