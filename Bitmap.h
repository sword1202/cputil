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
#if defined(__OBJC__)
        static inline Bitmap fromCGImage(CGImage* image) {
#if TARGET_OS_MAC && !TARGET_OS_IPHONE && !TARGET_OS_SIMULATOR
            NSBitmapImageRep* rep = [[NSBitmapImageRep alloc] initWithCGImage:image];
            return Bitmap(int(rep.size.width), int(rep.size.height), rep.bitmapData);
#else
            NSUInteger width = CGImageGetWidth(image);
            NSUInteger height = CGImageGetHeight(image);
            CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();
            Bitmap bitmap(static_cast<int>(width), static_cast<int>(height));
            bitmap.fill(Color::transparent());
            NSUInteger bytesPerPixel = 4;
            NSUInteger bytesPerRow = bytesPerPixel * width;
            NSUInteger bitsPerComponent = 8;
            CGContextRef context = CGBitmapContextCreate(bitmap.data,
                    width, height, bitsPerComponent,
                    bytesPerRow, colorSpace,
                    kCGImageAlphaPremultipliedLast | kCGBitmapByteOrder32Big);
            CGColorSpaceRelease(colorSpace);

            CGContextDrawImage(context, CGRectMake(0, 0, width, height), image);
            CGContextRelease(context);
            return bitmap;
#endif
        }
#endif
        Bitmap();
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
