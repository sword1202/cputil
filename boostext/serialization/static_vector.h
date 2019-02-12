//
// Created by Semyon Tikhonenko on 2019-02-12.
//

#ifndef TEXTIMAGESGENERATOR_SERIALIZATION_H
#define TEXTIMAGESGENERATOR_SERIALIZATION_H

#include <boost/serialization/serialization.hpp>
#include <boost/container/static_vector.hpp>
#include "stl_container.h"

namespace boost {
    namespace serialization {
        template<typename Archive, typename T, size_t N>
        void save(Archive & ar, const boost::container::static_vector<T, N>& t, unsigned int version) {
            save_stl_container(ar, t, version);
        }

        template<typename Archive, typename T, size_t N>
        void load(Archive & ar, boost::container::static_vector<T, N>& t, unsigned int version) {
            load_stl_container(ar, t, version);
        }

        template<class Archive, class T, size_t N>
        inline void serialize(Archive & ar,
                boost::container::static_vector<T, N>& t,
                const unsigned int file_version) {
            split_free(ar, t, file_version);
        }

    } // namespace serialization
} // namespace boost

#endif //TEXTIMAGESGENERATOR_SERIALIZATION_H
