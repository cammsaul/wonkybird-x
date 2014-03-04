//
//  HUDLayer.cpp
//  WonkyBird
//
//  Created by Cam Saul on 3/3/14.
//
//

#include "HUDLayer.h"
#include "GameManager.h"

static const string TitleLabelKey			= "Title.png";
static const string GetReadyLabelKey		= "Get_Ready.png";
static const string GameOverLabelKey		= "Game_Over.png";
static const string PlayButtonKey			= "Button_Play.png";
static const string RateButtonKey			= "Button_Rate.png";
static const string LeaderBoardButtonKey	= "Button_Leader_Board.png";
static const string ScoreBackgroundKey		= "Score_Background.png";
static const string CopyrightLabelKey		= "LuckyBird_2014.png";
static const string TapLeftKey				= "Button_Tap_Left.png";
static const string TapRightKey				= "Button_Tap_Right.png";
static const string TapFingerKey			= "Finger.png";
static const string TwitterButtonKey		= "Button_Twitter.png";
static const string FacebookButtonKey		= "Button_Facebook.png";
static const string TwitterGrayButtonKey	= "Button_Twitter_Gray.png";
static const string FacebookGrayButtonKey	= "Button_Facebook_Gray.png";

struct HUDSpriteInfo {
	GameState states;
	CCPoint position;	
};

HUDLayer::HUDLayer():
GameLayer("HUD"),
spriteInfo_(),
sprites_(),
scoreLabel_(),
scoreBoardScoreLabel_(),
scoreBoardBestLabel_()
{
	const float labelYPosition = ScreenHeight() * 0.75f;
	const float rateButtonY = ScreenHeight() * 0.45f;
	const float otherButtonsY = ScreenHeight() * 0.3f;
	const float scoreboardYPosition = (labelYPosition + rateButtonY) / 2.0f;
	const float scoreboardScoreYPosition = scoreboardYPosition + 12.0f;
	const float scoreboardBestYPosition = scoreboardYPosition - 28.0f;
	
	const CCPoint labelPosition = ccp(ScreenHalfWidth(), labelYPosition);
	static const GameState ButtonStates = (GameState)(GStateMainMenu|GStateGameOver);
	
	scoreLabel_.initWithString("", "Font_Score_Large.fnt");
	scoreLabel_.setPosition(ccp(ScreenHalfWidth(), ScreenHeight() * 0.9f));
	addChild(&scoreLabel_, 0);
	
	scoreBoardScoreLabel_.initWithString("10", "Font_Score_Small.fnt");
	scoreBoardScoreLabel_.setPosition(ccp(ScreenHalfWidth(), scoreboardScoreYPosition));
	addChild(&scoreBoardScoreLabel_, 1);
	
	scoreBoardBestLabel_.initWithString("100", "Font_Score_Small.fnt");
	scoreBoardBestLabel_.setPosition(ccp(ScreenHalfWidth(), scoreboardBestYPosition));
	addChild(&scoreBoardBestLabel_, 1);
	
	spriteInfo_[TitleLabelKey]			= { GStateMainMenu,		labelPosition };
	spriteInfo_[GetReadyLabelKey]		= { GStateGetReady,		labelPosition };
	spriteInfo_[GameOverLabelKey]		= { GStateGameOver,		labelPosition };
	spriteInfo_[CopyrightLabelKey]		= { GStateMainMenu,		ccp(ScreenHalfWidth(), ScreenHeight() * 0.15f) };
	spriteInfo_[ScoreBackgroundKey]		= { GStateGameOver,		ccp(ScreenHalfWidth(), scoreboardYPosition) };
	spriteInfo_[PlayButtonKey]			= { ButtonStates,		ccp(ScreenWidth() * 0.25f, otherButtonsY) };
	spriteInfo_[LeaderBoardButtonKey]	= { ButtonStates,		ccp(ScreenWidth() * 0.75f, otherButtonsY) };
	spriteInfo_[RateButtonKey]			= { ButtonStates,		ccp(ScreenWidth() * 0.5f, rateButtonY) };
	spriteInfo_[TapLeftKey]				= { GStateGetReady,		ccp(ScreenWidth() * 0.3f, ScreenHeight() * BirdGetReadyHeight) };
	spriteInfo_[TapRightKey]			= { GStateGetReady,		ccp(ScreenWidth() * 0.7f, ScreenHeight() * BirdGetReadyHeight) };
	spriteInfo_[TapFingerKey]			= { GStateGetReady,		ccp(ScreenHalfWidth(), ScreenHeight() * (BirdGetReadyHeight - 0.08f)) };
	spriteInfo_[TwitterButtonKey]		= { GStateGameOver,		ccp(ScreenWidth() * 0.3f, scoreboardYPosition) };
	spriteInfo_[FacebookButtonKey]		= { GStateGameOver,		ccp(ScreenWidth() * 0.7f, scoreboardYPosition) };
	spriteInfo_[TwitterGrayButtonKey]	= { GStateGameOver,		ccp(ScreenWidth() * 0.3f, scoreboardYPosition) };
	spriteInfo_[FacebookGrayButtonKey]	= { GStateGameOver,		ccp(ScreenWidth() * 0.7f, scoreboardYPosition) };
	
	for (auto itr = spriteInfo_.begin(); itr != spriteInfo_.end(); itr++) {
		const auto& key = itr->first;
		sprites_[key] = unique_ptr<CCSprite>(nullptr);
	}
	
	scheduleUpdate();
	setTouchEnabled(true);
}

void HUDLayer::registerWithTouchDispatcher() {
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, YES);
}

void HUDLayer::AddSpriteWithKeyIfNeeded(const string* key) {
	unique_ptr<CCSprite>& sprite = sprites_[*key];
	if (sprite) return;
	
	sprite = unique_ptr<CCSprite>(new CCSprite {});
	sprite->initWithSpriteFrameName(key->c_str());
	sprite->setPosition(spriteInfo_[*key].second);
	spriteBatchNode_.addChild(sprite.get());
}

void HUDLayer::RemoveSpriteCallback(CCNode *node, const string* key) {
	node->removeFromParentAndCleanup(true);
	sprites_[*key] = nullptr;
}

void HUDLayer::RemoveSpriteWithKeyIfNeeded(const string* key) {
	unique_ptr<CCSprite>& sprite = sprites_[*key];
	if (!sprite) return;
	
	auto* seq = CCSequence::createWithTwoActions(CCSequence::createWithTwoActions(CCScaleBy::create(HUDSpriteRemovalDuration, 4.0f), CCFadeOut::create(HUDSpriteRemovalDuration)),
												 CCCallFuncND::create(this, callfuncND_selector(HUDLayer::RemoveSpriteCallback), (void *)key));
	sprite->runAction(seq);
}

void HUDLayer::AddOrReomveSpriteWithKey(const string* key, GameState states) {
	if (GState() & states)	AddSpriteWithKeyIfNeeded(key);
	else					RemoveSpriteWithKeyIfNeeded(key);
}


void HUDLayer::update(float delta) {
	if (GState() != LastFrameState()) {
		for (const auto& spriteInfo : spriteInfo_) {
			const auto* key = &spriteInfo.first;
			const GameState& states = spriteInfo.second.first;
			AddOrReomveSpriteWithKey(key, states);
		}
		
		scoreLabel_.setVisible(GStateIsActive());
		scoreBoardBestLabel_.setVisible(GStateIsGameOver());
		scoreBoardScoreLabel_.setVisible(GStateIsGameOver());
	}
	
	if (GStateIsGetReady()) {
		static float timeSinceLastTap = 0;
		timeSinceLastTap += delta;
		if (timeSinceLastTap > 0.8f) {
			timeSinceLastTap = 0;
			auto& tapSprite = sprites_[TapFingerKey];
			tapSprite->setScale(0.8f);
			tapSprite->runAction(CCScaleTo::create(0.25f, 1.0f));
		}
	}
	if (GStateIsActive()) {
		scoreLabel_.setString(to_string(GameManager::sharedInstance()->TotalScore()).c_str());
	} else if (GStateIsGameOver()) {
		scoreBoardScoreLabel_.setString(to_string(GameManager::sharedInstance()->TotalScore()).c_str());
		scoreBoardBestLabel_.setString(to_string(GameManager::sharedInstance()->BestTotalScore()).c_str());
	}
}

bool HUDLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent) {
	if (GStateIsActive()) return false;
	
	auto TouchedSprite = [&](const string& spriteKey) -> CCSprite* {
		auto& sprite = sprites_[spriteKey];
		return (sprite && sprite->boundingBox().containsPoint(pTouch->getLocationInView())) ? sprite.get() : nullptr;
	};
	for (auto spriteKey : vector<string>{PlayButtonKey, RateButtonKey, LeaderBoardButtonKey}) {
		if (auto sprite = TouchedSprite(spriteKey)) {
			sprite->setScale(0.9f);
		}
	}
	return true;
}

void HUDLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent) {
	if (GStateIsActive()) return;
	
	auto TouchOnSprite = [=](const string& spriteKey) -> bool {
		auto& sprite = sprites_[spriteKey];
		return sprite && sprite->boundingBox().containsPoint(pTouch->getLocation()) && sprite->isVisible();
//		if (touched) {
//			[[Mixpanel sharedInstance] track:[NSString stringWithFormat:@"button_touch_%@", spriteKey]];
//		}
	};
	
	for (auto spriteKey : vector<string>{PlayButtonKey, RateButtonKey, LeaderBoardButtonKey}) {
		if (auto& sprite = sprites_[spriteKey]) {
			sprite->setScale(1.0f);
		}
	}
	
	if (GState() & GameState(GStateMainMenu|GStateGameOver)) {
		if (TouchOnSprite(PlayButtonKey)) {
			SetGState(GStateGetReady);
		}
		else if (TouchOnSprite(RateButtonKey))
		{
//			NSNumber *appID = [NSBundle mainBundle].infoDictionary[@"LBAppID"];
//			NSAssert([appID intValue], @"Set the key 'LBAppID' in the app's info.plist!");
//			[[UIApplication sharedApplication] openURL:[NSURL URLWithString:[NSString stringWithFormat:@"itms-apps://itunes.apple.com/app/id%@", appID]]];
		}
		else if (TouchOnSprite(LeaderBoardButtonKey))
		{
//			[[GameKitManager sharedInstance] showLeaderboard];
		}
		else if (TouchOnSprite(TwitterGrayButtonKey))
		{
//			[self shareToTwitter];
		}
		else if (TouchOnSprite(TwitterButtonKey))
		{
//			[TwitterManager sharedInstance].enableShareToTwitter = NO;
//			self[TwitterButtonKey].visible = NO;
//			self[TwitterGrayButtonKey].visible = YES;
		}
		else if (TouchOnSprite(FacebookGrayButtonKey))
		{
//			[self shareToFB];
		}
		else if (TouchOnSprite(FacebookButtonKey))
		{
//			[FacebookShare sharedInstance].enableShareToFB = NO;
//			self[FacebookButtonKey].visible = NO;
//			self[FacebookGrayButtonKey].visible = YES;
		}
		return;
	}
	if (GStateIsGetReady()) {
		SetGState(GStateActive);
	}
}

