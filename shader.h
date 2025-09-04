#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class shader
{
public:
	unsigned int id;

	shader(const char* vertex_path, const char* fragment_path)
	{
		std::string vertexCode;
		std::string fragmentCode;
		std::ifstream vShaderFile;
		std::ifstream fShaderFile;

		vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

		try
		{
			vShaderFile.open(vertex_path);
			fShaderFile.open(fragment_path);

			std::stringstream vShaderStream, fShaderStream;

			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();

			vShaderFile.close();
			fShaderFile.close();

			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();
		}
		catch (std::ifstream::failure& e)
		{
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << std::endl;
		}

		const char* vShaderCode = vertexCode.c_str();
		const char* fShaderCode = fragmentCode.c_str();

		unsigned int vertex, fragment;

		vertex = glCreateShader(GL_VERTEX_SHADER);

		glShaderSource(vertex, 1, &vShaderCode, nullptr);
		glCompileShader(vertex);

		check_compile_errors(vertex, "VERTEX");

		fragment = glCreateShader(GL_FRAGMENT_SHADER);

		glShaderSource(fragment, 1, &fShaderCode, nullptr);
		glCompileShader(fragment);

		check_compile_errors(fragment, "FRAGMENT");

		id = glCreateProgram();

		glAttachShader(id, vertex);
		glAttachShader(id, fragment);

		glLinkProgram(id);

		check_compile_errors(id, "PROGRAM");

		glDeleteShader(vertex);
		glDeleteShader(fragment);

	}

	void use() const
	{
		glUseProgram(id);
	}

	void set_bool(const std::string& name, const bool value) const
	{
		glUniform1i(glGetUniformLocation(id, name.c_str()), static_cast<int>(value));
	}

	void set_int(const std::string& name, const int value) const
	{
		glUniform1i(glGetUniformLocation(id, name.c_str()), value);
	}

	void set_float(const std::string& name, const float value) const
	{
		glUniform1f(glGetUniformLocation(id, name.c_str()), value);
	}

	void set_vec2(const std::string& name, const glm::vec2& value) const
	{
		glUniform2fv(glGetUniformLocation(id, name.c_str()), 1, &value[0]);
	}

	void set_vec2(const std::string& name, const float x, const float y) const
	{
		glUniform2f(glGetUniformLocation(id, name.c_str()), x, y);
	}

	void set_vec3(const std::string& name, const glm::vec3& value) const
	{
		glUniform3fv(glGetUniformLocation(id, name.c_str()), 1, &value[0]);
	}

	void set_vec3(const std::string& name, const float x, const float y, const float z) const
	{
		glUniform3f(glGetUniformLocation(id, name.c_str()), x, y, z);
	}

	void set_vec4(const std::string& name, const glm::vec4& value) const
	{
		glUniform4fv(glGetUniformLocation(id, name.c_str()), 1, &value[0]);
	}

	void set_vec4(const std::string& name, const float x, const float y, const float z, const float w) const
	{
		glUniform4f(glGetUniformLocation(id, name.c_str()), x, y, z, w);
	}

	void set_mat2(const std::string& name, const glm::mat2& mat) const
	{
		glUniformMatrix2fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}

	void set_mat3(const std::string& name, const glm::mat3& mat) const
	{
		glUniformMatrix3fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}

	void set_mat4(const std::string& name, const glm::mat4& mat) const
	{
		glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}

private:
	static void check_compile_errors(const GLuint shader, const std::string& type)
	{
		GLint success;
		GLchar infoLog[1024];

		if (type != "PROGRAM")
		{
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

			if (!success)
			{
				glGetShaderInfoLog(shader, 1024, nullptr, infoLog);

				std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n"
				<< infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
			}
		}
		else
		{
			glGetProgramiv(shader, GL_LINK_STATUS, &success);

			if (!success)
			{
				glGetProgramInfoLog(shader, 1024, nullptr, infoLog);

				std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n"
				<< infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
			}
		}
	}
};
#endif