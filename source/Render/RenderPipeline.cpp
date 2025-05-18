#include "RenderPipeline.h"

#include <fstream>
#include <Logger.h>

SDLPG::Render::RenderPipeline::RenderPipeline(const std::string& vertFilepath,
	const std::string& fragFilepath)
{
	CreateGraphicsPipeline(vertFilepath, fragFilepath);
}

std::vector<char> SDLPG::Render::RenderPipeline::ReadFile(const std::string& filepath)
{
	std::ifstream file{filepath, std::ios::ate | std::ios::binary};

	if (!file.is_open())
	{
		SDLPG_LOG_ERROR << "[RenderPipeline::ReadFile] Failed to open file: " << filepath;
		{
			return {};
		}
	}

	size_t fileSize = static_cast<size_t>(file.tellg());
	std::vector<char> buffer(fileSize);

	// Read the data into the buffer
	file.seekg(0);
	file.read(buffer.data(), fileSize);
	file.close();
	return buffer;
}

void SDLPG::Render::RenderPipeline::CreateGraphicsPipeline(const std::string& vertFilepath,
	const std::string& fragFilepath)
{
	auto vertCode = ReadFile(vertFilepath);
	auto fragCode = ReadFile(fragFilepath);

	SDLPG_LOG_INFO << "Vertex shader code size: " << vertCode.size();
	SDLPG_LOG_INFO << "Fragment shader code size: " << fragCode.size();
}