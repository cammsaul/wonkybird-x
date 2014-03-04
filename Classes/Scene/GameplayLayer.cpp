//
//  GameplayLayer.cpp
//  WonkyBird
//
//  Created by Cam Saul on 3/3/14.
//
//

#include "GameplayLayer.h"
#include "Toucan.h"

GameplayLayer::GameplayLayer():
	Box2DLayer("Textures"),
	birds_ {}
{
	scheduleUpdate();
}

void GameplayLayer::update(float dt) {
	Box2DLayer::update(dt);
	
	static bool hasAddedBird = false;
	if (!hasAddedBird) {
		hasAddedBird = true;
		AddBird(make_shared<Toucan>(Toucan{}));
	}
}

void GameplayLayer::AddBird(shared_ptr<Bird> bird) {
	birds_.insert(bird);
	bird->setPosition({ScreenHalfWidth(), ScreenHeight() * kBirdMenuHeight});
	spriteBatchNode_.addChild(bird.get());
	bird->AddToWorld(world_);
}