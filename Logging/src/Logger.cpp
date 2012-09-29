#include "Stoughton1004Lib/Logging/Logger.h"

#include <mutex>

namespace Stoughton1004Lib {

using std::lock_guard;
using std::make_pair;
using std::mutex;
using std::string;
using std::unordered_map;
using std::unordered_set;

unordered_map<string, Logger> Logger::loggers;
static mutex loggerMutex;

Logger* Logger::getLogger(const string &loggerName) {
    {
        lock_guard<mutex> lock(loggerMutex);
        if (!loggers.count(loggerName)) {
            loggers.insert(make_pair(loggerName, Logger()));
        }
        return &loggers.at(loggerName);
    }
}

Logger::Logger() {
    level= Level::INFO;
}

void Logger::addHandler(Handler *handler) {
    handlers.insert(handler);
}

void Logger::removeHandler(Handler *handler) {
    handlers.erase(handler);
}

void Logger::removeAllHandlers() {
    handlers.clear();
}

void Logger::setLevel(Level newLevel) {
    level= newLevel;
}

void Logger::log(Level level, const string &msg) {
    auto publish= [this, &level, &msg]() -> bool {
        for(auto it= handlers.begin(); it != handlers.end(); it++) {
            (*it)->getLevel() >= level && (*it)->publish(msg);
        }
        return true;
    };
    
    (level >= this->level) && publish();
}

const unordered_set<Handler*>& Logger::getHandlers() const {
    return handlers;
}

Level Logger::getLevel() const {
    return level;
}

}