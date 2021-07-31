#include <cstdint>
#include <assert.h>
#include "Color.h"
#include "MathUtils.h"
#include "BinaryMath.h"
#include "StringUtils.h"
#include "BinaryMath.h"
#include "MathUtils.h"
#include <cassert>

using namespace CppUtils;

Color::Color() {
    rgba[3] = 255;
}

Color::Color(uchar r, uchar g, uchar b, uchar a) {
    rgba[0] = r;
    rgba[1] = g;
    rgba[2] = b;
    rgba[3] = a;
}

Color::Color(int r, int g, int b, int a) : Color(uchar(r), uchar(g), uchar(b), uchar(a)) {
}

Color::Color(double r, double g, double b, double a) {
    setRgba(r, g, b, a);
}

uchar Color::operator[](int index) const {
    assert(index >= 0 && index < 4);
    return rgba[index];
}

uchar &Color::operator[](int index) {
    assert(index >= 0 && index < 4);
    return rgba[index];
}

uchar Color::r() const {
    return rgba[0];
}

uchar Color::g() const {
    return rgba[1];
}

uchar Color::b() const {
    return rgba[2];
}

uchar Color::a() const {
    return rgba[3];
}

uchar &Color::r() {
    return rgba[0];
}

uchar &Color::g() {
    return rgba[1];
}

uchar &Color::b() {
    return rgba[2];
}

uchar &Color::a() {
    return rgba[3];
}

Color Color::white() {
    return fromRgba(0xffffffff);
}

Color Color::black() {
    return fromRgba(0x000000ff);
}

Color Color::red() {
    return fromRgba(0xff0000ff);
}

Color Color::green() {
    return fromRgba(0x00ff00ff);
}

Color Color::blue() {
    return fromRgba(0x0000ffff);
}

Color Color::transparent() {
    return fromRgba(0);
}

bool Color::operator==(const Color &rhs) const {
    return *reinterpret_cast<const int32_t*>(rgba) == *reinterpret_cast<const int32_t*>(rhs.rgba);
}

bool Color::operator!=(const Color &rhs) const {
    return !(rhs == *this);
}

const uchar *Color::getRgba() const {
    return rgba;
}

Color Color::applyOpacity(double opacity) {
    assert(opacity >= 0 && opacity <= 1.0);
    return Color {r(), g(), b(), uchar(a() * opacity)};
}

Color Color::fromHexString(const std::string &hexString) {
    assert(hexString.size() == 6 || hexString.size() == 8);

    Color color;
    int index = 0;
    // Has alpha channel
    if (hexString.size() == 8) {
        color.a() = Strings::ParseHexByte(hexString.data());
        index += 2;
    }

    color.r() = Strings::ParseHexByte(hexString.data() + index);
    index += 2;
    color.g() = Strings::ParseHexByte(hexString.data() + index);
    index += 2;
    color.b() = Strings::ParseHexByte(hexString.data() + index);

    return color;
}

std::string Color::toHexString() const {
    std::string result;
    result.reserve(8);
    result += Strings::ToHexByteString(a());
    result += Strings::ToHexByteString(r());
    result += Strings::ToHexByteString(g());
    result += Strings::ToHexByteString(b());
    return result;
}

Color Color::fromRgba(uint32_t rgba) {
    return Color(
            BinaryMath::GetByte(rgba, 3),
            BinaryMath::GetByte(rgba, 2),
            BinaryMath::GetByte(rgba, 1),
            BinaryMath::GetByte(rgba, 0));
}

void Color::getHSV(double *hue, double *saturation, double *value) const {
    double fR = r() / 255.0;
    double fG = g() / 255.0;
    double fB = b() / 255.0;
    rgbToHsv(fR, fG, fB, hue, saturation, value);
}

void Color::rgbToHsv(double r, double g, double b, double *hue, double *saturation, double *value) {
    assert(r >= 0 && r <= 1);
    assert(g >= 0 && g <= 1);
    assert(b >= 0 && b <= 1);
    double max = std::max(std::max(r, g), b);
    double min = std::min(std::min(r, g), b);
    double delta = max - min;

    if (delta > 0) {
        if(max == r) {
            *hue = 60 * (fmod(((g - b) / delta), 6));
        } else if(max == g) {
            *hue = 60 * (((b - r) / delta) + 2);
        } else if(max == b) {
            *hue = 60 * (((r - g) / delta) + 4);
        }

        if(max > 0) {
            *saturation = delta / max;
        } else {
            *saturation = 0;
        }

        *value = max;
    } else {
        *hue = 0;
        *saturation = 0;
        *value = max;
    }

    if (*hue < 0) {
        *hue = 360 + *hue;
    }
}

void Color::rotateHue(double hueChange) {
    double h,s,v;
    getHSV(&h, &s, &v);
    h += hueChange;
    double r,g,b;
    hsvToRgb(h, s, v, &r, &g, &b);
    setRgb(r, g, b);
}

void Color::hsvToRgb(double hue, double saturation, double value, double *r, double *g, double *b) {
    assert(value >= 0 && value <= 1);
    assert(saturation >= 0 && saturation <= 1);
    double chroma = value * saturation; // Chroma
    double huePrime = fmod(hue / 60.0, 6);
    double x = chroma * (1 - fabs(fmod(huePrime, 2) - 1));
    double m = value - chroma;

    if(0 <= huePrime && huePrime < 1) {
        *r = chroma;
        *g = x;
        *b = 0;
    } else if(1 <= huePrime && huePrime < 2) {
        *r = x;
        *g = chroma;
        *b = 0;
    } else if(2 <= huePrime && huePrime < 3) {
        *r = 0;
        *g = chroma;
        *b = x;
    } else if(3 <= huePrime && huePrime < 4) {
        *r = 0;
        *g = x;
        *b = chroma;
    } else if(4 <= huePrime && huePrime < 5) {
        *r = x;
        *g = 0;
        *b = chroma;
    } else if(5 <= huePrime && huePrime < 6) {
        *r = chroma;
        *g = 0;
        *b = x;
    } else {
        *r = 0;
        *g = 0;
        *b = 0;
    }

    *r += m;
    *g += m;
    *b += m;
}

Color Color::fromHSV(double hue, double saturation, double value, double alpha) {
    assert(value >= 0 && value <= 1);
    assert(saturation >= 0 && saturation <= 1);
    double r, g, b;
    hsvToRgb(hue, saturation, value, &r, &g, &b);
    return Color(r, g, b, alpha);
}

void Color::setRgb(double r, double g, double b) {
    assert(r >= 0 && r <= 1);
    assert(g >= 0 && g <= 1);
    assert(b >= 0 && b <= 1);
    this->r() = Math::RoundToUnsignedChar(255.0 * r);
    this->g() = Math::RoundToUnsignedChar(255.0 * g);
    this->b() = Math::RoundToUnsignedChar(255.0 * b);
}

void Color::setRgba(double r, double g, double b, double a) {
    setRgb(r, g, b);
    assert(a >= 0 && a <= 1);
    this->a() = Math::RoundToUnsignedChar(255.0 * a);
}

void Color::rotateHue(double hueChange, double *r, double *g, double *b) {
    double h,s,v;
    rgbToHsv(*r, *g, *b, &h, &s, &v);
    h += hueChange;
    hsvToRgb(h, s, v, r, g, b);
}

uint32_t Color::toRgbaUint32() const {
    return (uint32_t(r()) << 24) | (uint32_t(g()) << 16) | (uint32_t(b()) << 8) | uint32_t(a());
}

Color Color::fromCmyk(double c, double m, double y, double k, uchar a) {
    uchar r = Math::RoundToUnsignedChar(255 * (1 - c) * (1 - k));
    uchar g = Math::RoundToUnsignedChar(255 * (1 - m) * (1 - k));
    uchar b = Math::RoundToUnsignedChar(255 * (1 - y) * (1 - k));
    return Color(r, g, b, a);
}

#ifdef QT_CORE_LIB
QColor Color::toQColor() const {
    return QColor(r(), g(), b(), a());
}
#endif
