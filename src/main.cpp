#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<iostream>

int main(int argc, char* argv[]) {
    //init glfw
    glfwInit();
    //request OpenGL version 3.3 by configuring with glfwWindowHint
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    //Set OpenGL core profile
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    //straightforward, create a window with x,y dimensions, window title, Monitor(GLFWmointor*) - monitor to use for fullscreen mode or NULL for windowed mode, or and Share(GLFWindow*) - window whose context to share resources with, or NULL to not share resources.
    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    //init GLAD so it can manage function pointers for openGL
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    //set up a viewport. 0,0 sets location of the lower-left corner of the window. Third and Fourth are width and height;
    glViewport(0, 0, 800, 600);

    //render loop
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        //clear viewport
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //render by swapping buffers
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}

//callback that gets executed every time the window is resized
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

//GLFW's keys
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}