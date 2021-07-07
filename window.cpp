#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Shader.h"
#include "stb_image.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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
	// ������Ȳ���
	glEnable(GL_DEPTH_TEST);

	// build and compile shader programe
	Shader ourShader("res/shaders/cubevert.vs" ,"res/shaders/cubefrag.fs");

	// ��һ������
	float verties[] = {
		// λ��				  // ��ɫ	          // �������꣨���ҷ�ת��
		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   0.0f, 1.0f, // ����
		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   0.0f, 0.0f, // ����
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   1.0f, 0.0f, // ����
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   1.0f, 1.0f  // ���� 
	};
	unsigned int indies[] = {
		0, 1, 3,
		1, 2, 3
	};
	// ������
	float cubeVertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

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
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indies), indies, GL_STATIC_DRAW);
	// A1/B3.���ö�������ָ��
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// �� VertexAttrib (Location 1): Color
	/*glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);*/
	// �� UV����
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// T1:����Texture����
	// Texture 1
	unsigned int texture1, texture2;
	glGenTextures(1, &texture1);
	// ������
	glBindTexture(GL_TEXTURE_2D, texture1);
	// T2:Texture Wrap Mode
	// GL_REPEAT��GL_MIRRORED_REPEAT��GL_CLAMP_TO_EDGE��GL_CLAMP_TO_BORDER
	// S��T��R���������3��ά�ȣ�����Texture 3D��
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	//float borderColor[] = { 1.0f, 1.0f, 0.0f, 1.0f };
	//glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

	// Texture Filter Mode
	// Nearest Neighbor Filtering��(Bi)linear Filtering
	// GL_NEAREST��GL_LINEAR��GL_NEAREST_MIPMAP_NEAREST��GL_LINEAR_MIPMAP_NEAREST��GL_NEAREST_MIPMAP_LINEAR��GL_LINEAR_MIPMAP_LINEAR
	// ����4�ֹ��˷�ʽ��ָMipmap��ͬ�༶��Զ������֮��Ĺ��˷�ʽ��ֻ��������С���������GL_TEXTURE_MIN_FILTER���Ż�������
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// T3:������������
	stbi_set_flip_vertically_on_load(true);	//ͼƬ��Y���ڶ�����OpenGL���ڵײ�������ǰ��Ҫflip_vertical
	
	int width, height, nrChannels;
	unsigned char* data = stbi_load("res/textures/container.jpg", &width, &height, &nrChannels, 0);
	if (data)
	{
		// ����GL����Target, mipmap Level, �洢��ʽ�����ߣ���Զ��0��ԭͼ��ʽ�������������ͣ��������ݣ�
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	// �ͷ����������ڴ�
	stbi_image_free(data);
	// Texture 2
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	data = stbi_load("res/textures/awesomeface.png", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	// �ͷ����������ڴ�
	stbi_image_free(data);

	ourShader.use(); 
	ourShader.setInt("texture1", 0);
	ourShader.setInt("texture2", 1);

	while (!glfwWindowShouldClose(window))
	{
		// input
		processInput(window);

		// render command
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		// Clear Color&Deepth Buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// �ڰ�����֮ǰ�ȼ�������Ԫ
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);

		

		// A2.��������Ⱦһ������ʱҪʹ����ɫ������
		ourShader.use();
		// ����Shader��uniformֵ,uniform��Shader��ȫ�ֱ���
		float timeValue = (float)glfwGetTime();
		
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
		projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / SCR_HEIGHT, 0.1f, 100.0f);
		ourShader.setMatrix4fv("view", glm::value_ptr(view));
		ourShader.setMatrix4fv("projection", glm::value_ptr(projection));
		

		// B4.��������
		glBindVertexArray(VAO);
		for (unsigned int i = 0; i < 10; i++)
		{
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			float angle = 20.0f * i;
			model = glm::rotate(model, glm::radians(angle), glm::vec3(0.5f, 1.0f, 0.4f));
			ourShader.setMatrix4fv("model", glm::value_ptr(model));
			glDrawArrays(GL_TRIANGLES, 0, 36);
			float alphaValue = (sin(timeValue + i) / 2.0f) + 0.5f;
			ourShader.setFloat("ourAlpha", alphaValue);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		
		// A3.��������
		// glDrawArrays(GL_TRIANGLES, 0, 3);
		// glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		
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