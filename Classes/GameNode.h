//
//  GameNode.h
//  WonkyBird
//
//  Created by Cam Saul on 3/3/14.
//
//

#ifndef WONKYBIRD_GameNode_H
#define WONKYBIRD_GameNode_H

#include "Box2DItem.h"
#include "NoCopy.h"

class GameNode : public Box2DItem, private NoCopy, private NoMove {
public:
	GameNode();
	virtual ~GameNode();
	
	virtual const Point& getPosition() const = 0;
	virtual void setPosition(const Point &position) = 0;
	virtual const Size& getContentSize() const = 0;
	
	virtual float getPositionX() const;
	virtual float getPositionY() const;
		
	virtual void SetPositionFromBox2D(const b2Vec2& pos) override;
	virtual b2Vec2 PositionForBox2D() const override;

	virtual b2Vec2 ContentSizeForBox2D() const override;
	
	bool IsOffscreen() const;
	
	float X() const;
	float Y() const;
	void SetX(float x);
	void SetY(float y);
	
	virtual void Update(float dt);
};

class GameSprite : public Sprite, public GameNode {
public:
	virtual const Point& getPosition() const override;
	virtual void setPosition(const Point &position) override;
	virtual const Size& getContentSize() const override;
};

#endif