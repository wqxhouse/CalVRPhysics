//
//  Scene.h
//  CalVR_Plugins
//
//  Created by Robin Wu on 2/22/15.
//
//

#ifndef __CalVR_Plugins__Scene__
#define __CalVR_Plugins__Scene__

#include <stdio.h>
#include <osg/Group>
#include "../src/AssetDB.h"
#include "../src/DirectionalLightGroup.h"
#include "../src/LightGroup.h"

class Scene
{
public:
    static void setupSceneGeometries(const osg::ref_ptr<osg::Group> geoms, Assets *const asset);
    static void setupDirectionalLights(DirectionalLightGroup *const dirLightGroup);
    static void setupPointLights(LightGroup *const pointLightGroup);
};

#endif /* defined(__CalVR_Plugins__Scene__) */
