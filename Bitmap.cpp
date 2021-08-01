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
    delete[] data;
}

void Bitmap::setPixelRGBAColor(int x, int y, const uchar *rgba) {
    assert(x < width && y < height);
    int index = x + y * width;
    reinterpret_cast<int32_t*>(data)[index] = *reinterpret_cast<const int32_t*>(rgba);
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
    bitmap.width = -1;
    bitmap.height = -1;
}

Bitmap::Bitmap(const Bitmap &bitmap) {
    if (bitmap.data) {
        init(bitmap.width, bitmap.height);
        std::copy(bitmap.data, bitmap.data + getDataArraySize(), data);
    } else {
        width = -1;
        height = -1;
    }
}

void Bitmap::init(int width, int height) {
    this->width = width;
    this->height = height;
    data = new uchar[getDataArraySize()];
}

void Bitmap::fill(const Color &color) {
    for (int i = 0; i < width * height; i++) {
        reinterpret_cast<int32_t*>(data)[i] = *reinterpret_cast<const int32_t*>(color.getRgba());
    }
}

Bitmap::Bitmap(int width, int height, unsigned char *data) {
    assert(data);
    init(width, height);
    std::copy(data, data + getDataArraySize(), this->data);
}

int Bitmap::getDataArraySize() const {
    return width * height * PIXEL_SIZE;
}

Bitmap::Bitmap() {
    width = -1;
    height = -1;
}
