#ifndef LWSDLGL_GPU_H
#define LWSDLGL_GPU_H

#include <SDL3/SDL.h>
#include <SDL3/SDL_gpu.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct LwsdlglGPUAPI {
    SDL_GPUDevice *(*createDevice)(SDL_GPUShaderFormat formats, bool debugMode, const char *driverName);
    SDL_GPUDevice *(*createDeviceWithProperties)(SDL_PropertiesID props);
    void (*destroyDevice)(SDL_GPUDevice *device);
    int (*getDriverCount)(void);
    const char *(*getDriver)(int index);
    const char *(*getDeviceDriver)(SDL_GPUDevice *device);
    SDL_GPUShaderFormat (*getShaderFormats)(SDL_GPUDevice *device);
    bool (*supportsShaderFormats)(SDL_GPUShaderFormat formats, const char *driverName);
    bool (*supportsProperties)(SDL_PropertiesID props);
    SDL_PropertiesID (*getDeviceProperties)(SDL_GPUDevice *device);

    bool (*claimWindow)(SDL_GPUDevice *device, SDL_Window *window);
    void (*releaseWindow)(SDL_GPUDevice *device, SDL_Window *window);
    SDL_GPUTextureFormat (*getSwapchainTextureFormat)(SDL_GPUDevice *device, SDL_Window *window);
    bool (*setSwapchainParameters)(SDL_GPUDevice *device, SDL_Window *window, SDL_GPUSwapchainComposition composition, SDL_GPUPresentMode presentMode);
    bool (*windowSupportsPresentMode)(SDL_GPUDevice *device, SDL_Window *window, SDL_GPUPresentMode presentMode);
    bool (*windowSupportsSwapchainComposition)(SDL_GPUDevice *device, SDL_Window *window, SDL_GPUSwapchainComposition composition);
    bool (*waitForSwapchain)(SDL_GPUDevice *device, SDL_Window *window);

    SDL_GPUBuffer *(*createBuffer)(SDL_GPUDevice *device, const SDL_GPUBufferCreateInfo *info);
    SDL_GPUTransferBuffer *(*createTransferBuffer)(SDL_GPUDevice *device, const SDL_GPUTransferBufferCreateInfo *info);
    SDL_GPUTexture *(*createTexture)(SDL_GPUDevice *device, const SDL_GPUTextureCreateInfo *info);
    SDL_GPUSampler *(*createSampler)(SDL_GPUDevice *device, const SDL_GPUSamplerCreateInfo *info);
    SDL_GPUShader *(*createShader)(SDL_GPUDevice *device, const SDL_GPUShaderCreateInfo *info);
    SDL_GPUGraphicsPipeline *(*createGraphicsPipeline)(SDL_GPUDevice *device, const SDL_GPUGraphicsPipelineCreateInfo *info);
    SDL_GPUComputePipeline *(*createComputePipeline)(SDL_GPUDevice *device, const SDL_GPUComputePipelineCreateInfo *info);
    void (*releaseBuffer)(SDL_GPUDevice *device, SDL_GPUBuffer *buffer);
    void (*releaseTransferBuffer)(SDL_GPUDevice *device, SDL_GPUTransferBuffer *buffer);
    void (*releaseTexture)(SDL_GPUDevice *device, SDL_GPUTexture *texture);
    void (*releaseSampler)(SDL_GPUDevice *device, SDL_GPUSampler *sampler);
    void (*releaseShader)(SDL_GPUDevice *device, SDL_GPUShader *shader);
    void (*releaseGraphicsPipeline)(SDL_GPUDevice *device, SDL_GPUGraphicsPipeline *pipeline);
    void (*releaseComputePipeline)(SDL_GPUDevice *device, SDL_GPUComputePipeline *pipeline);
    void (*releaseFence)(SDL_GPUDevice *device, SDL_GPUFence *fence);

    void *(*mapTransferBuffer)(SDL_GPUDevice *device, SDL_GPUTransferBuffer *buffer, bool cycle);
    void (*unmapTransferBuffer)(SDL_GPUDevice *device, SDL_GPUTransferBuffer *buffer);

    SDL_GPUCommandBuffer *(*acquireCommandBuffer)(SDL_GPUDevice *device);
    bool (*cancelCommandBuffer)(SDL_GPUCommandBuffer *commandBuffer);
    bool (*submitCommandBuffer)(SDL_GPUCommandBuffer *commandBuffer);
    SDL_GPUFence *(*submitCommandBufferAndAcquireFence)(SDL_GPUCommandBuffer *commandBuffer);
    bool (*queryFence)(SDL_GPUDevice *device, SDL_GPUFence *fence);
    bool (*waitForFences)(SDL_GPUDevice *device, bool waitAll, SDL_GPUFence *const *fences, Uint32 count);
    bool (*waitForIdle)(SDL_GPUDevice *device);
    bool (*setAllowedFramesInFlight)(SDL_GPUDevice *device, Uint32 frames);

    bool (*acquireSwapchainTexture)(SDL_GPUCommandBuffer *commandBuffer, SDL_Window *window, SDL_GPUTexture **texture, Uint32 *width, Uint32 *height);
    bool (*waitAndAcquireSwapchainTexture)(SDL_GPUCommandBuffer *commandBuffer, SDL_Window *window, SDL_GPUTexture **texture, Uint32 *width, Uint32 *height);

    SDL_GPURenderPass *(*beginRenderPass)(SDL_GPUCommandBuffer *commandBuffer, const SDL_GPUColorTargetInfo *colors, Uint32 colorCount, const SDL_GPUDepthStencilTargetInfo *depthStencil);
    void (*endRenderPass)(SDL_GPURenderPass *pass);
    SDL_GPUComputePass *(*beginComputePass)(SDL_GPUCommandBuffer *commandBuffer, const SDL_GPUStorageTextureReadWriteBinding *textures, Uint32 textureCount, const SDL_GPUStorageBufferReadWriteBinding *buffers, Uint32 bufferCount);
    void (*endComputePass)(SDL_GPUComputePass *pass);
    SDL_GPUCopyPass *(*beginCopyPass)(SDL_GPUCommandBuffer *commandBuffer);
    void (*endCopyPass)(SDL_GPUCopyPass *pass);

    void (*bindGraphicsPipeline)(SDL_GPURenderPass *pass, SDL_GPUGraphicsPipeline *pipeline);
    void (*bindVertexBuffers)(SDL_GPURenderPass *pass, Uint32 firstSlot, const SDL_GPUBufferBinding *bindings, Uint32 count);
    void (*bindIndexBuffer)(SDL_GPURenderPass *pass, const SDL_GPUBufferBinding *binding, SDL_GPUIndexElementSize indexSize);
    void (*bindVertexSamplers)(SDL_GPURenderPass *pass, Uint32 firstSlot, const SDL_GPUTextureSamplerBinding *bindings, Uint32 count);
    void (*bindFragmentSamplers)(SDL_GPURenderPass *pass, Uint32 firstSlot, const SDL_GPUTextureSamplerBinding *bindings, Uint32 count);
    void (*bindVertexStorageTextures)(SDL_GPURenderPass *pass, Uint32 firstSlot, SDL_GPUTexture *const *textures, Uint32 count);
    void (*bindFragmentStorageTextures)(SDL_GPURenderPass *pass, Uint32 firstSlot, SDL_GPUTexture *const *textures, Uint32 count);
    void (*bindVertexStorageBuffers)(SDL_GPURenderPass *pass, Uint32 firstSlot, SDL_GPUBuffer *const *buffers, Uint32 count);
    void (*bindFragmentStorageBuffers)(SDL_GPURenderPass *pass, Uint32 firstSlot, SDL_GPUBuffer *const *buffers, Uint32 count);
    void (*setViewport)(SDL_GPURenderPass *pass, const SDL_GPUViewport *viewport);
    void (*setScissor)(SDL_GPURenderPass *pass, const SDL_Rect *scissor);
    void (*setBlendConstants)(SDL_GPURenderPass *pass, SDL_FColor constants);
    void (*setStencilReference)(SDL_GPURenderPass *pass, Uint8 reference);
    void (*drawPrimitives)(SDL_GPURenderPass *pass, Uint32 vertexCount, Uint32 instanceCount, Uint32 firstVertex, Uint32 firstInstance);
    void (*drawIndexedPrimitives)(SDL_GPURenderPass *pass, Uint32 indexCount, Uint32 instanceCount, Uint32 firstIndex, Sint32 vertexOffset, Uint32 firstInstance);
    void (*drawPrimitivesIndirect)(SDL_GPURenderPass *pass, SDL_GPUBuffer *buffer, Uint32 offset, Uint32 drawCount);
    void (*drawIndexedPrimitivesIndirect)(SDL_GPURenderPass *pass, SDL_GPUBuffer *buffer, Uint32 offset, Uint32 drawCount);

    void (*bindComputePipeline)(SDL_GPUComputePass *pass, SDL_GPUComputePipeline *pipeline);
    void (*bindComputeSamplers)(SDL_GPUComputePass *pass, Uint32 firstSlot, const SDL_GPUTextureSamplerBinding *bindings, Uint32 count);
    void (*bindComputeStorageTextures)(SDL_GPUComputePass *pass, Uint32 firstSlot, SDL_GPUTexture *const *textures, Uint32 count);
    void (*bindComputeStorageBuffers)(SDL_GPUComputePass *pass, Uint32 firstSlot, SDL_GPUBuffer *const *buffers, Uint32 count);
    void (*dispatchCompute)(SDL_GPUComputePass *pass, Uint32 groupCountX, Uint32 groupCountY, Uint32 groupCountZ);
    void (*dispatchComputeIndirect)(SDL_GPUComputePass *pass, SDL_GPUBuffer *buffer, Uint32 offset);

    void (*pushVertexUniformData)(SDL_GPUCommandBuffer *commandBuffer, Uint32 slot, const void *data, Uint32 length);
    void (*pushFragmentUniformData)(SDL_GPUCommandBuffer *commandBuffer, Uint32 slot, const void *data, Uint32 length);
    void (*pushComputeUniformData)(SDL_GPUCommandBuffer *commandBuffer, Uint32 slot, const void *data, Uint32 length);

    void (*uploadToBuffer)(SDL_GPUCopyPass *pass, const SDL_GPUTransferBufferLocation *source, const SDL_GPUBufferRegion *destination, bool cycle);
    void (*uploadToTexture)(SDL_GPUCopyPass *pass, const SDL_GPUTextureTransferInfo *source, const SDL_GPUTextureRegion *destination, bool cycle);
    void (*downloadFromBuffer)(SDL_GPUCopyPass *pass, const SDL_GPUBufferRegion *source, const SDL_GPUTransferBufferLocation *destination);
    void (*downloadFromTexture)(SDL_GPUCopyPass *pass, const SDL_GPUTextureRegion *source, const SDL_GPUTextureTransferInfo *destination);
    void (*copyBufferToBuffer)(SDL_GPUCopyPass *pass, const SDL_GPUBufferLocation *source, const SDL_GPUBufferLocation *destination, Uint32 size, bool cycle);
    void (*copyTextureToTexture)(SDL_GPUCopyPass *pass, const SDL_GPUTextureLocation *source, const SDL_GPUTextureLocation *destination, Uint32 width, Uint32 height, Uint32 depth, bool cycle);
    void (*blitTexture)(SDL_GPUCommandBuffer *commandBuffer, const SDL_GPUBlitInfo *info);
    void (*generateMipmaps)(SDL_GPUCommandBuffer *commandBuffer, SDL_GPUTexture *texture);

    bool (*textureSupportsFormat)(SDL_GPUDevice *device, SDL_GPUTextureFormat format, SDL_GPUTextureType type, SDL_GPUTextureUsageFlags usage);
    bool (*textureSupportsSampleCount)(SDL_GPUDevice *device, SDL_GPUTextureFormat format, SDL_GPUSampleCount sampleCount);
    Uint32 (*textureFormatTexelBlockSize)(SDL_GPUTextureFormat format);
    Uint32 (*calculateTextureFormatSize)(SDL_GPUTextureFormat format, Uint32 width, Uint32 height, Uint32 depth);
    SDL_PixelFormat (*getPixelFormatFromTextureFormat)(SDL_GPUTextureFormat format);
    SDL_GPUTextureFormat (*getTextureFormatFromPixelFormat)(SDL_PixelFormat format);

    void (*setBufferName)(SDL_GPUDevice *device, SDL_GPUBuffer *buffer, const char *name);
    void (*setTextureName)(SDL_GPUDevice *device, SDL_GPUTexture *texture, const char *name);
    void (*insertDebugLabel)(SDL_GPUCommandBuffer *commandBuffer, const char *text);
    void (*pushDebugGroup)(SDL_GPUCommandBuffer *commandBuffer, const char *name);
    void (*popDebugGroup)(SDL_GPUCommandBuffer *commandBuffer);

    size_t abiSize;
    unsigned abiVersion;
} LwsdlglGPUAPI;

extern const LwsdlglGPUAPI GPU;

#ifdef __cplusplus
}
#endif

#endif
