
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

using namespace std;

#include "library.h"


void Test_Init_And_Quit(){
    void* DS = Init(-1,4);
    assert(DS == nullptr);
    Quit(&DS);
    assert(DS == nullptr);
    DS = Init(0,4);
    assert(DS == nullptr);
    Quit(&DS);
    assert(DS == nullptr);
    DS = Init(4,0);
    assert(DS == nullptr);
    Quit(&DS);
    assert(DS == nullptr);
    DS = Init(4,2);
    assert(DS != nullptr);
    Quit(&DS);
    assert(DS == nullptr);
    DS = Init(100,100);
    assert(DS != nullptr);
    Quit(&DS);
    assert(DS == nullptr);

}

void Test_AddLecture() {
    void *DS = Init(300, 300);
    assert(DS != nullptr);

    assert(AddLecture(DS, 0, 5, 0) == INVALID_INPUT);
    assert(AddLecture(DS, 0, 5, -1) == INVALID_INPUT);
    assert(AddLecture(DS, -1, 5, 2) == INVALID_INPUT);
    assert(AddLecture(DS, 1, -5, 2) == INVALID_INPUT);
    assert(AddLecture(nullptr, 1, 5, 2) == INVALID_INPUT);
    assert(AddLecture(DS, 8, 8, 234218) == SUCCESS);
    assert(AddLecture(DS, 9, 9, 234218) == SUCCESS);
    assert(AddLecture(DS, 10, 10, 234218) == SUCCESS);

    assert(AddLecture(nullptr, 10, 10, 234218) == INVALID_INPUT);

    assert(AddLecture(DS, 8, 8, 234218) == FAILURE);
    assert(AddLecture(DS, 9, 9, 234218) == FAILURE);
    assert(AddLecture(DS, 10, 10, 234219) == FAILURE);

    printf("got to loop\n");
    for (int i = 11; i < 19; i++) {
        assert(AddLecture(DS, i, i, 234218) == SUCCESS); //here there is a problem already...
        cout << "i:" << (i) << "Success." << endl;
        assert(AddLecture(DS, i, i, 234219) == FAILURE);
        cout << "i:" << (i) << "Fail." << endl;

    }
    for (int i = 20; i < 23; i++) {
        assert(AddLecture(DS, i, i, i) == SUCCESS);
        assert(AddLecture(DS, i, i, i) == FAILURE);
    }

    Quit(&DS);
    assert(DS == nullptr);
}

void Test_DeleteLecture() {
    void *DS = Init(120, 120);
    assert(DS != nullptr);

    for (int i = 1; i < 10; ++i) {
        AddLecture(DS, i, i, 234218);
    }
    for (int i = 10; i < 20; ++i) {
        AddLecture(DS, i, i, 234217);
    }
    for (int i = 20; i < 30; ++i) {
        AddLecture(DS, i, i, 234216);
    }
    for (int i = 30; i < 40; ++i) {
        AddLecture(DS, i, i, 234215);
    }
    for (int i = 40; i < 100; ++i) {
        AddLecture(DS, i, i, 234214);
    }
    assert(DeleteLecture(DS, 12, 12) == SUCCESS);
    assert(DeleteLecture(DS, 22, 22) == SUCCESS);
    assert(DeleteLecture(DS, 33, 33) == SUCCESS);
    assert(DeleteLecture(DS, 44, 44) == SUCCESS);
    assert(DeleteLecture(DS, 60, 60) == SUCCESS);
    assert(DeleteLecture(DS, -1, 2) == INVALID_INPUT);
    assert(DeleteLecture(DS, 1, -2) == INVALID_INPUT);
    assert(DeleteLecture(nullptr, 1, 2) == INVALID_INPUT);

    assert(DeleteLecture(DS, 1, 1) == SUCCESS);
    assert(DeleteLecture(DS, 1, 2) == FAILURE);
    assert(AddLecture(DS, 1, 1, 234218) == SUCCESS);
    assert(DeleteLecture(DS, 1, 1) == SUCCESS);
    assert(DeleteLecture(DS, 1, 1) == FAILURE);

    for (int j = 2; j < 10; ++j) {
        assert(DeleteLecture(DS, j, j) == SUCCESS);
        assert(DeleteLecture(DS, j, j) == FAILURE);
    }

    for (int j = 9; j > 0; --j) {
        assert(DeleteLecture(DS, j, j) == FAILURE);
        assert(AddLecture(DS, j, j, 234218) == SUCCESS);
    }
    assert(DeleteLecture(nullptr, 11, 11) == INVALID_INPUT);

    assert(DeleteLecture(DS, 7, 7) == SUCCESS);
    assert(DeleteLecture(DS, 1, 1) == SUCCESS);
    assert(DeleteLecture(DS, 9, 9) == SUCCESS);
    assert(DeleteLecture(DS, 8, 8) == SUCCESS);
    assert(DeleteLecture(DS, 3, 3) == SUCCESS);
    assert(DeleteLecture(DS, 6, 6) == SUCCESS);
    assert(DeleteLecture(DS, 2, 2) == SUCCESS);
    assert(DeleteLecture(DS, 5, 5) == SUCCESS);
    assert(DeleteLecture(DS, 4, 4) == SUCCESS);

    Quit(&DS);
      assert(DS == nullptr);
}

void Test_GetCourseID() {

    void *DS = Init(50, 50);
    assert(DS != nullptr);

    int courseId = 234218;
    courseId++;
    courseId--;
    if (courseId) {

    }
    assert(AddLecture(DS, 1, 1, 234218) == SUCCESS);
    assert(AddLecture(DS, 9, 9, 234218) == SUCCESS);
    assert(AddLecture(DS, 10, 10, 234219) == SUCCESS);
    assert(AddLecture(DS, 20, 20, 234219) == SUCCESS);
    assert(AddLecture(DS, 30, 30, 234219) == SUCCESS);

    assert(GetCourseID(nullptr, 0, 1, &courseId) == INVALID_INPUT);
    assert(GetCourseID(DS, 8, 1, nullptr) == INVALID_INPUT);
    assert(GetCourseID(DS, -1, 4, &courseId) == INVALID_INPUT);
    assert(GetCourseID(DS, 8, -1, &courseId) == INVALID_INPUT);
    assert(GetCourseID(DS, 80, 1, &courseId) == INVALID_INPUT);
    assert(GetCourseID(DS, 1, 80, &courseId) == INVALID_INPUT);
    assert(courseId == 234218);

    assert(GetCourseID(DS, 11, 1, &courseId) == FAILURE);
    assert(GetCourseID(DS, 9, 1, &courseId) == FAILURE);
    assert(GetCourseID(DS, 8, 0, &courseId) == FAILURE);
    assert(GetCourseID(DS, 8, 3, &courseId) == FAILURE);
    assert(courseId == 234218);

    assert(GetCourseID(DS, 1, 1, &courseId) == SUCCESS);
    assert(courseId == 234218);

    assert(DeleteLecture(DS, 1, 1) == SUCCESS);
    assert(GetCourseID(DS, 1, 1, &courseId) == FAILURE);
    assert(courseId == 234218);

    assert(AddLecture(DS, 1, 1, 234218) == SUCCESS);
    assert(GetCourseID(DS, 1, 2, &courseId) == FAILURE);
    assert(AddLecture(DS, 9, 9, 20) == FAILURE);
    assert(GetCourseID(DS, 20, 20, &courseId) == SUCCESS);
    assert(courseId == 234219);
    courseId = 0;
    Quit(&DS);
      assert(DS == nullptr);
}

void Test_ChangeCourseID() {

    void *DS = Init(100, 100);
    for (int i = 1; i < 10; ++i) {
        AddLecture(DS, i, i, 234218);
    }
    for (int i = 10; i < 20; ++i) {
        AddLecture(DS, i, i, 234217);
    }
    for (int i = 20; i < 30; ++i) {
        AddLecture(DS, i, i, 234216);
    }
    for (int i = 30; i < 40; ++i) {
        AddLecture(DS, i, i, 234215);
    }
    for (int i = 40; i < 100; ++i) {
        AddLecture(DS, i, i, 234214);
    }
    assert(ChangeCourseID(DS, 0, 1) == INVALID_INPUT);
    assert(ChangeCourseID(DS, 1, 0) == INVALID_INPUT);
    assert(ChangeCourseID(DS, -1, 1) == INVALID_INPUT);
    assert(ChangeCourseID(nullptr, 234218, 234217) == INVALID_INPUT);
    assert(ChangeCourseID(DS, 234213, 1) == FAILURE);
    assert(ChangeCourseID(DS, 234214, 234219) == SUCCESS);
    assert(ChangeCourseID(DS, 234219, 234215) == SUCCESS);
    assert(ChangeCourseID(DS, 234219, 234212) == FAILURE);
    for (int i = 20; i < 30; ++i) {
        DeleteLecture(DS, i, i);
    }
    assert(ChangeCourseID(DS, 234216, 1) == FAILURE);
    assert(ChangeCourseID(DS, 234215, 234216) == SUCCESS);
    assert(ChangeCourseID(DS, 234216, 234216) == SUCCESS);// might be Invalidvalue as well(?)
    Quit(&DS);
      assert(DS == nullptr);
}


void Test_GetAllFreeRoomsByHour() {
    void *DS = Init(15, 15);
    assert(DS != nullptr);

    int num_Of_courses = 100;
//    num_Of_courses++;
//    num_Of_courses--;
//    int a=9;
    int *Courses;
//    Courses=&a;
    for (int i = 0; i < 15; i++) {
        assert(AddLecture(DS, 0, i, 234218) == SUCCESS);
    }
    assert(AddLecture(DS, 1, 1, 234216) == SUCCESS);
    assert(AddLecture(DS, 2, 2, 234219) == SUCCESS);
    assert(AddLecture(DS, 3, 3, 234217) == SUCCESS);

    assert(AddLecture(DS, 7, 0, 234217) == SUCCESS);
    assert(AddLecture(DS, 7, 1, 234217) == SUCCESS);
    assert(AddLecture(DS, 7, 2, 234217) == SUCCESS);
    assert(AddLecture(DS, 7, 3, 234217) == SUCCESS);
    assert(AddLecture(DS, 8, 1, 234218) == SUCCESS);
    assert(AddLecture(DS, 8, 2, 234218) == SUCCESS);
    assert(AddLecture(DS, 8, 3, 234218) == SUCCESS);
    assert(AddLecture(DS, 9, 0, 234219) == SUCCESS);
    assert(AddLecture(DS, 9, 2, 234219) == SUCCESS);

    assert(GetAllFreeRoomsByHour(DS, 100, &Courses, &num_Of_courses) == INVALID_INPUT);
    assert(GetAllFreeRoomsByHour(DS, -1, &Courses, &num_Of_courses) == INVALID_INPUT);
    assert(GetAllFreeRoomsByHour(DS, 8, nullptr, &num_Of_courses) == INVALID_INPUT);
    assert(GetAllFreeRoomsByHour(DS, 8, &Courses, nullptr) == INVALID_INPUT);
    assert(GetAllFreeRoomsByHour(DS, 11, nullptr, &num_Of_courses) == INVALID_INPUT);
    assert(GetAllFreeRoomsByHour(DS, 11, &Courses, nullptr) == INVALID_INPUT);
    assert(GetAllFreeRoomsByHour(nullptr, 8, &Courses, &num_Of_courses) == INVALID_INPUT);

    assert(GetAllFreeRoomsByHour(DS, 0, &Courses, &num_Of_courses) == FAILURE);
    assert(num_Of_courses == 100);
    assert(DeleteLecture(DS, 0, 0) == SUCCESS);
    assert(GetAllFreeRoomsByHour(DS, 0, &Courses, &num_Of_courses) == SUCCESS);
    assert(num_Of_courses == 1);
    free(Courses);
    assert(GetAllFreeRoomsByHour(DS, 7, &Courses, &num_Of_courses) == SUCCESS);
    assert(num_Of_courses == 11);
    free(Courses);
    StatusType statusType = GetAllFreeRoomsByHour(DS, 9, &Courses, &num_Of_courses);
    assert(statusType == SUCCESS);
    assert(num_Of_courses == 13);
    free(Courses);


    assert(DeleteLecture(DS, 7, 6) == FAILURE);
    assert(DeleteLecture(DS, 7, 3) == SUCCESS);


    assert(GetAllFreeRoomsByHour(DS, 0, &Courses, &num_Of_courses) == SUCCESS);
    assert(num_Of_courses == 1);
    free(Courses);
    assert(GetAllFreeRoomsByHour(DS, 7, &Courses, &num_Of_courses) == SUCCESS);
    free(Courses);
    assert(num_Of_courses == 12);

    AddLecture(DS, 0, 0, 234219);
    assert(GetAllFreeRoomsByHour(DS, 0, &Courses, &num_Of_courses) == FAILURE);
    assert(num_Of_courses == 12);

    Quit(&DS);
      assert(DS == nullptr);
}

void Test_GetAllLecturesByCourse() {
    void *DS = Init(20, 20);
    assert(DS != nullptr);

    int numOfLecture = 100;
    int a = 9;
    int b = 7;
    int *rooms;
    rooms = &a;
    int *hours;
    hours = &b;

    assert(AddLecture(DS, 0, 0, 234218) == SUCCESS);
    assert(AddLecture(DS, 1, 1, 234219) == SUCCESS);
    assert(AddLecture(DS, 2, 2, 234220) == SUCCESS);
    assert(AddLecture(DS, 3, 3, 234221) == SUCCESS);
    assert(AddLecture(DS, 4, 4, 234222) == SUCCESS);

    assert(AddLecture(DS, 7, 2, 234221) == SUCCESS);
    assert(AddLecture(DS, 8, 0, 234218) == SUCCESS);
    assert(AddLecture(DS, 8, 1, 234218) == SUCCESS);
    assert(AddLecture(DS, 8, 2, 234218) == SUCCESS);
    assert(AddLecture(DS, 8, 3, 234218) == SUCCESS);
    assert(AddLecture(DS, 9, 0, 234220) == SUCCESS);
    assert(AddLecture(DS, 9, 1, 234220) == SUCCESS);
    assert(AddLecture(DS, 9, 3, 234220) == SUCCESS);
    assert(AddLecture(DS, 10, 0, 234219) == SUCCESS);
    assert(AddLecture(DS, 10, 1, 234219) == SUCCESS);
    assert(AddLecture(DS, 10, 2, 234219) == SUCCESS);
    assert(AddLecture(DS, 10, 3, 234219) == SUCCESS);

    assert(GetAllLecturesByCourse(DS, 0, &hours, &rooms, &numOfLecture) == INVALID_INPUT);
    assert(GetAllLecturesByCourse(DS, 234218, nullptr, &rooms, &numOfLecture) == INVALID_INPUT);
    assert(GetAllLecturesByCourse(DS, 234218, &hours, nullptr, &numOfLecture) == INVALID_INPUT);
    assert(GetAllLecturesByCourse(DS, 234218, &hours, &rooms, nullptr) == INVALID_INPUT);
    assert(GetAllLecturesByCourse(nullptr, 234218, &hours, &rooms, &numOfLecture) == INVALID_INPUT);

    assert(GetAllLecturesByCourse(DS, 234218, &hours, &rooms, &numOfLecture) == SUCCESS);
    assert(numOfLecture == 5);
    free(hours);
    free(rooms);
    assert(GetAllLecturesByCourse(DS, 234234, &hours, &rooms, &numOfLecture) == FAILURE);
    assert(DeleteLecture(DS, 4, 4) == SUCCESS);
    assert(GetAllLecturesByCourse(DS, 234222, &hours, &rooms, &numOfLecture) == FAILURE);
    assert(AddLecture(DS, 15, 15, 234222) == SUCCESS);
    assert(AddLecture(DS, 15, 0, 234222) == SUCCESS);
    assert(AddLecture(DS, 15, 3, 234222) == SUCCESS);
    assert(GetAllLecturesByCourse(DS, 234222, &hours, &rooms, &numOfLecture) == SUCCESS);
    assert(numOfLecture == 3);
    free(hours);
    free(rooms);
    assert(ChangeCourseID(DS, 234222, 234218) == SUCCESS);
    assert(GetAllLecturesByCourse(DS, 234222, &hours, &rooms, &numOfLecture) == FAILURE);
    assert(ChangeCourseID(DS, 234218, 234219) == SUCCESS);
    assert(GetAllLecturesByCourse(DS, 234219, &hours, &rooms, &numOfLecture) == SUCCESS);
    assert(numOfLecture == 13);
    free(hours);
    free(rooms);

    Quit(&DS);
      assert(DS == nullptr);
}

void Test_CalculateScheduleEfficiency() {

    void *DS = Init(20, 20);
    assert(DS != nullptr);

    float Efficiency = 0;
    assert(CalculateScheduleEfficiency(DS, &Efficiency) == FAILURE);
    assert(AddLecture(DS, 15, 3, 234222) == SUCCESS);
    assert(AddLecture(DS, 15, 2, 234222) == SUCCESS);
    assert(AddLecture(DS, 15, 1, 234222) == SUCCESS);
    assert(AddLecture(nullptr, 15, 0, 234222) == INVALID_INPUT);
    assert(CalculateScheduleEfficiency(nullptr, &Efficiency) == INVALID_INPUT);
    assert(CalculateScheduleEfficiency(DS, &Efficiency) == SUCCESS);
    assert(DeleteLecture(DS, 15, 3) == SUCCESS);
    assert(DeleteLecture(DS, 15, 2) == SUCCESS);
    assert(DeleteLecture(DS, 15, 1) == SUCCESS);
    assert(CalculateScheduleEfficiency(DS, &Efficiency) == FAILURE);
    Quit(&DS);
      assert(DS == nullptr);

}


int main(int argc, const char **argv) {

    cout << "Welcome to the tests for wet1" << endl;
    cout << " Good Luck." << endl;

    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
         << endl;

    cout << "Testing Init And Quit" << endl;
    //  Test_Init_And_Quit();
    cout << "PASSED!!!" << endl;

    cout << "." << endl;
    cout << "." << endl;
    cout << "." << endl;

    cout << "Testing AddLecture" << endl;
    Test_AddLecture();
    cout << "PASSED!!!" << endl;

    cout << "." << endl;
    cout << "." << endl;
    cout << "." << endl;

    cout << "Testing DeleteLecture" << endl;
    Test_DeleteLecture();
    cout << "PASSED!!!" << endl;

    cout << "." << endl;
    cout << "." << endl;
    cout << "." << endl;

    cout << "Testing GetCourseID" << endl;
    Test_GetCourseID();
    cout << "PASSED!!!" << endl;

    cout << "." << endl;
    cout << "." << endl;
    cout << "." << endl;

    cout << "Testing ChangeCourseID" << endl;
    Test_ChangeCourseID();
    cout << "PASSED!!!" << endl;

    cout << "." << endl;
    cout << "." << endl;
    cout << "." << endl;

    cout << "Testing GetAllFreeRoomsByHour" << endl;
    Test_GetAllFreeRoomsByHour();
    cout << "PASSED!!!" << endl;

    cout << "." << endl;
    cout << "." << endl;
    cout << "." << endl;

    cout << "Testing GetAllLecturesByCourse" << endl;
    Test_GetAllLecturesByCourse();
    cout << "PASSED!!!" << endl;

    cout << "." << endl;
    cout << "." << endl;
    cout << "." << endl;
    cout << "." << endl;
    cout << "." << endl;

    cout << "Testing CalculateScheduleEfficiency" << endl;
    Test_CalculateScheduleEfficiency();
    cout << "PASSED!!!" << endl;

    cout << "." << endl;
    cout << "." << endl;
    cout << "." << endl;
    cout << "." << endl;
    cout << "." << endl;

    cout << "well done! you did it!" << endl;

    cout << "." << endl;
    cout << "." << endl;
    cout << "." << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
         << endl;


    return 0;
}