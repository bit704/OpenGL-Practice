/*
* 使用nuget安装nupengl
* 参考：https://www.cnblogs.com/steamedbun/p/11259376.html
* 包在packages文件夹下
* 
* 使用GLFW库
* LearnOpenGL 使用GLFW
* https://learnopengl-cn.github.io/01%20Getting%20started/03%20Hello%20Window/
* 
* 需要下载glad
* https://glad.dav1d.de/
* 将头文件文件夹加入 属性 -> C/C++ -> 附加包含目录
* 将源文件（glad.c）加入项目
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

    // 创建一个窗口对象
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

    glViewport(0, 0, 800, 600); // 视口大小

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); // 注册，窗口调整大小的时候调用这个函数

    while (!glfwWindowShouldClose(window)) // 渲染循环
    {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT); // 清空

        glfwSwapBuffers(window); // 双缓冲
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





