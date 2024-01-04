//
// Created by Toni on 1/1/2024.
//

#include <format>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "luna/core/Application.hpp"

namespace Luna::Core {
    Logging Application::classLogger{ToString(Application) };

    Application::Application(const std::string& title, int width, int height) {
        log4cplus::PropertyConfigurator::doConfigure("logging.ini");

        glfwSetErrorCallback(Application::onError);
        m_isInitialized = glfwInit();
        if (!m_isInitialized) {
            Application::classLogger.error("Failed to initialize GLFW");
            return;
        }

        Application::classLogger.info("GLFW initialized");


        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OpenGLMajorVersion);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OpenGLMinorVersion);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        m_window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
        if (!m_window) {
            Application::classLogger.error("Failed to create main window");
            m_isInitialized = false;
            return;
        }

        Application::classLogger.info(std::format(R"(Window "{}" created)", title));

        glfwMakeContextCurrent(m_window);
        gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));
        glViewport(0, 0, width, height);

        // Window callbacks
        glfwSetWindowCloseCallback(m_window, Application::onClose);
        glfwSetFramebufferSizeCallback(m_window, Application::onSizeChanged);

        Application::classLogger.info("App correctly initialized");

        this->initializeImGui();
    }

    Application::~Application() {
        glfwDestroyWindow(m_window);
        glfwTerminate();
    }

    void Application::run() {
        if (!m_isInitialized) {
            Application::classLogger.error("Attempted to run uninitialized application");
            return;
        }

        // start from 0
        glfwSetTime({});
        while (!glfwWindowShouldClose(m_window)) {
            double currentTime = glfwGetTime();
            m_deltaTime = currentTime - m_previousTime;
            m_previousTime = currentTime;

            this->render();
        }
    }

    void Application::onError(int error, const char *description) {
        Logging coreLogging{"core"};
        coreLogging.error(std::format(
            "GLFW error occurred with code {} and message {}",
            error,
            description));
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

    void Application::initializeImGui() {
        Application::classLogger.info("Initializing ImGui");

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io{ ImGui::GetIO() };
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
        ImGui::StyleColorsDark();

        ImGui_ImplGlfw_InitForOpenGL(m_window, true);
        ImGui_ImplOpenGL3_Init("#version 150");

        Application::classLogger.info("ImGui initialized successfully");
    }

    void Application::startImGuiRender() {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        this->onDrawGui();

        ImGui::Render();
    }

    void Application::render() {
        glfwPollEvents();
        this->startImGuiRender();

        glClearColor(255, 0, 0, 255);
        glClear(GL_COLOR_BUFFER_BIT);
        this->onRender();
        Application::finishImGuiRender();
        glfwSwapBuffers(m_window);
    }

    void Application::finishImGuiRender() {
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }
} // Core