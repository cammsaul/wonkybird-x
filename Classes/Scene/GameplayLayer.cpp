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

//static const std::hash<BirdPtr>(BirdPtr ptr) BirdsHashFn = [](BirdPtr birdPtr) -> std::hash<BirdPtr> {
//	return std::hash<BirdPtr>();
//};
//
//static auto BirdsEqlFn = [](BirdPtr first, BirdPtr second) -> bool {
//	return true;
//};


GameplayLayer::GameplayLayer():
	Box2DLayer("Textures"),
	birds_    (),
	toucan_   (nullptr),
	pigeon_   (nullptr),
	mainBird_ (nullptr),
	ground_   ()
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
}

void GameplayLayer::update(float dt) {
	Box2DLayer::update(dt);
	
	static bool hasAddedBird = false;
	if (!hasAddedBird) {
		hasAddedBird = true;
		AddBird<Toucan>();
	}
	
	if (GStateIsMainMenu()) {
		UpdateMainMenu();
	} else if (GStateIsGetReady()) {
		UpdateGetReady();
	} else if (GStateIsActive()) {
		UpdateActive();
	} else if (GStateIsGameOver()) {
		UpdateGameOver();
	}
	
	CCArray* gameObjects = spriteBatchNode_.getChildren();
	const auto count = gameObjects->count();
	for (int i = 0; i < count; i++) {
		auto* gameObject = gameObjects->objectAtIndex(i);
		auto* gameSprite = dynamic_cast<GameSprite *>(gameObject);
		if (gameSprite) {
			gameSprite->Update(dt);
		}
	}
}

void GameplayLayer::UpdateMainMenu() {
	if (!toucan_) toucan_ = AddBird<Toucan>();
	if (!pigeon_) pigeon_ = AddBird<Pigeon>();
	toucan_->FlapAroundOnMainScreen(birds_);
	pigeon_->FlapAroundOnMainScreen(birds_);
	
	if (!MainBird()) {
		SetMainBird(toucan_);
	}
}

void GameplayLayer::UpdateGetReady() {
	if (LastFrameState() != GStateGetReady && LastFrameState() != GStateMainMenu) {
		// switch out the birds
		if (typeid(*MainBird()) == typeid(Toucan)) {
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
	
	for (auto b : birds_) if (b != MainBird()) {
		b->SetXVelocity(PipeXVelocity * GameManager::sharedInstance()->GameSpeed());
		if (b->X() < -(b->getContentSize().width / 2.0f)) {
			RemoveBird(b);
			break; // don't remove any more birds this round, since RemoveBird() affects birds_
		}
	}
	
	MainBird()->SetState(Bird::State::Flapping);
	const float BirdYDiff = ((MainBird()->Y() - (ScreenHeight() * BirdGetReadyHeight)) / kPTMRatio) * 4;
	const float BirdXDiff = ((MainBird()->X() - ScreenHalfWidth()) / kPTMRatio) * 4;
	MainBird()->SetVelocity({-BirdXDiff, -BirdYDiff});
	
//	for (Pipe *p in self.pipes) {
//		[self removeChild:p.layer cleanup:YES];
//	}
//	[self.pipes removeAllObjects];
}

void GameplayLayer::UpdateActive() {
	if (LastFrameScore() != GStateActive) {
		RemoveExtraBirds();
		MainBird()->SetX(ScreenHalfWidth());
		MainBird()->SetXVelocity(0.0f);
	}
	
	if (ABS(MainBird()->XVelocity()) >= BirdXVelocityDeathThreshold) {
		BOOL shouldDie = YES;
		if (CurrentRoundScore() == 0 && ABS(MainBird()->XVelocity()) <= 0.8f) {
			shouldDie = NO; // be a little more forgiving when the round is just starting
		}
		if (shouldDie) {
			NSLog(@"Bird x: %.2f", MainBird()->XVelocity());
			MainBird()->SetState(Bird::State::Dead);
		}
	}
	
	if (MainBird()->State() == Bird::State::Dead) {
		SetGState(GStateGameOver);
	} else {
//		[self addRandomPipeIfNeeded];
	}
	
//	for (Pipe *p in self.pipes) {
//		const float pipeXVelocity = PipeXVelocity * [GameManager sharedInstance].gameSpeed;
//		p.item.body->SetLinearVelocity({pipeXVelocity, 0});
//		[p updateStateWithDeltaTime:delta];
//	}
}

void GameplayLayer::UpdateGameOver() {
//	for (Pipe *p in self.pipes) {
//		p.item.body->SetLinearVelocity({0, 0});
//		[p updateStateWithDeltaTime:delta];
//	}
}

template <class BirdT>
BirdPtr GameplayLayer::AddBird() {
//	if (birds_.find(std::find_if(birds_.begin(), birds_.end(), [=](BirdPtr b){ return typeid(*b) != typeid(BirdT); })) != birds_.end()) {
		printf("Adding new bird.\n");
		BirdPtr bird = make_shared<BirdT>();
		birds_.insert(bird);
		bird->setPosition({ScreenHalfWidth(), ScreenHeight() * kBirdMenuHeight});
		spriteBatchNode_.addChild(bird.get());
		bird->AddToWorld(world_);
		return bird;
//	} else {
//		printf("Bird of type already exists.");
//		return nullptr;
//	}
}

void GameplayLayer::RemoveBird(BirdPtr bird) {
	bird->removeFromParentAndCleanup(true);
	birds_.erase(std::find_if(birds_.begin(), birds_.end(), [=](BirdPtr b){ return b == bird; }), birds_.end());
}

void GameplayLayer::RemoveExtraBirds() {
	for (auto itr = birds_.begin(); itr != birds_.end();) {
		if (*itr != MainBird()) {
			(*itr)->removeFromParentAndCleanup(true);
			itr = birds_.erase(itr);
		} else {
			itr++;
		}
	}
}