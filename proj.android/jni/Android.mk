LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
			../../Classes/AppDelegate.cpp \
			../../Classes/GLES-Render.cpp \
			../../Classes/GameNode.cpp \
			../../Classes/Pigeon.cpp \
			../../Classes/StaticBackgroundLayer.cpp \
			../../Classes/Bird.cpp \
			../../Classes/GameLayer.cpp \
			../../Classes/GameplayLayer.cpp \
			../../Classes/Pipe.cpp \
			../../Classes/TiledMapWithBox2D.cpp \
			../../Classes/Box2DItem.cpp \
			../../Classes/GameListener.cpp \
			../../Classes/HUDLayer.cpp \
			../../Classes/ReflectiveClass.cpp \
			../../Classes/Toucan.cpp \
			../../Classes/Box2DLayer.cpp \
			../../Classes/GameManager.cpp \
			../../Classes/MainScene.cpp \
			../../Classes/ScrollingBackgroundLayer.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes
LOCAL_CPP_FEATURES += exceptions
LOCAL_CPPFLAGS := -include ../../proj.ios_mac/mac/Prefix.pch -std=c++11 -Wno-format

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static
LOCAL_WHOLE_STATIC_LIBRARIES += box2d_static


include $(BUILD_SHARED_LIBRARY)

$(call import-module,2d)
$(call import-module,audio/android)
$(call import-module,Box2D)
