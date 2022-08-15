/*
* ����һ����ʱ��仯��ɫ��������
* ʹ����ɫ����
* ʹ��uniform
* https://learnopengl-cn.github.io/01%20Getting%20started/05%20Shaders/
*/

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "../tools/shader.h"

void framebuffer_size_callback(GLFWwindow*, int, int);
void processInput(GLFWwindow*);
int glsl();

//int main()
//{
//    return glsl();
//}

int glsl()
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
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); // ע�ᣬ���ڵ�����С��ʱ������������

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// ������ɫ��
	Shader ourShader("./shader/3-vs.glsl", "./shader/3-fs.glsl");


	// �����ζ���λ�á���ɫ
	float vertices[] = {
		 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // ����
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // ����
		 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // ����
	};

	// ����VAO
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	// �Ȱ�VAO���ٰ�VBO�������ö�������
	glBindVertexArray(VAO);

	// ����VBO
	unsigned int VBO;
	glGenBuffers(1, &VBO); // ����һ��VBO����
	glBindBuffer(GL_ARRAY_BUFFER, VBO); // ���´����Ļ���󶨵�GL_ARRAY_BUFFERĿ��
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // �������ݸ��Ƶ�������ڴ���

	// λ������
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// ��ɫ����
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// ���Խ��Ҳ�ɲ����
	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glBindVertexArray(0);

	while (!glfwWindowShouldClose(window)) // ��Ⱦѭ��
	{
		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT); // ���

		ourShader.use(); // ����

		float timeValue = glfwGetTime();
		float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
		ourShader.setUniformColor("uniformColor", 0.0f, greenValue, 0.0f, 1.0f); // ����uniform��ɫ

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3); // ����

		glfwSwapBuffers(window); // ˫����
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	glfwTerminate();
	return 0;
}
