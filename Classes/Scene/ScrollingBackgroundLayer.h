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

class ScrollingBackgroundLayer : public GameLayer {
public:
	ScrollingBackgroundLayer();
	
	virtual void update(float dt) override;
private:
	class TiledMapWithBox2D: public CCTMXTiledMap, public Box2DItem {
		virtual b2Vec2 PositionForBox2D() const override;
		virtual void SetPositionForBox2D(const b2Vec2& pos) override;
		virtual b2Vec2 ContentSizeForBox2D() const override;
	};
	CCUniquePtr<TiledMapWithBox2D> grass_;
	
	void CreateCloud();
	void ResetCloud(CCUniquePtr<CCSprite>&& cloud);
	void CloudResetCallback(CCNode* node);
};

#endif