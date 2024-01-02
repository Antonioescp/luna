//
// Created by Toni on 1/1/2024.
//

#include <format>

#include "luna/core/Application.hpp"

namespace Luna::Core {
    int Application::OpenGLMajorVersion{4};
    int Application::OpenGLMinorVersion{3};

    Application::Application(const std::string& title, int width, int height) {
        log4cplus::PropertyConfigurator::doConfigure("logging.ini");

        m_isInitialized = glfwInit();
        if (!m_isInitialized) {
            m_classLogger.error("Failed to initialize GLFW");
            return;
        }

        m_classLogger.info("GLFW initialized");

        glfwSetErrorCallback(Application::onError);

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OpenGLMajorVersion);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OpenGLMinorVersion);
        m_window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
        if (!m_window) {
            m_classLogger.error("Failed to create main window");
            return;
        }

        m_classLogger.info(std::format("Window {} created", title));

        glfwMakeContextCurrent(m_window);
        gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));
        glViewport(0, 0, width, height);

        // Window callbacks
        glfwSetWindowCloseCallback(m_window, Application::onClose);
        glfwSetFramebufferSizeCallback(m_window, Application::onSizeChanged);

        m_classLogger.info("App correctly initialized");
    }

    Application::~Application() {
        glfwDestroyWindow(m_window);
        glfwTerminate();
    }

    void Application::onError(int error, const char *description) {
        Logging coreLogging{"core"};
        coreLogging.error(std::format(
            "GLFW error occurred with code {} and message {}",
            error,
            description));
    }

    void Application::run() {
        // start from 0
        glfwSetTime({});
        while (!glfwWindowShouldClose(m_window)) {
            double currentTime = glfwGetTime();
            m_deltaTime = currentTime - m_previousTime;
            m_previousTime = currentTime;

            m_classLogger.debug(std::format("deltaTime is {}", this->getDeltaTime()));

            glfwSwapBuffers(m_window);
            glfwPollEvents();
        }
    }

    void Application::onClose(GLFWwindow *window) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }

    void Application::onSizeChanged([[maybe_unused]] GLFWwindow *window, int width, int height) {
        glViewport(0, 0, width, height);
    }

    double Application::getDeltaTime() const {
        return m_deltaTime;
    }
} // Core