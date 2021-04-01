#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

void mouse_callback(GLFWwindow* window, double xpos, double ypos){};
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset){};
void framebuffer_size_callback(GLFWwindow* window, int width, int height){};

int main(void) {
    // initialize GLFW
    if (!glfwInit())
        return -1;

    // use OpenGL 4.3 Core
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // create a windowed mode window and its OpenGL context
    GLFWwindow* window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // make the window's context current
    glfwMakeContextCurrent(window);

    // register callback functions
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // load GL functions using GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // loop until the user closes the window
    while (!glfwWindowShouldClose(window)) {
        // render here
        glClear(GL_COLOR_BUFFER_BIT);

        // swap front and back buffers
        glfwSwapBuffers(window);

        // poll for and process events
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
