//
//  GameLayer.h
//  WonkyBird
//
//  Created by Cam Saul on 3/3/14.
//
//

#ifndef WONKYBIRD_GAMELAYER_H
#define WONKYBIRD_GAMELAYER_H

#include <memory>
#include <cocos2d.h>

using namespace cocos2d;
using namespace std;

class GameLayer : public CCLayer {
public:
	GameLayer(const string& textureAtlasName);
private:
	CCSpriteBatchNode spriteBatchNode_;
};

#endif