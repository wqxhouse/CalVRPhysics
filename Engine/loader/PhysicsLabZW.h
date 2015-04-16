//
//  PhysicsLabZW.h
//  CalVR_Plugins
//
//  Created by Robin Wu on 2/20/15.
//
//

#ifndef __CalVR_Plugins__PhysicsLabZW__
#define __CalVR_Plugins__PhysicsLabZW__

#include <stdio.h>
#include <osgGA/TrackballManipulator>
#include <osg/Matrix>

// CVR
#include <cvrKernel/CVRPlugin.h>
#include <cvrKernel/PluginHelper.h>
#include <cvrKernel/SceneManager.h>
#include <cvrKernel/ComController.h>
#include <cvrKernel/Navigation.h>
#include <cvrMenu/MenuSystem.h>
#include <cvrMenu/SubMenu.h>
#include <cvrMenu/MenuButton.h>
#include <cvrKernel/InteractionEvent.h>

#include "../src/Core.h"
#include "CustomTrackballManipulator.h"
#include "CVRKeyboardHandler.h"

class PhysicsLabZW : public cvr::CVRPlugin, public cvr::MenuCallback
{
protected:
    cvr::SubMenu *_mainMenu;
    
public:
    PhysicsLabZW();
    virtual ~PhysicsLabZW();
    void menuCallback(cvr::MenuItem *);
    
    bool init();
    void preFrame();
    bool processEvent(cvr::InteractionEvent *);
    
    void disableEngineRender();
    void enableEngineRender();
    void toggleEngineRender();
    
private:
    int _screenWidth;
    int _screenHeight;
    
    void loadConfigSettings();
    void configMainCamera();
    void configTrackball();
    void configMenuBoard();
    void configEngineCore();
    void configFilePath();
    
    Core *_core;
    bool _coreEngineEnabled;
    
    osg::ref_ptr<osg::Camera> _mainCamera;
    
    osg::ref_ptr<CustomTrackballManipulator> _trackBallM;
    CVRKeyboardHandler *_keyboardM;
};

#endif /* defined(__CalVR_Plugins__PhysicsLabZW__) */
