//
//  GameLayer.cpp
//  WonkyBird
//
//  Created by Cam Saul on 3/3/14.
//
//
#include "GameLayer.h"

GameLayer::GameLayer(const string& textureAtlasName):
	BasicLayer()
{
	auto plistFilename = (textureAtlasName + "@2x.plist");
	auto textureFilename = (textureAtlasName + "@2x.png");
	spriteBatchNode_ = SpriteBatchNode::create(textureFilename);
	spriteBatchNode_->initWithFile(textureFilename, 20);
	cocos2d::SpriteFrameCache::getInstance()->addSpriteFramesWithFile(plistFilename.c_str(), spriteBatchNode_->getTexture());
	
	addChild(spriteBatchNode_.Get());
}