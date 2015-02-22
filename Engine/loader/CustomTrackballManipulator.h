//
//  CustomTrackballManipulator.h
//  CalVR_Plugins
//
//  Created by Robin Wu on 2/20/15.
//
//

#ifndef __CalVR_Plugins__CustomTrackballManipulator__
#define __CalVR_Plugins__CustomTrackballManipulator__

#include <stdio.h>
#include <osgGA/TrackballManipulator>
#include <cvrKernel/InteractionEvent.h>
#include <cvrKernel/InteractionManager.h>

class CustomTrackballManipulator : public osgGA::TrackballManipulator
{
    typedef osgGA::TrackballManipulator inherited;
public:
    
    CustomTrackballManipulator( int winWdith, int winHeight, int flags = DEFAULT_SETTINGS );
    virtual ~CustomTrackballManipulator() {};
    
    virtual bool handleCVREvent(cvr::InteractionEvent * event);
    
    inline void setUseDefaultProjectionMatirx(bool tf)
    {
        _useDefaultOSGProjection = tf;
    }
   
    // override
    virtual void updateCamera(osg::Camera& camera);
    
protected:
    
    float getXnormalized(float x) const
    {
        float val = (x-_xMin)/(_xMax-_xMin)*2.0f-1.0f;
        return val;
    }
    float getYnormalized(float y) const
    {
        float val = (y-_yMin)/(_yMax-_yMin)*2.0f-1.0f;
        return val;
    }
    
    bool handleMouseMoveCVR( cvr::InteractionEvent *event );
    bool handleMouseDragCVR( cvr::InteractionEvent *event );
    bool handleMousePushCVR( cvr::InteractionEvent *event );
    bool handleMouseReleaseCVR( cvr::InteractionEvent *event );
    bool handleKeyDownCVR( cvr::InteractionEvent *event );
    bool handleMouseWheelCVR( cvr::InteractionEvent *event );
    bool isMouseMovingCVR();
    
    void addMouseEventCVR( cvr::InteractionEvent *event );
    void flushMouseEventCVR();
    bool performMovementCVR();
    bool performMovementLeftMouseButtonCVR(const double eventTimeDelta, const double dx, const double dy);
    

    // virtual void applyAnimationStep( const double currentProgress, const double prevProgress );
    // virtual bool startAnimationByMousePointerIntersection( const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& us );
    
    cvr::InteractionEvent *_currEvent;
//    cvr::InteractionEvent *_event1;
    
    double _prevX;
    double _prevY;
    
    double _currX;
    double _currY;
    
    // TODO : potentially replace it with InteractionManager::_dragEventTime
    double _event0Time;
    double _event1Time;
    
    unsigned int _event0MouseButtonMask;
    unsigned int _event1MousebuttonMask;
    
    bool _useDefaultOSGProjection;
    
    osg::Matrix _defaultOSGProjectionMatrix;
    void configDefaultOSGProjectionMatrix();
    
    // normalize settings
    float _xMin;
    float _xMax;
    float _yMin;
    float _yMax;

private:
    double getElaspedTime();


};

#endif /* defined(__CalVR_Plugins__CustomTrackballManipulator__) */
