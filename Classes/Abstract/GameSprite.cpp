//
//  GameSprite.cpp
//  WonkyBird
//
//  Created by Cam Saul on 3/3/14.
//
//

#include "GameSprite.h"

GameSprite::GameSprite():
	body_(nullptr),
	bodyDef_(),
	shape_(),
	fixture_()
{}

GameSprite::~GameSprite() {
	removeFromWorld();
}

b2Vec2 GameSprite::PositionForBox2D() const {
	return {0, 0};
}

b2Vec2 GameSprite::ContentSizeForBox2D() const {
	return {0, 0};
}

void GameSprite::addToWorld(b2World& world) {
	
}

void GameSprite::removeFromWorld() {
	body_->GetWorld()->DestroyBody(body_);
	body_ = nullptr;
}

void GameSprite::moveToNewPosition() {
	
}