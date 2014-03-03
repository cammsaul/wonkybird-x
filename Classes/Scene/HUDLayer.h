//
//  HUDLayer.h
//  WonkyBird
//
//  Created by Cam Saul on 3/3/14.
//
//

#ifndef WONKYBIRD_HUDLAYER_H
#define WONKYBIRD_HUDLAYER_H

#include <memory>
#include <unordered_map>

#include <cocos2d.h>
#include "GameLayer.h"

using namespace cocos2d;
using namespace std;

class HUDLayer : public GameLayer {
public:
	HUDLayer();
private:
	unordered_map<std::string, unique_ptr<CCSprite>> sprites_;
};

#endif