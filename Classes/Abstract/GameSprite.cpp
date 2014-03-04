//
//  GameSprite.cpp
//  WonkyBird
//
//  Created by Cam Saul on 3/3/14.
//
//

#include "GameSprite.h"

GameSprite::GameSprite(const string& spriteFrameName) {
	initWithSpriteFrameName(spriteFrameName.c_str());
}

void GameSprite::SetPositionForBox2D(const b2Vec2& pos) {
	CCNode::setPosition(pos.x * kPTMRatio, pos.y * kPTMRatio);
}

b2Vec2 GameSprite::PositionForBox2D() const {
	return { getPositionX() / kPTMRatio, getPositionY() / kPTMRatio };
}

b2Vec2 GameSprite::ContentSizeForBox2D() const {
	return { getContentSize().width / kPTMRatio, getContentSize().height / kPTMRatio };
}