APP_STL := gnustl_static

# Following is my addition
APP_ABI := armeabi-v7a

APP_CPPFLAGS := -frtti -DCC_ENABLE_CHIPMUNK_INTEGRATION=1 -std=c++11 -fsigned-char
APP_LDFLAGS := -latomic

#APP_ABI := arm64-v8a
APP_ABI := armeabi


ifeq ($(NDK_DEBUG),1)
  APP_CPPFLAGS += -DCOCOS2D_DEBUG=1
  APP_OPTIM := debug
else
  APP_CPPFLAGS += -DNDEBUG
  APP_OPTIM := release
endif

# Following is my addition (allows printf etc)
APP_CFLAGS += -Wno-error=format-security
