/*
* ʹ��nuget��װnupengl
* �ο���https://www.cnblogs.com/steamedbun/p/11259376.html
* ����packages�ļ�����
* 
* ʹ��GLFW��
* LearnOpenGL ʹ��GLFW
* https://learnopengl-cn.github.io/01%20Getting%20started/03%20Hello%20Window/
* 
* ��Ҫ����glad
* https://glad.dav1d.de/
* ��ͷ�ļ��ļ��м��� ���� -> C/C++ -> ���Ӱ���Ŀ¼
* ��Դ�ļ���glad.c��������Ŀ
*/

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow*, int, int);
void processInput(GLFWwindow*);
int testGLFW();

//int main()
//{
//    return testGLFW();
//}

int testGLFW()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // for Mac OS X

    // ����һ�����ڶ���
    GLFWwindow* window = glfwCreateWindow(800, 600, "test", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glViewport(0, 0, 800, 600); // �ӿڴ�С

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); // ע�ᣬ���ڵ�����С��ʱ������������

    while (!glfwWindowShouldClose(window)) // ��Ⱦѭ��
    {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT); // ���

        glfwSwapBuffers(window); // ˫����
        glfwPollEvents(); 
    }

    glfwTerminate();

    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}





