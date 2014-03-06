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
#include "GameListener.h"

using namespace std::placeholders;

float MaxTotalSize() {
	return MIN((InitialMaxSize + (CurrentRoundScore() / 2)), MaxMaxSize);
}

float RandomPipeSize() {
	const int SizeRange = MaxTotalSize() - (MinPipeSize * 2);
	return (random() % SizeRange) + MinPipeSize;
}

struct GameplayLayer::Impl {
	void UpdateMainMenu(float dt);
	void UpdateGetReady(float dt);
	void UpdateActive(float dt);
	void UpdateGameOver(float dt);
	
	void AddExtraBirds();
	void RemoveExtraBirds();
	
	void AddPipe(int size, bool upsideDown);
	void RemoveOldPipes();
	void AddRandomPipeIfNeeded();
	
	template <class BirdT>
	BirdPtr AddBird();
	
	BirdPtr& CurrentBird() { return currentBird_; }
	void SetCurrentBird(BirdPtr& bird) { currentBird_ = BirdPtr(bird); }
	
	Flock birds_;
	BirdPtr toucan_;
	BirdPtr pigeon_;
	BirdPtr currentBird_;
	GameSprite ground_;
	
	GameListener::Ptr listener_;
	
	deque<GamePtr<Pipe>> pipes_;
	
	unsigned touchBeginTime_; ///< time current touch began, used to keep track for touch-sensitive birds like Rasta
	
	GameplayLayer& this_;
	Impl(GameplayLayer& parent):
	this_(parent)
	{
		// add the ground
		ground_.BodyDef()->type = b2_staticBody;
		ground_.setPosition({ScreenHalfWidth(), GroundHeight() / 2.0f});
		ground_.setContentSize({ScreenWidth() * 2 /* extend out past edges a bit */, GroundHeight()});
		ground_.FixtureDef()->density = 0.0f;
		ground_.FixtureDef()->friction = 0.8f;
		ground_.AddToWorld(this_.world_);
		
		// todo - add roof
	}

};

GameplayLayer::GameplayLayer():
	Box2DLayer("Textures"),
	impl(new Impl(*this))
{
	impl->listener_ = Binder<GameplayLayer>().TouchBegan(&GameplayLayer::onTouchBegan).TouchEnded(&GameplayLayer::onTouchEnded).Bind(this);
	scheduleUpdate();
}

void GameplayLayer::update(float dt) {
	Box2DLayer::update(dt);
	
	if (GStateIsMainMenu()) {
		impl->UpdateMainMenu(dt);
	} else if (GStateIsGetReady()) {
		impl->UpdateGetReady(dt);
	} else if (GStateIsActive()) {
		impl->UpdateActive(dt);
	} else if (GStateIsGameOver()) {
		impl->UpdateGameOver(dt);
	}
	
	for (auto* obj : spriteBatchNode_->getChildren()) {
		if (auto* gameNode = dynamic_cast<GameNode *>(obj)) {
			gameNode->Update(dt);
		}
	}
}

BirdPtr& GameplayLayer::CurrentBird() { return impl->CurrentBird(); }

void GameplayLayer::Impl::UpdateMainMenu(float dt) {
	if (!toucan_) toucan_ = AddBird<Toucan>();
	if (!pigeon_) pigeon_ = AddBird<Pigeon>();
	toucan_->FlapAroundOnMainScreen(birds_);
	pigeon_->FlapAroundOnMainScreen(birds_);
	
	if (!CurrentBird()) {
		SetCurrentBird(toucan_);
	}
}

void GameplayLayer::Impl::UpdateGetReady(float dt) {
	if (LastFrameState() != GStateGetReady && LastFrameState() != GStateMainMenu) {
		// switch out the birds
		if (typeid(*CurrentBird()) == typeid(Toucan)) {
			if (!pigeon_) pigeon_ = AddBird<Pigeon>();
			SetCurrentBird(pigeon_);
			
			auto mask = ~GStateRound1;
			SetGState((GState() & mask)|GStateRound2);
		} else if (!toucan_) { toucan_ = AddBird<Toucan>();
			SetCurrentBird(toucan_);
			
			auto mask = ~GStateRound2;
			SetGState((GState() & mask)|GStateRound1);
		}
	}
	
	remove_if(birds_.begin(), birds_.end(), [&](BirdPtr& b){
		return b != CurrentBird() && b->X() < -(b->getContentSize().width / 2.0f);
	});
	CurrentBird()->SetXVelocity(PipeXVelocity * GameManager::sharedInstance().GameSpeed());
	
	CurrentBird()->SetState(Bird::State::Flapping);
	const float BirdYDiff = ((CurrentBird()->Y() - (ScreenHeight() * BirdGetReadyHeight)) / kPTMRatio) * 4;
	const float BirdXDiff = ((CurrentBird()->X() - ScreenHalfWidth()) / kPTMRatio) * 4;
	CurrentBird()->SetVelocity({-BirdXDiff, -BirdYDiff});
	
	for (auto& pipe : pipes_) {
		this_.removeChild(pipe->Layer().Get(), true);
	}
	pipes_.clear();
}

void GameplayLayer::Impl::UpdateActive(float dt) {
	if (LastFrameState() != GStateActive) {
		RemoveExtraBirds();
		CurrentBird()->SetX(ScreenHalfWidth());
		CurrentBird()->SetXVelocity(0.0f);
	}
	
	if (abs(CurrentBird()->XVelocity()) >= BirdXVelocityDeathThreshold) {
		bool shouldDie = true;
		if (CurrentRoundScore() == 0 && abs(CurrentBird()->XVelocity()) <= 0.8f) {
			shouldDie = false; // be a little more forgiving when the round is just starting
		}
		if (shouldDie) {
			printf("Bird x: %.2f", CurrentBird()->XVelocity());
			CurrentBird()->SetState(Bird::State::Dead);
		}
	}
	
	if (CurrentBird()->GetState() == Bird::State::Dead) {
		SetGState(GStateGameOver);
	} else {
		AddRandomPipeIfNeeded();
	}
	
	for (auto itr = pipes_.begin(); itr != pipes_.end(); itr++) {
		auto& pipe = *itr;
		pipe->SetVelocity({PipeXVelocity * GameManager::sharedInstance().GameSpeed(), 0});
		pipe->Update(dt);
	}
}

void GameplayLayer::Impl::UpdateGameOver(float dt) {
	for (auto& pipe : pipes_) {
		pipe->Body()->SetLinearVelocity({0, 0});
		pipe->Update(dt);
	}
}

void GameplayLayer::Impl::AddPipe(int pipeSize, bool upsideDown) {
	assert(pipeSize >= MinPipeSize);
	assert(pipeSize <= MaxPipeSize);
	assert(pipeSize <= MaxTotalSize() - MinPipeSize);
	
	auto pipe = GamePtr<Pipe> { new Pipe(pipeSize, upsideDown) };
	const float pipeHalfHeight = pipe->getContentSize().height / 2.0f;
	const float x = GameManager::sharedInstance().IsReversed() ? (0 - pipe->getContentSize().width) : (ScreenWidth() + pipe->getContentSize().width / 2);
	const float y = upsideDown ? (ScreenHeight() - pipeHalfHeight + 2) : (pipeHalfHeight + GroundHeight() + 2);
	pipe->setPosition({x, y});
	this_.addChild(pipe->Layer().Get());
	pipe->AddToWorld(this_.world_);
	pipes_.push_back(pipe);
	
	pipe->Body()->SetLinearVelocity({PipeXVelocity * GameManager::sharedInstance().GameSpeed(), -GravityVelocity()});
	pipe->Body()->SetGravityScale(0.0f); // pipes unaffected by gravity !
	
	// call self recursively to add upside-down pipe if needed
	if (!upsideDown) {
		const auto newPipeSize = MaxTotalSize() - pipeSize;
		AddPipe(newPipeSize, true);
	}
}

void GameplayLayer::Impl::RemoveOldPipes() {
	if (pipes_.empty()) return;
	
	auto& pipe = pipes_.front();
	if (pipe->X() < -(pipe->getContentSize().width / 2) || (pipe->X() > ScreenWidth() + pipe->getContentSize().width)) {
		pipes_.pop_front();
		this_.removeChild(pipe->Layer().Get(), true);
		RemoveOldPipes();
	}
}

void GameplayLayer::Impl::AddRandomPipeIfNeeded() {
	RemoveOldPipes();
	
	if (pipes_.size() >= kMaxNumPipes) return;
	
	if (pipes_.size()) {
		// how far was the most recent pipe?
		auto& lastPipe = pipes_.back();
		
		if ((GameManager::sharedInstance().IsReversed() && lastPipe->Layer() && lastPipe->Layer()->getPositionX() < (ScreenWidth() * (1 - NextPipeDistance)))
			|| (!GameManager::sharedInstance().IsReversed() && lastPipe->Layer()->getPositionX() > ScreenWidth() * NextPipeDistance)) return; // too soon
	}
	
	AddPipe(RandomPipeSize(), false);
}

template <class BirdT>
BirdPtr GameplayLayer::Impl::AddBird() {
	BirdPtr newBird { new BirdT() };
	for (auto& bird : birds_) {
		if (bird->MetaClass() == newBird->MetaClass()) {
			printf("Bird of type already exists.\n");
			return nullptr;
		}
	}
	
	printf("Adding new bird: %s\n", DumpSmartPtr(newBird).c_str());
	newBird->InitializeAnimations(this_.spriteBatchNode_->getTexture());
	birds_.push_back(newBird);
	newBird->setPosition({ScreenHalfWidth(), ScreenHeight() * kBirdMenuHeight});
	this_.spriteBatchNode_->addChild(newBird.Get());
	newBird->AddToWorld(this_.world_);
	return newBird;
}

void GameplayLayer::Impl::RemoveExtraBirds() {
	printf("Removing extra birds. CurrentBird = %s\n", DumpSmartPtr(CurrentBird()).c_str());
	
	while (birds_.size() > 1) {
		for (auto& bird : birds_) {
			if (bird != CurrentBird()) {
				bird->removeFromParentAndCleanup(true);
				birds_.erase(find(birds_.begin(), birds_.end(), bird));
				printf("Removed: %s (retain count: %d)\n", DumpSmartPtr(bird).c_str(), bird->getReferenceCount());
				break;
			}
		}
	}
	
	assert(birds_.size() == 1);
}

bool GameplayLayer::onTouchBegan(Touch *pTouch, Event *pEvent) {
	if (!GStateIsActive()) return false;
	
	impl->touchBeginTime_ = Director::getInstance()->getTotalFrames();
	return true;
}

void GameplayLayer::onTouchEnded(Touch *pTouch, Event *pEvent) {
	const unsigned numFrames = Director::getInstance()->getTotalFrames() - impl->touchBeginTime_;
	
	if (CurrentBird()->GetState() != Bird::State::Dead) {
		CurrentBird()->Body()->SetAwake(true);
		
		// move Bird towards horizontal center of screen if needed
		CurrentBird()->SetXVelocity((ScreenHalfWidth() / kPTMRatio) - CurrentBird()->Box2DX());
		CurrentBird()->ApplyTouch(numFrames);

		SimpleAudioEngine::getInstance()->playEffect("Shaker_2.wav");
	}
}

