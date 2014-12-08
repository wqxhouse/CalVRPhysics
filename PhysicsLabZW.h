#ifndef _PHYSICSLABZW_H
#define _PHYSICSLABZW_H

// CVR
#include <cvrKernel/CVRPlugin.h>
#include <cvrKernel/PluginHelper.h>
#include <cvrKernel/ComController.h>
#include <cvrMenu/MenuSystem.h>
#include <cvrMenu/SubMenu.h>
#include <cvrMenu/MenuButton.h>

// OSG
#include <osgDB/ReadFile>
#include <osgViewer/viewer>
#include <osg/Camera>
#include <osg/PolygonMode>

#include "ScreenMonoChild.h"

#include "Engine/GeometryPass.h"
#include "Engine/DirectionalLightingPass.h"
#include "Engine/DirectionalLightGroup.h"
#include "Engine/LightingPass.h"
#include "Engine/LightGroup.h"
#include "Engine/SSAOPass.h"
#include "Engine/FinalPass.h"
#include "Engine/AssetDB.h"

// Engine
class DirectionalLightGroup;
class LightGroup;
class PhysicsLabZW : public cvr::CVRPlugin, public cvr::MenuCallback
{
public:
	PhysicsLabZW();
	virtual ~PhysicsLabZW();
	void menuCallback(cvr::MenuItem*);
	bool init();
	void preFrame();
protected:
	cvr::SubMenu * _mainMenu, * _loadMenu;
	cvr::MenuButton * _removeButton;

private:
	DirectionalLightGroup *_dirLightGroup;
	LightGroup *_pointLightGroup;
	float _near;
	float _far;
	osg::ref_ptr<osg::Camera> _mainCamera;
	std::vector<ScreenPass *> _passes;

	// helper functions
	osg::Camera *createHUDCamera(double left,
                             double right,
                             double bottom,
                             double top);
	osg::Geode *createScreenQuad(float width,
                             float height,
                             float scaleX,
                             float scaleY,
                             osg::Vec3 corner);
	osg::ref_ptr<osg::Camera> createTextureDisplayQuad(
                                                   const osg::Vec3 &pos,
                                                   osg::StateAttribute *tex,
                                                   float scaleX,
                                                   float scaleY,
                                                   float width,
                                                   float height);

	osg::ref_ptr<osg::TextureRectangle> createTextureImage(const char *imageName);
	osg::ref_ptr<osg::Geode> createTexturedQuad(int _TextureWidth, int _TextureHeight);
	DirectionalLightGroup *addDirectionalLights(osg::Group *geomGroup);
	LightGroup *addPointLights(osg::Group *geomGroup);
	GeometryPass *configGeomPass(osg::Camera *camera, AssetDB &assetDB);
	DirectionalLightingPass *configDirectionalLightPass(osg::Camera *camera, GeometryPass *geomPass, DirectionalLightGroup *dirLightGroup);
	LightingPass *configPointLightPass(osg::Camera *camera, GeometryPass *geomPass, LightGroup *lightGroup);
	SSAOPass *configSSAOPass(osg::Camera *camera, GeometryPass *geomPass);
	FinalPass *configFinalPass(osg::Camera *camera, GeometryPass *geomPass, DirectionalLightingPass *dirLightPass, LightingPass *lightPass, SSAOPass *ssaoPass);
	void setupHUDForPasses(GeometryPass *gp, DirectionalLightingPass *dp, LightingPass *lp, SSAOPass *ssaoPass, FinalPass *fp, osg::Group *sceneRoot);
	std::vector<ScreenPass *> configPasses(AssetDB &assetDB, osg::Camera *camera, DirectionalLightGroup *dirLightGroup, LightGroup *pointLightGroup, osg::Group *sceneRoot);
	void freeHeap(std::vector<ScreenPass *> screenPasses, DirectionalLightGroup *dirLightGroup, LightGroup *ptLightGroup);
};
#endif
