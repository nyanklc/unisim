#pragma once

#include "vuniverse_window.h"

// std lib headers
#include <string>
#include <vector>

namespace vuniverse
{

    struct SwapChainSupportDetails
    {
        VkSurfaceCapabilitiesKHR capabilities;
        std::vector<VkSurfaceFormatKHR> formats;
        std::vector<VkPresentModeKHR> presentModes;
    };

    struct QueueFamilyIndices
    {
        uint32_t graphicsFamily;
        uint32_t presentFamily;
        bool graphicsFamilyHasValue = false;
        bool presentFamilyHasValue = false;
        bool isComplete() { return graphicsFamilyHasValue && presentFamilyHasValue; }
    };

    class VuniverseDevice
    {
    public:
#ifdef NDEBUG
        const bool enableValidationLayers = false;
#else
        const bool enableValidationLayers = true;
#endif

        VuniverseDevice(VuniverseWindow &window);
        ~VuniverseDevice();

        // Not copyable or movable
        VuniverseDevice(const VuniverseDevice&) = delete;
        void operator=(const VuniverseDevice&) = delete;
        VuniverseDevice(VuniverseDevice&&) = delete;
        VuniverseDevice &operator=(VuniverseDevice&&) = delete;

        VkCommandPool getCommandPool() { return _commandPool; }
        VkDevice device() { return _device; }
        VkSurfaceKHR surface() { return _surface; }
        VkQueue graphicsQueue() { return _graphicsQueue; }
        VkQueue presentQueue() { return _presentQueue; }

        SwapChainSupportDetails getSwapChainSupport() { return querySwapChainSupport(_physicalDevice); }
        uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
        QueueFamilyIndices findPhysicalQueueFamilies() { return findQueueFamilies(_physicalDevice); }
        VkFormat findSupportedFormat(
        const std::vector<VkFormat> &candidates, VkImageTiling tiling, VkFormatFeatureFlags features);

        // Buffer Helper Functions
        void createBuffer(
        VkDeviceSize size,
        VkBufferUsageFlags usage,
        VkMemoryPropertyFlags properties,
        VkBuffer &buffer,
        VkDeviceMemory &bufferMemory);
        VkCommandBuffer beginSingleTimeCommands();
        void endSingleTimeCommands(VkCommandBuffer commandBuffer);
        void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
        void copyBufferToImage(
        VkBuffer buffer, VkImage image, uint32_t width, uint32_t height, uint32_t layerCount);

        void createImageWithInfo(
        const VkImageCreateInfo &imageInfo,
        VkMemoryPropertyFlags properties,
        VkImage &image,
        VkDeviceMemory &imageMemory);

        VkPhysicalDeviceProperties properties;

    private:
        void createInstance();
        void setupDebugMessenger();
        void createSurface();
        void pickPhysicalDevice();
        void createLogicalDevice();
        void createCommandPool();

        // helper functions
        bool isDeviceSuitable(VkPhysicalDevice device);
        std::vector<const char *> getRequiredExtensions();
        bool checkValidationLayerSupport();
        QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
        void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT &createInfo);
        void hasGflwRequiredInstanceExtensions();
        bool checkDeviceExtensionSupport(VkPhysicalDevice device);
        SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);

        VkInstance _instance;
        VkDebugUtilsMessengerEXT _debugMessenger;
        VkPhysicalDevice _physicalDevice = VK_NULL_HANDLE;
        VuniverseWindow &_window;
        VkCommandPool _commandPool;

        VkDevice _device;
        VkSurfaceKHR _surface;
        VkQueue _graphicsQueue;
        VkQueue _presentQueue;

        const std::vector<const char *> _validationLayers = {"VK_LAYER_KHRONOS_validation"};
        const std::vector<const char *> _deviceExtensions = {VK_KHR_SWAPCHAIN_EXTENSION_NAME};
    };

}