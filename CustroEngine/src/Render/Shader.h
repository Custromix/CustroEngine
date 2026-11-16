#pragma once

#include <glad/glad.h>
  
#include <string>
#include <iostream>
#include <map>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "types.hpp"
#include "utils/String.h"

class Material;

using namespace Engine;

class Shader
{
public:
	Shader();
	Shader(const String shaderPath, const String shaderName, uint32 programID);
	~Shader();
	
	void setBoolean(const std::string& name, bool value);
	void setInteger(const std::string& name, int value);
	void setFloat(const std::string& name, float value);  
	void setVector2(const std::string& name, float x, float y);
	void setVector3(const std::string& name, float x, float y, float z);
	void setVector3(const std::string& name, glm::vec3 vec3);
	void setMatrix4(const std::string& name, glm::mat4 model);
	void setMatrix4(int32 location, glm::mat4 model);
	
	void setTexture(const String& name, uint32 slot);
	
	void Subscribe(Material* mat);
	void UnSubscribe(Material* mat);
	
	String GetShaderCode()		{	return ShaderCode;	}
	String GetName()			{	return Name;		}
	uint32 GetProgramID() const {	return ProgramID;	}
	
	const std::vector<Material*>& GetMyMaterials() const { return MyMaterials; }
	
	static Shader* GetShaderByName(const String name);
	
private:
	
	String ShaderCode;
	String Name;
	uint32 ProgramID;
	
	std::vector<Material*> MyMaterials;
	
	static std::map<const String, Shader*> AllShadersMap;
};
