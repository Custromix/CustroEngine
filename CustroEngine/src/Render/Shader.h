#pragma once

#include <glad/glad.h> // include glad to get all the required OpenGL headers
  
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "types.hpp"
#include "utils/String.h"

using namespace Engine;

class Shader
{
public:
	Shader(const String& shaderPath, const String& shaderName);

	static void setBoolean(uint32 ProgramID, const std::string& name, bool value);
	static void setInteger(uint32 ProgramID, const std::string& name, int value);
	static void setFloat(uint32 ProgramID, const std::string& name, float value);  
	static void setVector2(uint32 ProgramID, const std::string& name, float x, float y);
	static void setVector3(uint32 ProgramID, const std::string& name, float x, float y, float z);
	static void setVector3(uint32 ProgramID, const std::string& name, glm::vec3 vec3);
	static void setMatrix4(uint32 ProgramID, const std::string& name, glm::mat4 model);
	
	String ShaderCode;
	
	String Name;
};
