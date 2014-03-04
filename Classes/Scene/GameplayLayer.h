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
#include "Bird.h"

class GameplayLayer : public Box2DLayer {
public:
	GameplayLayer();
	
	virtual void update(float dt) override;
private:
	void AddBird(shared_ptr<Bird> bird);

	unordered_set<shared_ptr<Bird>> birds_;
};

#endif