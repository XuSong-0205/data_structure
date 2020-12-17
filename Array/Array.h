/*
 * @Author: 穹
 * @Date: 2020-12-15 00:16:43
 * @LastEditTime: 2020-12-15 19:14:32
 * @LastEditors: Please set LastEditors
 * @Description: Upgraded version of built-in array
 * @FilePath: \cpp_code\Array\Array.h
 */
#ifndef _ARRAY_H_
#define _ARRAY_H_

#include <array>
#include <algorithm>
#include <stdexcept>

#define SX_NAMESPACE_BEGIN namespace sx {
#define SX_NAMESPACE_END   }


SX_NAMESPACE_BEGIN


template<typename T, size_t _size>
class Array
{
private:
    T _array[_size];
    
public:
    using value_type = T;
    using size_type = size_t;
    using pointer = value_type *;
    using const_pointer = const value_type *;
    using reference = value_type &;
    using const_reference = const value_type &;

    template <typename _reverse_iterator>
    class _Array_reverse_iterator;

    using iterator = pointer;
    using const_iterator = const_pointer;
    using reverse_iterator = _Array_reverse_iterator<iterator>;
    using const_reverse_iterator = _Array_reverse_iterator<const_iterator>;

    template <typename _reverse_iterator>
    class _Array_reverse_iterator
    {
    private:
        _reverse_iterator current;
        _Array_reverse_iterator(_reverse_iterator p) : current(p) {}

        friend class Array;

    public:
        _Array_reverse_iterator() : current(nullptr) {}

        reverse_iterator &operator++()
        {
            --current;
            return *this;
        }
        reverse_iterator operator++(int)
        {
            T *temp = current;
            --current;
            return temp;
        }

        reverse_iterator &operator--()
        {
            ++current;
            return *this;
        }

        reverse_iterator operator--(int)
        {
            T *temp;
            ++current;
            return temp;
        }

        reference operator*() { return *current; }
        const_reference operator*() const { return *current; }

        bool operator==(const reverse_iterator &iter) noexcept { return current == iter.current; }
        bool operator==(const reverse_iterator &iter) const noexcept { return current == iter.current; }
        bool operator!=(const reverse_iterator &iter) noexcept { return !(*this == iter); }
        bool operator!=(const reverse_iterator &iter) const noexcept { return !(*this == iter); }

    };  // class reverse_iterator end


    Array() : _array{T()} {}
    explicit Array(const T &t) { fill(t); }
    Array(const std::array<T, _size> &arr) { std::copy(arr.begin(), arr.end(), begin()); }

    constexpr size_type size() const noexcept { return _size; }
    constexpr bool empty() const noexcept { return size() == 0; }

    void fill(const T &t) { std::fill(begin(), end(), t); }
    void swap(Array<T, _size> &arr) noexcept { std::swap(_array, arr._array); }

    reference operator[](size_t pos) { return _array[pos]; }
    const_reference operator[](size_t pos) const { return _array[pos]; }

    reference at(size_t pos) 
    {
        if(pos >= size())
            std::out_of_range("Array::at pos >= _size");
        return operator[](pos);
    }
    const_reference at(size_t pos) const
    {
        if(pos >= size())
            std::out_of_range("Array::at pos >= _size");
        return operator[](pos);
    }

    pointer data() noexcept { return _array; }
    const_pointer data() const noexcept { return _array; }

    iterator begin() noexcept { return data(); }
    const_iterator begin() const noexcept { return data(); }
    const_iterator cbegin() const noexcept { return data(); }
    reverse_iterator rbegin() noexcept { return reverse_iterator(empty() ? data() : (data() + size() - 1)); }
    const_reverse_iterator crbegin() const noexcept { return reverse_iterator(empty() ? data() : (data() + size() - 1)); }
    iterator end() noexcept { return data() + size(); }
    const_iterator end() const noexcept { return data() + size(); }
    const_iterator cend() const noexcept { return data() + size(); }
    reverse_iterator rend() noexcept { return reverse_iterator(empty() ? data() : (data() - 1)); }
    const_reverse_iterator crend() const noexcept { return reverse_iterator(empty() ? data() : (data() - 1)); }

    reference front() noexcept { return *begin(); }
    const_reference front() const noexcept { return *begin(); }
    reference back() noexcept { return empty() ? *end() : *(end() - 1); }
    const_reference back() const noexcept { return empty() ? *end() : *(end() - 1); }
};  // class Array end


SX_NAMESPACE_END

#endif // _ARRAY_H_ end