//
//  Box2DItem.h
//  WonkyBird
//
//  Created by Cam Saul on 3/3/14.
//
//

#ifndef WONKYBIRD_Box2DItem_H
#define WONKYBIRD_Box2DItem_H

class Box2DItem {
public:
	Box2DItem();
	
	virtual ~Box2DItem();
	
	b2Vec2 PositionForBox2D() const;
	b2Vec2 ContentSizeForBox2D() const;
	
	virtual void UpdateShape(); ///< set shape of the fixture right before it's added to world. Default implementation just creates box to match ContentSizeForBox2D()
	
	void AddToWorld(b2World& world);
	void RemoveFromWorld();
	void MoveToNewPosition();
private:
	b2Body *body_;
	b2BodyDef bodyDef_;
	b2PolygonShape shape_;
	b2FixtureDef fixture_;
};

#endif