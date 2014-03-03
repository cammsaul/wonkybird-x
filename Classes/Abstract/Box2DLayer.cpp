//
//  Box2DLayer.cpp
//  WonkyBird
//
//  Created by Cam Saul on 3/3/14.
//
//

#include "Box2DLayer.h"
#include "Constants.h"

Box2DLayer::Box2DLayer(const string& textureAtlasName):
	GameLayer(textureAtlasName),
	world_({0, kGravityVelocity})
{
}