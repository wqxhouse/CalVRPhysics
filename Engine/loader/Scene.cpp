//
//  Scene.cpp
//  CalVR_Plugins
//
//  Created by Robin Wu on 2/22/15.
//
//

#include "Scene.h"

void Scene::setupSceneGeometries(const osg::ref_ptr<osg::Group> geoms, Assets *const asset)
{
   asset->addGeometryWithFile("Testing/gi_test.dae");
}

void Scene::setupDirectionalLights(DirectionalLightGroup *const dirLightGroup)
{
}

void Scene::setupPointLights(LightGroup *const pointLightGroup)
{
}