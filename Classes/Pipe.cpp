//
//  Pipe.cpp
//  WonkyBird
//
//  Created by Cam Saul on 3/4/14.
//
//

#include "Pipe.h"
#include "GameManager.h"

static const int kTileSize = 64; ///< in pixels

Pipe::Pipe(unsigned size, bool upsideDown):
	TiledMapWithBox2D("Pipe.tmx"),
	upsideDown_ (upsideDown),
	numRows_	(size),
	cleared_	(false),
	layerName_  ("Pipe_" + to_string(size) + (upsideDown ? "R" : "")),
	layer_		(getLayer(layerName_.c_str()))
{
	layer_->removeFromParentAndCleanup(false);
	
	FixtureDef()->density = 100.0f;
}

Pipe::~Pipe() {
	printf("~Pipe()\n");
}

const Size& Pipe::getContentSize() const {
	Size size = {layer_->getContentSize().width, layer_->getContentSize().height};
	size.height = numRows_ * kTileSize;
	size.width *= 0.9f;
	contentSize_ = size;
	return contentSize_;
}

void Pipe::AddToWorld(b2World& world) {
	Box2DItem::AddToWorld(world);
	startPosition_ = getPosition();
}

void Pipe::Update(float dt) {
	if (!cleared_) {
		if ((startPosition_.x > ScreenHalfWidth() && X() < ScreenHalfWidth()) || (startPosition_.x < ScreenHalfWidth() && X() > ScreenHalfWidth())) {
			cleared_ = true;
			if (!upsideDown_) {
				GameManager::sharedInstance().IncrementScore();
			}
		}
	}
}

void Pipe::setPosition(const Point& pos) {
	Node::setPosition(pos);
	layer_->setPosition({pos.x - kTileSize, pos.y - getContentSize().height / 2.0f});
}
