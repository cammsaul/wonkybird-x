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