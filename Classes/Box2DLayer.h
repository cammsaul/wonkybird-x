//
//  Box2DLayer.h
//  WonkyBird
//
//  Created by Cam Saul on 3/3/14.
//
//

#ifndef WONKYBIRD_Box2DLayer_H
#define WONKYBIRD_Box2DLayer_H

#include "GameLayer.h"
#include "GLES-Render.h"

class Box2DLayer : public GameLayer {
public:
	Box2DLayer(const string& textureAtlasName);
	
	b2World& World() { return world_; }
	
	virtual void draw() override;
	virtual void update(float dt) override;
protected:
	b2World world_;
private:
	GLESDebugDraw debugDraw_;
};

#endif