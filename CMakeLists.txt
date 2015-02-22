SET(LIB_NAME vrphysics)
SET(PLUGIN_HEADERS
    PhysicsLabZW.h

    ScreenMonoChild.h
    Engine/DirectionalLight.h
	Engine/DirectionalLightCallback.h
	Engine/DirectionalLightGroup.h
	Engine/DirectionalLightingPass.h
	Engine/FinalPass.h
	Engine/GeometryPass.h
	Engine/ISmile.h
	Engine/LightCallback.h
	Engine/LightGroup.h
	Engine/LightGroupAnimationCallback.h
	Engine/LightingPass.h
	Engine/Material.h
	Engine/PointLight.h
	Engine/SSAOPass.h
	Engine/ScreenPass.h
	Engine/Shared.h
	Engine/Utils.h
	Engine/AssetDB.h

	Robert/AntiGravityField.h	
	Robert/NavHandler.h		
	Robert/BulletHandler.h		
	Robert/ObjectFactory.h
)

ADD_LIBRARY(${LIB_NAME}
    "SHARED"
    ${PLUGIN_HEADERS}
    PhysicsLabZW.cpp

    Engine/DirectionalLight.cpp
	Engine/DirectionalLightCallback.cpp
	Engine/DirectionalLightGroup.cpp
	Engine/DirectionalLightingPass.cpp
	Engine/FinalPass.cpp
	Engine/GeometryPass.cpp
	Engine/LightCallback.cpp
	Engine/LightGroup.cpp
	Engine/LightGroupAnimationCallback.cpp
	Engine/LightingPass.cpp
	Engine/Material.cpp
	Engine/PointLight.cpp
	Engine/SSAOPass.cpp
	Engine/ScreenPass.cpp
	Engine/Shared.cpp
	Engine/Utils.cpp
	Engine/AssetDB.cpp

	Robert/NavHandler.cpp
	Robert/BulletHandler.cpp
	Robert/ObjectFactory.cpp
)

FIND_PACKAGE(Bullet)
INCLUDE_DIRECTORIES(${BULLET_INCLUDE_DIR})
TARGET_LINK_LIBRARIES(${LIB_NAME} ${BULLET_LIBRARIES})

INCLUDE_DIRECTORIES(${OSG_INCLUDE_DIR})
TARGET_LINK_LIBRARIES(${LIB_NAME} ${OSG_LIBRARIES})

ADD_CALVR_LIBRARIES(${LIB_NAME})

INSTALL(TARGETS ${LIB_NAME} DESTINATION lib/plugins)
