//
//  HUDLayer.h
//  WonkyBird
//
//  Created by Cam Saul on 3/3/14.
//
//

#ifndef WONKYBIRD_HUDLAYER_H
#define WONKYBIRD_HUDLAYER_H

#include "GameLayer.h"

class HUDLayer : public GameLayer {
public:
	HUDLayer();
	
	virtual void update(float dt) override;
	virtual bool onTouchBegan(Touch* touch, Event* event) override;
    virtual void onTouchEnded(Touch* touch, Event* event) override;
private:
	struct Impl;
	unique_ptr<Impl> impl;
};

#endif