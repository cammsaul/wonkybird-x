//
//  GameSprite.h
//  WonkyBird
//
//  Created by Cam Saul on 3/3/14.
//
//

#ifndef WONKYBIRD_GAMESPRITE_H
#define WONKYBIRD_GAMESPRITE_H

#include "Box2DItem.h"

class GameSprite : public CCSprite, public Box2DItem {
public:
	GameSprite(const string& spriteFrameName);
	virtual ~GameSprite() = default;
private:
};

#endif