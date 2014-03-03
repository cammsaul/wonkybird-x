//
//  GameLayer.cpp
//  WonkyBird
//
//  Created by Cam Saul on 3/3/14.
//
//

#include "GameLayer.h"

GameLayer::GameLayer(const string& textureAtlasName):
spriteBatchNode_ {}
{
	auto plistFilename = (textureAtlasName + "@2x.plist");
	auto textureFilename = (textureAtlasName + "@2x.png");
	spriteBatchNode_.initWithFile(textureFilename.c_str(), 20);
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(plistFilename.c_str(), textureFilename.c_str());
	
	addChild(&spriteBatchNode_);
}