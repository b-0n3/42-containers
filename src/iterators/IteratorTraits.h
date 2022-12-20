//
// Created by Abdelouahad Ait hamd on 12/3/22.
//

#ifndef FT_CONTAINERS_ITERATORTRAITS_H
#define FT_CONTAINERS_ITERATORTRAITS_H
namespace ft {
    template<class Iterator>
    class IteratorTraits {
    public:
        typedef typename Iterator::value_type value_type;
        typedef typename Iterator::difference_type difference_type;
        typedef typename Iterator::pointer pointer;
        typedef typename Iterator::reference reference;
        typedef typename Iterator::iterator_category iterator_category;
    };
}
#endif //FT_CONTAINERS_ITERATORTRAITS_H
