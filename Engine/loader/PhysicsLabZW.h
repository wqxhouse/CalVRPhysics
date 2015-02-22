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

class PhysicsLabZW : public cvr::CVRPlugin, public cvr::MenuCallback
{
protected:
    cvr::SubMenu * _mainMenu, * _loadMenu;
    cvr::MenuButton * _removeButton;
    
public:
    PhysicsLabZW();
    virtual ~PhysicsLabZW();
    void menuCallback(cvr::MenuItem*);
    
    bool init();
    void preFrame();
    bool processEvent(cvr::InteractionEvent*);
    
private:
    int _screenWidth;
    int _screenHeight;
    
    void loadConfigSettings();
    void configMainCamera();
    void configTrackball();
    
    Core *_core;
    osg::ref_ptr<osg::Camera> _mainCamera;
    
    static void handleGeometries(const osg::ref_ptr<osg::Group> geoms, Assets *const asset);
    static void handleDirLights(DirectionalLightGroup *const dirLightGroup);
    
    osg::ref_ptr<CustomTrackballManipulator> _trackBallM;

};

#endif /* defined(__CalVR_Plugins__PhysicsLabZW__) */
