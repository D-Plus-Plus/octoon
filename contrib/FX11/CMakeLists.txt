PROJECT(FX11)

SET(LIB_NAME FX11)

SET(HEADER_PATH ${OCTOON_PATH_DEPENDENCIES}/${LIB_NAME}/include)
SET(SOURCE_PATH ${OCTOON_PATH_DEPENDENCIES}/${LIB_NAME}/source)

INCLUDE_DIRECTORIES(${OCTOON_PATH_DEPENDENCIES}/${LIB_NAME}/include)

SET(FX11_LIST
    ${HEADER_PATH}/d3dx11effect.h
    ${HEADER_PATH}/d3dxGlobal.h
    ${SOURCE_PATH}/d3dxGlobal.cpp
    ${SOURCE_PATH}/Effect.h
    ${SOURCE_PATH}/EffectAPI.cpp
    ${SOURCE_PATH}/EffectBinaryFormat.h
    ${SOURCE_PATH}/EffectLoad.cpp
    ${SOURCE_PATH}/EffectLoad.h
    ${SOURCE_PATH}/EffectNonRuntime.cpp
    ${SOURCE_PATH}/EffectStateBase11.h
    ${SOURCE_PATH}/EffectReflection.cpp
    ${SOURCE_PATH}/EffectStates11.h
    ${SOURCE_PATH}/EffectRuntime.cpp
    ${SOURCE_PATH}/EffectVariable.inl
    ${SOURCE_PATH}/IUnknownImp.h
    ${SOURCE_PATH}/pchfx.h
    ${SOURCE_PATH}/SOParser.h
    )
SOURCE_GROUP(${LIB_NAME} FILES ${FX11_LIST})

ADD_LIBRARY(${LIB_NAME} ${FX11_LIST})