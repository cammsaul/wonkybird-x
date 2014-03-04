//
//  GameLayer.h
//  WonkyBird
//
//  Created by Cam Saul on 3/3/14.
//
//

#ifndef WONKYBIRD_GAMELAYER_H
#define WONKYBIRD_GAMELAYER_H

class GameLayer : public CCLayer {
public:
	GameLayer(const string& textureAtlasName);
private:
	CCSpriteBatchNode spriteBatchNode_;
};

#endif