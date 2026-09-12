#ifndef LWSDLGL_SHADERCROSS_H
#define LWSDLGL_SHADERCROSS_H

#include <SDL3/SDL.h>
#include <SDL3/SDL_gpu.h>
#include <SDL3_shadercross/SDL_shadercross.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct LwsdlglShaderCrossAPI {
    bool (*init)(void);
    void (*quit)(void);
    SDL_GPUShaderFormat (*getSPIRVShaderFormats)(void);
    void *(*transpileMSLFromSPIRV)(const SDL_ShaderCross_SPIRV_Info *info);
    void *(*transpileHLSLFromSPIRV)(const SDL_ShaderCross_SPIRV_Info *info);
    void *(*compileDXBCFromSPIRV)(const SDL_ShaderCross_SPIRV_Info *info, size_t *size);
    void *(*compileDXILFromSPIRV)(const SDL_ShaderCross_SPIRV_Info *info, size_t *size);
    SDL_GPUShader *(*compileGraphicsShaderFromSPIRV)(SDL_GPUDevice *device, const SDL_ShaderCross_SPIRV_Info *info, const SDL_ShaderCross_GraphicsShaderResourceInfo *resources, SDL_PropertiesID props);
    SDL_GPUComputePipeline *(*compileComputePipelineFromSPIRV)(SDL_GPUDevice *device, const SDL_ShaderCross_SPIRV_Info *info, const SDL_ShaderCross_ComputePipelineMetadata *metadata, SDL_PropertiesID props);
    SDL_ShaderCross_GraphicsShaderMetadata *(*reflectGraphicsSPIRV)(const Uint8 *bytecode, size_t bytecodeSize, SDL_PropertiesID props);
    SDL_ShaderCross_ComputePipelineMetadata *(*reflectComputeSPIRV)(const Uint8 *bytecode, size_t bytecodeSize, SDL_PropertiesID props);
    SDL_GPUShaderFormat (*getHLSLShaderFormats)(void);
    void *(*compileDXBCFromHLSL)(const SDL_ShaderCross_HLSL_Info *info, size_t *size);
    void *(*compileDXILFromHLSL)(const SDL_ShaderCross_HLSL_Info *info, size_t *size);
    void *(*compileSPIRVFromHLSL)(const SDL_ShaderCross_HLSL_Info *info, size_t *size);
    size_t abiSize;
    unsigned abiVersion;
} LwsdlglShaderCrossAPI;

extern const LwsdlglShaderCrossAPI ShaderCross;

#ifdef __cplusplus
}
#endif

#endif
