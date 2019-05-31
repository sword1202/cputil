//
// Created by Semyon Tykhonenko on 2019-05-31.
//

#ifndef TEXTIMAGESGENERATOR_DEBUG_H
#define TEXTIMAGESGENERATOR_DEBUG_H

#include <iostream>

namespace CppUtils {
    namespace Debug {
        template <typename Map>
        void PrintMap(const Map& map) {
            for (const auto& pair : map) {
                std::cout<<pair.first<<"->"<<pair.second<<"\n";
            }
        }
    }
}


#endif //TEXTIMAGESGENERATOR_DEBUG_H
