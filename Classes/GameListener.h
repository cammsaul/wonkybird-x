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
	class Builder {
	public:
		typedef bool(Owner::*TouchBeganFnPtr)(Touch*, Event*);
		typedef function<bool(Touch*, Event*)> TouchBeganFn;
//		typedef function<bool(Touch*, Event*)> TouchBeganFn;
//		typedef function<void(Touch*, Event*)> TouchFn;
		
		Builder& TouchBegan(TouchBeganFnPtr fn) { touchBegan_ = fn; return *this; }
//		Builder& TouchMoved(TouchFn fn)		 { touchMoved_ = fn; return *this; }
//		Builder& TouchEnded(TouchFn fn)		 { touchEnded_ = fn; return *this; }
//		Builder& TouchCancelled(TouchFn fn)  { touchCancelled_ = fn; return *this; }
		
		Ptr Build(Owner* owner) {
			Ptr listener { ListenerT::create() };
			listener->onTouchBegan = std::bind(touchBegan_, owner, _1, _2);
			//		listener->onTouchEnded = touchEnded_;
			//		listener->onTouchMoved = touchMoved_;
			//		listener->onTouchCancelled = touchCancelled_;
			Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(*listener, owner);
			return listener;
		}
		
	private:
		TouchBeganFnPtr touchBegan_;
//		TouchFn touchMoved_;
//		TouchFn touchEnded_;
//		TouchFn touchCancelled_;
	};
}

#endif