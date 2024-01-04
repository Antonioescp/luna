//
// Created by Toni on 3/1/2024.
//

#include <imgui.h>

#include <luna/core/LunaApplication.hpp>

namespace Luna::Core {
    void LunaApplication::onDrawGui() {
        ImGui::Begin("Window test");
        {
            ImGui::Text("Hello world text");
        }
        ImGui::End();
    }

    void LunaApplication::onRender() {

    }
} // Luna::Core