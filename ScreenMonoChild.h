#ifndef _SCREEN_MONO_CHILD
#define _SCREEN_MONO_CHILD

#include <cvrKernel/ScreenMono.h>

// Engine
class ScreenMonoChild : public cvr::ScreenMono
{
public:
	ScreenMonoChild()
        {
        };
	virtual ~ScreenMonoChild() {} ;

        inline float getNear()
        {
            return _near;
        }
    
        inline float getFar()
        {
            return _far; 
        }

        inline osg::ref_ptr<osg::Camera> getCamera()
        {
            return _camera;
        }
};

#endif
