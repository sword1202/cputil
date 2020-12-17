#ifndef DRAWERCOLOR_H
#define DRAWERCOLOR_H

#include <string>
#ifdef QT_CORE_LIB
#include <QColor>
#endif

#if defined(__OBJC__) && TARGET_OS_MAC && !TARGET_OS_IPHONE && !TARGET_IPHONE_SIMULATOR
#define HAS_COCOA
#elif defined(__OBJC__) && (TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR)
#define HAS_UIKIT
#endif

#ifdef HAS_COCOA
#import <Cocoa/Cocoa.h>
#endif

#ifdef HAS_UIKIT
#import <UIKit/UIKit.h>
#endif

namespace CppUtils {
    typedef unsigned char uchar;

    class Color {
        uchar rgba[4];
    public:
        static Color white();
        static Color transparent();
        static Color black();
        static Color red();
        static Color green();
        static Color blue();

        Color();

        Color(uchar r, uchar g, uchar b, uchar a = 255);

        uchar operator[](int index) const;
        uchar &operator[](int index);

        uchar r() const;
        uchar g() const;
        uchar b() const;
        uchar a() const;

        uchar &r();
        uchar &g();
        uchar &b();
        uchar &a();

        const uchar *getRgba() const;

        // opacity - [0.0, 1.0]
        Color applyOpacity(double opacity);

        bool operator==(const Color &rhs) const;
        bool operator!=(const Color &rhs) const;

        static Color fromHexString(const std::string& hexString);
        std::string toHexString() const;

#ifdef QT_CORE_LIB
        QColor toQColor() const;
#endif

#ifdef HAS_COCOA
        inline NSColor* toNSColor() const {
            return [NSColor colorWithRed:r()/255.0 green:g()/255.0 blue:b()/255.0 alpha:a()/255.0];
        }
#endif
#ifdef HAS_UIKIT
        inline UIColor* toUIColor() const {
            return [UIColor colorWithRed:r()/255.0 green:g()/255.0 blue:b()/255.0 alpha:a()/255.0];
        }
#endif
    };
}

namespace std {
    template <>
    struct hash<CppUtils::Color> {
        std::size_t operator()(const CppUtils::Color& k) const {
            return (size_t) reinterpret_cast<const int32_t&>(k);
        }
    };

}

#undef HAS_COCOA
#undef HAS_UIKIT

#endif // DRAWERCOLOR_H