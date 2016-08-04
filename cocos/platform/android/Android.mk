LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2dxandroid_static

LOCAL_MODULE_FILENAME := libcocos2dandroid

LOCAL_SRC_FILES := \
CCApplication-android.cpp \
CCCommon-android.cpp \
CCDevice-android.cpp \
CCGLViewImpl-android.cpp \
CCFileUtils-android.cpp \
javaactivity-android.cpp \
CCEnhanceAPI-android.cpp \
jni/Java_org_cocos2dx_lib_Cocos2dxAccelerometer.cpp \
jni/Java_org_cocos2dx_lib_Cocos2dxBitmap.cpp \
jni/Java_org_cocos2dx_lib_Cocos2dxHelper.cpp \
jni/Java_org_cocos2dx_lib_Cocos2dxRenderer.cpp \
jni/JniHelper.cpp \
jni/TouchesJni.cpp \
jni/Java_org_cocos2dx_lib_Cocos2dxMOS.cpp


LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)

LOCAL_C_INCLUDES := $(LOCAL_PATH) \
                    $(LOCAL_PATH)/.. \
                    $(LOCAL_PATH)/../.. \
                    /dev/cocos2d-x \
                    /dev/cocos2d-x/external \
                    /dev/cocos2d-x/external/android/$(TARGET_ARCH_ABI)/include \
                    /dev/cocos2d-x/extensions \
                    /dev/MOS/libs \
                    /dev/MOS/mindofsound/Classes \

LOCAL_EXPORT_LDLIBS := -lGLESv1_CM \
                       -lGLESv2 \
                       -lEGL \
                       -llog \
                       -landroid

include $(BUILD_STATIC_LIBRARY)
