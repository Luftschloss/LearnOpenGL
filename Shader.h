#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
public:
	// Shader Program ID
	signed int ID;

	Shader(const GLchar* vertexPath, const GLchar* fragmentPath, const char* geometryPath = nullptr)
	{
		// 1. 从文件路径中获取顶点/片段着色器
		std::string vertexCode;
		std::string fragmentCode;
		std::string geometryCode;
		std::ifstream vertShaderFile;
		std::ifstream fragShaderFile;
		std::ifstream geomShaderFile;
		// 保证ifstream对象可以抛出异常：
		vertShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fragShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		geomShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try
		{
			// 打开文件
			vertShaderFile.open(vertexPath);
			fragShaderFile.open(fragmentPath);
			std::stringstream vertShaderStream, fragShaderStream;
			//读取文件到数据流
			vertShaderStream << vertShaderFile.rdbuf();
			fragShaderStream << fragShaderFile.rdbuf();
			//关闭文件处理器
			vertShaderFile.close();
			fragShaderFile.close();
			//转化数据流到string
			vertexCode = vertShaderStream.str();
			fragmentCode = fragShaderStream.str();

			if (geometryPath != nullptr)
			{
				geomShaderFile.open(geometryPath);
				std::stringstream gShaderStream;
				gShaderStream << geomShaderFile.rdbuf();
				geomShaderFile.close();
				geometryCode = gShaderStream.str();
			}
		}
		catch (std::ifstream::failure e)
		{
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
		}
		// 2. compile shaders
		const char* vShaderCode = vertexCode.c_str();
		const char* fShaderCode = fragmentCode.c_str();
		unsigned int vertex, fragment;
		// vertex shader
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vShaderCode, NULL);
		glCompileShader(vertex);
		checkCompileErrors(vertex, "VERTEX");
		// fragment Shader
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fShaderCode, NULL);
		glCompileShader(fragment);
		checkCompileErrors(fragment, "FRAGMENT");
		// geomtry Shader
		unsigned int geometry;
		if (geometryPath != nullptr)
		{
			const char* gShaderCode = geometryCode.c_str();
			geometry = glCreateShader(GL_GEOMETRY_SHADER);
			glShaderSource(geometry, 1, &gShaderCode, NULL);
			glCompileShader(geometry);
			checkCompileErrors(geometry, "GEOMETRY");
		}
		// shader Program
		ID = glCreateProgram();
		glAttachShader(ID, vertex);
		glAttachShader(ID, fragment);
		if (geometryPath != nullptr)
			glAttachShader(ID, geometry);
		glLinkProgram(ID);
		checkCompileErrors(ID, "PROGRAM");
		// delete the shaders as they're linked into our program now and no longer necessary
		glDeleteShader(vertex);
		glDeleteShader(fragment);
		if (geometryPath != nullptr)
			glDeleteShader(geometry);
	}

	void use()
	{
		glUseProgram(ID);
	}

	void setBool(const std::string& name, bool value) const
	{
		glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
	}
	void setInt(const std::string& name, int value) const
	{
		glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
	}
	void setFloat(const std::string& name, float value) const
	{
		glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
	}
	void setVec2(const std::string& name, float x, float y)
	{
		glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
	}
	void setVec2(const std::string& name, glm::vec2 &vec)
	{
		glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &vec[0]);
	}
	void setVec3(const std::string& name, float x, float y, float z)
	{
		glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
	}
	void setVec3(const std::string& name, glm::vec3 &vec)
	{
		glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &vec[0]);
	}
	void setVec4(const std::string& name, float v0, float v1, float v2, float v3) const
	{
		glUniform4f(glGetUniformLocation(ID, name.c_str()), v0, v1, v2, v3);
	}
	void setVec4(const std::string& name, glm::vec4 &vec) const
	{
		glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &vec[0]);
	}
	void setMat2(const std::string& name, const glm::mat2 &mat) const
	{
		glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
	}
	void setMat3(const std::string& name, const glm::mat3 &mat) const
	{
		glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
	}
	void setMat4(const std::string& name, const glm::mat4 &mat) const
	{
		glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
	}

private:
	int success;
	char infoLog[1024];
	// utility function for checking shader compilation/linking errors.
	void checkCompileErrors(unsigned int shader, std::string type)
	{
		if (type != "PROGRAM")
		{
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(shader, 1024, NULL, infoLog);
				std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
			}
		}
		else
		{
			glGetProgramiv(shader, GL_LINK_STATUS, &success);
			if (!success)
			{
				glGetProgramInfoLog(shader, 1024, NULL, infoLog);
				std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
			}
		}
	}
};

#endif