//
//  Pigeon.cpp
//  WonkyBird
//
//  Created by Cam Saul on 3/3/14.
//
//

#include "Pigeon.h"
#include "Toucan.h"

Pigeon::Pigeon():
	Bird("Pigeon_1.png")
{}

void Pigeon::ApplyTouch(unsigned numFrames) {
	
}

void Pigeon::FlapAroundOnMainScreen(Flock allBirds) {
	auto RandTimes10 = []{ return Rand() * kBirdMenuRandVelocity; };
	
	if (ABS(YVelocity()) < 2) {
		const float BirdXDiff = (X() - ScreenHalfWidth()) / ScreenHalfWidth(); /// < 1.0 = right edge, -1.0 = left
		
		const float newYVel = -kGravityVelocity * ((ScreenHeight() * kBirdMenuHeight) - Y()) * Rand() * Rand() * 0.1f;
		
		const float xVel = (Rand() > .5f) ? (RandTimes10() * -BirdXDiff) : ((RandTimes10() * 2) - kBirdMenuRandVelocity);
		Body()->ApplyForceToCenter({xVel, newYVel});
		
		// move away from toucans
		for (BirdPtr bird : allBirds) {
			if (bird.get() == this) continue;
			if (typeid(*bird) == typeid(Toucan)) {
				Body()->ApplyForceToCenter({(Box2DX() - bird->Box2DX()) / 10.0f, (Box2DY() - bird->Box2DY()) * 2.0f});
			}
		}
	}
}