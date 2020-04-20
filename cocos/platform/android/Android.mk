LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2dxandroid_static

LOCAL_MODULE_FILENAME := libcocos2dandroid

LOCAL_SRC_FILES := \
CCDevice-android.cpp \
CCFileUtils-android.cpp \
CCApplication-android.cpp \
CCView.cpp \
CCCanvasRenderingContext2D-android.cpp \
jni/JniImp.cpp \
jni/JniHelper.cpp

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)

LOCAL_C_INCLUDES := $(LOCAL_PATH) \
                    $(LOCAL_PATH)/.. \
                    $(LOCAL_PATH)/../.. \
                    $(LOCAL_PATH)/../../..

LOCAL_EXPORT_LDLIBS := -lGLESv2 \
                       -lEGL \
                       -llog \
                       -landroid

LOCAL_STATIC_LIBRARIES := v8_static android_native_app_glue
LOCAL_STATIC_LIBRARIES += android_game_sdk

include $(BUILD_STATIC_LIBRARY)
$(call import-module, android/native_app_glue)
$(call import-module,android)
