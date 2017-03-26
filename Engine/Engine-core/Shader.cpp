#include "Shader.h"
#include "Utils.h"



Engine::Graphics::Shader::Shader(const char * vertFile, const char * fragFile):vertPath(vertFile),fragPath(fragFile)
{
	this->program_id = load();
}

Engine::Graphics::Shader::~Shader()
{
	glDeleteProgram(program_id);
}

GLuint Engine::Graphics::Shader::load()
{
	GLuint program = glCreateProgram();
	GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);

	
	std::string vertSourcestr = Utils::read_f(vertPath);
	std::string fragSourcestr = Utils::read_f(fragPath);

	const char * vertSource = vertSourcestr.c_str();
	const char * fragSource = fragSourcestr.c_str();

	glShaderSource(vertex, 1, &vertSource, nullptr);
	glCompileShader(vertex);
	std::cout << *vertSource << std::endl;
	GLint result;
	GLint length;
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		GLint length;
		glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &length);
		std::vector<char> error(length);
		glGetShaderInfoLog(vertex, length, &length, &error[0]);
		std::cout << &error[0] << std::endl;
		
	}
	glShaderSource(fragment, 1, &fragSource, nullptr);
	glCompileShader(fragment);

	glGetShaderiv(fragment, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		
		glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &length);
		std::vector<char> error(length);
		glGetShaderInfoLog(fragment, length, &length, &error[0]);
		std::cout << &error[0] << std::endl;
		
	}
	
	glAttachShader(program, fragment);
	glAttachShader(program, vertex);
	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &result);
	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
	if (length > 0) {
		std::vector<char> error(length + 1);
		glGetProgramInfoLog(program, length, NULL, &error[0]);
		printf("%s\n", &error[0]);
	}
	
	glDetachShader(program, fragment);
	glDetachShader(program, vertex);
	glDeleteShader(fragment);
	glDeleteShader(vertex);


	return program;
}

void Engine::Graphics::Shader::enable()
{
	glUseProgram(program_id);
}

void Engine::Graphics::Shader::disable()
{
	glUseProgram(0);
}

void Engine::Graphics::Shader::setUniformMat4(const char * name, Math::Mat4f& matrix)
{
	glUniformMatrix4fv(glGetUniformLocation(program_id, name), 1, GL_FALSE, matrix.values);
	
}


