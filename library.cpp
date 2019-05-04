//
// Created by lucio on 4/30/2019.
//

#include "library.h"
#include "Schedule.h"

void *Init(int hours, int rooms) {
    try {
        Schedule *DS = new Schedule(hours, rooms);
    }
    catch (const Wet1Exceptions& e){
        return NULL;
    }
    catch (std::bad_alloc& ba){
        return NULL;
    }
    return (void*)DS;
}

StatusType AddLecture(void *DS, int hour, int roomID, int courseID) {

    if (!DS){
        return INVALID_INPUT;
    }
    try {
        ((Schedule *)DS)-> AddLecture(hour, roomID, courseID);
    }
    catch (const IllegalValue& e){
        return INVALID_INPUT;
    }
    catch (const FailureToAddLecture& e){
        return FAILURE;
    }
    catch (const std::bad_alloc& ba){
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

StatusType GetCourseID (void *DS, int hour, int roomID, int *courseID){

    if (!DS || !courseID){
        return INVALID_INPUT;
    }
    try {
        *courseID = ((Schedule *)DS)-> GetCourseID(hour, roomID);
    }
    catch (const IllegalValue& e){
        return INVALID_INPUT;
    }
    catch (const Failure& e){
        return FAILURE;
    }
    catch (const std::bad_alloc& ba){
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

StatusType DeleteLecture (void *DS, int hour, int roomID){
    if (!DS){
        return INVALID_INPUT;
    }
    try {
        ((Schedule *)DS)-> DeleteLecture(hour, roomID);
    }
    catch (const IllegalValue& e){
        return INVALID_INPUT;
    }
    catch (const Failure& e){
        return FAILURE;
    }
    catch (const std::bad_alloc& ba){
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

StatusType ChangeCourseID (void* DS, int oldCourseID, int newCourseID){

    if (!DS){
        return INVALID_INPUT;
    }
    try {
        ((Schedule *)DS)-> ChangeCourseID(oldCourseID, newCourseID);
    }
    catch (const IllegalValue& e){
        return INVALID_INPUT;
    }
    catch (const Failure& e){
        return FAILURE;
    }
    catch (const std::bad_alloc& ba){
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

StatusType CalculateScheduleEfficiency(void *DS, float *efficiency){

    if (!DS || !efficiency){
        return INVALID_INPUT;
    }
    try {
        *efficiency=((Schedule *)DS)-> CalculateScheduleEfficiency();
    }
    catch (const IllegalValue& e){
        return INVALID_INPUT;
    }
    catch (const Failure& e){
        return FAILURE;
    }
    catch (const std::bad_alloc& ba){
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

StatusType GetAllFreeRoomsByHour(void *DS, int hour, int **rooms, int* numOfRooms) {

    if (!DS || !numOfRooms || !rooms){
        return INVALID_INPUT;
    }

    try {
        ((Schedule *)DS)-> GetAllFreeRoomsByHour(hour, rooms, numOfRooms);
    }
    catch (const IllegalValue& e){
        return INVALID_INPUT;
    }
    catch (const Failure& e){
        return FAILURE;
    }
    catch (const std::bad_alloc& ba){
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

StatusType GetAllLecturesByCourse(void *DS, int courseID, int **hours, int **rooms, int *numOfLectures){

    if (!DS || !hours || !rooms || !numOfLectures){
        return INVALID_INPUT;
    }
    try{
        hours= ((Schedule *)DS)->GetAllLecturesByCourse(courseID, rooms, numOfLectures);
        }
    catch (const IllegalValue& e){
        return INVALID_INPUT;
    }
    catch (const Failure& e){
        return FAILURE;
    }
    catch (const std::bad_alloc& ba){
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}



