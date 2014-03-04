//
//  GameSprite.cpp
//  WonkyBird
//
//  Created by Cam Saul on 3/3/14.
//
//

#include "GameSprite.h"

void GameNode::SetPositionForBox2D(const b2Vec2& pos) {
	CCNode::setPosition(pos.x * kPTMRatio, pos.y * kPTMRatio);
}

b2Vec2 GameNode::PositionForBox2D() const {
	return { getPositionX() / kPTMRatio, getPositionY() / kPTMRatio };
}

b2Vec2 GameNode::ContentSizeForBox2D() const {
	return { getContentSize().width / kPTMRatio, getContentSize().height / kPTMRatio };
}

void GameNode::Update(float dt) {} // default implementation does nothing

GameSprite::GameSprite() {}

GameSprite::~GameSprite() {}

GameSprite::GameSprite(const string& spriteFrameName) {
	initWithSpriteFrameName(spriteFrameName.c_str());
}