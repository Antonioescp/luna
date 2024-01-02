//
// Created by Toni on 28/12/2023.
//

#include <luna/logging/Logging.hpp>

#include <filesystem>

Luna::Logging::Logging(const std::string& logger) {
    m_logger = (logger.length() > 0)
            ? log4cplus::Logger::getInstance(logger)
            : log4cplus::Logger::getRoot();
}

void Luna::Logging::debug(const std::string &message, const std::string& source, std::source_location location) {
    this->log(log4cplus::DEBUG_LOG_LEVEL, message, source, location);
}

void Luna::Logging::info(const std::string &message, const std::string& source, std::source_location location) {
    this->log(log4cplus::INFO_LOG_LEVEL, message, source, location);
}

void Luna::Logging::warn(const std::string &message, const std::string& source, std::source_location location) {
    this->log(log4cplus::WARN_LOG_LEVEL, message, source, location);
}

void Luna::Logging::error(const std::string &message, const std::string& source, std::source_location location) {
    this->log(log4cplus::ERROR_LOG_LEVEL, message, source, location);
}

void Luna::Logging::log(log4cplus::LogLevel level, const std::string &message, const std::string& source, std::source_location location) {
    auto messageSource = (source.length() > 0)
            ? source
            : std::filesystem::path(location.file_name()).filename().generic_string();

    m_logger.log(
            level,
            message,
            messageSource.c_str(),
            static_cast<int>(location.line()),
            location.function_name()
            );
}