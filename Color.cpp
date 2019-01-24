#include <cstdint>
#include <assert.h>
#include "Color.h"
#include "MathUtils.h"
#include "BinaryMath.h"
#include "StringUtils.h"
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
    return {255, 255, 255, 255};
}

Color Color::black() {
    return {0, 0, 0, 255};
}

Color Color::red() {
    return {255, 0, 0, 255};
}

Color Color::green() {
    return {0, 255, 0, 255};
}

Color Color::blue() {
    return {0, 0, 255, 255};
}

Color Color::transparent() {
    return {0, 0, 0, 0};
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
