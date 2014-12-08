#include "PhysicsLabZW.h"

#include <stdio.h>
#include <iostream>
#include <string>

#include <PluginMessageType.h>
#include <cvrKernel/ScreenConfig.h>
#include <cvrKernel/ScreenBase.h>
#include <cvrKernel/ScreenMono.h>
#include <cvrKernel/SceneManager.h>

#include "Engine/Utils.h"


CVRPLUGIN(PhysicsLabZW)

// Constructor
PhysicsLabZW::PhysicsLabZW() {}
// this is called if the plugin is removed at runtime
PhysicsLabZW::~PhysicsLabZW() 
{
    freeHeap(_passes, _dirLightGroup, _pointLightGroup);
}
void PhysicsLabZW::menuCallback(cvr::MenuItem* menuItem) {}

bool PhysicsLabZW::init()
{
    _mainMenu = new cvr::SubMenu("PhysicsLabZW", "PhysicsLabZW");
    _mainMenu->setCallback(this);
    cvr::MenuSystem::instance()->addMenuItem(_mainMenu);

    cvr::ScreenConfig *screenConfig = cvr::ScreenConfig::instance();
    cvr::ScreenInfo *screenInfo = screenConfig->getScreenInfo(0);

    // here assume mycalvr.xml configs the screen as MONO. needs to modify to stereo later.
    cvr::ScreenMono *screenMono = dynamic_cast<cvr::ScreenMono *>(screenConfig->getScreen(0));

    // this is a hack since normally it is impossible to get protected fields
    ScreenMonoChild *hackChild = reinterpret_cast<ScreenMonoChild *>(screenMono);
    osg::ref_ptr<osg::Camera> mainCamera = hackChild->getCamera();
    osg::Matrixd mt = mainCamera->getViewMatrix();
    _mainCamera = mainCamera;
    Utils::print(mt);

    osg::ref_ptr<osg::Group> sceneRoot(new osg::Group);
   
    AssetDB assets;
    assets.addGeometryWithFile("Testing/cornell-box/engine/a.dae");
    sceneRoot->addChild(assets.getGeomRoot());
    
    DirectionalLightGroup *dirLightGroup = addDirectionalLights(assets.getGeomRoot());
    _dirLightGroup = dirLightGroup;
    dirLightGroup->addMultipleLights(assets.getDirectionalLights());

    LightGroup *pointLightGroup = addPointLights(assets.getGeomRoot());
    _pointLightGroup = pointLightGroup;
    pointLightGroup->addMultipleLights(assets.getPointLights());

    _passes = configPasses(assets, mainCamera, dirLightGroup, pointLightGroup, sceneRoot);
    osg::ref_ptr<osg::MatrixTransform> translate(new osg::MatrixTransform);
    osg::Matrix cam;
    cam.makeTranslate(0, -1900, 0);
    translate->setMatrix(cam);
    translate->addChild(sceneRoot);

    //cvr::PluginHelper::setObjectScale(1000.0);
    //cvr::PluginHelper::getScene()->addChild(translate);
//    osg::Node *avatar = osgDB::readNodeFile("avatar.osg");

    cvr::SceneObject * so = new cvr::SceneObject("abc",false,false,false,true,false);
    cvr::PluginHelper::registerSceneObject(so,"abc");
    osg::Switch * sNode = new osg::Switch();
    sNode->addChild(sceneRoot);
    so->addChild(sNode);
    so->attachToScene();
    so->setNavigationOn(true);
    so->addMoveMenuItem();
    so->addNavigationMenuItem();

    return true;
}

void PhysicsLabZW::preFrame()
{
  printf("hello\n");
    //osg::Matrix m = cvr::SceneManager::instance()->getObjectToWorldTransform();
    //Utils::print(m);
  osg::Matrix m = cvr::PluginHelper::getHeadMat(0);
  osg::Matrix w_o = cvr::PluginHelper::getWorldToObjectTransform();
  osg::Matrix o_w = cvr::PluginHelper::getObjectToWorldTransform();
  Utils::print(m);
  printf("w_o:\n");
  Utils::print(w_o);
  printf("o_w:\n");
  Utils::print(o_w);
  printf("main_view\n");
  Utils::print(_mainCamera->getViewMatrix());
  printf("main_proj\n");
  Utils::print(_mainCamera->getProjectionMatrix());

}

// helper functions
osg::Camera * PhysicsLabZW::createHUDCamera(double left,
                         double right,
                         double bottom,
                         double top)
{
    osg::ref_ptr<osg::Camera> camera = new osg::Camera;
    camera->setReferenceFrame(osg::Transform::ABSOLUTE_RF);
    camera->setClearMask(GL_DEPTH_BUFFER_BIT);
    camera->setRenderOrder(osg::Camera::POST_RENDER);
    camera->setAllowEventFocus(false);
    camera->setProjectionMatrix(osg::Matrix::ortho2D(left, right, bottom, top));
    camera->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
    return camera.release();
}

osg::Geode * PhysicsLabZW::createScreenQuad(float width,
                         float height,
                         float scaleX,
                         float scaleY,
                         osg::Vec3 corner)
{
    osg::Geometry* geom = osg::createTexturedQuadGeometry(
                                                          corner,
                                                          osg::Vec3(width, 0, 0),
                                                          osg::Vec3(0, height, 0),
                                                          0,
                                                          0,
                                                          scaleX,
                                                          scaleY);
    osg::ref_ptr<osg::Geode> quad = new osg::Geode;
    quad->addDrawable(geom);
    int values = osg::StateAttribute::OFF | osg::StateAttribute::PROTECTED;
    quad->getOrCreateStateSet()->setAttribute(
                                              new osg::PolygonMode(osg::PolygonMode::FRONT_AND_BACK,
                                                                   osg::PolygonMode::FILL),
                                              values);
    quad->getOrCreateStateSet()->setMode(GL_LIGHTING, values);
    return quad.release(); 
}

osg::ref_ptr<osg::Camera> PhysicsLabZW::createTextureDisplayQuad(
                                               const osg::Vec3 &pos,
                                               osg::StateAttribute *tex,
                                               float scaleX,
                                               float scaleY,
                                               float width,
                                               float height)
{
    osg::ref_ptr<osg::Camera> hc = createHUDCamera(0,1,0,1);
    hc->addChild(createScreenQuad(width, height, scaleX, scaleY, pos));
    hc->getOrCreateStateSet()->setTextureAttributeAndModes(0, tex);
    return hc;
}

osg::ref_ptr<osg::TextureRectangle> PhysicsLabZW::createTextureImage(const char *imageName)
{
    osg::ref_ptr<osg::TextureRectangle> texture(new osg::TextureRectangle);
    texture->setImage(osgDB::readImageFile(imageName));
    texture->setWrap(osg::TextureRectangle::WRAP_S, osg::TextureRectangle::REPEAT);
    texture->setWrap(osg::TextureRectangle::WRAP_T, osg::TextureRectangle::REPEAT);
    texture->setFilter(osg::Texture::MIN_FILTER, osg::Texture::LINEAR_MIPMAP_LINEAR);
    texture->setFilter(osg::Texture::MAG_FILTER, osg::Texture::LINEAR);
    return texture;
}

osg::ref_ptr<osg::Geode> PhysicsLabZW::createTexturedQuad(int _TextureWidth, int _TextureHeight)
{
    osg::ref_ptr<osg::Geode> quad_geode = new osg::Geode;
    
    osg::ref_ptr<osg::Vec3Array> quad_coords = new osg::Vec3Array; // vertex coords
    // counter-clockwise
    quad_coords->push_back(osg::Vec3d(0, 0, -10));
    quad_coords->push_back(osg::Vec3d(10, 0, -10));
    quad_coords->push_back(osg::Vec3d(10, 10, -10));
    quad_coords->push_back(osg::Vec3d(0, 10, -10));
    
    osg::ref_ptr<osg::Vec2Array> quad_tcoords = new osg::Vec2Array; // texture coords
    quad_tcoords->push_back(osg::Vec2(0, 0));
    quad_tcoords->push_back(osg::Vec2(_TextureWidth, 0));
    quad_tcoords->push_back(osg::Vec2(_TextureWidth, _TextureHeight));
    quad_tcoords->push_back(osg::Vec2(0, _TextureHeight));
    
    osg::ref_ptr<osg::Geometry> quad_geom = new osg::Geometry;
    osg::ref_ptr<osg::DrawArrays> quad_da = new osg::DrawArrays(osg::PrimitiveSet::QUADS,0,4);
    
    quad_geom->setVertexArray(quad_coords.get());
    quad_geom->setTexCoordArray(0, quad_tcoords.get());
    quad_geom->addPrimitiveSet(quad_da.get());
    
    auto _StateSet = quad_geom->getOrCreateStateSet();
    _StateSet->setMode(GL_LIGHTING,osg::StateAttribute::OFF);
    
    quad_geode->addDrawable(quad_geom.get());
    
    return quad_geode;
}

DirectionalLightGroup * PhysicsLabZW::addDirectionalLights(osg::Group *geomGroup)
{
    // Directional Lights
    DirectionalLightGroup *dirLightGroup = new DirectionalLightGroup;
    // here we can optionally choose to display the geom of the directional light
    
    return dirLightGroup;
}

LightGroup * PhysicsLabZW::addPointLights(osg::Group *geomGroup)
{
    // Point lights
    LightGroup *lightGroup = new LightGroup;
        osg::BoundingSphere sp;
    sp.center() = osg::Vec3(0, 0, 0);
    sp.radius() = 10;
//    for(int i = 0; i < 50; i++)
//    {
//        lightGroup->addRandomLightWithBoundingSphere(sp);
//    }
//    for(int i = -20; i < 20; i += 4)
//    {
//        lightGroup->addLight(osg::Vec3(i, 0, -60), osg::Vec3(1, 1, 0));
//    }

    
    //    lightGroup.addLight(osg::Vec3(5, 0, 0), osg::Vec3(1, 1, 0));
    //    lightGroup.addLight(osg::Vec3(5, 5, 5), osg::Vec3(1, 1, 0));
    //    lightGroup.addLight(osg::Vec3(-5, 5, 5), osg::Vec3(1, 0, 1));
    //    lightGroup.addLight(osg::Vec3(5, -5, 5), osg::Vec3(1, 1, 1));
    //    lightGroup.addLight(osg::Vec3(5, 5, -5), osg::Vec3(1, 0, 0));
    //    lightGroup.addLight(osg::Vec3(-5, 5, -5), osg::Vec3(0, 1, 1));
    //    lightGroup.addLight(osg::Vec3(-5, -5, 5), osg::Vec3(0, 1, 0));
    geomGroup->addChild(lightGroup->getGeomTransformLightGroup()); // point light geoms
    return lightGroup;
}

GeometryPass * PhysicsLabZW::configGeomPass(osg::Camera *camera, AssetDB &assetDB)
{
    GeometryPass *geomPass = new GeometryPass(camera, assetDB);
    return geomPass;
}

DirectionalLightingPass * PhysicsLabZW::configDirectionalLightPass(osg::Camera *camera, GeometryPass *geomPass, DirectionalLightGroup *dirLightGroup)
{
    // directional light pass
    DirectionalLightingPass *dirLightPass = new DirectionalLightingPass(camera, geomPass->getPositionOutTexure(),
                                         geomPass->getAlbedoOutTexture(),
                                         geomPass->getNormalDepthOutTexture(),
                                         dirLightGroup);
    return dirLightPass;
}

LightingPass * PhysicsLabZW::configPointLightPass(osg::Camera *camera, GeometryPass *geomPass, LightGroup *lightGroup)
{
    // point light pass
    LightingPass *lightPass = new LightingPass(camera,
                           geomPass->getPositionOutTexure(),
                           geomPass->getAlbedoOutTexture(),
                           geomPass->getNormalDepthOutTexture(),
                           lightGroup);
    return lightPass;
}

SSAOPass * PhysicsLabZW::configSSAOPass(osg::Camera *camera, GeometryPass *geomPass)
{
    SSAOPass *ssaoPass = new SSAOPass(camera, geomPass->getPositionOutTexure(), geomPass->getNormalDepthOutTexture(), createTextureImage("random.png"));
    return ssaoPass;
}

FinalPass * PhysicsLabZW::configFinalPass(osg::Camera *camera, GeometryPass *geomPass, DirectionalLightingPass *dirLightPass, LightingPass *lightPass, SSAOPass *ssaoPass)
{
    FinalPass *finalPass = new FinalPass(camera, geomPass->getAlbedoOutTexture(),
                        dirLightPass->getLightingOutTexture(),
                        lightPass->getLightingOutTexture(),
                        ssaoPass->getSSAOOutTexture());
    return finalPass;
}

void PhysicsLabZW::setupHUDForPasses(GeometryPass *gp, DirectionalLightingPass *dp, LightingPass *lp, SSAOPass *ssaoPass, FinalPass *fp, osg::Group *sceneRoot)
{
    osg::ref_ptr<osg::Camera> qTexN =
    createTextureDisplayQuad(osg::Vec3(0, 0.7, 0),
                             gp->getNormalDepthOutTexture(),
                             800, 600, 0.3333, 0.3);
//    osg::ref_ptr<osg::Camera> qTexN =
//    createTextureDisplayQuad(osg::Vec3(0, 0.7, 0),
//                             createTextureImage("random.png"),
//                             800, 600, 0.3333, 0.3);
    
    osg::ref_ptr<osg::Camera> qTexD =
    createTextureDisplayQuad(osg::Vec3(0.3333, 0.7, 0),
                             gp->getPositionOutTexure(),
                             800, 600, 0.3333, 0.3);

    osg::ref_ptr<osg::Camera> qTexP =
    createTextureDisplayQuad(osg::Vec3(0.6666, 0.7, 0),
                             lp->getLightingOutTexture(),
                             800, 600, 0.3333, 0.3);
    
    osg::ref_ptr<osg::Camera> qTexF =
    createTextureDisplayQuad(osg::Vec3(0.0, 0.0, 0),
                             fp->getFinalPassTexture(),
                             800, 600, 1, 1);
    
    sceneRoot->addChild(qTexF);
    sceneRoot->addChild(qTexN);
    sceneRoot->addChild(qTexD);
    sceneRoot->addChild(qTexP);
}

std::vector<ScreenPass *> PhysicsLabZW::configPasses(AssetDB &assetDB, osg::Camera *camera, DirectionalLightGroup *dirLightGroup, LightGroup *pointLightGroup, osg::Group *sceneRoot)
{
    GeometryPass *gp = configGeomPass(camera, assetDB);
    DirectionalLightingPass *dirLightPass = configDirectionalLightPass(camera, gp, dirLightGroup);
    LightingPass *pointLightPass = configPointLightPass(camera, gp, pointLightGroup);
    SSAOPass *ssaoPass = configSSAOPass(camera, gp);
    FinalPass *finalPass = configFinalPass(camera, gp, dirLightPass, pointLightPass,ssaoPass);
    
    sceneRoot->addChild(gp->getRoot());
    sceneRoot->addChild(dirLightPass->getRoot());
    sceneRoot->addChild(pointLightPass->getRoot());
    sceneRoot->addChild(ssaoPass->getRoot());
    sceneRoot->addChild(finalPass->getRoot());
    
    setupHUDForPasses(gp, dirLightPass, pointLightPass, ssaoPass, finalPass, sceneRoot);
    
    std::vector<ScreenPass *> passes;
    passes.push_back(gp);
    passes.push_back(dirLightPass);
    passes.push_back(pointLightPass);
    passes.push_back(finalPass);
    return passes;
}

void PhysicsLabZW::freeHeap(std::vector<ScreenPass *> screenPasses, DirectionalLightGroup *dirLightGroup, LightGroup *ptLightGroup)
{
    for(int i = 0; i < (int)screenPasses.size(); i++)
    {
        delete screenPasses[i];
    }
    delete dirLightGroup;
    delete ptLightGroup;
}

