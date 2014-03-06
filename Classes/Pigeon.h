//
//  Pigeon.h
//  WonkyBird
//
//  Created by Cam Saul on 3/3/14.
//
//

#ifndef WONKYBIRD_PIGEON_H
#define WONKYBIRD_PIGEON_H

#include "Bird.h"

class Pigeon : public Bird {
public:
//	Pigeon();
	virtual ~Pigeon();
	virtual const Metaclass* const MetaClass() const override;
	
	virtual void ApplyTouch(unsigned numFrames) override;
	virtual void FlapAroundOnMainScreen(Flock allBirds) override;
private:
};

#endif