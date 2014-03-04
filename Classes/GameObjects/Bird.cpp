//
//  Bird.cpp
//  WonkyBird
//
//  Created by Cam Saul on 3/3/14.
//
//

#include "Bird.h"

Bird::Bird(const string& spriteFrameName):
	GameSprite(spriteFrameName)
{}

Bird::~Bird() {
	printf("~Bird()\n");
}