#include <dpp/dpp.h>
#include <libconfig.h++>
#include <argh.h>
#include "botConfig.h"
#include <fmt/format.h>

int loadBotConf(BotConfig *&botConfig, std::string file) {
    if(botConfig != nullptr) return (std::cerr << "Not replacing existing config" << std::endl, -5);

    try {
        botConfig = BotConfig::getInstance(file);
    } catch(const libconfig::FileIOException &exception) {
        return (fmt::print(stderr,"Unable to load config file, missing or insufficient permissions?\n"), 1);
    } catch(const libconfig::ParseException &exception) {
        return (fmt::print(stderr, "Parsing error in {} at line {}: {}\n", exception.getFile(), exception.getLine(), exception.getError()), 2);
    } catch(const libconfig::SettingNotFoundException &exception) {
        return (fmt::print(stderr, "Missing setting in config file: {}\n", exception.getPath()), 3);
    } catch(const libconfig::ConfigException &exception) {
        return (fmt::print(stderr, "Unknown error occured while loading config: {}\n", exception.what()), -1);
    }

    return 0;
}

int initBot(dpp::cluster *&bot, const std::string token, const bool debug) {
    if(bot != nullptr) return (fmt::print("Can't replace existing bot instance.\n"), -6);

    try {
        bot = new dpp::cluster(token);
    } catch(const dpp::invalid_token_exception &exception) {
        return(fmt::print(stderr, "Provided bot token appears to be invalid.\n"), 4);
    }

    if(debug) bot->on_log(dpp::utility::cout_logger());

    return 0;
}

int main(int argc, char** argv) {
    argh::parser cmdl(argc, argv);

    BotConfig *botConfig;

    if(int ret = loadBotConf(botConfig, cmdl({"-c", "--config"}, "bot.cfg").str()) != 0) return ret;

    dpp::cluster *bot;

    if(int ret = initBot(bot, botConfig->getToken(), true) != 0) return ret;

    bot->on_slashcommand([&bot](const dpp::slashcommand_t& event) {
        if(event.command.get_command_name() == "ping") {
            event.reply("Pong!");
        }
    });

    bot->on_ready([&bot, &botConfig](const dpp::ready_t& event) {
        if(dpp::run_once<struct register_bot_commands>()) {
            bot->guild_command_create(
                    dpp::slashcommand("ping", "Ping pong!", bot->me.id),
                    botConfig->getGuild().value()
            );
        }
    });

    bot->start(dpp::st_wait);
}