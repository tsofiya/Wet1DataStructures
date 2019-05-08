//
// Created by tsofi on 29/04/2019.
//

#ifndef WET1DATASTRUCTURES_SCHEDULE_H
#define WET1DATASTRUCTURES_SCHEDULE_H

#include "AVLtree.h"
#include "BiDirectionalList.h"
#include "library.h"
#include <iostream>


class Schedule{
  /*  typedef struct{
        int room;
        int hour;
    }RoomAndHour;
*/

  class RoomAndHour{
      int room;
      int hour;
    public:
      RoomAndHour(int r=0, int h=0): room(r), hour(h){}
      int getHour() {
          return hour;
      }
      int getRoom(){
          return room;
      }
  };

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
    int hoursWithLecture;

    AVLtree<int, AVLtree<int, RoomAndHour>*> courses;

public:
    Schedule(int h, int r):hours(h), rooms(r), courses(){
        idPointerArray= new idAndPointer [rooms*hours];
        emptyRoomsList= new BiDirectionalList<int>[h];

        for (int i = 0; i < hours ; ++i) {
           emptyRoomsList[i]= BiDirectionalList<int>(); //this isnt right
            for (int j = 0; j < rooms; ++j) {
                int index=dimensionsToIndex(j, i);
                idPointerArray[index].n = emptyRoomsList[i].push(index);
                idPointerArray[index].courseId = -1;
            }
        }

        emptyRoomsAmount= new int [hours];
        for (int k = 0; k < hours; ++k) {
            emptyRoomsAmount[k]= rooms;
        }

        lecturesNum=0;
        hoursWithLecture= 0;

    }

    ~Schedule(){

        delete[](emptyRoomsList);
        delete[](idPointerArray);

    }

    //Throws key not exist exception.
    void ChangeCourseID(int oldCourseID, int newCourseID){
        if (oldCourseID<=0 || newCourseID<=0)
            throw IllegalValue();
        AVLtree<int, RoomAndHour>* old= courses.getByKey(oldCourseID);
        RoomAndHour *rnhArray;
        rnhArray = old->getAllData();
        int size = old->getTreeSize();
        int index = 0, h = 0, r = 0;
        for (int i = 0; i < size; ++i) {
            h = rnhArray[i].getHour();
            r = rnhArray[i].getRoom();
            index = dimensionsToIndex(r, h);
            //  idPointerArray[*(rnhArray[i])].courseId= newCourseID;
            idPointerArray[index].courseId = newCourseID;
        }

        delete (rnhArray);
        try {
            AVLtree<int, RoomAndHour>* newid= courses.getByKey(newCourseID);
            newid->addTreeToTree(*old);
            courses.remove(oldCourseID);
        }catch (Wet1Utils::KeyNotExist& e) {
            courses.ChangeKey(oldCourseID, newCourseID);
        }
    }

    float CalculateScheduleEfficiency(){
        if (lecturesNum==0)
            throw Failure();
        return ((float) lecturesNum) / (rooms * hoursWithLecture);
    }


    int** GetAllFreeRoomsByHour(int hour, int *roomNum){
        if (hour<0|| hour>hours)
            throw IllegalValue();
        int size= emptyRoomsList[hour].size();
        if (size==0)
            throw Failure();
        int** empty=(int**)malloc(sizeof(int*)*size);
        if (!empty)
            throw std::bad_alloc();
        auto it= emptyRoomsList[hour].beginForward();
        for (int i = 0; i < size; ++i) {
            empty[i]=(int*)malloc(sizeof(int));
            if (!empty[i]) {
                for (int j = 0; j < i; ++j) {
                    free(empty[i]);
                }
                throw std::bad_alloc();
            }
            *empty[i] = getRoomByIndex(*it);
        }
        *roomNum=size;
        return empty;

    }

    void AddLecture (int hour, int roomID, int courseID){
        if (hour<0 || roomID<0 || courseID<=0 || roomID>=rooms ||
                hour >= hours){
            throw IllegalValue();
        }
        int index= dimensionsToIndex(roomID, hour);
        if (idPointerArray[index].courseId != -1){
            throw Failure();
        }
        //Todo: check and fix the node removal function in the bi-directional list class, there is a problem
//TODO: change this.
        emptyRoomsList[hour].removeNode(idPointerArray[index].n);
        idPointerArray[index].courseId=courseID;

        if (!(courses.elementExistsByKey(courseID))){

            AVLtree<int,RoomAndHour> *tree= new AVLtree<int,RoomAndHour>; // this is new
            //courses.insert(courseID, new AVLtree<int, RoomAndHour>());
            courses.insert(courseID, tree);
        }

        //courses.preOrderPrint();

        RoomAndHour rah=RoomAndHour(roomID, hour);

        AVLtree<int, RoomAndHour>* courseTree=courses.getByKey(courseID);
        //todo: this is the problematic function:
        courseTree->insert(index, rah);
        lecturesNum++;
        emptyRoomsAmount[hour]--;
        if (emptyRoomsAmount[hour] == (rooms-1)){
            hoursWithLecture++;
        }

    }



    int GetCourseID (int hour, int roomID){
        if (hour<0 || roomID<0  ||
                roomID>=rooms || hour >= hours){
            throw IllegalValue();
        }
        int index=dimensionsToIndex(roomID, hour);
        if (idPointerArray[index].courseId ==-1){
            throw Failure();
        }
        return idPointerArray[index].courseId;
    }


    void DeleteLecture (int hour, int roomID){

        if (hour<0 || roomID<0 || roomID>=rooms || hour >= hours){
            throw IllegalValue();
        }
        int index = dimensionsToIndex(roomID, hour);
        if (idPointerArray[index].courseId==-1){
            throw Failure();
        }
        int courseID=idPointerArray[index].courseId;
        AVLtree<int, RoomAndHour>* lectures = courses.getByKey(courseID); //may throw exception
        lectures->remove(index);
        //if this was the course's last lecture...
        if (lectures->getTreeSize()==0){
            courses.remove(courseID);
        }

        idPointerArray[index].n=emptyRoomsList[hour].push(roomID);
        idPointerArray[index].courseId=-1;
        emptyRoomsAmount[hour]++;
        if (emptyRoomsAmount[hour] == rooms) {
            hoursWithLecture--;
        }
        lecturesNum--;

        }
//will actually return the hours array, and put the room array in "room"

    //throws exception KeyNotExist!
    int *GetAllLecturesByCourse(int courseID, int **rooms, int *numOfLectures) {

        if (!hours || !rooms || !numOfLectures){
            throw NullArgument();
        }
        if (courseID<=0){
            throw IllegalValue();
        }
        AVLtree<int, RoomAndHour>* lectures = courses.getByKey(courseID); //may throw exception
        RoomAndHour* lectureArray= lectures->getAllData();
        int lecturesNum= lectures->getTreeSize();
        *numOfLectures=lecturesNum;

        int *hours = (int *) malloc(sizeof(int) * lecturesNum);
        if (!hours){
            throw std::bad_alloc();
        }
        int *rooms2 = (int *) malloc(sizeof(int) * lecturesNum);
        if (!rooms2){
            throw std::bad_alloc();
        }

        for (int i=0; i<lecturesNum; i++) {

            hours[i] = lectureArray[i].getHour();
            rooms2[i] = lectureArray[i].getRoom();
        }
        *rooms = rooms2;
        return hours;
        }

private:
    int dimensionsToIndex(int i, int j){
        return i*rooms+j;
    }

    int getRoomByIndex(int index) {
        return index / rooms;
    }

    int getHourByIndex(int index) {
        return index % rooms;
    }
};

#endif //WET1DATASTRUCTURES_SCHEDULE_H
