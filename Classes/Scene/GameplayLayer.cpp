//
//  GameplayLayer.cpp
//  WonkyBird
//
//  Created by Cam Saul on 3/3/14.
//
//

#include "GameplayLayer.h"

GameplayLayer::GameplayLayer():
	Box2DLayer("Textures"),
	birds_ {}
{
	scheduleUpdate();
}

void GameplayLayer::update(float dt) {
	Box2DLayer::update(dt);
	printf("GameplayLayer::update\n");
}