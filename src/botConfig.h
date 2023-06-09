//
// Created by zoezo on 4/8/23.
//

#ifndef COMPATHIC_BOTCONFIG_H
#define COMPATHIC_BOTCONFIG_H


#include <string>
#include <libconfig.h++>
#include <dpp/dpp.h>

class BotConfig {
private:
    static BotConfig *botConfig;

    libconfig::Config *config;

    std::string token;
    std::optional<dpp::snowflake> guild;

    BotConfig(std::string fileName);

    template<typename T>
    std::optional<T> getOptional(const std::string &path);

public:
    static BotConfig* getInstance(std::string fileName = "bot.cfg");

    libconfig::Config* getConfig() const;

    std::string getToken() const;
    std::optional<dpp::snowflake> getGuild() const;
};

#endif //COMPATHIC_BOTCONFIG_H
