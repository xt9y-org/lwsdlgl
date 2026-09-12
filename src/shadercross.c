#include <lwsdlgl/lwsdlgl.h>

const LwsdlglShaderCrossAPI ShaderCross = {
    SDL_ShaderCross_Init,
    SDL_ShaderCross_Quit,
    SDL_ShaderCross_GetSPIRVShaderFormats,
    SDL_ShaderCross_TranspileMSLFromSPIRV,
    SDL_ShaderCross_TranspileHLSLFromSPIRV,
    SDL_ShaderCross_CompileDXBCFromSPIRV,
    SDL_ShaderCross_CompileDXILFromSPIRV,
    SDL_ShaderCross_CompileGraphicsShaderFromSPIRV,
    SDL_ShaderCross_CompileComputePipelineFromSPIRV,
    SDL_ShaderCross_ReflectGraphicsSPIRV,
    SDL_ShaderCross_ReflectComputeSPIRV,
    SDL_ShaderCross_GetHLSLShaderFormats,
    SDL_ShaderCross_CompileDXBCFromHLSL,
    SDL_ShaderCross_CompileDXILFromHLSL,
    SDL_ShaderCross_CompileSPIRVFromHLSL,
    sizeof(LwsdlglShaderCrossAPI),
    LWSDLGL_ABI_VERSION
};
