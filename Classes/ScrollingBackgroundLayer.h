//
//  ScrollingBackgroundLayer.h
//  WonkyBird
//
//  Created by Cam Saul on 3/3/14.
//
//

#ifndef WONKYBIRD_SCROLLINGBACKGROUNDLAYER_H
#define WONKYBIRD_SCROLLINGBACKGROUNDLAYER_H

#include "GameLayer.h"
#include "Box2DItem.h"
#include "TiledMapWithBox2D.h"

class ScrollingBackgroundLayer : public GameLayer {
public:
	ScrollingBackgroundLayer();
	
	virtual void update(float dt) override;
private:
	GamePtr<TiledMapWithBox2D> grass_;
	
	void CreateCloud();
	void ResetCloud(Node* cloud);
	void CloudResetCallback(Node* node);
};

#endif