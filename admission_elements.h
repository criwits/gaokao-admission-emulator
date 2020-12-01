#ifndef GAOKAO_ADMISSION_EMULATOR_ADMISSION_ELEMENTS_H
#define GAOKAO_ADMISSION_EMULATOR_ADMISSION_ELEMENTS_H

#include <stdio.h>
#include <string.h>

#define MAX_STU_NUMBER 200
#define MAX_SCH_NUMBER 30
#define MAX_SUB_NUMBER 20
#define MAX_WISH_SCH_NUMBER 8
#define MAX_WISH_SUB_NUMBER 6

#define MAX_STU_NAME 25
#define MAX_SCH_NAME 25

typedef struct student_wishes
{
    int wish_enabled;
    int wish_exchange;
    int wish_sch_id;
    int wish_sub[MAX_WISH_SUB_NUMBER];
} WISH;

typedef struct student_elements
{
    int stu_id;
    char stu_name[MAX_STU_NAME];
    int stu_score;
    WISH stu_wishes[MAX_WISH_SCH_NUMBER];
} STU;

typedef struct school_elements
{
    int sch_id;
    char sch_name[MAX_SCH_NAME];
    int sch_sub_number;
    int sch_planned_number[MAX_SUB_NUMBER][2];

} SCH;

extern int import_student_info(FILE *, int *, STU *);
extern int import_school_info(FILE *, int *, SCH *);
extern void merge_array(STU *, int, int, int);
extern void merge_sort(STU *, int, int);


#endif