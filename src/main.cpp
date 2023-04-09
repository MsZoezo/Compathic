#include <dpp/dpp.h>
#include <libconfig.h++>
#include <argh.h>
#include "botConfig.h"

int main(int argc, char** argv) {
    argh::parser cmdl(argc, argv);

    BotConfig* botConfig;

    try {
        botConfig = (cmdl["--config"] ? BotConfig::getInstance(cmdl("--config").str()) : BotConfig::getInstance());
    } catch(const libconfig::FileIOException &exception) {
        std::cerr << "Can't find config file, missing or insufficient permissions." << std::endl;

        return 1;
    } catch(const libconfig::ParseException &exception) {
        std::cerr << "There appears to be an error in the config file." << std::endl;

        return 2;
    }

    libconfig::Config *config = botConfig->getConfig();
    std::string token;

    try {
        token = config->lookup("botToken").operator std::string();
    } catch(const libconfig::SettingNotFoundException &exception) {
        std::cerr << "No 'bottoken' setting in configuration file." << std::endl;
        return 3;
    }

    dpp::cluster *bot;

    try {
        bot = new dpp::cluster(token);
    } catch(const dpp::invalid_token_exception &exception) {
        std::cerr << "The provided bot token appears to be invalid." << std::endl;
        return 4;
    }

    bot->on_log(dpp::utility::cout_logger());

    bot->on_slashcommand([&bot](const dpp::slashcommand_t& event) {
        if (event.command.get_command_name() == "ping") {
            event.reply("Pong!");
        }
    });

    bot->on_ready([&bot](const dpp::ready_t& event) {
        if (dpp::run_once<struct register_bot_commands>()) {
            bot->guild_command_create(
                    dpp::slashcommand("ping", "Ping pong!", bot->me.id),
                    -1
            );
        }
    });

    bot->start(dpp::st_wait);
}