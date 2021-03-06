#pragma once
#include <map>
#include <functional>
#include "Renderer/ShaderProgram.h"

class ShaderManager
{
public:

	bool CreateShader(const std::string & ShaderProgramName, const std::string & VertexShaderFilename, const std::string & FragmentShaderFilename, size_t & ShaderProgramID);
	
	inline ShaderProgram & GetShader(const std::string & ShaderProgramName, bool & FoundShader)
	{
		std::size_t hash = std::hash<std::string>{}(ShaderProgramName);
		return GetShader(hash, FoundShader);
	}

	ShaderProgram & GetShader(size_t ShaderProgramID, bool & FoundShader);

	void UseProgram(size_t Program);

	static ShaderManager & GetShaderManager()
	{
		static ShaderManager Manager;
		return Manager;
	}

	std::function<void(size_t)> OnShaderAdded;

private:
	std::map<std::size_t, ShaderProgram> Shaders;
};

