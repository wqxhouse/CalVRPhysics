SET(LIB_NAME LatestZW)
SET(PLUGIN_HEADERS
	Engine/src/AssetDB.h
	Engine/src/BlurPass.h
	Engine/src/Core.h
	Engine/src/CustomFirstPersonManipulator.h
	Engine/src/DirectionalLightCallback.h
	Engine/src/DirectionalLight.h
	Engine/src/DirectionalLightGroup.h
	Engine/src/DirectionalLightingPass.h
	Engine/src/FinalPass.h
	Engine/src/FrustumData.h
	Engine/src/GeometryPass.h
	Engine/src/HDRPass.h
	Engine/src/ImportanceSamplingPass.h
	Engine/src/IndirectLightingPass.h
	Engine/src/KeyboardHandler.h
	Engine/src/LightCallback.h
	Engine/src/LightGroupAnimationCallback.h
	Engine/src/LightGroup.h
	Engine/src/LightHandler.h
	Engine/src/LightingPass.h
	Engine/src/LightTrackBallManipulator.h
	Engine/src/Material.h
	Engine/src/PointLight.h
	Engine/src/SceneEventCallback.h
	Engine/src/ScreenPass.h
	Engine/src/ShadowCallback.h
	Engine/src/ShadowGroup.h
	Engine/src/Shared.h
	Engine/src/SSAOPass.h
	Engine/src/Utils.h
	Engine/src/VPLGroup.h

	Engine/loader/CustomTrackballManipulator.h
	Engine/loader/CustomVCoordFrameCB.h
	Engine/loader/CVRKeyboardHandler.h
	Engine/loader/PhysicsLabZW.h
	Engine/loader/Scene.h
	
)

ADD_LIBRARY(${LIB_NAME}
    "SHARED"
    ${PLUGIN_HEADERS}
	Engine/src/AssetDB.cpp
	Engine/src/BlurPass.cpp
	Engine/src/Core.cpp
	Engine/src/CustomFirstPersonManipulator.cpp
	Engine/src/DirectionalLightCallback.cpp
	Engine/src/DirectionalLight.cpp
	Engine/src/DirectionalLightGroup.cpp
	Engine/src/DirectionalLightingPass.cpp
	Engine/src/FinalPass.cpp
	Engine/src/FrustumData.cpp
	Engine/src/GeometryPass.cpp
	Engine/src/HDRPass.cpp
	Engine/src/ImportanceSamplingPass.cpp
	Engine/src/IndirectLightingPass.cpp
	Engine/src/KeyboardHandler.cpp
	Engine/src/LightCallback.cpp
	Engine/src/LightGroupAnimationCallback.cpp
	Engine/src/LightGroup.cpp
	Engine/src/LightHandler.cpp
	Engine/src/LightingPass.cpp
	Engine/src/LightTrackBallManipulator.cpp
	Engine/src/Material.cpp
	Engine/src/PointLight.cpp
	Engine/src/SceneEventCallback.cpp
	Engine/src/ScreenPass.cpp
	Engine/src/ShadowCallback.cpp
	Engine/src/ShadowGroup.cpp
	Engine/src/Shared.cpp
	Engine/src/SSAOPass.cpp
	Engine/src/Utils.cpp
	Engine/src/VPLGroup.cpp

	Engine/loader/CustomTrackballManipulator.cpp
	Engine/loader/CustomVCoordFrameCB.cpp
	Engine/loader/CVRKeyboardHandler.cpp
	Engine/loader/PhysicsLabZW.cpp
	Engine/loader/Scene.cpp
)

FIND_PACKAGE(Bullet)
INCLUDE_DIRECTORIES(${BULLET_INCLUDE_DIR})
TARGET_LINK_LIBRARIES(${LIB_NAME} ${BULLET_LIBRARIES})

INCLUDE_DIRECTORIES(${OSG_INCLUDE_DIR})
TARGET_LINK_LIBRARIES(${LIB_NAME} ${OSG_LIBRARIES})

ADD_CALVR_LIBRARIES(${LIB_NAME})

INSTALL(TARGETS ${LIB_NAME} DESTINATION lib/plugins)
