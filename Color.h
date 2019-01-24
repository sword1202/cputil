#ifndef DRAWERCOLOR_H
#define DRAWERCOLOR_H

#include <string>
#ifdef QT_CORE_LIB
#include <QColor>
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

#endif // DRAWERCOLOR_H