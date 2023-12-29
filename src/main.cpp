//
// Created by Toni on 26/12/2023.
//

#include <luna/logging/Logging.hpp>

int main() {
    log4cplus::Initializer init{};
    log4cplus::PropertyConfigurator::doConfigure("../data/loggingSettings.txt");
    Luna::Logging root{};
    root.info("Hello there");
}