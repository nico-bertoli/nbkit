#pragma once
#include <vector>
#include <iterator>

namespace nbkit
{
    /// <summary>
    /// Implementation of a 2D vector using monodimensional vector for cache efficiency
    /// </summary>
    template<typename T>
    class Matrix
    {
        // -------------------------------------------------------------------- fields
    private:
        size_t width_ = 0;
        std::vector<T> vector_;

        // -------------------------------------------------------------------- methods
    public:
        Matrix() : Matrix(0) {};
        Matrix(size_t width) : width_(width) { vector_.resize(width); }

        Matrix(size_t width, const std::vector<T>& vect) : width_(width)
        {
            vector_ = vect;
        }

        size_t GetSizeX() const { return width_; }
        size_t GetSizeY() const { return width_ == 0 ? 0 : vector_.size() / width_; }

        void IncreaseSizeY() { vector_.resize(vector_.size() + width_); }
        void Resize(size_t width, size_t height)
        {
            width_ = width;
            vector_.resize(width * height);
        }
        void Clear() { vector_.clear(); width_ = 0; }

        const T& Get(size_t x, size_t y) const { return vector_[width_ * y + x]; }
        T& Get(size_t x, size_t y) { return vector_[width_ * y + x]; }

        // -------------------------------------------------------------------- iterator
    public:
        class Iterator
        {
        public:
            // iterator traits
            using iterator_category = std::random_access_iterator_tag;
            using value_type = T;
            using difference_type = std::ptrdiff_t; 
            using pointer = T*;
            using reference = T&;

        private:
            typename std::vector<T>::iterator it_;

        public:
            Iterator(typename std::vector<T>::iterator it) : it_(it) {}

            reference operator*() { return *it_; }
            pointer operator->() { return &(*it_); }
            Iterator& operator++() { ++it_; return *this; }
            Iterator operator++(int) { Iterator temp = *this; ++it_; return temp; }
            Iterator& operator--() { --it_; return *this; }
            Iterator operator--(int) { Iterator temp = *this; --it_; return temp; }
            Iterator operator+(difference_type n) const { return Iterator(it_ + n); }
            Iterator operator-(difference_type n) const { return Iterator(it_ - n); }
            Iterator& operator+=(difference_type n) { it_ += n; return *this; }
            Iterator& operator-=(difference_type n) { it_ -= n; return *this; }
            difference_type operator-(const Iterator& other) const { return it_ - other.it_; }
            bool operator==(const Iterator& other) const { return it_ == other.it_; }
            bool operator!=(const Iterator& other) const { return it_ != other.it_; }
            bool operator<(const Iterator& other) const { return it_ < other.it_; }
            bool operator<=(const Iterator& other) const { return it_ <= other.it_; }
            bool operator>(const Iterator& other) const { return it_ > other.it_; }
            bool operator>=(const Iterator& other) const { return it_ >= other.it_; }
            reference operator[](difference_type n) const { return *(it_ + n); }
        };

        Iterator begin() { return Iterator(vector_.begin()); }
        Iterator end() { return Iterator(vector_.end()); }

        // -------------------------------------------------------------------- const Iterator
        class ConstIterator
        {
        public:
            using iterator_category = std::random_access_iterator_tag;
            using value_type = const T;
            using difference_type = std::ptrdiff_t;
            using pointer = const T*;
            using reference = const T&;

        private:
            typename std::vector<T>::const_iterator it_;

        public:
            ConstIterator(typename std::vector<T>::const_iterator it) : it_(it) {}

            reference operator*() const { return *it_; }
            pointer operator->() const { return &(*it_); }
            ConstIterator& operator++() { ++it_; return *this; }
            ConstIterator operator++(int) { ConstIterator temp = *this; ++it_; return temp; }
            ConstIterator& operator--() { --it_; return *this; }
            ConstIterator operator--(int) { ConstIterator temp = *this; --it_; return temp; }
            ConstIterator operator+(difference_type n) const { return ConstIterator(it_ + n); }
            ConstIterator operator-(difference_type n) const { return ConstIterator(it_ - n); }
            ConstIterator& operator+=(difference_type n) { it_ += n; return *this; }
            ConstIterator& operator-=(difference_type n) { it_ -= n; return *this; }
            difference_type operator-(const ConstIterator& other) const { return it_ - other.it_; }
            bool operator==(const ConstIterator& other) const { return it_ == other.it_; }
            bool operator!=(const ConstIterator& other) const { return it_ != other.it_; }
            bool operator<(const ConstIterator& other) const { return it_ < other.it_; }
            bool operator<=(const ConstIterator& other) const { return it_ <= other.it_; }
            bool operator>(const ConstIterator& other) const { return it_ > other.it_; }
            bool operator>=(const ConstIterator& other) const { return it_ >= other.it_; }
            reference operator[](difference_type n) const { return *(it_ + n); }
        };

        ConstIterator begin() const { return ConstIterator(vector_.begin()); }
        ConstIterator end() const { return ConstIterator(vector_.end()); }
    };
}
