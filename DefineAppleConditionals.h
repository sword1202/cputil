#if defined(__OBJC__)
    #include <TargetConditionals.h>
    #if TARGET_OS_MAC && !TARGET_OS_IPHONE && !TARGET_IPHONE_SIMULATOR
        #define HAS_COCOA
    #elif TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR
        #define HAS_UIKIT
    #endif
#endif