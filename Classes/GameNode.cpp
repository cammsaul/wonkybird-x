//
//  GameNode.cpp
//  WonkyBird
//
//  Created by Cam Saul on 3/3/14.
//
//

#include "GameNode.h"

GameNode::GameNode() {
	printf("GameNode()\n");
}

GameNode::~GameNode() {
	printf("~GameNode()\n");
}


void GameNode::SetPositionFromBox2D(const b2Vec2& pos) {
	setPosition({pos.x * kPTMRatio, pos.y * kPTMRatio});
}

float GameNode::getPositionX() const { return getPosition().x; }
float GameNode::getPositionY() const { return getPosition().y; }

bool GameNode::IsOffscreen() const {
	return X() < -(getContentSize().width / 2.0f);
}

b2Vec2 GameNode::PositionForBox2D() const {
	return { getPositionX() / kPTMRatio, getPositionY() / kPTMRatio };
}

b2Vec2 GameNode::ContentSizeForBox2D() const {
	return { getContentSize().width / kPTMRatio, getContentSize().height / kPTMRatio };
}

float GameNode::X() const { return getPositionX(); }
float GameNode::Y() const { return getPositionY(); }
void GameNode::SetX(float x) { setPosition({x, Y()}); }
void GameNode::SetY(float y) { setPosition({X(), y}); }

void GameNode::Update(float dt) {} // default implementation does nothing


const Point& GameSprite::getPosition() const {
	return Sprite::getPosition();
}

void GameSprite::setPosition(const Point &position) {
	Sprite::setPosition(position);
}

const Size& GameSprite::getContentSize() const {
	return Sprite::getContentSize();
}