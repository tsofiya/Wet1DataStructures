/***************************************************************************/
/*                                                                         */
/* 234218 Data DSs 1, Winter 2018-2019                                     */
/* Homework : Wet 1                                                        */
/*                                                                         */
/***************************************************************************/

/***************************************************************************/
/*                                                                         */
/* File Name : main2.cpp                                                   */
/*                                                                         */
/* Holds the "int main()" function and the parser of the shell's           */
/* command line.                                                           */
/***************************************************************************/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "library.h"

#ifdef __cplusplus
extern "C" {
#endif

/* The command's strings */
typedef enum {
    NONE_CMD = -2,
    COMMENT_CMD = -1,
    INIT_CMD = 0,
    ADDLECTURE_CMD = 1,
    GETCOURSEID_CMD = 2,
    DELETELECTURE_CMD = 3,
    CHANGECOURSEID_CMD = 4,
    CALCULATESCHEDULEEFFICIENCY_CMD = 5,
    GETALLFREEROOMSBYHOUR_CMD = 6,
    GETALLLECTURESBYCOURSE_CMD = 7,
    QUIT_CMD = 8
} commandType;

static const int numActions = 9;
static const char *commandStr[] = {
        "Init",
        "AddLecture",
        "GetCourseID",
        "DeleteLecture",
        "ChangeCourseID",
        "CalculateScheduleEfficiency",
        "GetAllFreeRoomsByHour",
        "GetAllLecturesByCourse",
        "Quit" };

static const char* ReturnValToStr(int val) {
    switch (val) {
        case SUCCESS:
            return "SUCCESS";
        case ALLOCATION_ERROR:
            return "ALLOCATION_ERROR";
        case FAILURE:
            return "FAILURE";
        case INVALID_INPUT:
            return "INVALID_INPUT";
        default:
            return "";
    }
}

/* we assume maximum string size is not longer than 256  */
#define MAX_STRING_INPUT_SIZE (255)
#define MAX_BUFFER_SIZE       (255)

#define StrCmp(Src1,Src2) ( strncmp((Src1),(Src2),strlen(Src1)) == 0 )

typedef enum {
    error_free, error
} errorType;
static errorType parser(const char* const command);

#define ValidateRead(read_parameters,required_parameters,ErrorString,ErrorParams) \
if ( (read_parameters)!=(required_parameters) ) { printf(ErrorString, ErrorParams); return error; }

static bool isInit = false;

/***************************************************************************/
/* main                                                                    */
/***************************************************************************/

int main(int argc, const char**argv) {

    char buffer[MAX_STRING_INPUT_SIZE];

    // Reading commands
    while (fgets(buffer, MAX_STRING_INPUT_SIZE, stdin) != NULL) {
        fflush(stdout);
        if (parser(buffer) == error)
            break;
    };
    return 0;
}

/***************************************************************************/
/* Command Checker                                                         */
/***************************************************************************/

static commandType CheckCommand(const char* const command,
                                const char** const command_arg) {
    if (command == NULL || strlen(command) == 0 || StrCmp("\n", command))
        return (NONE_CMD);
    if (StrCmp("#", command)) {
        if (strlen(command) > 1)
            printf("%s", command);
        return (COMMENT_CMD);
    };
    for (int index = 0; index < numActions; index++) {
        if (StrCmp(commandStr[index], command)) {
            *command_arg = command + strlen(commandStr[index]) + 1;
            return ((commandType)index);
        };
    };
    return (NONE_CMD);
}

/***************************************************************************/
/* Commands Functions                                                      */
/***************************************************************************/

static errorType OnInit(void** DS, const char* const command);
static errorType OnAddLecture(void* DS, const char* const command);
static errorType OnGetCourseID(void* DS, const char* const command);
static errorType OnDeleteLecture(void* DS, const char* const command);
static errorType OnChangeCourseID(void* DS, const char* const command);
static errorType OnCalculateScheduleEfficiency(void* DS, const char* const command);
static errorType OnGetAllFreeRoomsByHour(void* DS, const char* const command);
static errorType OnGetAllLecturesByCourse(void* DS, const char* const command);
static errorType OnQuit(void** DS, const char* const command);

/***************************************************************************/
/* Parser                                                                  */
/***************************************************************************/

static errorType parser(const char* const command) {
    static void *DS = NULL; /* The general data structure */
    const char* command_args = NULL;
    errorType rtn_val = error;

    commandType command_val = CheckCommand(command, &command_args);

    switch (command_val) {

        case (INIT_CMD):
            rtn_val = OnInit(&DS, command_args);
            break;
        case (ADDLECTURE_CMD):
            rtn_val = OnAddLecture(DS, command_args);
            break;
        case (GETCOURSEID_CMD):
            rtn_val = OnGetCourseID(DS, command_args);
            break;
        case (DELETELECTURE_CMD):
            rtn_val = OnDeleteLecture(DS, command_args);
            break;
        case (CHANGECOURSEID_CMD):
            rtn_val = OnChangeCourseID(DS, command_args);
            break;
        case (CALCULATESCHEDULEEFFICIENCY_CMD):
            rtn_val = OnCalculateScheduleEfficiency(DS, command_args);
            break;
        case (GETALLFREEROOMSBYHOUR_CMD):
            rtn_val = OnGetAllFreeRoomsByHour(DS, command_args);
            break;
        case (GETALLLECTURESBYCOURSE_CMD):
            rtn_val = OnGetAllLecturesByCourse(DS, command_args);
            break;
        case (QUIT_CMD):
            rtn_val = OnQuit(&DS, command_args);
            break;

        case (COMMENT_CMD):
            rtn_val = error_free;
            break;
        case (NONE_CMD):
            rtn_val = error;
            break;
        default:
            assert(false);
            break;
    };
    return (rtn_val);
}

static errorType OnInit(void** DS, const char* const command) {
    if (isInit) {
        printf("init was already called.\n");
        return (error_free);
    };
    isInit = true;

    int hours, rooms;
    ValidateRead(sscanf(command, "%d %d", &hours, &rooms), 2, "%s failed.\n", commandStr[INIT_CMD]);
    *DS = Init(hours, rooms);

    if (*DS == NULL) {
        printf("init failed.\n");
        return error;
    };

    printf("init done.\n");
    return error_free;
}

static errorType OnAddLecture(void* DS, const char* const command) {
    int hour, roomID, courseID;
    ValidateRead(sscanf(command, "%d %d %d", &hour, &roomID, &courseID), 3, "%s failed.\n", commandStr[ADDLECTURE_CMD]);
    StatusType res = AddLecture(DS, hour, roomID, courseID);

    if (res != SUCCESS) {
        printf("%s: %s\n", commandStr[ADDLECTURE_CMD], ReturnValToStr(res));
        return error_free;
    }

    printf("%s: %s\n", commandStr[ADDLECTURE_CMD], ReturnValToStr(res));
    return error_free;
}

static errorType OnGetCourseID(void* DS, const char* const command) {
    int hour, roomID, courseID;
    ValidateRead(sscanf(command, "%d %d", &hour, &roomID), 2, "%s failed.\n", commandStr[GETCOURSEID_CMD]);
    StatusType res = GetCourseID(DS, hour, roomID, &courseID);

    if (res != SUCCESS) {
        printf("%s: %s\n", commandStr[GETCOURSEID_CMD], ReturnValToStr(res));
        return error_free;
    }

    printf("%s: %d\n", commandStr[GETCOURSEID_CMD], courseID);
    return error_free;
}

static errorType OnDeleteLecture(void* DS, const char* const command) {
    int hour, roomID;
    ValidateRead(sscanf(command, "%d %d", &hour, &roomID), 2, "%s failed.\n", commandStr[DELETELECTURE_CMD]);
    StatusType res = DeleteLecture(DS, hour, roomID);

    if (res != SUCCESS) {
        printf("%s: %s\n", commandStr[DELETELECTURE_CMD], ReturnValToStr(res));
        return error_free;
    }

    printf("%s: %s\n", commandStr[DELETELECTURE_CMD], ReturnValToStr(res));
    return error_free;
}

static errorType OnChangeCourseID(void* DS, const char* const command) {
    int oldCourseID, newCourseID;
    ValidateRead(sscanf(command, "%d %d", &oldCourseID, &newCourseID), 2, "%s failed.\n", commandStr[CHANGECOURSEID_CMD]);
    StatusType res = ChangeCourseID(DS, oldCourseID, newCourseID);

    if (res != SUCCESS) {
        printf("%s: %s\n", commandStr[CHANGECOURSEID_CMD], ReturnValToStr(res));
        return error_free;
    }

    printf("%s: %s\n", commandStr[CHANGECOURSEID_CMD], ReturnValToStr(res));
    return error_free;
}

static errorType OnCalculateScheduleEfficiency(void* DS, const char* const command) {
    float efficiency;
#pragma GCC diagnostic ignored "-Wformat-zero-length"
    ValidateRead(sscanf(command, ""), 0, "%s failed.\n", commandStr[CALCULATESCHEDULEEFFICIENCY_CMD]);
#pragma GCC diagnostic ignored "-Wformat-zero-length"
    StatusType res = CalculateScheduleEfficiency(DS, &efficiency);

    if (res != SUCCESS) {
        printf("%s: %s\n", commandStr[CALCULATESCHEDULEEFFICIENCY_CMD], ReturnValToStr(res));
        return error_free;
    }

    printf("%s: %.2f\n", commandStr[CALCULATESCHEDULEEFFICIENCY_CMD], efficiency);
    return error_free;
}

int CompareInt(const void* a, const void* b)
{
    if (*(int*)a == *(int*)b) return 0;
    return *(int*)a < *(int*)b ? -1 : 1;
}

static errorType OnGetAllFreeRoomsByHour(void* DS, const char* const command) {
    int hour, numOfRooms;
    int *rooms;
    ValidateRead(sscanf(command, "%d", &hour), 1, "%s failed.\n", commandStr[GETALLFREEROOMSBYHOUR_CMD]);
    StatusType res = GetAllFreeRoomsByHour(DS, hour, &rooms, &numOfRooms);

    if (res != SUCCESS) {
        printf("%s: %s\n", commandStr[GETALLFREEROOMSBYHOUR_CMD], ReturnValToStr(res));
        return error_free;
    }

    printf("%s: %s\n", commandStr[GETALLFREEROOMSBYHOUR_CMD], ReturnValToStr(res));

    if (numOfRooms > 0) {
        //Sort the values
        qsort(rooms, numOfRooms, sizeof(int), CompareInt);
    }

    for (int i = 0; i < numOfRooms; i++)
    {
        printf("%d\n", rooms[i]);
    }

    printf("--End of room list--\n");

    free(rooms);
    return error_free;
}

static errorType OnGetAllLecturesByCourse(void* DS, const char* const command) {
    int courseID, numOfLecturess;
    int *hours, *rooms;
    ValidateRead(sscanf(command, "%d", &courseID), 1, "%s failed.\n", commandStr[GETALLLECTURESBYCOURSE_CMD]);
    StatusType res = GetAllLecturesByCourse(DS, courseID, &hours, &rooms, &numOfLecturess);

    if (res != SUCCESS) {
        printf("%s: %s\n", commandStr[GETALLLECTURESBYCOURSE_CMD], ReturnValToStr(res));
        return error_free;
    }

    printf("%s: %s\n", commandStr[GETALLLECTURESBYCOURSE_CMD], ReturnValToStr(res));
    if (numOfLecturess > 0) {
        printf("Hour\t||\tRoom\n");
    }

    for (int i = 0; i < numOfLecturess; i++)
    {
        printf("%d\t||\t%d\n", hours[i], rooms[i]);
    }

    printf("--End of lecture list--\n");

    free(hours);
    free(rooms);

    return error_free;
}

static errorType OnQuit(void** DS, const char* const command) {
    Quit(DS);
    if (*DS != NULL) {
        printf("quit failed.\n");
        return error;
    };

    isInit = false;
    printf("quit done.\n");
    return error_free;
}

#ifdef __cplusplus
}
#endif