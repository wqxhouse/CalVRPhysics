//
//  CustomVCoordFrameCB.h
//  CalVR_Plugins
//
//  Created by Robin Wu on 2/20/15.
//
//

#ifndef __CalVR_Plugins__CustomVCoordFrameCB__
#define __CalVR_Plugins__CustomVCoordFrameCB__

#include <stdio.h>
#include <osgGA/CameraManipulator>
#include <osgViewer/View>

class CustomVCoordFrameCB : public osgGA::CameraManipulator::CoordinateFrameCallback
{
public:
    
    CustomVCoordFrameCB(osgViewer::View* view):
    _view(view) {}
    
    virtual osg::CoordinateFrame getCoordinateFrame(const osg::Vec3d& position) const
    {
        // OSG_DEBUG<<"getCoordinateFrame("<<position<<")"<<std::endl;
        
        osg::NodePath tmpPath = _view->getCoordinateSystemNodePath();
        
        if (!tmpPath.empty())
        {
            osg::Matrixd coordinateFrame;
            
            osg::CoordinateSystemNode* csn = dynamic_cast<osg::CoordinateSystemNode*>(tmpPath.back());
            if (csn)
            {
                osg::Vec3 local_position = position*osg::computeWorldToLocal(tmpPath);
                
                // get the coordinate frame in world coords.
                coordinateFrame = csn->computeLocalCoordinateFrame(local_position)* osg::computeLocalToWorld(tmpPath);
                
                // keep the position of the coordinate frame to reapply after rescale.
                osg::Vec3d pos = coordinateFrame.getTrans();
                
                // compensate for any scaling, so that the coordinate frame is a unit size
                osg::Vec3d x(1.0,0.0,0.0);
                osg::Vec3d y(0.0,1.0,0.0);
                osg::Vec3d z(0.0,0.0,1.0);
                x = osg::Matrixd::transform3x3(x,coordinateFrame);
                y = osg::Matrixd::transform3x3(y,coordinateFrame);
                z = osg::Matrixd::transform3x3(z,coordinateFrame);
                coordinateFrame.preMultScale(osg::Vec3d(1.0/x.length(),1.0/y.length(),1.0/z.length()));
                
                // reapply the position.
                coordinateFrame.setTrans(pos);
                
                //OSG_DEBUG<<"csn->computeLocalCoordinateFrame(position)* osg::computeLocalToWorld(tmpPath)"<<coordinateFrame<<std::endl;
                
            }
            else
            {
                OSG_DEBUG<<"osg::computeLocalToWorld(tmpPath)"<<std::endl;
                coordinateFrame =  osg::computeLocalToWorld(tmpPath);
            }
            return coordinateFrame;
        }
        else
        {
            OSG_DEBUG<<"   no coordinate system found, using default orientation"<<std::endl;
            return osg::Matrixd::translate(position);
        }
    }
    
protected:
    virtual ~CustomVCoordFrameCB() {}
    
    osg::observer_ptr<osgViewer::View> _view;
};

#endif /* defined(__CalVR_Plugins__CustomVCoordFrameCB__) */
