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

typedef pair<GameState, Point> SpriteInfo;

struct HUDLayer::Impl {
	HUDLayer& this_;
	Impl(HUDLayer& parent):
		this_(parent)
	{}
	
	unordered_map<string, SpriteInfo> spriteInfo_ = {};
	unordered_map<string, GamePtr<Sprite>> sprites_ = {};
	LabelBMFont scoreLabel_ = {};
	LabelBMFont scoreBoardScoreLabel_ = {};
	LabelBMFont scoreBoardBestLabel_ = {};
	
	void AddSpriteWithKeyIfNeeded(const string* key);
	void RemoveSpriteWithKeyIfNeeded(const string *key);
	void AddOrReomveSpriteWithKey(const string* key, GameState states);
	
	void RemoveSpriteCallback(Node *node, const string* key);
};

HUDLayer::HUDLayer():
	GameLayer("HUD"),
	impl_(new Impl(*this))
{
	const float labelYPosition = ScreenHeight() * 0.75f;
	const float rateButtonY = ScreenHeight() * 0.45f;
	const float otherButtonsY = ScreenHeight() * 0.3f;
	const float scoreboardYPosition = (labelYPosition + rateButtonY) / 2.0f;
	const float scoreboardScoreYPosition = scoreboardYPosition + 12.0f;
	const float scoreboardBestYPosition = scoreboardYPosition - 28.0f;
	
	const Point labelPosition = Point(ScreenHalfWidth(), labelYPosition);
	static const GameState ButtonStates = (GameState)(GStateMainMenu|GStateGameOver);
	
	impl_->scoreLabel_.initWithString("", "Font_Score_Large.fnt");
	impl_->scoreLabel_.setPosition(Point(ScreenHalfWidth(), ScreenHeight() * 0.9f));
	addChild(&impl_->scoreLabel_, 0);
	
	impl_->scoreBoardScoreLabel_.initWithString("10", "Font_Score_Small.fnt");
	impl_->scoreBoardScoreLabel_.setPosition(Point(ScreenHalfWidth(), scoreboardScoreYPosition));
	addChild(&impl_->scoreBoardScoreLabel_, 1);
	
	impl_->scoreBoardBestLabel_.initWithString("100", "Font_Score_Small.fnt");
	impl_->scoreBoardBestLabel_.setPosition(Point(ScreenHalfWidth(), scoreboardBestYPosition));
	addChild(&impl_->scoreBoardBestLabel_, 1);
	
	impl_->spriteInfo_[TitleLabelKey]			= { GStateMainMenu,		labelPosition };
	impl_->spriteInfo_[GetReadyLabelKey]		= { GStateGetReady,		labelPosition };
	impl_->spriteInfo_[GameOverLabelKey]		= { GStateGameOver,		labelPosition };
	impl_->spriteInfo_[CopyrightLabelKey]		= { GStateMainMenu,		Point(ScreenHalfWidth(), ScreenHeight() * 0.15f) };
	impl_->spriteInfo_[ScoreBackgroundKey]		= { GStateGameOver,		Point(ScreenHalfWidth(), scoreboardYPosition) };
	impl_->spriteInfo_[PlayButtonKey]			= { ButtonStates,		Point(ScreenWidth() * 0.25f, otherButtonsY) };
	impl_->spriteInfo_[LeaderBoardButtonKey]	= { ButtonStates,		Point(ScreenWidth() * 0.75f, otherButtonsY) };
	impl_->spriteInfo_[RateButtonKey]			= { ButtonStates,		Point(ScreenWidth() * 0.5f, rateButtonY) };
	impl_->spriteInfo_[TapLeftKey]				= { GStateGetReady,		Point(ScreenWidth() * 0.3f, ScreenHeight() * BirdGetReadyHeight) };
	impl_->spriteInfo_[TapRightKey]				= { GStateGetReady,		Point(ScreenWidth() * 0.7f, ScreenHeight() * BirdGetReadyHeight) };
	impl_->spriteInfo_[TapFingerKey]			= { GStateGetReady,		Point(ScreenHalfWidth(), ScreenHeight() * (BirdGetReadyHeight - 0.08f)) };
	impl_->spriteInfo_[TwitterButtonKey]		= { GStateGameOver,		Point(ScreenWidth() * 0.3f, scoreboardYPosition) };
	impl_->spriteInfo_[FacebookButtonKey]		= { GStateGameOver,		Point(ScreenWidth() * 0.7f, scoreboardYPosition) };
	impl_->spriteInfo_[TwitterGrayButtonKey]	= { GStateGameOver,		Point(ScreenWidth() * 0.3f, scoreboardYPosition) };
	impl_->spriteInfo_[FacebookGrayButtonKey]	= { GStateGameOver,		Point(ScreenWidth() * 0.7f, scoreboardYPosition) };
	
	for (auto itr = impl_->spriteInfo_.begin(); itr != impl_->spriteInfo_.end(); itr++) {
		const auto& key = itr->first;
		impl_->sprites_[key] = nullptr;
	}
	
	scheduleUpdate();
	setTouchEnabled(true);
}

void HUDLayer::Impl::AddSpriteWithKeyIfNeeded(const string* key) {
	auto sprite = sprites_[*key];
	if (sprite) return;
	
	sprite = GamePtr<Sprite>(Sprite::createWithSpriteFrameName(*key));
	sprite->setPosition(spriteInfo_[*key].second);
	this_.spriteBatchNode_->addChild(sprite.Get());
}

void HUDLayer::Impl::RemoveSpriteCallback(Node *node, const string* key) {
	
}

void HUDLayer::Impl::RemoveSpriteWithKeyIfNeeded(const string* key) {
	auto sprite = sprites_[*key];
	if (!sprite) return;
	
	auto* seq = CCSequence::createWithTwoActions(CCSequence::createWithTwoActions(CCScaleBy::create(HUDSpriteRemovalDuration, 4.0f), CCFadeOut::create(HUDSpriteRemovalDuration)),
												 CallFuncN::create([&](Node* node){
		node->removeFromParentAndCleanup(true);
		sprites_[*key] = nullptr;
	}));
	
	sprite->runAction(seq);
}

void HUDLayer::Impl::AddOrReomveSpriteWithKey(const string* key, GameState states) {
	if (GState() & states)	AddSpriteWithKeyIfNeeded(key);
	else					RemoveSpriteWithKeyIfNeeded(key);
}


void HUDLayer::update(float delta) {
	if (GState() != LastFrameState()) {
		for (const auto& spriteInfo : impl_->spriteInfo_) {
			const auto* key = &spriteInfo.first;
			const GameState& states = spriteInfo.second.first;
			impl_->AddOrReomveSpriteWithKey(key, states);
		}
		
		impl_->scoreLabel_.setVisible(GStateIsActive());
		impl_->scoreBoardBestLabel_.setVisible(GStateIsGameOver());
		impl_->scoreBoardScoreLabel_.setVisible(GStateIsGameOver());
	}
	
	if (GStateIsGetReady()) {
		static float timeSinceLastTap = 0;
		timeSinceLastTap += delta;
		if (timeSinceLastTap > 0.8f) {
			timeSinceLastTap = 0;
			auto& tapSprite = impl_->sprites_[TapFingerKey];
			tapSprite->setScale(0.8f);
			tapSprite->runAction(CCScaleTo::create(0.25f, 1.0f));
		}
	}
	if (GStateIsActive()) {
		impl_->scoreLabel_.setString(to_string(GameManager::sharedInstance().TotalScore()).c_str());
	} else if (GStateIsGameOver()) {
		impl_->scoreBoardScoreLabel_.setString(to_string(GameManager::sharedInstance().TotalScore()).c_str());
		impl_->scoreBoardBestLabel_.setString(to_string(GameManager::sharedInstance().BestTotalScore()).c_str());
	}
}

bool HUDLayer::onTouchBegan(Touch *pTouch, Event *pEvent) {
	if (GStateIsActive()) return false;
	
	auto TouchedSprite = [&](const string& spriteKey) -> Sprite* {
		auto& sprite = impl_->sprites_[spriteKey];
		return (sprite && sprite->boundingBox().containsPoint(pTouch->getLocationInView())) ? sprite.Get() : nullptr;
	};
	for (auto spriteKey : vector<string>{PlayButtonKey, RateButtonKey, LeaderBoardButtonKey}) {
		if (auto sprite = TouchedSprite(spriteKey)) {
			sprite->setScale(0.9f);
		}
	}
	return true;
}

void HUDLayer::onTouchEnded(Touch *pTouch, Event *pEvent) {
	if (GStateIsActive()) return;
	
	auto TouchOnSprite = [=](const string& spriteKey) -> bool {
		auto& sprite = impl_->sprites_[spriteKey];
		return sprite && sprite->boundingBox().containsPoint(pTouch->getLocation()) && sprite->isVisible();
//		if (touched) {
//			[[Mixpanel sharedInstance] track:[NSString stringWithFormat:@"button_touch_%@", spriteKey]];
//		}
	};
	
	for (auto spriteKey : vector<string>{PlayButtonKey, RateButtonKey, LeaderBoardButtonKey}) {
		if (auto& sprite = impl_->sprites_[spriteKey]) {
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

