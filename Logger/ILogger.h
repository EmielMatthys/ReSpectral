//
// Created by emiel on 6/03/21.
//

#ifndef RESPECTRAL_ILOGGER_H
#define RESPECTRAL_ILOGGER_H
#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>

typedef void (*stringConsumerFn)(const char*);

class ILogger {
public:
    static ILogger *logger;

    enum Level: int {
        INFO = 0,
        DEBUG = 1,
        WARN = 2,
        ERROR = 3
    };

    virtual void logMessage(const char *message, Level level) = 0;

    ILogger* appendLogger(ILogger *nextLogger)
    {
        // Define anonymous class that forwards logMessage calls to the provided nextLogger
        class _ : public ILogger {
        public:
            _(ILogger *nextLogger) : _nextLogger(nextLogger)
            {}

            void logMessage(const char *message, Level level) override
            {
                _nextLogger->logMessage(message, level);
            }

        private:
            ILogger * _nextLogger;
        };
        return new _(nextLogger);
    }

    static ILogger* write(std::vector<Level> levels, stringConsumerFn consumer)
    {
        // Define anonymous class that only passes messages to the stringconsumer when it's level is in levels
        class _ : public ILogger {
        public:
            _(std::vector<Level> levels, void (*consumer)(const char *) ) : _levels(std::move(levels)),
                                                                            _consumer(consumer)
            {}

            const char* getLevelString(Level l)
            {
                switch (l) {
                    case INFO: return "I";
                    case DEBUG: return "D";
                    case WARN: return "W";
                    case ERROR: return "E";
                }
                return nullptr;
            }

            void logMessage(const char *message, Level level) override
            {
                if (std::count(_levels.begin(), _levels.end(), level))
                {
                    char buffer[256];
                    sprintf(buffer, "%s/ %s", getLevelString(level), message);
                    _consumer(buffer);
                }
            }

        private:
            std::vector<Level> _levels;
            stringConsumerFn _consumer;
        };
        return new _(std::move(levels), consumer);
    };

    static ILogger* consoleLogger(std::vector<Level> levels) {

        return write(std::move(levels), [](auto message) { printf("[ReSPECTRAL] - %s\n", message); });
    }
    
protected:

};




#endif //RESPECTRAL_ILOGGER_H
