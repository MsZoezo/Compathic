//
// Created by zoezo on 4/8/23.
//

#include "botConfig.h"

#include <libconfig.h++>

BotConfig* BotConfig::botConfig = nullptr;

BotConfig::BotConfig(std::string fileName) : config() {
    this->config = new libconfig::Config();

    try {
        this->config->readFile(fileName.c_str());
    } catch(const libconfig::FileIOException &exception) {
        throw exception;
    } catch(const libconfig::ParseException &exception) {
        throw exception;
    }

    try {
        this->token = this->config->lookup("token").operator std::string();
        this->guild = this->config->lookup("guild").operator unsigned int();
    } catch (const libconfig::SettingNotFoundException &exception) {
        throw exception;
    }
}
}

BotConfig *BotConfig::getInstance(std::string fileName) {
    if(BotConfig::botConfig != nullptr) return BotConfig::botConfig;

    BotConfig::botConfig = new BotConfig(fileName);
    return BotConfig::botConfig;
}

libconfig::Config* BotConfig::getConfig() const {
    return this->config;
}
