//
//  GameLayer.h
//  WonkyBird
//
//  Created by Cam Saul on 3/3/14.
//
//

#ifndef WONKYBIRD_GAMELAYER_H
#define WONKYBIRD_GAMELAYER_H

class GameLayer : public cocos2d::CCLayer {
public:
	GameLayer(const std::string& textureAtlasName);
private:
	cocos2d::CCSpriteBatchNode spriteBatchNode_;
};

#endif