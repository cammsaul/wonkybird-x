//
//  GameSprite.h
//  WonkyBird
//
//  Created by Cam Saul on 3/3/14.
//
//

#ifndef WONKYBIRD_GAMESPRITE_H
#define WONKYBIRD_GAMESPRITE_H

#include "Box2DItem.h"

class GameNode : public virtual CCNode, public virtual Box2DItem {
public:
	virtual void SetPositionForBox2D(const b2Vec2& pos) override;
	virtual b2Vec2 PositionForBox2D() const override;
	
	virtual b2Vec2 ContentSizeForBox2D() const override;
	
	bool IsOffscreen() const { return X() < -(getContentSize().width / 2.0f); }
	
	float X() const { return getPositionX(); }
	float Y() const { return getPositionY(); }
	void SetX(float x) { setPosition({x, Y()}); }
	void SetY(float y) { setPosition({X(), y}); }
	
	virtual void Update(float dt);
};

class GameSprite : public virtual CCSprite, public virtual GameNode {
public:
	GameSprite(); ///< game sprite with no image, e.g. for use as wall, etc
	GameSprite(const string& spriteFrameName);
	virtual ~GameSprite();
private:
};

#endif