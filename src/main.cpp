//
// Created by Toni on 26/12/2023.
//

#include <format>

#include <luna/core/LunaApplication.hpp>
#include <luna/logging/Logging.hpp>

using namespace Luna;
using namespace Luna::Core;

int main() {
    LunaApplication app{"Luna Playground"};

    Logging mainLogger{"main" };

    try {
        app.run();
    }
    catch (const std::exception& exception) {
        mainLogger.error(std::format("An exception of type {} occurred: {}",
                                     typeid(exception).name(),
                                     exception.what()));
    }
}