//
//  Pigeon.cpp
//  WonkyBird
//
//  Created by Cam Saul on 3/3/14.
//
//

#include "Pigeon.h"
#include "Toucan.h"

const Metaclass* const Pigeon::MetaClass() const {
	static const Metaclass m = { "Pigeon" };
	return &m;
}

Pigeon::~Pigeon() {}

void Pigeon::ApplyTouch(unsigned numFrames) {
	if (YVelocity() < 0) {
		SetYVelocity(-GravityVelocity() * 0.6f);
		
		const float angle = RotationBox2D();
		Body()->ApplyTorque(-angle);
	}
}

void Pigeon::FlapAroundOnMainScreen(Flock allBirds) {
	auto RandTimes10 = []{ return Rand() * kBirdMenuRandVelocity; };
	
	if (abs(YVelocity()) < 2) {
		const float BirdXDiff = (X() - ScreenHalfWidth()) / ScreenHalfWidth(); /// < 1.0 = right edge, -1.0 = left
		
		const float newYVel = -GravityVelocity() * ((ScreenHeight() * kBirdMenuHeight) - Y()) * Rand() * Rand() * 0.1f;
		
		const float xVel = (Rand() > .5f) ? (RandTimes10() * -BirdXDiff) : ((RandTimes10() * 2) - kBirdMenuRandVelocity);
		Body()->ApplyForceToCenter({xVel, newYVel});
		
		// move away from toucans
		for (BirdPtr bird : allBirds) {
			if (bird.get() == this) continue;
			if (bird->MetaClass()->Name() == "Toucan") {
				Body()->ApplyForceToCenter({(Box2DX() - bird->Box2DX()) / 10.0f, (Box2DY() - bird->Box2DY()) * 2.0f});
			}
		}
	}
}