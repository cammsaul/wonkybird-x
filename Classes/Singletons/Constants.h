//
//  Constants.h
//  WonkyBird
//
//  Created by Cam Saul on 3/3/14.
//
//

#ifndef WONKYBIRD_CONSTANTS_H
#define WONKYBIRD_CONSTANTS_H

static const float kPTMRatio = 100.0f; // retina scaling problem: 100.0f;

static const float kGravityVelocity = -(kPTMRatio / 10.0f);

static inline CCSize ScreenSize()		{ return CCDirector::sharedDirector()->getWinSize(); }
static inline float ScreenWidth()		{ return ScreenSize().width; }
static inline float ScreenHalfWidth()	{ return ScreenWidth() / 2.0f; }
static inline float ScreenHeight()		{ return ScreenSize().height; }
static inline float ScreenHalfHeight()	{ return ScreenHeight() / 2.0f; }
static inline bool IsIphone5()			{ return ScreenHeight() > (480.0f * 2.0f); }

typedef enum : int {
	GStateMainMenu	= 0b000001, ///< 01
	GStateGetReady	= 0b000010, ///< 02
	GStateActive	= 0b000100, ///< 04
	GStateGameOver	= 0b001000, ///< 08
	GStateRound1	= 0b010000, ///< 16
	GStateRound2	= 0b100000  ///< 32
} GameState;


GameState LastFrameState();
GameState GState();
void SetGState(int gState);
static inline bool GStateIsActive()		{ return GState() & GStateActive; }
static inline bool GStateIsGetReady()	{ return GState() & GStateGetReady; }
static inline bool GStateIsMainMenu()	{ return GState() & GStateMainMenu; }
static inline bool GStateIsGameOver()	{ return GState() & GStateGameOver; }

unsigned CurrentRoundScore(); ///< Returns the score for the current game round.
unsigned LastFrameScore(); ///< Score for the previous frame

static auto Rand = bind (uniform_real_distribution<float>(0.0f, 1.0f), default_random_engine()); // nice random number between 0.0f and 1.0f

static const float PipeXVelocity = -1.1f; ///< base x velocity for pipe movement
static const float ScorePipeXVelocityMultiplier = 0.01f; ///< Amount each point should increase pipe velocity. e.g. if ScorePipeXVelocityMultiplier = 0.01f, 100 points means pipes move at double speed

static const float NextPipeDistance = 0.25f; ///< position on screen pipes must get to before adding new ones, e.g. 0.25 is 25% from the left. Lower numbers means waiting longer before adding new pipes.

static const float kBirdMenuRandVelocity = 10.0f; ///< Apply +/- this amount to Bird's x velocity in main menu

static const float BirdGetReadyHeight = 0.6f; ///< How far up (percent of screen height) bird should flap at during the "Get Ready" stage
static const float BirdXVelocityDeathThreshold = 0.2f; ///< During gameplay, if absolute value of bird's x velocity >= this amount, bird is dead. This allows for a some sliding and slight bumping of pipes without causing death

static const int MinPipeSize = 2;
static const int InitialMaxSize = 6;
static const int MaxMaxSize = 9;
static const int MaxPipeSize = MaxMaxSize - MinPipeSize;

static inline int GroundHeight() { return ScreenHeight() * 0.23f; }
static const int kMaxNumPipes = 12;

static const int CrazyBackwardsModeScore = 25;		///< game reverses every time you pass this many points in a single round
static const int CrazySwitchBackgroundsScore = 10;	///< switch background every time we pass 10
static const int CrazyBackgroundSkewScore = 50;		///< apply skew transforms to BG every point after this
static const int CrazyBackgroundToucanChance = 1000; ///< approx every 1000 points we will switch the BG to toucan for a lil bit

static const float kBirdMenuHeight = 0.6f; ///< Bird is 60% way up screen when flapping in menu

static const int32 Box2DLayerVelocityIterations = 3; ///< Number of iterations Box2D world should do for every frame. Higher number means more accurate physics, but comes with a performance penalty.
static const int32 Box2DLayerPositionIterations = 2; ///< Number of iterations Box2D world should do for every frame. Higher number means more accurate physics, but comes with a performance penalty.

static const float HUDSpriteRemovalDuration = 0.5f; ///< How long the sprites in the HUD take to animate out

static const int MaxNumClouds = 6;

#endif