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
	addChild(dynamic_cast<CCNode*>(grass_.get()));
	grass_->setPosition(ccp(0, GroundHeight() - 32.0f));
	grass_->BodyDef()->type = b2_dynamicBody;
	grass_->FixtureDef()->filter.categoryBits = 0;
	grass_->BodyDef()->gravityScale = 0;
	grass_->AddToWorld(MainScene::SharedInstance().Box2DLayer().World());

	scheduleUpdate();
}

void ScrollingBackgroundLayer::update(float dt) {
	if (GState() != LastFrameState()) {
		CCUniquePtr<CCArray> children { spriteBatchNode_.getChildren()};
		for (int i = 0; i < children->count(); i++) {
			CCUniquePtr<CCSprite> child { dynamic_cast<CCSprite *>(children->objectAtIndex(i)) };
			if (GStateIsGameOver()) {
				child->stopAllActions();
			} else {
				ResetCloud(std::move(child));
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
	CCUniquePtr<CCSprite> cloud {};
	string frameName = "Cloud_" + to_string(cloudToDraw + 1) + ".png";
	cloud->initWithSpriteFrameName(frameName.c_str());
	spriteBatchNode_.addChild(cloud.get());
	ResetCloud(std::move(cloud));
}

void ScrollingBackgroundLayer::ResetCloud(CCUniquePtr<CCSprite>&& cloud) {
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
	
	cloud->runAction(CCSequence::createWithTwoActions(CCMoveTo::create(moveDuration, ccp(offscreenXPosition, cloud->getPositionY())),
													  CCCallFuncN::create(this, callfuncN_selector(ScrollingBackgroundLayer::CloudResetCallback))));
	
	const int newZOrder = MaxCloudMoveDuration - moveDuration;
	cloud->setScale((((MaxCloudMoveDuration - moveDuration) / (float)MaxCloudMoveDuration) * 0.5f) + 0.5f);
	spriteBatchNode_.reorderChild(cloud.get(), newZOrder);
}

void ScrollingBackgroundLayer::CloudResetCallback(CCNode* node) {
	ResetCloud(CCUniquePtr<CCSprite>{ dynamic_cast<CCSprite*>(node) });
}
