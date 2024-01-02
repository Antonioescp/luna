//
// Created by Toni on 26/12/2023.
//

#include <format>

#include <luna/core/Application.hpp>
#include <luna/logging/Logging.hpp>

int main() {
    Luna::Core::Application app{"Hello world"};

    Luna::Logging mainLogger{"main" };

    try {
        app.run();
    }
    catch (const std::exception& exception) {
        mainLogger.error(std::format("An exception occurred: {}", exception.what()));
    }
}