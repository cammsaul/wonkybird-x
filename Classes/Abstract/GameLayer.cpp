//
//  GameLayer.cpp
//  WonkyBird
//
//  Created by Cam Saul on 3/3/14.
//
//

#include "GameLayer.h"

GameLayer::GameLayer(const string& textureAtlasName):
textureAtlas_ {},
spriteBatchNode_ {}
{
	textureAtlas_.initWithFile((textureAtlasName + "@2x.png").c_str(), 20); // capacity = 20 (?)
	spriteBatchNode_.setTextureAtlas(&textureAtlas_);
	
	addChild(&spriteBatchNode_);
}