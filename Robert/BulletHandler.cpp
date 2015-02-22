#include "BulletHandler.h"
#include <iostream>

int clnumavfs = 0;
std::vector<AntiGravityField*> clavfs;
int buttonState = 0, prevButtonState = -1;
AntiGravityField* hand;
btRigidBody* closest;
btVector3 initGrabPos;
btVector3 distToStylus;

void ghostCallback (btDynamicsWorld *world, btScalar timeStep)
{
    // AVF
    for (int i = 0; i < clnumavfs; ++i) {
        //std::cout << "Num Ghost Collisions: " << clavfs[i]->getNumOverlappingObjects() << "\n";
        for(int j = 0; j < clavfs[i]->getNumOverlappingObjects(); j++) {
            btRigidBody *pRigidBody = dynamic_cast<btRigidBody *>(clavfs[i]->getOverlappingObject(j));
            pRigidBody->setGravity( clavfs[i]->getGravity() );
        }
    }
    
    if (closest) closest->setGravity( btVector3(0,0,0) );
    // Grab Hand
    //std::cout << "ButtonState: " << buttonState << "\n";
    if (buttonState != prevButtonState && hand) {
        switch (buttonState) {
            case 1:
                std::cout << "Hand Origin: " << hand->getWorldTransform().getOrigin().x() << ", " << hand->getWorldTransform().getOrigin().y() << ", " << hand->getWorldTransform().getOrigin().z() << "\n";
                std::cout << "Num Hand Collisions: " << hand->getNumOverlappingObjects() << "\n";
                for(int i = 0; i < hand->getNumOverlappingObjects(); ++i) {
                    btRigidBody *pRigidBody = dynamic_cast<btRigidBody *>(hand->getOverlappingObject(i));
                    if (!closest) closest = pRigidBody;
                    else {
                      btVector3 handPos = hand->getWorldTransform().getOrigin();
                      btVector3 closestPos = closest->getCenterOfMassTransform().getOrigin();
                      btVector3 newPos = pRigidBody->getCenterOfMassTransform().getOrigin();
                      if ((closestPos - handPos) > (newPos - handPos)) closest = pRigidBody;
                    }
                }
                if (closest) {
                  closest->setGravity( btVector3(0,0,0) );
                  initGrabPos = closest->getCenterOfMassPosition();
                  distToStylus = initGrabPos - hand->getWorldTransform().getOrigin();
                }
                break;
            case 0:
                closest = (btRigidBody*) 0;
                break;
        }
    }
    if (buttonState != prevButtonState && buttonState == 1 && hand) {
      std::cout << "Num Hand Collisions: " << hand->getNumOverlappingObjects() << "\n";
      for(int i = 0; i < hand->getNumOverlappingObjects(); ++i) {
          btRigidBody *pRigidBody = dynamic_cast<btRigidBody *>(hand->getOverlappingObject(i));
          if (!closest) closest = pRigidBody;
          else {
            btVector3 handPos = hand->getWorldTransform().getOrigin();
            btVector3 closestPos = closest->getCenterOfMassTransform().getOrigin();
            btVector3 newPos = pRigidBody->getCenterOfMassTransform().getOrigin();
            if ((closestPos - handPos) > (newPos - handPos)) closest = pRigidBody;
          }
      }
    }
}

BulletHandler::BulletHandler() {
    // Create World
    broadphase = new btDbvtBroadphase();
    btcc = new btDefaultCollisionConfiguration();
    btcd = new btCollisionDispatcher(btcc);
    btsolver = new btSequentialImpulseConstraintSolver;
    dynamicsWorld = new btDiscreteDynamicsWorld(btcd, broadphase, btsolver, btcc);
    dynamicsWorld->setGravity( btVector3(0,0,-10000) );
    
    // Add Floor
    btCollisionShape* groundShape = new btStaticPlaneShape(btVector3(0, 0, 1), 1);
    btDefaultMotionState* groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 0, 0)));
    btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI(0, groundMotionState, groundShape, btVector3(0, 0, 0));
    btRigidBody* groundRigidBody = new btRigidBody(groundRigidBodyCI);
    dynamicsWorld->addRigidBody(groundRigidBody);
    dynamicsWorld->setInternalTickCallback(ghostCallback,this,true);
    dynamicsWorld->getBroadphase()->getOverlappingPairCache()->setInternalGhostPairCallback(new btGhostPairCallback());
    
    numRigidBodies = 0;
    numavfs = 0;
}

BulletHandler::~BulletHandler() {
    delete dynamicsWorld;
    delete btsolver;
    delete broadphase;
    delete btcc;
    delete btcd;
}

int BulletHandler::addBox( osg::Vec3 origin, osg::Vec3 halfLengths, bool physEnabled ) {
    btCollisionShape* boxShape = new btBoxShape( *(btVector3*) &halfLengths );
    btDefaultMotionState* boxMotionState =
        new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1), btVector3(origin.x(), origin.y(), origin.z())));
        
    btRigidBody * boxRigidBody;
    if (physEnabled) {
        btVector3 boxInertia(0,0,0);
        boxShape->calculateLocalInertia(btScalar(1), boxInertia);
        btRigidBody::btRigidBodyConstructionInfo boxRigidBodyCI(1, boxMotionState, boxShape, boxInertia);
        boxRigidBody = new btRigidBody(boxRigidBodyCI);
    } else {
        btRigidBody::btRigidBodyConstructionInfo boxRigidBodyCI(0, boxMotionState, boxShape, btVector3(0,0,0));
        boxRigidBody = new btRigidBody(boxRigidBodyCI);
    }
    dynamicsWorld->addRigidBody(boxRigidBody);
    rbodies.push_back(boxRigidBody);
    
    return numRigidBodies++;
}

int BulletHandler::addSeesaw( osg::Vec3 origin, osg::Vec3 halflengths, bool physEnabled ) {
    btCollisionShape* boxShape = new btBoxShape( *(btVector3*) &halflengths );
    btDefaultMotionState* boxMotionState =
        new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1), *(btVector3*)&origin));
        
    btRigidBody * boxRigidBody;
    if (physEnabled) {
        btVector3 boxInertia(0,0,0);
        boxShape->calculateLocalInertia(btScalar(1), boxInertia);
        btRigidBody::btRigidBodyConstructionInfo boxRigidBodyCI(1, boxMotionState, boxShape, boxInertia);
        boxRigidBody = new btRigidBody(boxRigidBodyCI);
    } else {
        btRigidBody::btRigidBodyConstructionInfo boxRigidBodyCI(0, boxMotionState, boxShape, btVector3(0,0,0));
        boxRigidBody = new btRigidBody(boxRigidBodyCI);
    }
    
    if (halflengths.x() > halflengths.y()) {
        btHingeConstraint* hinge = new btHingeConstraint(*boxRigidBody,btVector3(0,0,0),btVector3(0,1,0),true);
		    dynamicsWorld->addConstraint(hinge);
		} else {
        btHingeConstraint* hinge = new btHingeConstraint(*boxRigidBody,btVector3(0,0,0),btVector3(1,0,0),true);
		    dynamicsWorld->addConstraint(hinge);
		}
    dynamicsWorld->addRigidBody(boxRigidBody);
    rbodies.push_back(boxRigidBody);
    
    return numRigidBodies++;
}

int BulletHandler::addOpenBox( osg::Vec3 origin, osg::Vec3 halflengths, double innerWidth, bool physEnabled ) {
    btCompoundShape* boxShape = new btCompoundShape();
    std::vector<btVector3> planePoints [14];
    
    // Left Plane - Outer
    planePoints[0].push_back( btVector3( origin.x() - halflengths.x(), origin.y() - halflengths.y(), origin.z() - halflengths.z()) );
    planePoints[0].push_back( btVector3( origin.x() - halflengths.x(), origin.y() - halflengths.y(), origin.z() + halflengths.z()) );
    planePoints[0].push_back( btVector3( origin.x() + halflengths.x(), origin.y() - halflengths.y(), origin.z() + halflengths.z()) );
    planePoints[0].push_back( btVector3( origin.x() + halflengths.x(), origin.y() - halflengths.y(), origin.z() - halflengths.z()) );
    
    // Back Plane - Outer
    planePoints[1].push_back( btVector3( origin.x() - halflengths.x(), origin.y() - halflengths.y(), origin.z() - halflengths.z()) );
    planePoints[1].push_back( btVector3( origin.x() - halflengths.x(), origin.y() - halflengths.y(), origin.z() + halflengths.z()) );
    planePoints[1].push_back( btVector3( origin.x() - halflengths.x(), origin.y() + halflengths.y(), origin.z() + halflengths.z()) );
    planePoints[1].push_back( btVector3( origin.x() - halflengths.x(), origin.y() + halflengths.y(), origin.z() - halflengths.z()) );
    
    // Right Plane - Outer
    planePoints[2].push_back( btVector3( origin.x() - halflengths.x(), origin.y() + halflengths.y(), origin.z() - halflengths.z()) );
    planePoints[2].push_back( btVector3( origin.x() - halflengths.x(), origin.y() + halflengths.y(), origin.z() + halflengths.z()) );
    planePoints[2].push_back( btVector3( origin.x() + halflengths.x(), origin.y() + halflengths.y(), origin.z() + halflengths.z()) );
    planePoints[2].push_back( btVector3( origin.x() + halflengths.x(), origin.y() + halflengths.y(), origin.z() - halflengths.z()) );
    
    // Front Plane - Outer
    planePoints[3].push_back( btVector3( origin.x() + halflengths.x(), origin.y() - halflengths.y(), origin.z() - halflengths.z()) );
    planePoints[3].push_back( btVector3( origin.x() + halflengths.x(), origin.y() - halflengths.y(), origin.z() + halflengths.z()) );
    planePoints[3].push_back( btVector3( origin.x() + halflengths.x(), origin.y() + halflengths.y(), origin.z() + halflengths.z()) );
    planePoints[3].push_back( btVector3( origin.x() + halflengths.x(), origin.y() + halflengths.y(), origin.z() - halflengths.z()) );
    
    // Bottom Plane - Outer
    planePoints[4].push_back( btVector3( origin.x() - halflengths.x(), origin.y() + halflengths.y(), origin.z() - halflengths.z()) );
    planePoints[4].push_back( btVector3( origin.x() - halflengths.x(), origin.y() - halflengths.y(), origin.z() - halflengths.z()) );
    planePoints[4].push_back( btVector3( origin.x() + halflengths.x(), origin.y() - halflengths.y(), origin.z() - halflengths.z()) );
    planePoints[4].push_back( btVector3( origin.x() + halflengths.x(), origin.y() + halflengths.y(), origin.z() - halflengths.z()) );
    
    if (innerWidth > 0.0) {
    
        // Left Plane - Inner
        planePoints[5].push_back( btVector3( origin.x() - halflengths.x() + innerWidth, origin.y() - halflengths.y() + innerWidth, origin.z() - halflengths.z() + innerWidth));
        planePoints[5].push_back( btVector3( origin.x() - halflengths.x() + innerWidth, origin.y() - halflengths.y() + innerWidth, origin.z() + halflengths.z()) );
        planePoints[5].push_back( btVector3( origin.x() + halflengths.x() - innerWidth, origin.y() - halflengths.y() + innerWidth, origin.z() + halflengths.z()) );
        planePoints[5].push_back( btVector3( origin.x() + halflengths.x() - innerWidth, origin.y() - halflengths.y() + innerWidth, origin.z() - halflengths.z() + innerWidth));
    
        // Back Plane - Inner
        planePoints[6].push_back( btVector3( origin.x() - halflengths.x() + innerWidth, origin.y() - halflengths.y() + innerWidth, origin.z() - halflengths.z() + innerWidth) );
        planePoints[6].push_back( btVector3( origin.x() - halflengths.x() + innerWidth, origin.y() - halflengths.y() + innerWidth, origin.z() + halflengths.z()) );
        planePoints[6].push_back( btVector3( origin.x() - halflengths.x() + innerWidth, origin.y() + halflengths.y() - innerWidth, origin.z() + halflengths.z()) );
        planePoints[6].push_back( btVector3( origin.x() - halflengths.x() + innerWidth, origin.y() + halflengths.y() - innerWidth, origin.z() - halflengths.z() + innerWidth) );
        
        // Right Plane - Inner
        planePoints[7].push_back( btVector3( origin.x() - halflengths.x() + innerWidth, origin.y() + halflengths.y() - innerWidth, origin.z() - halflengths.z() + innerWidth) );
        planePoints[7].push_back( btVector3( origin.x() - halflengths.x() + innerWidth, origin.y() + halflengths.y() - innerWidth, origin.z() + halflengths.z()) );
        planePoints[7].push_back( btVector3( origin.x() + halflengths.x() - innerWidth, origin.y() + halflengths.y() - innerWidth, origin.z() + halflengths.z()) );
        planePoints[7].push_back( btVector3( origin.x() + halflengths.x() - innerWidth, origin.y() + halflengths.y() - innerWidth, origin.z() - halflengths.z() + innerWidth) );
        
        // Front Plane - Inner
        planePoints[8].push_back( btVector3( origin.x() + halflengths.x() - innerWidth, origin.y() - halflengths.y() + innerWidth, origin.z() - halflengths.z() + innerWidth) );
        planePoints[8].push_back( btVector3( origin.x() + halflengths.x() - innerWidth, origin.y() - halflengths.y() + innerWidth, origin.z() + halflengths.z()) );
        planePoints[8].push_back( btVector3( origin.x() + halflengths.x() - innerWidth, origin.y() + halflengths.y() - innerWidth, origin.z() + halflengths.z()) );
        planePoints[8].push_back( btVector3( origin.x() + halflengths.x() - innerWidth, origin.y() + halflengths.y() - innerWidth, origin.z() - halflengths.z() + innerWidth) );
        
        // Bottom Plane - Inner
        
        planePoints[9].push_back( btVector3( origin.x() - halflengths.x() + innerWidth, origin.y() + halflengths.y() - innerWidth, origin.z() - halflengths.z() + innerWidth) );
        planePoints[9].push_back( btVector3( origin.x() - halflengths.x() + innerWidth, origin.y() - halflengths.y() + innerWidth, origin.z() - halflengths.z() + innerWidth) );
        planePoints[9].push_back( btVector3( origin.x() + halflengths.x() - innerWidth, origin.y() - halflengths.y() + innerWidth, origin.z() - halflengths.z() + innerWidth) );
        planePoints[9].push_back( btVector3( origin.x() + halflengths.x() - innerWidth, origin.y() + halflengths.y() - innerWidth, origin.z() - halflengths.z() + innerWidth) );
        // Left Plane - Connect
        planePoints[10].push_back( btVector3( origin.x() - halflengths.x(), origin.y() - halflengths.y(), origin.z() + halflengths.z()) );
        planePoints[10].push_back( btVector3( origin.x() - halflengths.x() + innerWidth, origin.y() - halflengths.y(), origin.z() + halflengths.z()) );
        planePoints[10].push_back( btVector3( origin.x() + halflengths.x() - innerWidth, origin.y() - halflengths.y(), origin.z() + halflengths.z()) );
        planePoints[10].push_back( btVector3( origin.x() + halflengths.x(), origin.y() - halflengths.y(), origin.z() + halflengths.z()) );
    
        // Back Plane - Connect
        planePoints[11].push_back( btVector3( origin.x() - halflengths.x(), origin.y() - halflengths.y(), origin.z() + halflengths.z()) );
        planePoints[11].push_back( btVector3( origin.x() - halflengths.x(), origin.y() - halflengths.y() + innerWidth, origin.z() + halflengths.z()) );
        planePoints[11].push_back( btVector3( origin.x() - halflengths.x(), origin.y() + halflengths.y() - innerWidth, origin.z() + halflengths.z()) );
        planePoints[11].push_back( btVector3( origin.x() - halflengths.x(), origin.y() + halflengths.y(), origin.z() + halflengths.z()) );
        
        // Right Plane - Connect
        planePoints[12].push_back( btVector3( origin.x() - halflengths.x(), origin.y() + halflengths.y(), origin.z() + halflengths.z()) );
        planePoints[12].push_back( btVector3( origin.x() - halflengths.x() + innerWidth, origin.y() + halflengths.y(), origin.z() + halflengths.z()) );
        planePoints[12].push_back( btVector3( origin.x() + halflengths.x() - innerWidth, origin.y() + halflengths.y(), origin.z() + halflengths.z()) );
        planePoints[12].push_back( btVector3( origin.x() + halflengths.x(), origin.y() + halflengths.y(), origin.z() + halflengths.z()) );
        
        // Front Plane - Connect
        planePoints[13].push_back( btVector3( origin.x() + halflengths.x(), origin.y() - halflengths.y(), origin.z() + halflengths.z()) );
        planePoints[13].push_back( btVector3( origin.x() + halflengths.x(), origin.y() - halflengths.y() + innerWidth, origin.z() + halflengths.z()) );
        planePoints[13].push_back( btVector3( origin.x() + halflengths.x(), origin.y() + halflengths.y() - innerWidth, origin.z() + halflengths.z()) );
        planePoints[13].push_back( btVector3( origin.x() + halflengths.x(), origin.y() + halflengths.y(), origin.z() + halflengths.z()) );
        
        
    }
    
    btConvexHullShape * boxPlanes [((innerWidth > 0) ? 14 : 5)];
    for (int i = 0; i < ((innerWidth > 0) ? 14 : 5); ++i) {
        if (i < 14 ) {
        boxPlanes[i] = new btConvexHullShape();
        for (int j = 0; j < 4; ++j)
            boxPlanes[i]->addPoint( planePoints[i][j] );
            
        boxShape->addChildShape (btTransform::getIdentity(), boxPlanes[i]);
        }
    }
    
    btDefaultMotionState* boxMotionState =
        new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1), *(btVector3*) &origin));
        
    btRigidBody * boxRigidBody;
    if (physEnabled) {
        btVector3 boxInertia(0,0,0);
        boxShape->calculateLocalInertia(btScalar(1), boxInertia);
        btRigidBody::btRigidBodyConstructionInfo boxRigidBodyCI(1, boxMotionState, boxShape, boxInertia);
        boxRigidBody = new btRigidBody(boxRigidBodyCI);
    } else {
        btRigidBody::btRigidBodyConstructionInfo boxRigidBodyCI(0, boxMotionState, boxShape, btVector3(0,0,0));
        boxRigidBody = new btRigidBody(boxRigidBodyCI);
    }
    dynamicsWorld->addRigidBody(boxRigidBody);
    rbodies.push_back(boxRigidBody);
    
    return numRigidBodies++;
}

int BulletHandler::addHollowBox( osg::Vec3 origin, osg::Vec3 halflengths, bool physEnabled ) {
    btCompoundShape* boxShape = new btCompoundShape();
    std::vector<btVector3> planePoints [6];
    
    // Left Plane
    planePoints[0].push_back( btVector3( origin.x() - halflengths.x(), origin.y() - halflengths.y(), origin.z() - halflengths.z()) );
    planePoints[0].push_back( btVector3( origin.x() - halflengths.x(), origin.y() - halflengths.y(), origin.z() + halflengths.z()) );
    planePoints[0].push_back( btVector3( origin.x() + halflengths.x(), origin.y() - halflengths.y(), origin.z() + halflengths.z()) );
    planePoints[0].push_back( btVector3( origin.x() + halflengths.x(), origin.y() - halflengths.y(), origin.z() - halflengths.z()) );
    
    // Back Plane
    planePoints[1].push_back( btVector3( origin.x() - halflengths.x(), origin.y() - halflengths.y(), origin.z() - halflengths.z()) );
    planePoints[1].push_back( btVector3( origin.x() - halflengths.x(), origin.y() - halflengths.y(), origin.z() + halflengths.z()) );
    planePoints[1].push_back( btVector3( origin.x() - halflengths.x(), origin.y() + halflengths.y(), origin.z() + halflengths.z()) );
    planePoints[1].push_back( btVector3( origin.x() - halflengths.x(), origin.y() + halflengths.y(), origin.z() - halflengths.z()) );
    
    // Right Plane
    planePoints[2].push_back( btVector3( origin.x() - halflengths.x(), origin.y() + halflengths.y(), origin.z() - halflengths.z()) );
    planePoints[2].push_back( btVector3( origin.x() - halflengths.x(), origin.y() + halflengths.y(), origin.z() + halflengths.z()) );
    planePoints[2].push_back( btVector3( origin.x() + halflengths.x(), origin.y() + halflengths.y(), origin.z() + halflengths.z()) );
    planePoints[2].push_back( btVector3( origin.x() + halflengths.x(), origin.y() + halflengths.y(), origin.z() - halflengths.z()) );
    
    // Front Plane
    planePoints[3].push_back( btVector3( origin.x() + halflengths.x(), origin.y() - halflengths.y(), origin.z() - halflengths.z()) );
    planePoints[3].push_back( btVector3( origin.x() + halflengths.x(), origin.y() - halflengths.y(), origin.z() + halflengths.z()) );
    planePoints[3].push_back( btVector3( origin.x() + halflengths.x(), origin.y() + halflengths.y(), origin.z() + halflengths.z()) );
    planePoints[3].push_back( btVector3( origin.x() + halflengths.x(), origin.y() + halflengths.y(), origin.z() - halflengths.z()) );
    
    // Top Plane
    planePoints[4].push_back( btVector3( origin.x() - halflengths.x(), origin.y() + halflengths.y(), origin.z() + halflengths.z()) );
    planePoints[4].push_back( btVector3( origin.x() - halflengths.x(), origin.y() - halflengths.y(), origin.z() + halflengths.z()) );
    planePoints[4].push_back( btVector3( origin.x() + halflengths.x(), origin.y() - halflengths.y(), origin.z() + halflengths.z()) );
    planePoints[4].push_back( btVector3( origin.x() + halflengths.x(), origin.y() + halflengths.y(), origin.z() + halflengths.z()) );
    
    // Bottom Plane
    planePoints[5].push_back( btVector3( origin.x() - halflengths.x(), origin.y() + halflengths.y(), origin.z() - halflengths.z()) );
    planePoints[5].push_back( btVector3( origin.x() - halflengths.x(), origin.y() - halflengths.y(), origin.z() - halflengths.z()) );
    planePoints[5].push_back( btVector3( origin.x() + halflengths.x(), origin.y() - halflengths.y(), origin.z() - halflengths.z()) );
    planePoints[5].push_back( btVector3( origin.x() + halflengths.x(), origin.y() + halflengths.y(), origin.z() - halflengths.z()) );
    
    btConvexHullShape * boxPlanes [6];
    for (int i = 0; i < 6; ++i) {
        boxPlanes[i] = new btConvexHullShape();
        for (int j = 0; j < 4; ++j)
            boxPlanes[i]->addPoint( planePoints[i][j] );
            
        boxShape->addChildShape (btTransform::getIdentity(), boxPlanes[i]);
    }
    
    btDefaultMotionState* boxMotionState =
        new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1), btVector3(origin.x(), origin.y(), origin.z())));
        
    btRigidBody * boxRigidBody;
    if (physEnabled) {
        btVector3 boxInertia(0,0,0);
        boxShape->calculateLocalInertia(btScalar(1), boxInertia);
        btRigidBody::btRigidBodyConstructionInfo boxRigidBodyCI(1, boxMotionState, boxShape, boxInertia);
        boxRigidBody = new btRigidBody(boxRigidBodyCI);
    } else {
        btRigidBody::btRigidBodyConstructionInfo boxRigidBodyCI(0, boxMotionState, boxShape, btVector3(0,0,0));
        boxRigidBody = new btRigidBody(boxRigidBodyCI);
    }
    dynamicsWorld->addRigidBody(boxRigidBody);
    rbodies.push_back(boxRigidBody);
    
    return numRigidBodies++;
}

int BulletHandler::addSphere( osg::Vec3 origin, double width, bool physEnabled ) {
    btCollisionShape* sphereShape = new btSphereShape( width );
    btDefaultMotionState* sphereMotionState =
        new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1), *(btVector3*)&origin));
        
    btRigidBody * sphereRigidBody;
    if (physEnabled) {
        btVector3 sphereInertia(0,0,0);
        sphereShape->calculateLocalInertia(btScalar(1), sphereInertia);
        btRigidBody::btRigidBodyConstructionInfo sphereRigidBodyCI(1, sphereMotionState, sphereShape, sphereInertia);
        sphereRigidBodyCI.m_linearSleepingThreshold = 50.0f;
        sphereRigidBody = new btRigidBody(sphereRigidBodyCI);
    } else {
        btRigidBody::btRigidBodyConstructionInfo sphereRigidBodyCI(0, sphereMotionState, sphereShape, btVector3(0,0,0));
        sphereRigidBody = new btRigidBody(sphereRigidBodyCI);
    }
    dynamicsWorld->addRigidBody(sphereRigidBody);
    rbodies.push_back(sphereRigidBody);
    
    return numRigidBodies++;
}

int BulletHandler::addCylinder( osg::Vec3 origin, osg::Vec3 halfLengths, bool physEnabled ) {
    btCollisionShape* cylShape = new btCylinderShapeZ( *(btVector3*) &halfLengths );
    btDefaultMotionState* cylMotionState =
        new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1), *(btVector3*)&origin));
        
    btRigidBody * cylRigidBody;
    if (physEnabled) {
        btVector3 cylInertia(0,0,0);
        cylShape->calculateLocalInertia(btScalar(1), cylInertia);
        btRigidBody::btRigidBodyConstructionInfo cylRigidBodyCI(1, cylMotionState, cylShape, cylInertia);
        cylRigidBodyCI.m_linearSleepingThreshold = 50.0f;
        cylRigidBody = new btRigidBody(cylRigidBodyCI);
    } else {
        btRigidBody::btRigidBodyConstructionInfo cylRigidBodyCI(0, cylMotionState, cylShape, btVector3(0,0,0));
        cylRigidBody = new btRigidBody(cylRigidBodyCI);
    }
    dynamicsWorld->addRigidBody(cylRigidBody);
    rbodies.push_back(cylRigidBody);
    
    return numRigidBodies++;
}

void BulletHandler::addAntiGravityField(osg::Vec3 pos, double halflength, osg::Vec3 grav) {
    btCollisionShape* ghostBox = new btBoxShape( btVector3(halflength,halflength,halflength) );
    AntiGravityField* avf = new AntiGravityField();
    
    btVector3 btGrav;
    btGrav.setValue(grav.x(), grav.y(), grav.z());
    //avf->setGravity( *(btVector3*) &grav );
    avf->setGravity(btGrav);
    avf->setCollisionShape( ghostBox );
    avf->setCollisionFlags(avf->getCollisionFlags() | btCollisionObject::CF_NO_CONTACT_RESPONSE);
    btVector3 btPos;
    btPos.setValue(pos.x(), pos.y(), pos.z());
//    avf->setWorldTransform( btTransform(btQuaternion(0,0,0,1), *(btVector3*) &pos) );
    avf->setWorldTransform( btTransform(btQuaternion(0,0,0,1), btPos) );
    dynamicsWorld->addCollisionObject(avf);
    
    avfs.push_back(avf);
    clavfs.push_back(avf);
    numavfs++;
    clnumavfs++;
}

void BulletHandler::setLinearVelocity( int id, osg::Vec3 vel ) {
    rbodies[id]->setLinearVelocity( *(btVector3*) &vel );
}

void BulletHandler::translate( int id, osg::Vec3 vel ) {
    rbodies[id]->translate( *(btVector3*) &vel );
}

osg::Vec3 BulletHandler::getLinearVelocity( int id ) {
    btVector3 lv = rbodies[id]->getLinearVelocity();
    return *(osg::Vec3*) &lv;
}

void BulletHandler::stepSim( double lastFrame ) {
    dynamicsWorld->stepSimulation( lastFrame, 10, 1./80. );
}

void BulletHandler::getWorldTransform( int id, osg::Matrixd & boxm ) {
    btTransform m;
    if (id >= numRigidBodies) {
        boxm.makeIdentity();
        return;
    }
    btMotionState* ms = rbodies[id]->getMotionState();
    if (ms) {
        ms->getWorldTransform(m);
        boxm.setTrans( *(osg::Vec3*) &m.getOrigin() );
        btQuaternion btquat = rbodies[id]->getOrientation();
        osg::Quat osgquat(btquat.x(),btquat.y(),btquat.z(),btquat.w());
        boxm.setRotate( osgquat );
    } else boxm.makeIdentity();
}

void BulletHandler::setWorldTransform( int id, osg::Matrixd & boxm ) {
    btTransform m;
    if (id >= numRigidBodies) return;
    
    btMotionState* ms = rbodies[id]->getMotionState();
    if (ms) {
        osg::Vec3 t = boxm.getTrans();
        btVector3 btv( t.x(), t.y(), t.z() );
    
        osg::Quat q = boxm.getRotate();
        btQuaternion btq( q.x(), q.y(), q.z(), q.w() );
        btTransform btt(btq, btv);
        //std::cout << *(osg::Vec3*) &btt.getOrigin() << "\n";
        rbodies[id]->setCenterOfMassTransform(btt);
        ms->setWorldTransform(btt);
        rbodies[id]->setLinearVelocity(btv);
        dynamicsWorld->synchronizeSingleMotionState( rbodies[id] );
    }
}

void BulletHandler::addHand(osg::Vec3 pos, osg::Vec3 halfLengths) {
    btVector3 btHalfLength;
    btHalfLength.setValue(halfLengths.x(), halfLengths.y(), halfLengths.y());
//    btCollisionShape* ghostBox = new btCylinderShapeZ( *(btVector3*) &halfLengths );
    btCollisionShape* ghostBox = new btCylinderShapeZ( btHalfLength );
    AntiGravityField* avf = new AntiGravityField();
    avf->setGravity( btVector3(0,0,0) );
    avf->setCollisionShape( ghostBox );
    avf->setCollisionFlags(avf->getCollisionFlags() | btCollisionObject::CF_NO_CONTACT_RESPONSE);
    btVector3 btPos;
    btPos.setValue(pos.x(), pos.y(), pos.z());
    avf->setWorldTransform( btTransform(btQuaternion(0,0,0,1), btPos) );
    dynamicsWorld->addCollisionObject(avf);
    
    //if (hand) delete hand;
    hand = avf;
}

void BulletHandler::moveHand(osg::Matrixd & boxm ) {
  if (!hand) return;
    
  osg::Vec3 t = boxm.getTrans();
  btVector3 btv( t.x(), t.y(), t.z() );

  osg::Quat q = boxm.getRotate();
  btQuaternion btq( q.x(), q.y(), q.z(), q.w() );
  btTransform btt(btq, btv);
  //std::cout << *(osg::Vec3*) &btt.getOrigin() << "\n";
  //hand->setCenterOfMassTransform(btt);
  hand->setWorldTransform(btt);
  if (closest) {
    btMotionState* ms = closest->getMotionState();
    if (ms) {
        btTransform btt(btq, btv);
        //std::cout << *(osg::Vec3*) &btt.getOrigin() << "\n";
        closest->setCenterOfMassTransform(btt);
        ms->setWorldTransform(btt);
        closest->setLinearVelocity(btVector3(0,0,0));
        dynamicsWorld->synchronizeSingleMotionState( closest );
    }
    //btv = hand->getWorldTransform().getOrigin();
    //std::cout << "GhostHand: " << btv.x() << ", " << btv.y() << ", " << btv.z() << "\n";
  }
}

void BulletHandler::updateButtonState( int bs ) {
  prevButtonState = buttonState;
  buttonState = bs;
}

btDiscreteDynamicsWorld* BulletHandler::getDynamicsWorld() {
    return dynamicsWorld;
}

void BulletHandler::setGravity( osg::Vec3 g ) {
    dynamicsWorld->setGravity( *(btVector3*) &g );
}
