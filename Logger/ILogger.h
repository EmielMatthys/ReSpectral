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
    enum Level: int {
        INFO = 0,
        DEBUG = 1,
        WARN = 2,
        ERROR = 3
    };

    virtual void logMessage(const char *message, Level level) = 0;

    ILogger* setNextLogger(ILogger *nextLogger)
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

            void logMessage(const char *message, Level level) override
            {
                if (std::count(_levels.begin(), _levels.end(), level))
                {
                    _consumer(message);
                }
            }

        private:
            std::vector<Level> _levels;
            stringConsumerFn _consumer;
        };
        return new _(std::move(levels), consumer);
    };

    static ILogger* consoleLogger(Level levels...) {
        std::vector<Level> vLevels = {};
        vLevels.push_back(levels);
        return write(vLevels, [](auto message) { printf(" - %s", message); });
    }

protected:

};


#endif //RESPECTRAL_ILOGGER_H
