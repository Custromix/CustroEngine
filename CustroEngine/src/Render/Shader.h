#pragma once

#include <glad/glad.h>
  
#include <string>
#include <iostream>
#include <map>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Texture.h"
#include "types.hpp"
#include "utils/String.h"

using namespace Engine;

class Shader
{
public:
	Shader(const String shaderPath, const String shaderName);
	
	std::vector<Texture*> GetTextures() const { return textures; }

	void setBoolean(const std::string& name, bool value);
	void setInteger(const std::string& name, int value);
	void setFloat(const std::string& name, float value);  
	void setVector2(const std::string& name, float x, float y);
	void setVector3(const std::string& name, float x, float y, float z);
	void setVector3(const std::string& name, glm::vec3 vec3);
	void setMatrix4(const std::string& name, glm::mat4 model);
	
	void SetTexture(Texture* texture, String TextureName);
	
	static Shader* GetShaderByName(const String name);
	
	String ShaderCode;
	
	String Name;
	
	uint32 ProgramID;
	
	static std::map<const String, Shader*> AllShadersMap;
	
private:
	std::vector<Texture*> textures;
};
