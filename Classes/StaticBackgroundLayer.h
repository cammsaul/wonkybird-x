//
//  StaticBackgroundLayer.h
//  WonkyBird
//
//  Created by Cam Saul on 3/3/14.
//
//

#ifndef WONKYBIRD_STATICBACKGROUNDLAYER_H
#define WONKYBIRD_STATICBACKGROUNDLAYER_H

#include "GameLayer.h"

class StaticBackgroundLayer : public BasicLayer {
public:
	StaticBackgroundLayer();
		
	virtual void update(float dt) override;
private:
	struct Impl;
	unique_ptr<Impl> impl_;
};

#endif
