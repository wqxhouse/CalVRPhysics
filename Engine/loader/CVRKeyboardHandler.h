//
//  Keyboardhandler.h
//  CalVR_Plugins
//
//  Created by Robin Wu on 2/22/15.
//
//

#ifndef __CalVR_Plugins__Keyboardhandler__
#define __CalVR_Plugins__Keyboardhandler__

#include <stdio.h>
#include <cvrKernel/InteractionEvent.h>

class Core;
class PhysicsLabZW;
class CVRKeyboardHandler
{
public:
    CVRKeyboardHandler(PhysicsLabZW *mainClass, Core *engine)
    : _main(mainClass), _engine(engine) {};
    
    ~CVRKeyboardHandler() {};
    
    void handleCVREvent(cvr::InteractionEvent *event);
    
private:
    // keep week references for state manipulation
    PhysicsLabZW *_main;
    Core *_engine;
};

#endif /* defined(__CalVR_Plugins__Keyboardhandler__) */
