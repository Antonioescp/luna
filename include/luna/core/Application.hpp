//
// Created by Toni on 1/1/2024.
//

#ifndef LUNA_APPLICATION_HPP
#define LUNA_APPLICATION_HPP

#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <log4cplus/log4cplus.h>

#include <luna/logging/Logging.hpp>

namespace Luna::Core {

    class ApplicationError : public std::exception {
    public:
        using std::exception::exception;
    };

    class Application {
    public:
        explicit Application(const std::string& title, int width = 640, int height = 480);
        ~Application();

        void run();
        [[nodiscard]] double getDeltaTime() const;
    private:
        GLFWwindow* m_window{ nullptr };
        log4cplus::Initializer m_log4cplusInitializer{};
        double m_deltaTime{};
        double m_previousTime{};
        bool m_isInitialized{};

        static Logging classLogger;
        constexpr static int OpenGLMajorVersion{ 4 };
        constexpr static int OpenGLMinorVersion{ 3 };

        virtual void onDrawGui() = 0;
        virtual void onRender() = 0;

        void render();
        void initializeImGui();
        void startImGuiRender();

        static void finishImGuiRender();
        static void onError(int error, const char* description);
        static void onClose(GLFWwindow* window);
        static void onSizeChanged(GLFWwindow* window, int width, int height);
    };
}// Core

#endif //LUNA_APPLICATION_HPP
