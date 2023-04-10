//
// Created by zoezo on 4/8/23.
//

#include "botConfig.h"

#include <libconfig.h++>

BotConfig* BotConfig::botConfig = nullptr;

BotConfig::BotConfig(std::string fileName) : config() {
    this->config = new libconfig::Config();

    this->config->readFile(fileName.c_str());

    this->token = this->config->lookup("botToken").operator std::string();

    this->guild = this->getOptional<std::string>("guildId");
}

BotConfig *BotConfig::getInstance(std::string fileName) {
    if(BotConfig::botConfig != nullptr) return BotConfig::botConfig;

    BotConfig::botConfig = new BotConfig(fileName);
    return BotConfig::botConfig;
}

libconfig::Config* BotConfig::getConfig() const {
    return this->config;
}

std::string BotConfig::getToken() const {
    return this->token;
}

std::optional<dpp::snowflake> BotConfig::getGuild() const {
    return this->guild;
}

template<typename T>
std::optional<T> BotConfig::getOptional(const std::string &path) {
    return (this->config->exists(path)) ? std::optional(this->config->lookup(path).operator T()) : std::nullopt;
}
