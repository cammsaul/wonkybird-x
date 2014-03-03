//
//  GameLayer.cpp
//  WonkyBird
//
//  Created by Cam Saul on 3/3/14.
//
//
#include <sprite_nodes/CCSpriteFrameCache.h>

#include "GameLayer.h"

GameLayer::GameLayer(const std::string& textureAtlasName):
spriteBatchNode_ {}
{
	auto plistFilename = (textureAtlasName + "@2x.plist");
	auto textureFilename = (textureAtlasName + "@2x.png");
	spriteBatchNode_.initWithFile(textureFilename.c_str(), 20);
	cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(plistFilename.c_str(), textureFilename.c_str());
	
	addChild(&spriteBatchNode_);
}