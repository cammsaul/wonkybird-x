//
//  Toucan.cpp
//  WonkyBird
//
//  Created by Cam Saul on 3/3/14.
//
//

#include "Toucan.h"
#include "Pigeon.h"

const Metaclass* const Toucan::MetaClass() const {
	static const Metaclass m = { "Toucan" };
	return &m;
}

void Toucan::ApplyTouch(unsigned numFrames) {
	SetYVelocity(-kGravityVelocity * (.05f + (.075f * numFrames)));
}

void Toucan::FlapAroundOnMainScreen(Flock allBirds) {
	auto RandTimes10 = []{ return Rand() * kBirdMenuRandVelocity; };
	
	if (ABS(YVelocity()) < 2) {
		const float BirdXDiff = (X() - ScreenHalfWidth()) / ScreenHalfWidth(); /// < 1.0 = right edge, -1.0 = left
		
		static const float MinAntiGravityAmount = 0.0f;
		static const float MaxAntiGravityAmount = 0.7f;
		static const float AntiGravityRange = MaxAntiGravityAmount - MinAntiGravityAmount;
		static const int NumAntiGravityTurnsBeforeChanging = 200;
		static int NumAntiGravityTurns = NumAntiGravityTurnsBeforeChanging;
		static float AntiGravityAmount = MinAntiGravityAmount; // amount of gravity to apply on home screen will be random
		if (NumAntiGravityTurns > NumAntiGravityTurnsBeforeChanging) {
			AntiGravityAmount = (Rand() / (1.0/AntiGravityRange)) + MinAntiGravityAmount;
			NumAntiGravityTurns = 0;
		}
		NumAntiGravityTurns++;
		
		const float heightCorrectionVel = ((ScreenHeight() * kBirdMenuHeight) - Y()) * Rand() * AntiGravityAmount * 0.1f; ///< add neccessary velocity to keep Bird around the right y spot during flapping
		
		const float newYVel = (-kGravityVelocity * AntiGravityAmount) + heightCorrectionVel + RandTimes10();
		
		const float xVel = (Rand() > .5f) ? (RandTimes10() * -BirdXDiff) : ((RandTimes10() * 2) - kBirdMenuRandVelocity);
		Body()->ApplyForceToCenter({xVel, newYVel});
		
		// move towards pigeons
		for (BirdPtr bird : allBirds) {
			if (bird.get() == this) continue;
			if (bird->MetaClass()->Name() == "Pigeon") {
				Body()->ApplyForceToCenter({(bird->Box2DX() - Box2DX()) * 0.5f, (bird->Box2DY() - Box2DY()) * 0.5f});
			}
		}
		
		if (ABS(YVelocity()) < 2.0f) {
			Body()->ApplyTorque(-RotationBox2D());
		}
	}
}