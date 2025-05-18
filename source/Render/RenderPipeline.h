#pragma once

#include <string>
#include <vector>

#include "Export.h"

namespace LV::Render
{
	class SDLPG_RENDER_API RenderPipeline
	{
	public:
		RenderPipeline(const std::string& vertFilePath, const std::string& fragFilepath);

	private:
		static std::vector<char> ReadFile(const std::string& filepath);

		void CreateGraphicsPipeline(const std::string& verFilepath, const std::string& fragFilepath);
	};
} // namespace LV::Render