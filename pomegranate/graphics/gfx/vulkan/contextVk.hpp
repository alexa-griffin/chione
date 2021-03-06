#pragma once

#include "base.hpp"

#include "../context.hpp"

#include "instanceVk.hpp"

#include "platform/window.hpp"

namespace pom::gfx {
    /// @addtogroup gfx
    /// @{

    struct SwapchainSupportDetailsVk {
        VkSurfaceCapabilitiesKHR capabilities;
        std::vector<VkSurfaceFormatKHR> formats;
        std::vector<VkPresentModeKHR> presentModes;
    };

    class POM_API ContextVk final : public Context {
    public:
        [[nodiscard]] inline GraphicsAPI getAPI() const final
        {
            return GraphicsAPI::VULKAN;
        }

        ~ContextVk() final;

        void recreateSwapchain(const maths::vec2& extent) final;

        void present() final;

    public:
        friend class Context;
        friend class InstanceVk;

        SwapchainSupportDetailsVk getSwapchainSupportDetails(VkPhysicalDevice device) const;

        ContextVk(InstanceVk* instance, Window* window);

        void createSwapchain(const VkExtent2D& extent, bool firstTime);

        void acquireNextSwapchainImage();

        POM_NOCOPY(ContextVk);

        InstanceVk* instance;
        VkSurfaceKHR surface;

        VkRenderPass swapchainRenderPass;
        VkSwapchainKHR swapchain;
        VkFormat swapchainImageFormat;
        VkExtent2D swapchainExtent;
        std::vector<VkImage> swapchainImages;
        std::vector<VkImageView> swapchainImageViews;
        std::vector<VkFramebuffer> swapchainFramebuffers;
        VkViewport swapchainViewport;
        u32 swapchainImageIndex = 0;

        static const u32 MAX_FRAMES_IN_FLIGHT = 1;

        VkSemaphore imageAvailableSemaphores[MAX_FRAMES_IN_FLIGHT];
        VkSemaphore renderFinishedSemaphores[MAX_FRAMES_IN_FLIGHT];
        VkFence inFlightFences[MAX_FRAMES_IN_FLIGHT];
        std::vector<VkFence> imagesInFlight;
        u32 frameIndex = 0;
    };

    /// @}
} // namespace pom::gfx