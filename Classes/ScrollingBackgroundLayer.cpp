//
//  ScrollingBackgroundLayer.cpp
//  WonkyBird
//
//  Created by Cam Saul on 3/3/14.
//
//

#include "ScrollingBackgroundLayer.h"
#include "MainScene.h"
#include "GameManager.h"

ScrollingBackgroundLayer::ScrollingBackgroundLayer():
	GameLayer("Clouds"),
	grass_(new TiledMapWithBox2D("Grass.tmx"))
{
	// create the grass
	addChild(dynamic_cast<Node*>(grass_.Get()));
	grass_->setPosition(Point(0, GroundHeight() - 32.0f));
	grass_->BodyDef()->type = b2_dynamicBody;
	grass_->FixtureDef()->filter.categoryBits = 0;
	grass_->BodyDef()->gravityScale = 0;
	grass_->AddToWorld(MainScene::GetBox2DLayer().World());

	scheduleUpdate();
}

void ScrollingBackgroundLayer::update(float dt) {
	if (GState() != LastFrameState()) {
		for (auto* node : spriteBatchNode_->getChildren()) {
			if (auto* child =  dynamic_cast<Sprite *>(node)) {
				if (GStateIsGameOver()) {
					child->stopAllActions();
				} else {
					ResetCloud(std::move(child));
				}
			}
		}
	}
	
	auto pos = grass_->getPosition();
	if (pos.x < - 80.0f) {
		pos.x += 80.0f;
		grass_->setPosition(pos);
		grass_->MoveToNewPosition();
	} else if (pos.x > 0.0f) {
		pos.x -= 80.0f;
		grass_->setPosition(pos);
		grass_->MoveToNewPosition();
	}
	
	grass_->Body()->SetLinearVelocity({PipeXVelocity * GameManager::sharedInstance().GameSpeed(), 0});
}

void ScrollingBackgroundLayer::CreateCloud() {
	const int cloudToDraw = random() % 2; ///< which of the 6 cloud assets to draw
	string frameName = "Cloud_" + to_string(cloudToDraw + 1) + ".png";
	auto cloud = Sprite::createWithSpriteFrameName(frameName);
	spriteBatchNode_->addChild(cloud);
	ResetCloud(cloud);
}

void ScrollingBackgroundLayer::ResetCloud(Node* cloud) {
	const float cloudHalfWidth = cloud->boundingBox().size.width / 2.0f;
	
	const int xPosition = GameManager::sharedInstance().IsReversed() ? -cloudHalfWidth : (ScreenWidth() + cloudHalfWidth);
	
	const int yMin = (int)ScreenHeight() * 0.33f;
	const int yMax = (int)ScreenHeight();
	const int yRange = yMax - yMin;
	const int yPosition = (random() % yRange) + yMin;
	
	cloud->setPosition({xPosition, yPosition});
	
	const int MaxCloudMoveDuration = GStateIsActive() ? 8 : 40;
	const int MinCloudMoveDuration = GStateIsActive() ? 2 : 20;
	const int moveDuration = (random() % (MaxCloudMoveDuration - MinCloudMoveDuration)) + MinCloudMoveDuration;
	
	const float offscreenXPosition = GameManager::sharedInstance().IsReversed() ? (ScreenWidth() + cloudHalfWidth) : -cloudHalfWidth;
	
	cloud->runAction(CCSequence::createWithTwoActions(CCMoveTo::create(moveDuration, Point(offscreenXPosition, cloud->getPositionY())),
													  CCCallFuncN::create([&](Node* node){
		ResetCloud(node);
	})));
	
	const int newZOrder = MaxCloudMoveDuration - moveDuration;
	cloud->setScale((((MaxCloudMoveDuration - moveDuration) / (float)MaxCloudMoveDuration) * 0.5f) + 0.5f);
	spriteBatchNode_->reorderChild(cloud, newZOrder);
}
