//
// Created by Toni on 28/12/2023.
//

#ifndef LUNA_LOGGING_HPP
#define LUNA_LOGGING_HPP

#include <source_location>
#include <string>
#include <string_view>

#include <log4cplus/log4cplus.h>

#define ToString(x) std::string{#x}

namespace Luna {
    class Logging {
    public:

        explicit Logging(const std::string& name = "");

        void debug(const std::string& message, const std::string& source = "", std::source_location location = std::source_location::current());
        void info(const std::string& message, const std::string& source = "", std::source_location location = std::source_location::current());
        void warn(const std::string& message, const std::string& source = "", std::source_location location = std::source_location::current());
        void error(const std::string& message, const std::string& source = "", std::source_location location = std::source_location::current());

    private:
        log4cplus::Logger m_logger;

        void log(log4cplus::LogLevel level, const std::string& message, const std::string& source, std::source_location location);
    };
}

#endif //LUNA_LOGGING_HPP
