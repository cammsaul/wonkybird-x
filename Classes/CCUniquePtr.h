//
//  GamePtr.h
//  WonkyBird
//
//  Created by Cam Saul on 3/4/14.
//
//

#ifndef WONKYBIRD_GamePtr_H
#define WONKYBIRD_GamePtr_H

#include <cxxabi.h>
#include "NoCopy.h"

template <typename T>
inline string readable_name() {
	auto mangled_name = typeid(T).name();
	int status ;
	char *temp = __cxxabiv1::__cxa_demangle(mangled_name, nullptr, nullptr, &status);
	if(temp) {
		string result{temp};
		free(temp);
		return result;
	}
	else return mangled_name;
}

template <typename T>
inline string readable_name(const T& t) {
	auto mangled_name = typeid(t).name();
	int status ;
	char *temp = __cxxabiv1::__cxa_demangle(mangled_name, nullptr, nullptr, &status);
	if(temp) {
		string result{temp};
		free(temp);
		return result;
	}
	else return mangled_name;
}

template <typename T>
string DumpPtr(T* Ptr) {
	char buff[50];
	sprintf(buff, "%s 0x%016lx", readable_name(Ptr).c_str(), (size_t)Ptr);
	return string{buff};
}

template <typename T>
string DumpSmartPtr(T& Ptr) {
	return DumpPtr(Ptr.Get());
}

struct DebugReleaser {
public:
	template <typename T>
	static void Release(T* t) {
		printf("Released: %s (ref count: %d)\n", readable_name(t).c_str(), t->getReferenceCount());
	}
};

struct NullReleaser {
public:
	template <typename T>
	static void Release(T*) {};
};

template <class T, typename Releaser = DebugReleaser>
class GamePtr {
public:
	GamePtr():
		obj_(nullptr)
	{}
	
	GamePtr(T* obj):
		obj_(obj)
	{
		if (obj_ != nullptr) {
			obj_->retain();
		}
	}
	
	// copying must be done explicitly, to prevent creating wayyy to many objects
	explicit GamePtr(const GamePtr& rhs) {
		if (this != &rhs) {
			obj_ = rhs.obj_;
			if (obj_) obj_->retain();
		}
	}
	
	GamePtr& operator=(const GamePtr&) = delete; // disallow copy assignment, use explict copy construction instead
	
	// moving ok
	GamePtr(GamePtr&& rhs) {
		obj_ = rhs.obj_;
		rhs.obj_ = nullptr;
	}
	
	GamePtr& operator=(GamePtr&& rhs) {
		if (this != &rhs) {
			obj_ = rhs.obj_;
			rhs.obj_ = nullptr;
		}
		return *this;
	}
	
	~GamePtr() {
		if (obj_) {
			Releaser::Release(obj_);
			obj_->release();
		}
	}
	
	T* operator*() { return Get(); }
	T* operator->() { return Get(); }
	T* Get() {
		if (!obj_) {
			throw runtime_error { "nullptr dereference in GamePtr<" + readable_name(obj_) + ">" };
		}
		return obj_;
	}
	
	const T* operator*() const { return Get(); }
	const T* operator->() const { return Get(); }
	const T* Get() const { return obj_; }
	
	operator bool() const { return obj_ != nullptr; }
private:
	T* obj_ = nullptr;
};

#endif
