/*
* ����һ���߿����
* ʹ��IBO��Index Buffer Object��
* https://learnopengl-cn.github.io/01%20Getting%20started/04%20Hello%20Triangle/
*/

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow*, int, int);
void processInput(GLFWwindow*);
int rectangle();

//int main()
//{
//	return rectangle();
//}

int rectangle()
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

	// ����������ɫ��
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	// Ӳ����
	const char* vertexShaderSource =
		"#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";

	// �󶨲�����
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	// ��ȡ������Ϣ
	int  success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// ����Ƭ����ɫ��
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	const char* fragmentShaderSource =
		R"(#version 330 core
		out vec4 FragColor;
		void main()
		{
			FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
		})";

	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// ������ɫ���������
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::Link_FAILED\n" << infoLog << std::endl;
	}

	// ɾ����ɫ��
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);


	// ����
	float vertices[] = 
	{
		0.5f, 0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		-0.5f, 0.5f, 0.0f
	};

	// ������0��ʼ�������Ƕ�������vertices���±�
	unsigned int indices[] = 
	{
		0, 1, 3, 
		1, 2, 3
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
	
	// ����IBO
	unsigned int IBO;
	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// ���ö�������ָ��
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// ���Խ��Ҳ�ɲ����
	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glBindVertexArray(0);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // �߿�ģʽ
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	while (!glfwWindowShouldClose(window)) // ��Ⱦѭ��
	{
		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT); // ���

		glUseProgram(shaderProgram); // ����
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); // ����

		glfwSwapBuffers(window); // ˫����
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &IBO);
	glDeleteProgram(shaderProgram);

	glfwTerminate();
	return 0;
}
