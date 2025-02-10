#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<iostream>
#include"../include/Shader.h"

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

int main(int argc, char* argv[]) {
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    //request OpenGL version 3.3 by configuring with glfwWindowHint
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    //Set OpenGL core profile
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // glfw window creation
    // --------------------
    //straightforward, create a window with x,y dimensions, window title, Monitor(GLFWmointor*) - monitor to use for fullscreen mode or NULL for windowed mode, or and Share(GLFWindow*) - window whose context to share resources with, or NULL to not share resources.
    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);//bind the callback to the window.

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    //set up a viewport. 0,0 sets location of the lower-left corner of the window. Third and Fourth are width and height;
    glViewport(0, 0, 800, 600);

    Shader ourShader("shaders/basic.vs", "shaders/basic.fs");

    //arbitrary vertices
    float vertices[] = {
     0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
    -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
     0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top 
    };

    ///unsigned int indices[] = {// note that we start from 0!
    //0, 1, 2,   // first triangle
    //};

    //openGL gens buffers and then gives you an ID number to reference them.
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    //then bind the buffer that was just generated to the GL_ARRAY_BUFFER target
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //copy the data in vertices into the vertex buffer. 1st arg is the buffer copying into, 2nd arg is the size of data we want to pass to it.
    //3rd parameter is the actual data we want to send. Fourth parameter specifies how we want the graphics card to manage the data. Can take 3 forms:
    // GL_STREAM_DRAW, data set only once and used by GPU at most a few times; GL_STATIC_DRAW, data set only once and used many times; GL_DYNAMIC_DRAW, data is changed a lot and used many times
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //create an Element Buffer Object for the indices
    //unsigned int EBO;
    //glGenBuffers(1, &EBO);
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    

    //glVertexAttribPointer:
        //param 1: specifies which vertex attribute we want to configure. we get layout location 0, which we've defined as position.
        //param 2: specifies size of vertex attribute. It's a vec3, so composed of 3 values.
        //param 3: Type of data, which is GL_FLOAT (a vec* in GLSL consists of floating point values)
        //param 4: specifies if we want the data to be normalized. We don't so GL_FALSE.
        //param 5: stride, tells space between consecutive vertex attributes
        //param 6: type void* so requires casting. This is the offset.
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);//vertex attributes are disabled by default, so we have to enable it.

    //Generate a Vertex Array Object
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);

    // ..:: Initialization code (done once (unless your object frequently changes)) :: ..
    // 1. bind Vertex Array Object
    glBindVertexArray(VAO);
    // 2. copy our vertices array in a buffer for OpenGL to use
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // 3. then set our vertex attributes pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);


    //render loop
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        //clear viewport with a greyish colour
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        ourShader.use();

        glBindVertexArray(VAO);
        //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        //render by swapping buffers
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}
