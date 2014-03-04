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

class Bird : public GameSprite {
public:
	Bird();
	virtual Bird() = default;
	
	virtual void ApplyTouch(unsigned numFrames) = 0;	///< apply a touch to the bird when GameState is active
	virtual void FlapAroundOnMainScreen() = 0;			///< Instruct the bird to start flapping around main screen
private:
};

#endif