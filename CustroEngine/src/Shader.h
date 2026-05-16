#pragma once

#include <glad/glad.h> // include glad to get all the required OpenGL headers
  
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "utils/String.h"

using namespace Engine;

class Shader
{
public:
	Shader(String vertexPath, String fragmentPath);
	
	void use();

	void setBoolean(const std::string& name, bool value) const;
	void setInteger(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;  
	void setVector2(const std::string& name, float x, float y) const;
	void setVector3(const std::string& name, float x, float y, float z) const;
	void setVector3(const std::string& name, glm::vec3 vec3) const;
	void setMatrix4(const std::string& name, glm::mat4 model) const;
	
	
	unsigned int ID;
};
