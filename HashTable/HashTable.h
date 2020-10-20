#pragma once
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <array>
#include <list>
#include <ctime>
#include <random>
#include <unordered_set>

using std::cin;
using std::cout;
using std::endl;
using std::list;
using std::array;
using std::vector;
using std::string;
using std::unordered_set;
using std::default_random_engine;
using std::uniform_int_distribution;


/**********************************************************
 * HaspTable 的分离链接法实现                             *
 * 链表 + 数组                                            *
 * 实质为链表数组                                         *
 *********************************************************/ 
template<typename Key>
class HashTable
{
public:
    explicit HashTable(int num = 11) : hashTable(nextPrime(num)) {}

    bool contains(const Key& key)const
    {
        auto& whichList = hashTable.at(myhash(key));
        return find(begin(whichList), end(whichList), key) != end(whichList);
    }

    bool empty()const
    {
        return currentsize == 0;
    }

    void makeEmpty()
    {
        for (auto& theHashTable : hashTable)
            theHashTable.clear();
        currentsize = 0;
    }

    bool insert(const Key& key)
    {
        auto& whichList = hashTable.at(myhash(key));
        if (find(begin(whichList), end(whichList), key) != end(whichList))
            return false;
        whichList.push_back(key);

        if (++currentsize > hashTable.size())
            rehash();

        return true;
    }

    bool insert(Key&& key)
    {
        auto& whichList = hashTable.at(myhash(key));
        if (find(begin(whichList), end(whichList), key) != end(whichList))
            return false;
        whichList.push_back(std::move(key));

        if (++currentsize > hashTable.size())
            rehash();

        return true;
    }

    bool remove(const Key& key)
    {
        auto& whichList = hashTable.at(myhash(key));
        auto itr = find(begin(whichList), end(whichList), key);

        if (itr == end(whichList))
            return false;
        
        whichList.erase(itr);
        --currentsize;
        return true;
    }

    size_t size()const
    {
        return currentsize;
    }

    size_t capacity()const
    {
        return hashTable.size();
    }

private:
    vector<list<Key>> hashTable;
    size_t currentsize = 0;

    size_t primesArrayIndex = 0;
    const static array<int, 22> primesArray;

	int nextPrime(int nextpr = 0)
    {
        if (nextpr)
        {
			while (primesArrayIndex < 22)
            {
                if (primesArray.at(primesArrayIndex) >= nextpr)
                    return primesArray.at(primesArrayIndex);

                ++primesArrayIndex;
            }
        }

        // hashTable大小超过 26339969 ，即primeArrayIndex大于等于 22 将引发此异常
        if (++primesArrayIndex >= 22)
            throw "HashTable too big...";

        return primesArray.at(primesArrayIndex);
    }

    void rehash()
    {
        vector<list<Key>> oldTable = hashTable;

        // 创建一个两倍大的空表
        hashTable.resize(nextPrime());
        for (auto& thisList : hashTable)
            thisList.clear();

        // 复制整个表
        currentsize = 0;
        for (auto& thisList : oldTable)
            for (auto& key : thisList)
                insert(std::move(key));

    }

    size_t myhash(const Key& key)const noexcept
    {
        static std::hash<Key> hf;
        return hf(key) % hashTable.size();
    }
};

template<typename Key>
const array<int, 22> HashTable<Key>::primesArray{ 11, 23, 47, 97, 197, 397, 797, 1597, 3203, 6421,12853, 25717,
    51437, 102877, 205759, 411527, 823117, 1646237, 3292489, 6584983, 13169977, 26339969 };