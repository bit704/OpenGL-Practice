/*
* ������ɫ��
* ��ըЧ��
* https://learnopengl-cn.github.io/04%20Advanced%20OpenGL/09%20Geometry%20Shader/
*/
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../tools/shader.h"
#include "../tools/camera.h"
#include "../tools/model.h"

void framebuffer_size_callback(GLFWwindow*, int, int);
void processInput(GLFWwindow*);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
int geometry_shader();

const unsigned int ScreenWidth = 800;
const unsigned int ScreenHeight = 600;

// ���
extern Camera camera;
extern float lastX;
extern float lastY;
extern bool firstMouse;

// ��ʱ
extern float deltaTime;	// ��ǰ֡����һ֡��ʱ��
extern float lastFrame;

extern glm::vec3 lightPos;

//int main()
//{
//	return geometry_shader();
//}

int geometry_shader()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // for Mac OS X

	// ����һ�����ڶ���
	GLFWwindow* window = glfwCreateWindow(ScreenWidth, ScreenHeight, "test", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	// ����GLFW�������
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	/*
	* ͨ�ó�ʼ������
	*/

	// ����ȫ��OpenGL״̬
	glEnable(GL_DEPTH_TEST);

	Shader shader("./shader/5-vs.glsl", "./shader/5-fs.glsl", "./shader/5-gs.glsl");

	Model nanosuit("../obj/nanosuit/nanosuit.obj");

	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		processInput(window);

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// MVP
		glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)ScreenWidth / (float)ScreenHeight, 1.0f, 100.0f);
		glm::mat4 view = camera.GetViewMatrix();
		view = glm::translate(view, glm::vec3(0.f, -10.f, -10.f)); // �����������ƽ��
		glm::mat4 model = glm::mat4(1.0f);
		shader.use();
		shader.setMat4("projection", projection);
		shader.setMat4("view", view);
		shader.setMat4("model", model);

		// ����ʱ��
		shader.setFloat("time", static_cast<float>(glfwGetTime()));

		nanosuit.Draw(shader);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;

}