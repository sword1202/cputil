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
#if __OBJC__
        static inline Bitmap fromCGImage(CGImage* image) {
#if defined(__OBJC__) && TARGET_OS_MAC && !TARGET_OS_IPHONE && !TARGET_OS_SIMULATOR
            NSBitmapImageRep* rep = [[NSBitmapImageRep alloc] initWithCGImage:image];
            return Bitmap(int(rep.size.width), int(rep.size.height), rep.bitmapData);
#else
            CFDataRef rawData = CGDataProviderCopyData(CGImageGetDataProvider(image));
            UInt8* buf = (UInt8 *) CFDataGetBytePtr(rawData);
            CFIndex length = CFDataGetLength(rawData);
            int width = static_cast<int>(CGImageGetWidth(image));
            int height = static_cast<int>(CGImageGetHeight(image));
            Bitmap bitmap(width, height, buf);
            CFRelease(rawData);
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
