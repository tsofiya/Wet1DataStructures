//
// Created by tsofi on 28/04/2019.
//

#ifndef LIST_EFFICIENTARRAY_H
#define LIST_EFFICIENTARRAY_H

#include "Wet1Exceptions.h"

using namespace Wet1Utils;


template<class T>
class EfficientArray {
private:
    T *dataArray;
    int *safeZoneArray;
    int *defined;
    int top;
    int initValue;
    int size;

public:
    EfficientArray(int sz, int ivalue) : size(sz), initValue(ivalue), top(-1) {
        if (size < 1)
            throw IllegalValue();
        dataArray = new T[size];
        safeZoneArray = new int[size];
        defined = new int[size];

    }

    ~EfficientArray() {
        delete[] dataArray;
        delete[] defined;
        delete[] safeZoneArray;

    }

    const T &operator[](int position) {
        if (position > size - 1 || position < 0)
            throw OutOfBounds();

        if (!isGarbage(position))
            return dataArray[position];
        return initValue;
    }

    void insertValue(int index, const T &value) {
        if (index > size - 1 || index < 0)
            throw OutOfBounds();

        if (isGarbage(index)) {
            top++;
            safeZoneArray[index] = top;
            defined[top] = index;
        }

        dataArray[index] = T(value);
    }

private:
    bool isGarbage(int pos) {
        if (safeZoneArray[pos] <= top && safeZoneArray[pos]>=0)
            if (defined[safeZoneArray[pos]] == pos)
                return false;
        return true;
    }
};

#endif //LIST_EFFICIENTARRAY_H
