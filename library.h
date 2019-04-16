/****************************************************************************/
/*                                                                          */
/* This file contains the interface functions                               */
/* you should use for the wet ex 1                                          */
/*                                                                          */
/****************************************************************************/

/****************************************************************************/
/*                                                                          */
/* File Name : library.h                                                   */
/*                                                                          */
/****************************************************************************/

#ifndef _234218_WET1
#define _234218_WET1

#ifdef __cplusplus
extern "C" {
#endif

/* Return Values
 * ----------------------------------- */
typedef enum {
    SUCCESS = 0,
    FAILURE = -1,
    ALLOCATION_ERROR = -2,
    INVALID_INPUT = -3
} StatusType;


void *Init(int hours, int rooms);

StatusType AddLecture(void *DS, int hour, int roomID, int courseID);

StatusType GetCourseID(void *DS, int hour, int roomID, int *courseID);

StatusType DeleteLecture(void *DS, int hour, int roomID);

StatusType ChangeCourseID(void *DS, int oldCourseID, int newCourseID);

StatusType CalculateScheduleEfficiency(void *DS, float *efficiency);

StatusType GetAllFreeRoomsByHour(void *DS, int hour, int **rooms, int* numOfRooms);

StatusType GetAllLecturesByCourse(void *DS, int courseID, int **hours, int **rooms, int *numOfLectures);

void Quit(void** DS);

#ifdef __cplusplus
}
#endif

#endif    /*_234218_WET1 */
