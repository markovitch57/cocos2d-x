LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../../../../)

LOCAL_MODULE := cpp_empty_test_shared

LOCAL_MODULE_FILENAME := libcpp_empty_test

LOCAL_ARM_MODE := arm

LOCAL_SRC_FILES := main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/HelloWorldScene.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes \
                    $(LOCAL_PATH)/../../../../../MOS/libs \
                    $(LOCAL_PATH)/../../../../extensions \
                    $(LOCAL_PATH)/../../../.. \
                    $(LOCAL_PATH)/../../../../cocos/editor-support

LOCAL_STATIC_LIBRARIES := cocos2dx_static cocos2d_lua_static my_moscclib_static

LOCAL_SHARED_LIBRARIES := ffmpeg-prebuilt

include $(BUILD_SHARED_LIBRARY)

$(call import-module,scripting/lua-bindings/proj.android)
$(call import-module,MOS/libs/moslib)
$(call import-module,MOS/libs/ffmpeg/android)
$(call import-module,curl/prebuilt/android)
$(call import-module,.)
