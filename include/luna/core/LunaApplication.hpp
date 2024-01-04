//
// Created by Toni on 3/1/2024.
//

#ifndef LUNA_LUNAAPPLICATION_HPP
#define LUNA_LUNAAPPLICATION_HPP

#include <luna/core/Application.hpp>

namespace Luna::Core {
    class LunaApplication : public Application {
    public:
        using Application::Application;

    private:
        void onDrawGui() override;
        void onRender() override;
    };
} // Luna::Core

#endif //LUNA_LUNAAPPLICATION_HPP
