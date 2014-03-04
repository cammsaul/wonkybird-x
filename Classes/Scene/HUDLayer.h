//
//  HUDLayer.h
//  WonkyBird
//
//  Created by Cam Saul on 3/3/14.
//
//

#ifndef WONKYBIRD_HUDLAYER_H
#define WONKYBIRD_HUDLAYER_H

#include "GameLayer.h"

class HUDLayer : public GameLayer {
public:
	HUDLayer();
	
	virtual void update(float dt) override;
	virtual void registerWithTouchDispatcher() override;
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent) override;
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent) override;
private:
	typedef pair<GameState, CCPoint> SpriteInfo;
	unordered_map<string, SpriteInfo> spriteInfo_;
	unordered_map<string, unique_ptr<CCSprite>> sprites_;
	CCLabelBMFont scoreLabel_;
	CCLabelBMFont scoreBoardScoreLabel_;
	CCLabelBMFont scoreBoardBestLabel_;
	
	void AddSpriteWithKeyIfNeeded(const string* key);
	void RemoveSpriteWithKeyIfNeeded(const string *key);
	void AddOrReomveSpriteWithKey(const string* key, GameState states);
	
	void RemoveSpriteCallback(CCNode *node, const string* key);
};

#endif