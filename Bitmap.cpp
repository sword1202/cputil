//
// Created by Semyon Tikhonenko on 2019-01-07.
//

#include "Bitmap.h"
#include <assert.h>
#include <algorithm>

using namespace CppUtils;

constexpr int PIXEL_SIZE = 4;

Bitmap::Bitmap(int width, int height) {
    init(width, height);
}

Bitmap::~Bitmap() {
    delete data;
}

void Bitmap::setPixelRGBAColor(int x, int y, const uchar *rgba) {
    setPixelRGBAColor(x, y, rgba[0], rgba[1], rgba[2], rgba[3]);
}

void Bitmap::setPixel(int x, int y, const Color &color) {
    setPixelRGBAColor(x, y, color.getRgba());
}

void Bitmap::setPixelRGBAColor(int x, int y, uchar r, uchar g, uchar b, uchar a) {
    assert(x < width && y < height);
    int index = (x + y * width) * PIXEL_SIZE;
    data[index++] = r;
    data[index++] = g;
    data[index++] = b;
    data[index] = a;
}

unsigned char *Bitmap::getData() const {
    return data;
}

int Bitmap::getWidth() const {
    return width;
}

int Bitmap::getHeight() const {
    return height;
}

Bitmap::Bitmap(Bitmap &&bitmap) {
    this->width = bitmap.width;
    this->height = bitmap.height;
    this->data = bitmap.data;
    bitmap.data = nullptr;
}

Bitmap::Bitmap(const Bitmap &bitmap) {
    init(bitmap.width, bitmap.height);
    std::copy(bitmap.data, bitmap.data + getDataArraySize(), data);
}

void Bitmap::init(int width, int height) {
    this->width = width;
    this->height = height;
    data = new uchar[getDataArraySize()];
}

void Bitmap::fill(const Color &color) {
    for (int i = 0; i < getDataArraySize();) {
        data[i++] = color.r();
        data[i++] = color.g();
        data[i++] = color.b();
        data[i++] = color.a();
    }
}

Bitmap::Bitmap(int width, int height, unsigned char *data) {
    init(width, height);
    std::copy(data, data + getDataArraySize(), this->data);
}

int Bitmap::getDataArraySize() const {
    return width * height * PIXEL_SIZE;
}
