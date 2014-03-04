//
//  Box2DLayer.cpp
//  WonkyBird
//
//  Created by Cam Saul on 3/3/14.
//
//

#include "Box2DLayer.h"

Box2DLayer::Box2DLayer(const string& textureAtlasName):
	GameLayer(textureAtlasName),
	world_({0, kGravityVelocity}),
	debugDraw_(kPTMRatio)
{
	world_.SetDebugDraw(&debugDraw_);
	debugDraw_.SetFlags(b2Draw::e_shapeBit);
//	scheduleUpdate();
//	this->schedule(schedule_selector(Box2DLayer::update), 0, 1, 0);
}

void Box2DLayer::draw() {
	ccGLEnableVertexAttribs(kCCVertexAttribFlag_Position);
	kmGLPushMatrix();
	
	world_.DrawDebugData();
	
	kmGLPopMatrix();
}

void Box2DLayer::update(float dt) {
	printf("Box2DLayer::update\n");
}