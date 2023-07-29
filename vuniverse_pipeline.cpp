#include "vuniverse_pipeline.h"

#include <fstream>
#include <iostream>
#include <stdexcept>

vuniverse::VuniversePipeline::VuniversePipeline(VuniverseDevice* device, const std::string& vertFilePath, const std::string& fragFilePath, PipelineConfigInfo* configInfo)
	: _device(*device)
{	
	createGraphicsPipeline(vertFilePath, fragFilePath, *configInfo);
}

vuniverse::PipelineConfigInfo vuniverse::VuniversePipeline::defaultPipelineConfigInfo(uint32_t width, uint32_t height)
{
	PipelineConfigInfo configInfo;

	configInfo.inputAssemblyStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
	configInfo.inputAssemblyStateCreateInfo.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
	configInfo.inputAssemblyStateCreateInfo.primitiveRestartEnable = VK_FALSE;

	return configInfo;
}

std::vector<char> vuniverse::VuniversePipeline::readFile(const std::string& filePath)
{
	std::ifstream file(filePath, std::ios::ate | std::ios::binary);

	if (!file.is_open())
	{
		std::cerr << "couldn't open file " << filePath << std::endl;
		throw std::runtime_error("couldn't open file " + filePath);
	}

	size_t fileSize = static_cast<size_t>(file.tellg());
	std::vector<char> buffer(fileSize);

	file.seekg(0);
	file.read(buffer.data(), fileSize);

	file.close();
	return buffer;
}

void vuniverse::VuniversePipeline::createGraphicsPipeline(const std::string& vertFilePath, const std::string& fragFilePath, PipelineConfigInfo& configInfo)
{
	auto vertCode = readFile(vertFilePath);
	auto fragCode = readFile(fragFilePath);

	std::cout << "vertCode size: " << vertCode.size() << '\n';
	std::cout << "fragCode size: " << fragCode.size() << '\n';
}

void vuniverse::VuniversePipeline::createShaderModule(const std::vector<char>& code, VkShaderModule* shaderModule)
{
	VkShaderModuleCreateInfo createInfo;
	createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	createInfo.codeSize = code.size();
	createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());

	if (vkCreateShaderModule(_device.device(), &createInfo, nullptr, shaderModule) != VK_SUCCESS)
	{
		throw std::runtime_error("failed to create shader module");
	}
}
