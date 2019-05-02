//
// Created by tsofi on 29/04/2019.
//

#ifndef WET1DATASTRUCTURES_SCHEDULE_H
#define WET1DATASTRUCTURES_SCHEDULE_H

#include "AVLtree.h"
#include "BiDirectionalList.h"


class Schedule{
    typedef struct{
        int room;
        int hour;
    }RoomAndHour;

    typedef struct {
        int courseId;
        Node<int>* n;
    } idAndPointer;

    idAndPointer* idPointerArray;
    BiDirectionalList<int> * emptyRoomsList;
    int* emptyRoomsAmount;
    int hours;
    int rooms;
    int lecturesNum;
    int atListOne;
    AVLtree<int, AVLtree<int, RoomAndHour>*> courses;

public:
    Schedule(int h, int r):hours(h), rooms(r), courses(){
        idPointerArray= new idAndPointer [rooms*hours];
        emptyRoomsList= new BiDirectionalList<int>[h];

        for (int i = 0; i < rooms ; ++i) {
            emptyRoomsList[i]= BiDirectionalList<int>();
            for (int j = 0; j < hours; ++j) {
                int index=dimensionsToIndex(i, j);
                idPointerArray[index].n=  emptyRoomsList[i].push(index);
            }
        }

        emptyRoomsAmount= new int [hours];
        for (int k = 0; k < hours; ++k) {
            emptyRoomsAmount[k]= rooms;
        }

        lecturesNum=0;
        atListOne= 0;
    }

    //Throws key not exist exception.
    void ChangeCourseID(int oldCourseID, int newCourseID){
        AVLtree<int, RoomAndHour>* old= courses.getByKey(oldCourseID);
        RoomAndHour* rnhArray= old->getAllData();
        int size= old->getTreeSize();
        for (int i = 0; i < size; ++i) {
            idPointerArray[rnhArray[i]].courseId= newCourseID;
        }

        delete(rnhArray);
    }

    float CalculateScheduleEfficiency(){
        return (float)lecturesNum/(rooms*atListOne);
    }


    int** GetAllFreeRoomsByHour(int hour, int *roomNum){
        if (hours<=0&& hour<hours)
            throw IllegalValue();
        int size= emptyRoomsList[hour-1].size();
        int** empty=malloc(sizeof(int*)*hour);
        auto it= emptyRoomsList[hour-1].beginForward();
        for (int i = 0; i < size; ++i) {
            empty[i]=malloc(sizeof(int));
            *empty[i]=*it;
        }
        return empty;

    }


private:
    int dimensionsToIndex(int i, int j){
        return i*rooms+j;
    }
};

#endif //WET1DATASTRUCTURES_SCHEDULE_H
