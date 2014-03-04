//
//  HUDLayer.h
//  WonkyBird
//
//  Created by Cam Saul on 3/3/14.
//
//

#ifndef WONKYBIRD_HUDLAYER_H
#define WONKYBIRD_HUDLAYER_H

#include "GameLayer.h"

class HUDLayer : public GameLayer {
public:
	HUDLayer();
private:
	unordered_map<string, unique_ptr<CCSprite>> sprites_;
};

#endif