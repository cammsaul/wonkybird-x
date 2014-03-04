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
	
	shared_ptr<b2BodyDef> BodyDef()			{ return bodyDef_; }
	shared_ptr<b2FixtureDef> FixtureDef()	{ return fixtureDef_; }
	shared_ptr<b2PolygonShape> Shape()		{ return shape_; }
	
	virtual b2Vec2 PositionForBox2D() const = 0;
	virtual void SetPositionForBox2D(const b2Vec2& pos) = 0;
	
	virtual b2Vec2 ContentSizeForBox2D() const = 0;
	
	virtual void UpdateShape(); ///< set shape of the fixture right before it's added to world. Default implementation just creates box to match ContentSizeForBox2D()
	virtual void CreateFixtures(); ///< override to create custom fixture(s) for a body after it has been added to world. Default implementation is body_->CreateFixture(&fixtureDef_)
	
	void AddToWorld(b2World& world);
	void RemoveFromWorld();
	void MoveToNewPosition();
private:
	b2Body* body_;
	shared_ptr<b2BodyDef> bodyDef_;
	shared_ptr<b2PolygonShape> shape_;
	shared_ptr<b2FixtureDef> fixtureDef_;
};

#endif