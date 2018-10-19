#ifndef SHADER_PROGRAM
#define SHADER_PROGRAM

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>

class ShaderProgram
{
public:
	ShaderProgram() {}
	~ShaderProgram() {}

	void init(const std::string& vertexFile, const std::string& fragmentFile);
	void start();
	void stop();
	void cleanUp();

	std::string getVertexFile() const { return VERTEX_FILE; }
	std::string getFragmentFile() const { return FRAGMENT_FILE; }

protected:
	GLuint getUniformLocation(std::string name);
	void bindAttribute(int attrib, std::string name);
	void loadMatrix4f(int location, glm::mat4 matrix);

	virtual void bindAttributes() = 0;
	virtual void getUniformLocations() = 0;

	std::string VERTEX_FILE, FRAGMENT_FILE;

private:
	GLuint _programID;
	GLuint _vertexShaderID, _fragmentShaderID;

	GLuint loadShader(const std::string& file, GLuint type);
};

#endif  //SHADER_PROGRAM