//
//  Box2DLayer.cpp
//  WonkyBird
//
//  Created by Cam Saul on 3/3/14.
//
//

#include "Box2DLayer.h"
#include "Box2DItem.h"

Box2DLayer::Box2DLayer(const string& textureAtlasName):
	GameLayer(textureAtlasName),
	world_({0, kGravityVelocity}),
	debugDraw_(kPTMRatio)
{
	world_.SetDebugDraw(&debugDraw_);
	debugDraw_.SetFlags(b2Draw::e_shapeBit);
}

void Box2DLayer::draw() {
	ccGLEnableVertexAttribs(kCCVertexAttribFlag_Position);
	kmGLPushMatrix();
	
	world_.DrawDebugData();
	
	kmGLPopMatrix();
}

void Box2DLayer::update(float dt) {
	world_.Step(dt, Box2DLayerVelocityIterations, Box2DLayerPositionIterations);
	
	auto* body = world_.GetBodyList();
	while (body) {
		Box2DItem *item = static_cast<Box2DItem *>(body->GetUserData());
		item->SetPositionForBox2D(body->GetPosition());
		body = body->GetNext();
	}
}