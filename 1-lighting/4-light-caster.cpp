/*
* һ������⡢�ĸ���⡢һ���۹⣨�ֵ�Ͳ��
* �����ռ����װ��GLSL������
* https://learnopengl-cn.github.io/02%20Lighting/05%20Light%20casters/
* https://learnopengl-cn.github.io/02%20Lighting/06%20Multiple%20lights/
*/

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../tools/stb_image.h"
#include "../tools/shader.h"
#include "../tools/camera.h"

void framebuffer_size_callback(GLFWwindow*, int, int);
void processInput(GLFWwindow*);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
unsigned int loadTexture(const char* path);
int light_caster();

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

int main()
{
	return light_caster();
}

int light_caster()
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

	// ����
	float vertices[] = {
		// positions          // normals           // texture coords
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
	};

	// ��ͬ�����������ռ�λ��
	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	// �ĸ�����λ��
	glm::vec3 pointLightPositions[] = {
		glm::vec3(0.7f,  0.2f,  2.0f),
		glm::vec3(2.3f, -3.3f, -4.0f),
		glm::vec3(-4.0f,  2.0f, -12.0f),
		glm::vec3(0.0f,  0.0f, -3.0f)
	};

	// �������VAO��VBO
	unsigned int VBO, ordinaryCudeVAO;
	glGenVertexArrays(1, &ordinaryCudeVAO);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(ordinaryCudeVAO);
	// ��������
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// ���Դ��VAO������VBO��
	unsigned int lightCubeVAO;
	glGenVertexArrays(1, &lightCubeVAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBindVertexArray(lightCubeVAO);
	// ��������
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// ������ɫ��
	Shader lightShader("./shader/4-light-vs.glsl", "./shader/4-light-fs.glsl");
	Shader materialShader("./shader/4-material-vs.glsl", "./shader/4-material-fs.glsl");

	unsigned int diffuseMap = loadTexture("./texture/container2.png");
	unsigned int specularMap = loadTexture("./texture/container2_specular.png");

	materialShader.use();
	materialShader.setInt("material.diffuse", 0);
	materialShader.setInt("material.specular", 1);


	// ������Ȳ���
	glEnable(GL_DEPTH_TEST);

	while (!glfwWindowShouldClose(window)) // ��Ⱦѭ��
	{
		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// ��������
		materialShader.use();
		materialShader.setVec3("viewPos", camera.Position);
		materialShader.setFloat("material.shininess", 64.0f);

		// ������
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, diffuseMap);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, specularMap);

		// ��������
		// �����
		materialShader.setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
		materialShader.setVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
		materialShader.setVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
		materialShader.setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);
		// ��� 1
		materialShader.setVec3("pointLights[0].position", pointLightPositions[0]);
		materialShader.setVec3("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
		materialShader.setVec3("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
		materialShader.setVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
		materialShader.setFloat("pointLights[0].constant", 1.0f);
		materialShader.setFloat("pointLights[0].linear", 0.09f);
		materialShader.setFloat("pointLights[0].quadratic", 0.032f);
		// ��� 2
		materialShader.setVec3("pointLights[1].position", pointLightPositions[1]);
		materialShader.setVec3("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
		materialShader.setVec3("pointLights[1].diffuse", 0.8f, 0.8f, 0.8f);
		materialShader.setVec3("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
		materialShader.setFloat("pointLights[1].constant", 1.0f);
		materialShader.setFloat("pointLights[1].linear", 0.09f);
		materialShader.setFloat("pointLights[1].quadratic", 0.032f);
		// ��� 3
		materialShader.setVec3("pointLights[2].position", pointLightPositions[2]);
		materialShader.setVec3("pointLights[2].ambient", 0.05f, 0.05f, 0.05f);
		materialShader.setVec3("pointLights[2].diffuse", 0.8f, 0.8f, 0.8f);
		materialShader.setVec3("pointLights[2].specular", 1.0f, 1.0f, 1.0f);
		materialShader.setFloat("pointLights[2].constant", 1.0f);
		materialShader.setFloat("pointLights[2].linear", 0.09f);
		materialShader.setFloat("pointLights[2].quadratic", 0.032f);
		// ��� 4
		materialShader.setVec3("pointLights[3].position", pointLightPositions[3]);
		materialShader.setVec3("pointLights[3].ambient", 0.05f, 0.05f, 0.05f);
		materialShader.setVec3("pointLights[3].diffuse", 0.8f, 0.8f, 0.8f);
		materialShader.setVec3("pointLights[3].specular", 1.0f, 1.0f, 1.0f);
		materialShader.setFloat("pointLights[3].constant", 1.0f);
		materialShader.setFloat("pointLights[3].linear", 0.09f);
		materialShader.setFloat("pointLights[3].quadratic", 0.032f);
		// �۹�
		materialShader.setVec3("spotLight.position", camera.Position);
		materialShader.setVec3("spotLight.direction", camera.Front);
		materialShader.setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
		materialShader.setVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
		materialShader.setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
		materialShader.setFloat("spotLight.constant", 1.0f);
		materialShader.setFloat("spotLight.linear", 0.09f);
		materialShader.setFloat("spotLight.quadratic", 0.032f);
		materialShader.setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
		materialShader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));

		// View / Projection
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)ScreenWidth / (float)ScreenHeight, 0.1f, 100.0f);
		glm::mat4 view = camera.GetViewMatrix();
		materialShader.setMat4("projection", projection);
		materialShader.setMat4("view", view);

		// Model
		glBindVertexArray(ordinaryCudeVAO);
		glm::mat4 model;
		for (unsigned int i = 0; i < 10; i++)
		{

			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			float angle = 20.0f * i;
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			materialShader.setMat4("model", model);

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		// ���ƹ�Դ
		lightShader.use();
		lightShader.setMat4("projection", projection);
		lightShader.setMat4("view", view);

		glBindVertexArray(lightCubeVAO);
		for (unsigned int i = 0; i < 4; i++)
		{
			model = glm::mat4(1.0f);
			model = glm::translate(model, pointLightPositions[i]);
			model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
			lightShader.setMat4("model", model);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &ordinaryCudeVAO);
	glDeleteVertexArrays(1, &lightCubeVAO);
	glDeleteBuffers(1, &VBO);

	glfwTerminate();
	return 0;
}
