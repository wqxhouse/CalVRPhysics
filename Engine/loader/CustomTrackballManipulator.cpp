//
//  CustomTrackballManipulator.cpp
//  CalVR_Plugins
//
//  Created by Robin Wu on 2/20/15.
//
//

#include "CustomTrackballManipulator.h"
#include <sys/time.h>
#include <cvrKernel/PluginHelper.h>

CustomTrackballManipulator::CustomTrackballManipulator( int winWidth, int winHeight, int flag )
: inherited(flag),  _currEvent(NULL),  _prevX(-1.0), _prevY(-1.0),
  _currX(-1.0), _currY(-1.0), _event0Time(0.0), _event1Time(0.0),
    _event0MouseButtonMask(-1), _event1MousebuttonMask(-1), _useDefaultOSGProjection(false)
{
    _xMin = _yMin = 0.0f; // assume screen starts from the corner;
    _xMax = winWidth;
    _yMax = winHeight;
    
    configDefaultOSGProjectionMatrix();
}

void CustomTrackballManipulator::configDefaultOSGProjectionMatrix()
{
    double height = osg::DisplaySettings::instance()->getScreenHeight();
    double width = osg::DisplaySettings::instance()->getScreenWidth();
    double distance = osg::DisplaySettings::instance()->getScreenDistance();
    double vfov = osg::RadiansToDegrees(atan2(height/2.0f,distance)*2.0);
    
    _defaultOSGProjectionMatrix.makePerspective(vfov, width/height, 1.0f,10000.0f);
}

void CustomTrackballManipulator::updateCamera(osg::Camera &camera)
{
    camera.setViewMatrix(getInverseMatrix());
    if(_useDefaultOSGProjection)
    {
        camera.setProjectionMatrix(_defaultOSGProjectionMatrix);
    }
}

void CustomTrackballManipulator::addMouseEventCVR( cvr::InteractionEvent *event )
{
//    _event1 = _event0;
//    _event0 = event;
    
    _prevX = _currX;
    _currX = event->asMouseEvent()->getX();
    
    _prevY = _currY;
    _currY = event->asMouseEvent()->getY();
    
    _event1Time = _event0Time;
    _event0Time = getElaspedTime();
    
    
    _event1MousebuttonMask = _event0MouseButtonMask;
    _event0MouseButtonMask = cvr::InteractionManager::instance()->getMouseButtonMask();
}

void CustomTrackballManipulator::flushMouseEventCVR()
{
//    _event0 = NULL;
//    _event1 = NULL;
    
    _currX = -1.0;
    _currY = -1.0;
    
    _prevX = -1.0;
    _prevY = -1.0;
    
    _event0Time = 0.0;
    _event1Time = 0.0;
    
    _event1MousebuttonMask = -1;
    _event0MouseButtonMask = -1;
}

bool CustomTrackballManipulator::performMovementCVR()
{
    if( (_currX == -1.0 && _currY == -1.0) || (_prevX == -1.0 && _prevY == -1.0) )
    {
        return false;
    }
    
    // get delta time
    double eventTimeDelta = _event0Time - _event1Time;
    
    if( eventTimeDelta < 0. )
    {
        OSG_WARN << "Manipulator warning: eventTimeDelta = " << eventTimeDelta << std::endl;
        eventTimeDelta = 0.;
    }

    // get deltaX and deltaY
    float dx = getXnormalized(_currX) - getXnormalized(_prevX);
    float dy = getYnormalized(_currY)- getYnormalized(_prevY);
    
    // return if there is no movement.
    if( dx == 0. && dy == 0. )
        return false;
    
    // call appropriate methods
    unsigned int buttonMask = cvr::InteractionManager::instance()->getMouseButtonMask(); // TODO: button ? buttonMask?
    if( buttonMask == osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON )
    {
        return performMovementLeftMouseButtonCVR( eventTimeDelta, dx, dy );
    }
    else if( buttonMask == osgGA::GUIEventAdapter::MIDDLE_MOUSE_BUTTON ||
            buttonMask == (osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON | osgGA::GUIEventAdapter::RIGHT_MOUSE_BUTTON) )
    {
        return performMovementMiddleMouseButton( eventTimeDelta, dx, dy );
    }
    else if( buttonMask == osgGA::GUIEventAdapter::RIGHT_MOUSE_BUTTON )
    {
        // _thrown = false;
        // float t = getThrowScale( eventTimeDelta );
        return performMovementRightMouseButton( eventTimeDelta, dx, dy );
    }
    
    return false;
}

bool CustomTrackballManipulator::handleMouseMoveCVR( cvr::InteractionEvent *event )
{
    return false;
}

bool CustomTrackballManipulator::handleMouseDragCVR( cvr::InteractionEvent *event  )
{
    addMouseEventCVR(event);
    performMovementCVR();
    return true;
}

bool CustomTrackballManipulator::handleMousePushCVR( cvr::InteractionEvent *event )
{
    flushMouseEventCVR();
    addMouseEventCVR(event);
    performMovementCVR();
    return true;
}

bool CustomTrackballManipulator::isMouseMovingCVR()
{
//    if (_event0 == NULL || _event1 == NULL) return false;
//    
//    cvr::MouseInteractionEvent *ms0 = _event0->asMouseEvent();
//    cvr::MouseInteractionEvent *ms1 = _event1->asMouseEvent();
    
    static const float velocity = 0.1f;
    
    float dx = getXnormalized(_currX) - getXnormalized(_prevX);
    float dy = getYnormalized(_currY) - getYnormalized(_prevY);
    float len = sqrtf(dx*dx+dy*dy);
    float dt = _event0Time - _event1Time;
    
    return (len>dt*velocity);
}

// doc in parent
bool CustomTrackballManipulator::performMovementLeftMouseButtonCVR( const double eventTimeDelta, const double dx, const double dy )
{
    // rotate camera
    if( getVerticalAxisFixed() )
        rotateWithFixedVertical( dx, dy );
    else
        rotateTrackball(getXnormalized(_currX), getYnormalized(_currY),
                        getXnormalized(_prevX), getYnormalized(_prevY),
                        getThrowScale( eventTimeDelta ) );
    return true;
}

bool CustomTrackballManipulator::handleMouseReleaseCVR( cvr::InteractionEvent *event  )
{
    double currEventTime = getElaspedTime();
    if( cvr::InteractionManager::instance()->getMouseButtonMask() == 0 )
    {
        double timeSinceLastRecordEvent = (currEventTime - _event0Time);
        if( timeSinceLastRecordEvent > 0.02 )
            flushMouseEventStack();
        
        if( isMouseMovingCVR() )
        {
            performMovementCVR();
            return true;
        }
    }
    
    flushMouseEventCVR();
    addMouseEventCVR( event );
    performMovement();
    
    return true;
}

bool CustomTrackballManipulator::handleKeyDownCVR( cvr::InteractionEvent *event  )
{
    return false;
}

bool CustomTrackballManipulator::handleMouseWheelCVR( cvr::InteractionEvent *event )
{
    // From cvr source UP = 1, DOWN = -1
    int scrollMotion = cvr::InteractionManager::instance()->getMouseWheel();
    
    // handle centering
//    if( _flags & SET_CENTER_ON_WHEEL_FORWARD_MOVEMENT )
//    {
//        
//        if( ((sm == GUIEventAdapter::SCROLL_DOWN && _wheelZoomFactor > 0.)) ||
//           ((sm == GUIEventAdapter::SCROLL_UP   && _wheelZoomFactor < 0.)) )
//        {
//            
//            if( getAnimationTime() <= 0. )
//            {
//                // center by mouse intersection (no animation)
//                setCenterByMousePointerIntersection( ea, us );
//            }
//            else
//            {
//                // start new animation only if there is no animation in progress
//                if( !isAnimating() )
//                    startAnimationByMousePointerIntersection( ea, us );
//                
//            }
//            
//        }
//    }
    
    switch( scrollMotion )
    {
            // mouse scroll up event
        case 1: // UP
        {
            // perform zoom
            zoomModel( _wheelZoomFactor, true );
            return true;
        }
            
            // mouse scroll down event
        case 2: // DOWN
        {
            // perform zoom
            zoomModel( -_wheelZoomFactor, true );
            return true;
        }
            // unhandled mouse scrolling motion
        default:
            return false;
    }
    return false;
}

bool CustomTrackballManipulator::handleCVREvent(cvr::InteractionEvent * event)
{
    if(event->asMouseEvent() != NULL)
    {
        cvr::MouseInteractionEvent *ki = event->asMouseEvent();
        
        // scroll
        if( cvr::InteractionManager::instance()->getMouseWheel() != 0)
        {
            return handleMouseWheelCVR(event);
        }
        
        switch(ki->getInteraction())
        {
            case cvr::BUTTON_DOWN:
                return handleMousePushCVR(event);
            case cvr::BUTTON_UP:
                return handleMouseReleaseCVR(event);
            case cvr::BUTTON_DRAG:
                return handleMouseDragCVR(event);
            default:
                return false;
        }
    }
    return false;
}

double CustomTrackballManipulator::getElaspedTime()
{
    double delta = cvr::PluginHelper::getProgramDuration();
    return delta;
}