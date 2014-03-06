//
//  GameplayLayer.h
//  WonkyBird
//
//  Created by Cam Saul on 3/3/14.
//
//

#ifndef WONKYBIRD_GAMEPLAYLAYER_H
#define WONKYBIRD_GAMEPLAYLAYER_H

#include "Box2DLayer.h"
#include "GameNode.h"
#include "Bird.h"
#include "Pipe.h"
#include "GameListener.h"

class GameplayLayer : public Box2DLayer {
public:
	GameplayLayer();
	
	virtual void update(float dt) override;
	virtual bool onTouchBegan(Touch* touch, Event* event) override;
    virtual void onTouchEnded(Touch* touch, Event* event) override;
	
	BirdPtr& CurrentBird();
private:
	struct Impl;
	shared_ptr<Impl> impl;
};

#endif