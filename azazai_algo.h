//
// Created by Semyon Tikhonenko on 8/7/16.
//

#ifndef PITCHDETECTION_AZAZAI_ALGO_H
#define PITCHDETECTION_AZAZAI_ALGO_H

#include <algorithm>

namespace Azazai {
    template<typename Iterator, typename Element>
    Iterator find_nearest_element_in_sorted_collection(Iterator begin, Iterator end, const Element& value) {
        if (begin == end) {
            return end;
        }

        Iterator lowerBound = std::lower_bound(begin, end, value);

        if (lowerBound == end) {
            return lowerBound - 1;
        }

        if (*lowerBound == value) {
            return lowerBound;
        }

        Element downDistance = value - *(lowerBound - 1);
        Element upDistance = *lowerBound - value;

        if (upDistance > downDistance) {
            return lowerBound - 1;
        } else {
            return lowerBound;
        }
    };
}

#endif //PITCHDETECTION_AZAZAI_ALGO_H
