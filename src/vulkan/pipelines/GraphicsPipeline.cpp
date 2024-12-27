

#include "GraphicsPipeline.h"

GraphicsPipeline::GraphicsPipeline(const std::shared_ptr<VulkanContext>& context, std::shared_ptr<Shader> shader): Pipeline(context), shader(std::move(shader)) {
    this->shader->load();
}

void GraphicsPipeline::build() {
    buildPipelineLayout();

    //define a renderpass
    vk::RenderPass renderpass;
    vk::Pipeline vkpipeline;
    //define a pipeline state object
    uint32_t num_stages = 2;
    vk::PipelineCreateFlagBits tmp = {};
    vk::PipelineCreateFlags pipeline_create_flags = {};
    vk::PipelineStageFlags pipeline_stage_flags = {};
    vk::PipelineShaderStageCreateInfo shader_stage({}, vk::ShaderStageFlagBits::eAllGraphics, shader->shader.get(), "main");
    vk::PipelineVertexInputStateCreateInfo vertex_input_state = {};
    vk::PipelineInputAssemblyStateCreateInfo input_assembly_state({}, vk::PrimitiveTopology::eTriangleList, false);
    vk::PipelineTessellationStateCreateInfo tessellation_state = {};
    vk::PipelineViewportStateCreateInfo viewport_state({}, 1, nullptr, 1, nullptr);
    vk::PipelineRasterizationStateCreateInfo rasterization_state = {};
    vk::PipelineMultisampleStateCreateInfo multisample_state({}, vk::SampleCountFlagBits::e1);
    vk::PipelineDepthStencilStateCreateInfo depth_stencil_state({}, false, false, vk::CompareOp::eAlways, {}, {}, {}, { {}, {}, {}, vk::CompareOp::eAlways });
    vk::PipelineColorBlendStateCreateInfo color_blend_state = {};
    vk::PipelineDynamicStateCreateInfo dynamic_state = {};
   
    vk::GraphicsPipelineCreateInfo graphicsPipelineCreateInfo = { pipeline_create_flags,num_stages,
                                                              &shader_stage,
                                                              &vertex_input_state,
                                                              &input_assembly_state,
                                                              nullptr,
                                                              &viewport_state,
                                                              &rasterization_state,
                                                              &multisample_state,
                                                              &depth_stencil_state,
                                                              &color_blend_state,
                                                              &dynamic_state,
                                                              pipelineLayout.get(),
                                                              renderpass,2,vkpipeline,0,nullptr };
    pipeline = context->device->createGraphicsPipelineUnique(nullptr, graphicsPipelineCreateInfo).value;
}
