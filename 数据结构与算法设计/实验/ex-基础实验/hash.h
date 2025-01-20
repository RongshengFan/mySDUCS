#pragma once
#include <iostream>
#include <string>

using namespace std;
//实现散列，将类型为K的实例转换为类型为size_t的非负整数
//把关键字转换为非负整数
template <class K> class Hash;

template<>
class Hash<string>
{
public:
    size_t operator()(const string theKey) const
    {// Convert theKey to a nonnegative integer.
        unsigned long hashValue = 0;
        int length = (int)theKey.length();
        for (int i = 0; i < length; i++)
            hashValue = 5 * hashValue + theKey.at(i);

        return size_t(hashValue);
    }
};

template<>
class Hash<int>
{
public:
    size_t operator()(const int theKey) const
    {
        return size_t(theKey);
    }
};

template<>
class Hash<long>
{
public:
    size_t operator()(const long theKey) const
    {
        return size_t(theKey);
    }
};
