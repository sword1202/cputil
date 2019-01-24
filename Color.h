#ifndef DRAWERCOLOR_H
#define DRAWERCOLOR_H

#include <string>

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
    };
}

#endif // DRAWERCOLOR_H