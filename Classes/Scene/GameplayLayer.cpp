//
//  GameplayLayer.cpp
//  WonkyBird
//
//  Created by Cam Saul on 3/3/14.
//
//

#include "GameplayLayer.h"
#include "Toucan.h"
#include "Pigeon.h"
#include "GameManager.h"

float MaxTotalSize() {
	return MIN((InitialMaxSize + (CurrentRoundScore() / 2)), MaxMaxSize);
}

float RandomPipeSize() {
	const int SizeRange = MaxTotalSize() - (MinPipeSize * 2);
	return (random() % SizeRange) + MinPipeSize;
}


GameplayLayer::GameplayLayer():
	Box2DLayer("Textures"),
	birds_    (),
	toucan_   (nullptr),
	pigeon_   (nullptr),
	mainBird_ (nullptr),
	ground_   (),
	pipes_	  ()
{
	// add the ground
	ground_.BodyDef()->type = b2_staticBody;
	ground_.setPosition({ScreenHalfWidth(), GroundHeight() / 2.0f});
	ground_.setContentSize({ScreenWidth() * 2 /* extend out past edges a bit */, GroundHeight()});
	ground_.FixtureDef()->density = 0.0f;
	ground_.FixtureDef()->friction = 0.8f;
	ground_.AddToWorld(world_);
	
	// TODO : add the roof
	
	scheduleUpdate();
	setTouchEnabled(true);
}

void GameplayLayer::registerWithTouchDispatcher() {
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, YES);
}

void GameplayLayer::update(float dt) {
	Box2DLayer::update(dt);
	
	if (GStateIsMainMenu()) {
		UpdateMainMenu(dt);
	} else if (GStateIsGetReady()) {
		UpdateGetReady(dt);
	} else if (GStateIsActive()) {
		UpdateActive(dt);
	} else if (GStateIsGameOver()) {
		UpdateGameOver(dt);
	}
	
	auto gameObjects = CCUniquePtr<CCArray>(spriteBatchNode_.getChildren());
//	const auto count = gameObjects->count();
	for (int i = 0; i < gameObjects->count(); i++) {
		CCUniquePtr<CCObject> gameObject { gameObjects->objectAtIndex(i) };
		CCUniquePtr<GameSprite> gameSprite { dynamic_cast<GameSprite *>(gameObject.get()) };
		if (gameSprite) {
			gameSprite->Update(dt);
		}
	}
}

void GameplayLayer::UpdateMainMenu(float dt) {
	if (!toucan_) toucan_ = AddBird<Toucan>();
	if (!pigeon_) pigeon_ = AddBird<Pigeon>();
	toucan_->FlapAroundOnMainScreen(birds_);
	pigeon_->FlapAroundOnMainScreen(birds_);
	
	if (!CurrentBird()) {
		SetMainBird(toucan_);
	}
}

void GameplayLayer::UpdateGetReady(float dt) {
	if (LastFrameState() != GStateGetReady && LastFrameState() != GStateMainMenu) {
		// switch out the birds
		if (typeid(*CurrentBird()) == typeid(Toucan)) {
			if (!pigeon_) pigeon_ = AddBird<Pigeon>();
			SetMainBird(pigeon_);
			
			auto mask = ~GStateRound1;
			SetGState((GState() & mask)|GStateRound2);
		} else if (!toucan_) { toucan_ = AddBird<Toucan>();
			SetMainBird(toucan_);
			
			auto mask = ~GStateRound2;
			SetGState((GState() & mask)|GStateRound1);
		}
	}
	
	for (auto b : birds_) if (b != CurrentBird()) {
		b->SetXVelocity(PipeXVelocity * GameManager::sharedInstance().GameSpeed());
		if (b->X() < -(b->getContentSize().width / 2.0f)) {
			RemoveBird(b);
			break; // don't remove any more birds this round, since RemoveBird() affects birds_
		}
	}
	
	CurrentBird()->SetState(Bird::State::Flapping);
	const float BirdYDiff = ((CurrentBird()->Y() - (ScreenHeight() * BirdGetReadyHeight)) / kPTMRatio) * 4;
	const float BirdXDiff = ((CurrentBird()->X() - ScreenHalfWidth()) / kPTMRatio) * 4;
	CurrentBird()->SetVelocity({-BirdXDiff, -BirdYDiff});
	
	for (auto pipe : pipes_) {
		removeChild(pipe->Layer().get(), true);
	}
	pipes_.clear();
}

void GameplayLayer::UpdateActive(float dt) {
	if (LastFrameScore() != GStateActive) {
		RemoveExtraBirds();
		CurrentBird()->SetX(ScreenHalfWidth());
		CurrentBird()->SetXVelocity(0.0f);
	}
	
	if (ABS(CurrentBird()->XVelocity()) >= BirdXVelocityDeathThreshold) {
		BOOL shouldDie = YES;
		if (CurrentRoundScore() == 0 && ABS(CurrentBird()->XVelocity()) <= 0.8f) {
			shouldDie = NO; // be a little more forgiving when the round is just starting
		}
		if (shouldDie) {
			NSLog(@"Bird x: %.2f", CurrentBird()->XVelocity());
			CurrentBird()->SetState(Bird::State::Dead);
		}
	}
	
	if (CurrentBird()->State() == Bird::State::Dead) {
		SetGState(GStateGameOver);
	} else {
		AddRandomPipeIfNeeded();
	}
	
	for (auto itr = pipes_.begin(); itr != pipes_.end(); itr++) {
		auto pipe = *itr;
		pipe->SetVelocity({PipeXVelocity * GameManager::sharedInstance().GameSpeed(), 0});
		pipe->Update(dt);
	}
}

void GameplayLayer::UpdateGameOver(float dt) {
	for (auto pipe : pipes_) {
		pipe->Body()->SetLinearVelocity({0, 0});
		pipe->Update(dt);
	}
}

void GameplayLayer::AddPipe(int pipeSize, bool upsideDown) {
	assert(pipeSize >= MinPipeSize);
	assert(pipeSize <= MaxPipeSize);
	assert(pipeSize <= MaxTotalSize() - MinPipeSize);
	
	auto pipe = CCSharedPtr<Pipe> { new Pipe(pipeSize, upsideDown) };
	const float pipeHalfHeight = pipe->getContentSize().height / 2.0f;
	const float x = GameManager::sharedInstance().IsReversed() ? (0 - pipe->getContentSize().width) : (ScreenWidth() + pipe->getContentSize().width / 2);
	const float y = upsideDown ? (ScreenHeight() - pipeHalfHeight + 2) : (pipeHalfHeight + GroundHeight() + 2);
	pipe->setPosition({x, y});
	addChild(pipe->Layer().get());
	pipe->AddToWorld(world_);
	pipes_.push_back(pipe);
	
	pipe->Body()->SetLinearVelocity({PipeXVelocity * GameManager::sharedInstance().GameSpeed(), -kGravityVelocity});
	pipe->Body()->SetGravityScale(0.0f); // pipes unaffected by gravity !
	
	// call self recursively to add upside-down pipe if needed
	if (!upsideDown) {
		const auto newPipeSize = MaxTotalSize() - pipeSize;
		AddPipe(newPipeSize, true);
	}
}

void GameplayLayer::RemoveOldPipes() {
	if (pipes_.empty()) return;
	
	auto pipe = pipes_.front();
	if (pipe->X() < -(pipe->getContentSize().width / 2) || (pipe->X() > ScreenWidth() + pipe->getContentSize().width)) {
		pipes_.pop_front();
		removeChild(pipe->Layer().get(), true);
		RemoveOldPipes();
	}
}

void GameplayLayer::AddRandomPipeIfNeeded() {
	RemoveOldPipes();
	
	if (pipes_.size() >= kMaxNumPipes) return;
	
	if (pipes_.size()) {
		// how far was the most recent pipe?
		auto lastPipe = pipes_.back();
		
		if ((GameManager::sharedInstance().IsReversed() && lastPipe->Layer() && lastPipe->Layer()->getPositionX() < (ScreenWidth() * (1 - NextPipeDistance)))
			|| (!GameManager::sharedInstance().IsReversed() && lastPipe->Layer()->getPositionX() > ScreenWidth() * NextPipeDistance)) return; // too soon
	}
	
	AddPipe(RandomPipeSize(), false);
}

template <class BirdT>
BirdPtr GameplayLayer::AddBird() {
	BirdPtr newBird { new BirdT() };
	for (auto bird : birds_) {
		if (bird->MetaClass() == newBird->MetaClass()) {
			printf("Bird of type already exists.\n");
			return nullptr;
		}
	}
	
	printf("Adding new bird.\n");
	newBird->InitializeAnimations(spriteBatchNode_.getTexture());
	birds_.push_back(newBird);
	newBird->setPosition({ScreenHalfWidth(), ScreenHeight() * kBirdMenuHeight});
	spriteBatchNode_.addChild(newBird.get());
	newBird->AddToWorld(world_);
	return newBird;
}

void GameplayLayer::RemoveBird(BirdPtr bird) {
	bird->removeFromParentAndCleanup(true);
	birds_.erase(std::find_if(birds_.begin(), birds_.end(), [=](BirdPtr b){ return b == bird; }), birds_.end());
}

void GameplayLayer::RemoveExtraBirds() {
	for (auto itr = birds_.begin(); itr != birds_.end();) {
		if (*itr != CurrentBird()) {
			(*itr)->removeFromParentAndCleanup(true);
			itr = birds_.erase(itr);
		} else {
			itr++;
		}
	}
}

bool GameplayLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent) {
	if (!GStateIsActive()) return false;
	
	touchBeginTime_ = CCDirector::sharedDirector()->getTotalFrames();
	return true;
}

void GameplayLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent) {
	const unsigned numFrames = CCDirector::sharedDirector()->getTotalFrames() - touchBeginTime_;
	
	if (CurrentBird()->State() != Bird::State::Dead) {
		CurrentBird()->Body()->SetAwake(true);
		
		// move Bird towards horizontal center of screen if needed
		CurrentBird()->SetXVelocity((ScreenHalfWidth() / kPTMRatio) - CurrentBird()->Box2DX());
		CurrentBird()->ApplyTouch(numFrames);

		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Shaker_2.wav");
	}
}

