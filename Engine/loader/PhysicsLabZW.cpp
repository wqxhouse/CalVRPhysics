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
#include "Scene.h"
#include "CustomVCoordFrameCB.h"

CVRPLUGIN(PhysicsLabZW);

PhysicsLabZW::PhysicsLabZW()
: _coreEngineEnabled(true)
{
    _core = new Core;
    loadConfigSettings();
    
    _trackBallM = new CustomTrackballManipulator(_screenWidth, _screenHeight);
    _keyboardM = new CVRKeyboardHandler(this, _core);
}

PhysicsLabZW::~PhysicsLabZW()
{
    delete _core;
    delete _mainMenu;
    delete _keyboardM;
}

bool PhysicsLabZW::init()
{
    configMenuBoard();
    configMainCamera();
    configEngineCore();
   
    // needs to be called after _core is set up
    configTrackball();
    
    cvr::PluginHelper::getScene()->addChild(_core->getSceneRoot());
    
    return true;
}

void PhysicsLabZW::preFrame()
{
    _trackBallM->updateCamera(*_mainCamera);
}

bool PhysicsLabZW::processEvent(cvr::InteractionEvent *event)
{
    if(event->getInteraction() == cvr::NO_INTERACTION)
    {
        return false;
    }
    
    _trackBallM->handleCVREvent(event);
    _keyboardM->handleCVREvent(event);
    
    return true;
}


void PhysicsLabZW::menuCallback(cvr::MenuItem *menu)
{
}

void PhysicsLabZW::loadConfigSettings()
{
    std::string winConfigStr = "WindowConfig.Window";
    int winWidth = cvr::ConfigManager::getInt("width", winConfigStr, 800);
    int winHeight = cvr::ConfigManager::getInt("height", winConfigStr, 600);
    _screenWidth = winWidth;
    _screenHeight = winHeight;
}

void PhysicsLabZW::configMenuBoard()
{
    _mainMenu = new cvr::SubMenu("PhysicsLabZW", "PhysicsLabZW");
    _mainMenu->setCallback(this);
    cvr::MenuSystem::instance()->addMenuItem(_mainMenu);
}

void PhysicsLabZW::configEngineCore()
{
    _core->setWindowSize(_screenWidth, _screenHeight);
    
    // this disables the internal viewer of the _core
    _core->setCustomMainCamera(_mainCamera);
    _core->setGeometryHandler(Scene::setupSceneGeometries);
    _core->setDirectionalLightHandler(Scene::setupDirectionalLights);
    _core->setPointLightHandler(Scene::setupPointLights);
    _core->addExternalHUD(cvr::SceneManager::instance()->getMenuRoot());
    // _core->getSceneRoot()->addChild(cvr::SceneManager::instance()->getMenuRoot());
    _core->run();
}

void PhysicsLabZW::configTrackball()
{
    cvr::CVRViewer *viewer = cvr::CVRViewer::instance();
    if(_trackBallM.valid())
    {
        // customize from osgViewer/view.cpp
        _trackBallM->setUseOSGDefaultProjectionMatrix(true);
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

void PhysicsLabZW::enableEngineRender()
{
    if(!_coreEngineEnabled)
    {
        cvr::PluginHelper::getScene()->addChild(_core->getSceneRoot());
        _coreEngineEnabled = true;
    }
}

void PhysicsLabZW::disableEngineRender()
{
    if(_coreEngineEnabled)
    {
        cvr::PluginHelper::getScene()->removeChild(_core->getSceneRoot());
        _coreEngineEnabled = false;
    }
}

void PhysicsLabZW::toggleEngineRender()
{
    _coreEngineEnabled ? disableEngineRender() : enableEngineRender();
}