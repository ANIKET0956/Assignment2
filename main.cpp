#include <iostream>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// GLFW
#include <GLFW/glfw3.h>

// Other includes
#include "Shader.h"

// Function prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

// Window dimensions
const GLuint WIDTH = 1600, HEIGHT = 1200;

// The MAIN function, from here we start the application and run the game loop
int main()
{
    // Init GLFW
    glfwInit();

    // Set all the required options for GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    // Create a GLFWwindow object that we can use for GLFW's functions
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "OpenGL Assignment", NULL, NULL);
    glfwMakeContextCurrent(window);

    // Set the required callback functions
    glfwSetKeyCallback(window, key_callback);

    // Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
    glewExperimental = GL_TRUE;
    // Initialize GLEW to setup the OpenGL Function pointers
    glewInit();

    // Define the viewport dimensions
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);  
    glViewport(0, 0, width, height);




    // Build and compile our shader program
    Shader myShader("default.vs", "default.frag");
    Shader secondShader("second.vs","default.frag");

    GLfloat vertices[] = {
     0.05f,  0.05f, 0.0f,  // Top Right
     0.05f, -0.05f, 0.0f,  // Bottom Right
    -0.05f, -0.05f, 0.0f,  // Bottom Left
    -0.05f,  0.05f, 0.0f   // Top Left 
    };
    

    GLfloat firstlegvertices[] = {
     0.02f, -0.05f, 0.0f,  // Leg TR
     0.02f, -0.07f, 0.0f,  // Leg BR
     0.04f, -0.07f, 0.0f,  // Leg BL
     0.04f, -0.05f, 0.0f,  // Leg TL
    };


    GLfloat secondlegvertices[] = {
     -0.02f, -0.05f, 0.0f,  // Leg TR
     -0.02f, -0.07f, 0.0f,  // Leg BR
     -0.04f, -0.07f, 0.0f,  // Leg BL
     -0.04f, -0.05f, 0.0f,  // Leg TL
    };


    GLuint indices[] = {  // Note that we start from 0!
    0, 1, 3,   // First Triangle
    1, 2, 3    // Second Triangle
    };  

    // Set up vertex data (and buffer(s)) and attribute pointers
    // We add a new set of vertices to form a second triangle (a total of 6 vertices); the vertex attribute configuration remains the same (still one 3-float position vector per vertex)
    GLfloat firstTriangle[] = {
        -0.9f, -0.5f, 0.0f,  // Left 
        -0.0f, -0.5f, 0.0f,  // Right
        -0.45f, 0.5f, 0.0f,  // Top 
        //Color
        0.00, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
    };

    GLuint EBO,VBO;
    glGenBuffers(1, &EBO);
    glGenBuffers(1, &VBO);

    GLuint EBOm[2],VBOm[2];
    glGenBuffers(2, EBOm);
    glGenBuffers(2, VBOm);

    GLuint VBOs[2], VAOs[4];
    glGenVertexArrays(4, VAOs);
    glGenBuffers(2, VBOs);
    glBindVertexArray(VAOs[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);   // Vertex attributes stay the same
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)(9 * sizeof(GLfloat)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glBindVertexArray(0);
    
    glBindVertexArray(VAOs[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);

    glBindVertexArray(VAOs[2]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOm[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(firstlegvertices), firstlegvertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOm[0]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);


    glBindVertexArray(VAOs[3]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOm[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(secondlegvertices), secondlegvertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOm[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);


    GLfloat starttime = glfwGetTime(),currtime;
            
    currtime = starttime;
    // Game loop
    while (!glfwWindowShouldClose(window))
    {
        // Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
        glfwPollEvents();

        // Render
        // Clear the colorbuffer
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        secondShader.Use();

        //Adding Transformation
        glm::mat4 transform;


        if(currtime<starttime+1.00)
            currtime = glfwGetTime();
        transform = glm::translate(transform, glm::vec3(currtime* 0.05f, -0.05f, 0.0f));
        //transform = glm::rotate(transform, (GLfloat)glfwGetTime() * 50.0f, glm::vec3(0.0f, 0.0f, 1.0f));

        // Get matrix's uniform location and set matrix
        GLint transformLoc = glGetUniformLocation(secondShader.Program, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
        
        // Draw the first triangle using the data from our first VAO
        glBindVertexArray(VAOs[1]);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        //glDrawArrays(GL_TRIANGLES, 0, 3);   // This call should output an orange trianglE    
        

        glBindVertexArray(VAOs[2]);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        

        glBindVertexArray(VAOs[3]);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glBindVertexArray(0);

        // Swap the screen buffers
        glfwSwapBuffers(window);
    }
    // Properly de-allocate all resources once they've outlived their purpose
    glDeleteVertexArrays(2, VAOs);
    glDeleteBuffers(2, VBOs);
    // Terminate GLFW, clearing any resources allocated by GLFW.
    glfwTerminate();
    return 0;
}

// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}