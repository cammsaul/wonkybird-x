//
//  GameListener.h
//  WonkyBird
//
//  Created by Cam Saul on 3/6/14.
//
//

#ifndef WONKYBIRD_GameListener_H
#define WONKYBIRD_GameListener_H

namespace GameListener {
	using namespace std::placeholders;
	
	typedef EventListenerTouchOneByOne ListenerT;

	struct Releaser {
	public:
		static void Release(ListenerT* listener);
	};
	
	typedef GamePtr<ListenerT, Releaser> Ptr;
	
	template <typename Owner>
	class Binder {
	public:
		typedef bool(Owner::*TouchBeganFnPtr)(Touch*, Event*);
		typedef void(Owner::*TouchFnPtr)(Touch*, Event*);
		
		Binder& TouchBegan(TouchBeganFnPtr fn)  { touchBegan_ = fn; return *this; }
		Binder& TouchMoved(TouchFnPtr fn)		{ touchMoved_ = fn; return *this; }
		Binder& TouchEnded(TouchFnPtr fn)		{ touchEnded_ = fn; return *this; }
		Binder& TouchCancelled(TouchFnPtr fn)   { touchCancelled_ = fn; return *this; }
		
		Ptr Bind(Owner* owner) {
			Ptr listener { ListenerT::create() };
			if (touchBegan_) listener->onTouchBegan = std::bind(touchBegan_, owner, _1, _2);
			if (touchEnded_) listener->onTouchEnded = std::bind(touchEnded_, owner, _1, _2);
			if (touchMoved_) listener->onTouchMoved = std::bind(touchMoved_, owner, _1, _2);
			if (touchCancelled_) listener->onTouchCancelled = std::bind(touchCancelled_, owner, _1, _2);
			Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(*listener, owner);
			return listener;
		}
		
	private:
		TouchBeganFnPtr touchBegan_ = nullptr;
		TouchFnPtr touchMoved_ = nullptr;
		TouchFnPtr touchEnded_ = nullptr;
		TouchFnPtr touchCancelled_ = nullptr;
	};
}

using GameListener::Binder;

#endif