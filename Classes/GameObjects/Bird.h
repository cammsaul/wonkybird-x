//
//  Bird.h
//  WonkyBird
//
//  Created by Cam Saul on 3/3/14.
//
//

#ifndef WONKYBIRD_BIRD_H
#define WONKYBIRD_BIRD_H

#include "GameSprite.h"

class Bird;
using BirdPtr = shared_ptr<Bird>;
using Flock = unordered_set<BirdPtr>;

class Bird : public GameSprite {
public:
	enum class State {
		Dead,
		Falling,
		Flapping
	};
	
	Bird(const string& spriteFrameName);
	virtual ~Bird();
	
	enum State State() const { return state_; }
	virtual void SetState(enum State birdState) { state_ = birdState; }
	
	virtual void ApplyTouch(unsigned numFrames) = 0; ///< apply a touch to the bird when GameState is active
	virtual void FlapAroundOnMainScreen(Flock otherBirds) = 0; ///< Instruct the bird to start flapping around main screen
protected:
	enum State state_;
};

#endif