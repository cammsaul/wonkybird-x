//
//  Toucan.h
//  WonkyBird
//
//  Created by Cam Saul on 3/3/14.
//
//

#ifndef WONKYBIRD_TOUCAN_H
#define WONKYBIRD_TOUCAN_H

#include "Bird.h"

class Toucan : public Bird {
public:
	Toucan();
	virtual ~Toucan() = default;
	
	virtual void ApplyTouch(unsigned numFrames) override;
	virtual void FlapAroundOnMainScreen() override;
private:
};

#endif