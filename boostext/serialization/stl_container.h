//
// Created by Semyon Tikhonenko on 2019-02-12.
//

#ifndef TEXTIMAGESGENERATOR_STL_CONTAINER_H
#define TEXTIMAGESGENERATOR_STL_CONTAINER_H


namespace boost {
    namespace serialization {
        template<typename Archive, typename Container>
        void save_stl_container(Archive& ar, const Container& container, unsigned int version) {
            ar << container.size();
            for (const auto& item : container) {
                ar << item;
            }
        }

        template<typename Archive, typename Container>
        void load_stl_container(Archive& ar, Container& container, unsigned int version) {
            int size;
            ar >> size;
            for (int i = 0; i < size; ++i) {
                typename Container::value_type value;
                ar >> value;
                container.insert(container.end(), value);
            }
        }
    }
}

#endif //TEXTIMAGESGENERATOR_STL_CONTAINER_H
