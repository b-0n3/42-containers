//
// Created by Abdelouahad Ait hamd on 12/9/22.
//

#pragma  once
namespace ft {
    struct true_type {
        static const bool value = true;
    };
    struct false_type {
        static const bool value = false;
    };

    template<class T> struct is_integral : public false_type {};
    template<> struct is_integral<bool> : public true_type {};
    template<> struct is_integral<char> : public true_type {};
    template<> struct is_integral<signed char> : public true_type {};
    template<> struct is_integral<unsigned char> : public true_type {};
    template<> struct is_integral<wchar_t> : public true_type {};
    template<> struct is_integral<char16_t> : public true_type {};
    template<> struct is_integral<char32_t> : public true_type {};
    template<> struct is_integral<short> : public true_type {};
    template<> struct is_integral<unsigned short> : public true_type {};
    template<> struct is_integral<int> : public true_type {};
    template<> struct is_integral<unsigned int> : public true_type {};
    template<> struct is_integral<long> : public true_type {};
    template<> struct is_integral<unsigned long> : public true_type {};
    template<> struct is_integral<long long> : public true_type {};
    template<> struct is_integral<unsigned long long> : public true_type {};



    template <class T> struct is_InputIterator : public false_type {};
    template <> struct is_InputIterator<std::input_iterator_tag> : public true_type {};
}
