//
//  GameListener.cpp
//  WonkyBird
//
//  Created by Cam Saul on 3/6/14.
//
//

#include "GameListener.h"

namespace GameListener {
	auto netRefCount = [](ListenerT* l, const char *tag) -> int {
		return l->getReferenceCount() - (PoolManager::getInstance()->isObjectInPools(l) ? 1 : 0);
	};
	
	void Releaser::Release(ListenerT* listener) {
		if (netRefCount(listener, "RELEASE FN") == 2) {
			printf("Removing Event Listener: %s\n", DumpPtr(listener).c_str());
			Director::getInstance()->getEventDispatcher()->removeEventListener(listener);
		}
	}
}