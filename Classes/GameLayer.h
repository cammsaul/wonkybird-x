//
//  GameLayer.h
//  WonkyBird
//
//  Created by Cam Saul on 3/3/14.
//
//

#ifndef WONKYBIRD_GAMELAYER_H
#define WONKYBIRD_GAMELAYER_H

#include "NoCopy.h"

/// Layer subclass that disables moving/copying
class BasicLayer : public Layer, private NoCopy, private NoMove {
protected:
	BasicLayer() = default;
};

class GameLayer : public BasicLayer {
public:
	GameLayer(const string& textureAtlasName);
protected:
	GamePtr<SpriteBatchNode> spriteBatchNode_;
};

#endif