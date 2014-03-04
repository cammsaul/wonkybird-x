//
//  Box2DItem.cpp
//  WonkyBird
//
//  Created by Cam Saul on 3/3/14.
//
//

#include "Box2DItem.h"

Box2DItem::Box2DItem():
	body_		(nullptr),
	bodyDef_	(make_shared<b2BodyDef>()),
	shape_		(make_shared<b2PolygonShape>()),
	fixtureDef_	(make_shared<b2FixtureDef>())
{
	fixtureDef_->shape = shape_.get();
	bodyDef_->type = b2_dynamicBody;
}

Box2DItem::~Box2DItem() {
	RemoveFromWorld();
}

void Box2DItem::UpdateShape() {
	assert(ContentSizeForBox2D().x && ContentSizeForBox2D().y);
	shape_->SetAsBox(ContentSizeForBox2D().x / 2.0f, ContentSizeForBox2D().y / 2.0f);
	assert(shape_->m_vertexCount >= 3);
	assert(fixtureDef_->shape == shape_.get());
}

void Box2DItem::AddToWorld(b2World& world) {
	bodyDef_->position = PositionForBox2D();
	UpdateShape();
	
	body_ = world.CreateBody(bodyDef_.get());
	body_->SetUserData(this);
	body_->SetActive(true);
	
	CreateFixtures();
}

void Box2DItem::CreateFixtures() {
	body_->CreateFixture(fixtureDef_.get());
}

void Box2DItem::RemoveFromWorld() {
	if (body_) {
		body_->GetWorld()->DestroyBody(body_);
		body_ = nullptr;
	}
}

void Box2DItem::MoveToNewPosition() {
	assert(body_);
	auto* world = body_->GetWorld();
	RemoveFromWorld();
	AddToWorld(*world);
}