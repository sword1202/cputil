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
#ifdef __OBJC__
        static inline Bitmap fromCGImage(CGImage* image) {
            NSBitmapImageRep* rep = [[NSBitmapImageRep alloc] initWithCGImage:image];
            return Bitmap(int(rep.size.width), int(rep.size.height), rep.bitmapData);
        }
#endif

        Bitmap(Bitmap&& bitmap);
        Bitmap(const Bitmap& bitmap);
        Bitmap(int width, int height);

        Bitmap(int width, int height, unsigned char *data);

        void setPixelRGBAColor(int x, int y, const uchar *rgba);
        void setPixelRGBAColor(int x, int y, uchar r, uchar g, uchar b, uchar a);
        void setPixel(int x, int y, const Color& color);

        void fill(const Color& color);

        unsigned char *getData() const;
        int getDataArraySize() const;
        int getWidth() const;
        int getHeight() const;

        ~Bitmap();
    };
}

#endif //VOCALTRAINERTESTS_BITMAP_H
