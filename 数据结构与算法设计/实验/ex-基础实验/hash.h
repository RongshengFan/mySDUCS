#pragma once
#include <iostream>
#include <string>

using namespace std;
//ʵ��ɢ�У�������ΪK��ʵ��ת��Ϊ����Ϊsize_t�ķǸ�����
//�ѹؼ���ת��Ϊ�Ǹ�����
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
