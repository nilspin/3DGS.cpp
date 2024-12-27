#ifndef VULKAN_SPLATTING_GRAPHICSPIPELINE_H
#define VULKAN_SPLATTING_GRAPHICSPIPELINE_H


#include "Pipeline.h"
#include <memory>
#include "../Shader.h"

class GraphicsPipeline : public Pipeline {
public:
    explicit GraphicsPipeline(const std::shared_ptr<VulkanContext> &context, std::shared_ptr<Shader> shader);;

    void build() override;
private:
    std::shared_ptr<Shader> shader;
};


#endif //VULKAN_SPLATTING_FRAGMENTPIPELINE_H
