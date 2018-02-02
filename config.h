//
// Created by Semyon Tikhonenko on 11/24/17.
//

#ifndef CPP_UTILS_DLLHIDE
#ifdef __APPLE__
    #define CPP_UTILS_DLLHIDE __attribute__((visibility ("hidden")))
#else
    #define CPP_UTILS_DLLHIDE
#endif
#endif
