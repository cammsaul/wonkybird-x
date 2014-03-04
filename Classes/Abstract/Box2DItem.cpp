//
//  Box2DItem.cpp
//  WonkyBird
//
//  Created by Cam Saul on 3/3/14.
//
//

#include "Box2DItem.h"

Box2DItem::Box2DItem():
	body_(nullptr),
	bodyDef_(),
	shape_(),
	fixture_()
{}

Box2DItem::~Box2DItem() {
	RemoveFromWorld();
}

b2Vec2 Box2DItem::PositionForBox2D() const {
	return {0, 0};
}

b2Vec2 Box2DItem::ContentSizeForBox2D() const {
	return {0, 0};
}

void Box2DItem::UpdateShape() {
	shape_.SetAsBox(ContentSizeForBox2D().x / 2.0f, ContentSizeForBox2D().y / 2.0f);
}

void Box2DItem::AddToWorld(b2World& world) {
	bodyDef_.position = PositionForBox2D();
	UpdateShape();
}

void Box2DItem::RemoveFromWorld() {
	if (body_) {
		body_->GetWorld()->DestroyBody(body_);
		body_ = nullptr;
	}
}

void Box2DItem::MoveToNewPosition() {
	
}