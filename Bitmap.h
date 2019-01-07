//
// Created by Semyon Tikhonenko on 2019-01-07.
//

#ifndef VOCALTRAINERTESTS_BITMAP_H
#define VOCALTRAINERTESTS_BITMAP_H

#include "Color.h"

namespace CppUtils {
    class Bitmap {
        int width, height;
        unsigned char* data = nullptr;

        void init(int width, int height);
    public:
        Bitmap(Bitmap&& bitmap);
        Bitmap(const Bitmap&& bitmap);
        Bitmap(int width, int height);
        void setPixelRGBAColor(int x, int y, const uchar *rgba);
        void setPixelRGBAColor(int x, int y, uchar r, uchar g, uchar b, uchar a);
        void setPixel(int x, int y, const Color& color);

        void fill(const Color& color);

        unsigned char *getData() const;
        int getWidth() const;
        int getHeight() const;

        ~Bitmap();
    };
}

#endif //VOCALTRAINERTESTS_BITMAP_H
