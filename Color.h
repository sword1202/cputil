#ifndef DRAWERCOLOR_H
#define DRAWERCOLOR_H

#include <string>
#ifdef QT_CORE_LIB
#include <QColor>
#endif

#include "DefineAppleConditionals.h"

#ifdef HAS_COCOA
#import <Cocoa/Cocoa.h>
#endif

#ifdef HAS_UIKIT
#import <UIKit/UIKit.h>
#include "MathUtils.h"
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

        static Color fromRgba(uint32_t rgba);

        Color();
        Color(uchar r, uchar g, uchar b, uchar a = 255);
        Color(int r, int g, int b, int a = 255);
        explicit Color(double r, double g, double b, double a = 1.0);

        void setRgb(double r, double g, double b);
        void setRgba(double r, double g, double b, double a);

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

        uint32_t toRgbaUint32() const;

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

        inline Color(UIColor* color) {
            CGFloat r, g, b, a;
            [color getRed:&r green:&g blue:&b alpha:&a];
            rgba[0] = Math::RoundToUnsignedChar(255.0 * r);
            rgba[1] = Math::RoundToUnsignedChar(255.0 * g);
            rgba[2] = Math::RoundToUnsignedChar(255.0 * b);
            rgba[3] = Math::RoundToUnsignedChar(255.0 * a);
        }
#endif
        static void rgbToHsv(double r, double g, double b, double* hue, double* saturation, double* value);
        static void hsvToRgb(double hue, double saturation, double value, double* r, double* g, double* b);
        static Color fromHSV(double hue, double saturation, double value, double alpha = 1.0);
        void getHSV(double* hue, double* saturation, double* value) const;
        static void rotateHue(double hueChange, double* r, double* g, double* b);
        void rotateHue(double hueChange);
        static Color fromCmyk(double c, double m, double y, double k, uchar a = 255);
        void getCmy(double* c, double* m, double* y) const;
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

#include "UndefAppleConditionals.h"

#endif // DRAWERCOLOR_H