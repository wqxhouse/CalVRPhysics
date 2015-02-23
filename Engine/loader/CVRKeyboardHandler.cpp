//
//  Keyboardhandler.cpp
//  CalVR_Plugins
//
//  Created by Robin Wu on 2/22/15.
//
//

#include "CVRKeyboardHandler.h"
#include "PhysicsLabZW.h"
#include "../src/Core.h"

void CVRKeyboardHandler::handleCVREvent(cvr::InteractionEvent *event)
{
    cvr::KeyboardInteractionEvent *ke = event->asKeyboardEvent();
    if( ke == NULL ) return;
    
    if (ke->getInteraction() == cvr::KEY_DOWN)
    {
        switch (ke->getKey())
        {
            case 'h':
                _engine->toggleDebugHUD();
                break;
            case 'p':
                _main->toggleEngineRender();
                break;
                
        }
    }
    else if (ke->getInteraction() == cvr::KEY_UP)
    {
        // TODO : to be added
    }
}