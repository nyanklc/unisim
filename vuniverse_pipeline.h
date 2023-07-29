#pragma once

#include "vuniverse_device.h"

#include <string>
#include <vector>

namespace vuniverse
{
	struct PipelineConfigInfo
	{
		VkPipelineInputAssemblyStateCreateInfo inputAssemblyStateCreateInfo;
	};

	class VuniversePipeline
	{
	public:
		VuniversePipeline(VuniverseDevice* device, const std::string &vertFilePath, const std::string &fragFilePath, PipelineConfigInfo* configInfo);
	
		VuniversePipeline(const VuniversePipeline&) = delete;
		void operator=(const VuniversePipeline&) = delete;

		static PipelineConfigInfo defaultPipelineConfigInfo(uint32_t width, uint32_t height);

	private:
		static std::vector<char> readFile(const std::string &filePath);

		void createGraphicsPipeline(const std::string& vertFilePath, const std::string& fragFilePath, PipelineConfigInfo& configInfo);

		void createShaderModule(const std::vector<char>& code, VkShaderModule *shaderModule);

		VuniverseDevice& _device;
		VkPipeline _graphicsPipeline;
		VkShaderModule _vertShaderModule;
		VkShaderModule _fragShaderModule;
	};
}