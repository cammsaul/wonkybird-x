//
//  CCUniquePtr.h
//  WonkyBird
//
//  Created by Cam Saul on 3/4/14.
//
//

#ifndef WONKYBIRD_CCUNIQUEPTR_H
#define WONKYBIRD_CCUNIQUEPTR_H

class CCDeleter {
public:
	template <class T>
	void operator()(T* p) {
		if (p) p->release();
	}
};

template <class T>
class CCUniquePtr : public unique_ptr<T, CCDeleter> {
public:
	CCUniquePtr():
	unique_ptr<T, CCDeleter>(new T())
	{
		unique_ptr<T, CCDeleter>::get()->retain();
	}
	CCUniquePtr(T* item):
	unique_ptr<T, CCDeleter>(item)
	{
		if (item) {
			unique_ptr<T, CCDeleter>::get()->retain();
		}
	}
};

#endif
