//
//  PhysicsLabZW.cpp
//  CalVR_Plugins
//
//  Created by Robin Wu on 2/20/15.
//
//

#include "PhysicsLabZW.h"

#include <iostream>
#include <cvrConfig/ConfigManager.h>
#include <cvrKernel/SceneObject.h>
#include <osgGA/TrackballManipulator>
#include "../src/Utils.h"

#include "CustomVCoordFrameCB.h"

CVRPLUGIN(PhysicsLabZW);

void PhysicsLabZW::handleGeometries(const osg::ref_ptr<osg::Group> geoms, Assets *const asset)
{
    asset->addGeometryWithFile("Testing/gi_test.dae");
}

void PhysicsLabZW::handleDirLights(DirectionalLightGroup *const dirLightGroup)
{
    
}

PhysicsLabZW::PhysicsLabZW()
{
    _core = new Core;
    loadConfigSettings();
    
    _trackBallM = new CustomTrackballManipulator(_screenWidth, _screenHeight);
}

PhysicsLabZW::~PhysicsLabZW()
{
    delete _core;
}

void PhysicsLabZW::menuCallback(cvr::MenuItem*)
{
    
}

bool PhysicsLabZW::init()
{
    configMainCamera();
    
    cvr::CVRViewer::instance()->setCameraManipulator(new osgGA::TrackballManipulator());
    
    _core->setWindowSize(_screenWidth, _screenHeight);
    
    // this disables the internal viewer of the _core
    _core->setCustomMainCamera(_mainCamera);
    _core->setGeometryHandler(PhysicsLabZW::handleGeometries);
    _core->setDirectionalLightHandler(PhysicsLabZW::handleDirLights);
    _core->run();
   
    // needs to be called after _core is set up
    configTrackball();
    
    //cvr::PluginHelper::getScene()->addChild(_core->getSceneRoot());
    
    cvr::SceneObject * so = new cvr::SceneObject("abc",false,false,false,true,false);
    cvr::PluginHelper::registerSceneObject(so,"abc");
    osg::Switch * sNode = new osg::Switch();
    sNode->addChild(_core->getSceneRoot());
    so->addChild(sNode);
    so->attachToScene();
    so->setNavigationOn(true);
    so->addMoveMenuItem();
    so->addNavigationMenuItem();

    
    return true;
}

void PhysicsLabZW::preFrame()
{
    osg::Matrix m = cvr::PluginHelper::getHeadMat(0);
    osg::Matrix w_o = cvr::PluginHelper::getWorldToObjectTransform();
    osg::Matrix o_w = cvr::PluginHelper::getObjectToWorldTransform();
    
    _trackBallM->updateCamera(*_mainCamera);
    
//    std::cout << "view Mat\n";
//    Utils::print(_mainCamera->getViewMatrix());
    
    
//    std::cout << "proj Mat\n";
//    Utils::print(_mainCamera->getProjectionMatrix());
//    Utils::print(m);
//    printf("w_o:\n");
//    Utils::print(w_o);
//    printf("o_w:\n");
//    Utils::print(o_w);
//    printf("main_view\n");
//    std::cout << "main: " << std::endl;
//    Utils::print(_mainCamera->getViewMatrix());
//    std::cout << "head: " << std::endl;
//    Utils::print(cvr::PluginHelper::getHeadMat());
    
//     std::cout << "main:\n" << _mainCamera->getViewport()->width() << ", " << _mainCamera->getViewport()->height() << "\n";
    //    printf("main_proj\n");
//    Utils::print(_mainCamera->getProjectionMatrix());
}

bool PhysicsLabZW::processEvent(cvr::InteractionEvent *event)
{
    if(event->getInteraction() == cvr::NO_INTERACTION)
    {
        return false;
    }
    
    cvr::TrackedButtonInteractionEvent * he;
    if((he = event->asTrackedButtonEvent()) != NULL)
    {
        if (he->getHand() == 0 && he->getButton() == 0) {
            osg::Matrixd handmat = cvr::PluginHelper::getHandMat(0);
            
            if (he->getInteraction() == cvr::BUTTON_DOWN)
            {
            //    grabbing = of->grabObject( handmat, cvr::PluginHelper::getScene() );
            }
            else if (he->getInteraction() == cvr::BUTTON_UP)
            {
//                grabbing = false;
//                of->releaseObject();
            }
        }
    }
    
    _trackBallM->handleCVREvent(event);
    
    return true;
}

void PhysicsLabZW::loadConfigSettings()
{
    std::string winConfigStr = "WindowConfig.Window";
    int winWidth = cvr::ConfigManager::getInt("width", winConfigStr, 800);
    int winHeight = cvr::ConfigManager::getInt("height", winConfigStr, 600);
    _screenWidth = winWidth;
    _screenHeight = winHeight;
}

void PhysicsLabZW::configTrackball()
{
    if(_trackBallM.valid())
    {
        // customize from osgViewer/view.cpp
        cvr::CVRViewer *viewer = cvr::CVRViewer::instance();
        _trackBallM->setUseDefaultProjectionMatirx(true);
        _trackBallM->setCoordinateFrameCallback(new CustomVCoordFrameCB(viewer));
        _trackBallM->setNode(_core->getSceneRoot());
        
        osg::ref_ptr<osgGA::GUIEventAdapter> dummyEvent = new osgGA::GUIEventAdapter();
        _trackBallM->home(*dummyEvent, *viewer);
    }
}

void PhysicsLabZW::configMainCamera()
{
    // currently a hack for mono screen
    cvr::CVRViewer *viewer = cvr::CVRViewer::instance();
    osg::ref_ptr<osg::Camera> mainCamera = viewer->getSlave(0)._camera;
    _mainCamera = mainCamera;
    
    // hack 2: initially cvr camera is set to 1024 * 768 and
    // later updated to config settings; however, Core depends on this camera's initial
    // value to work correctly; thus we need to manually set the camera resolution
    // TODO: all passes resolution independent of camera's viewport size
    _mainCamera->setViewport(0, 0, _screenWidth, _screenHeight);
}
