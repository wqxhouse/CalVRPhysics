SET(LIB_NAME PhysicsLabZW)
SET(PLUGIN_HEADERS
	Engine/loader/CVRKeyboardHandler.h		
	Engine/loader/PhysicsLabZW.h
	Engine/loader/CustomTrackballManipulator.h	
	Engine/loader/Scene.h
	Engine/loader/CustomVCoordFrameCB.h

	Engine/src/AssetDB.h			
	Engine/src/LightTrackBallManipulator.h
	Engine/src/Core.h				
	Engine/src/LightingPass.h
	Engine/src/DirectionalLight.h		
	Engine/src/Material.h
	Engine/src/DirectionalLightCallback.h	
	Engine/src/PointLight.h
	Engine/src/DirectionalLightGroup.h		
	Engine/src/SSAOPass.h
	Engine/src/DirectionalLightingPass.h	
	Engine/src/SceneEventCallback.h
	Engine/src/FinalPass.h			
	Engine/src/ScreenPass.h
	Engine/src/GeometryPass.h			
	Engine/src/ShadowCallback.h
	Engine/src/HDRPass.h			
	Engine/src/ShadowGroup.h
	Engine/src/ImportanceSamplingPass.h	
	Engine/src/SphereSegment.h
	Engine/src/IndirectLightingPass.h		
	Engine/src/SpotLight.h
	Engine/src/KeyboardHandler.h		
	Engine/src/SpotLightGroup.h
	Engine/src/LightCallback.h			
	Engine/src/Utils.h
	Engine/src/LightGroup.h			
	Engine/src/VPLGroup.h
	Engine/src/LightGroupAnimationCallback.h
)

ADD_LIBRARY(${LIB_NAME}
    "SHARED"
    ${PLUGIN_HEADERS}
	Engine/loader/CVRKeyboardHandler.cpp		
	Engine/loader/PhysicsLabZW.cpp
	Engine/loader/CustomTrackballManipulator.cpp	
	Engine/loader/Scene.cpp
	Engine/loader/CustomVCoordFrameCB.cpp

	Engine/src/AssetDB.cpp			
	Engine/src/LightTrackBallManipulator.cpp
	Engine/src/Core.cpp				
	Engine/src/LightingPass.cpp
	Engine/src/DirectionalLight.cpp		
	Engine/src/Material.cpp
	Engine/src/DirectionalLightCallback.cpp	
	Engine/src/PointLight.cpp
	Engine/src/DirectionalLightGroup.cpp		
	Engine/src/SSAOPass.cpp
	Engine/src/DirectionalLightingPass.cpp	
	Engine/src/SceneEventCallback.cpp
	Engine/src/FinalPass.cpp			
	Engine/src/ScreenPass.cpp
	Engine/src/GeometryPass.cpp			
	Engine/src/ShadowCallback.cpp
	Engine/src/HDRPass.cpp			
	Engine/src/ShadowGroup.cpp
	Engine/src/ImportanceSamplingPass.cpp	
	Engine/src/SphereSegment.cpp
	Engine/src/IndirectLightingPass.cpp		
	Engine/src/SpotLight.cpp
	Engine/src/KeyboardHandler.cpp		
	Engine/src/SpotLightGroup.cpp
	Engine/src/LightCallback.cpp			
	Engine/src/Utils.cpp
	Engine/src/LightGroup.cpp			
	Engine/src/VPLGroup.cpp
	Engine/src/LightGroupAnimationCallback.cpp
)

INCLUDE_DIRECTORIES(${OSG_INCLUDE_DIR})
TARGET_LINK_LIBRARIES(${LIB_NAME} ${OSG_LIBRARIES})

ADD_CALVR_LIBRARIES(${LIB_NAME})

INSTALL(TARGETS ${LIB_NAME} DESTINATION lib/plugins)
