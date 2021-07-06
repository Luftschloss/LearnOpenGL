#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Shader.h"

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
	// glfw:initialize and configure
	glfwInit();
	// Set OpenGL Version: 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Set OpenGL Core
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// glfw window creation
	GLFWwindow *window = glfwCreateWindow(800, 600, "Learn OpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Faild to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Faild to initialize GLAD" << std::endl;
		return -1;
	}	

	// �߿�ģʽ
	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	// Ĭ��ģʽ
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// build and compile shader programe
	Shader ourShader("shaders/vert1.vs" ,"shaders/frag1.fs");

	// ��һ��������
	float verties[] = {
			// λ��              // ��ɫ
		0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // ����
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // ����
		0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // ����
	};
	unsigned int indies[] = {
		0,1,2
	};

	// VBO(Vertex Buffer Obejct)�󶨵���������A��˳��
	// VAO(Vertex Array Object)�󶨵���������B��˳��
	unsigned int VBO, VAO, EBO;
	// �������㻺�����
	glGenBuffers(1, &VBO);
	// ���������������
	glGenBuffers(1, &EBO);
	// ���������������
	glGenVertexArrays(1, &VAO);
	
	// B0. ��ʼ�����루ֻ����һ�� (�����������Ƶ���ı�)��
	// B1. ��VAO
	glBindVertexArray(VAO);
	// A0/B2.���ƶ������鵽�����й�OpenGLʹ��
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verties), verties, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indies), indies, GL_STATIC_DRAW);
	// A1/B3.���ö�������ָ��
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// �� VertexAttrib (Location 1): Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	while (!glfwWindowShouldClose(window))
	{
		// input
		processInput(window);

		// render command
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// A2.��������Ⱦһ������ʱҪʹ����ɫ������
		ourShader.use();

		// ����Shader��uniformֵ,uniform��Shader��ȫ�ֱ���
		float timeValue = glfwGetTime();
		float alphaValue = (sin(timeValue) / 2.0f) + 0.5f;
		ourShader.setFloat("ourAlpha", alphaValue);
		
		// B4.��������
		glBindVertexArray(VAO);
		// A3.��������
		// glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0); // no need to unbind it every time 
		
		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// optional: de-allocate all resources once they've outlived their purpose:
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}