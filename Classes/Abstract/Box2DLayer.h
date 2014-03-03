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

class Box2DLayer : public GameLayer {
public:
	Box2DLayer(const string& textureAtlasName);
private:
	b2World world_;
};

#endif