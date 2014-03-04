//
//  Toucan.cpp
//  WonkyBird
//
//  Created by Cam Saul on 3/3/14.
//
//

#include "Toucan.h"

Toucan::Toucan():
	Bird("Toucan_1.png")
{}

void Toucan::ApplyTouch(unsigned numFrames) {
	SetYVelocity(-kGravityVelocity * (.05f + (.075f * numFrames)));
}

void Toucan::FlapAroundOnMainScreen() {
	
}