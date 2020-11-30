#include "admission_elements.h"
#define MAX_FILENAME 30
int main(void)
{
    STU all_student_list[MAX_STU_NUMBER];
    SCH all_school_list[MAX_SCH_NUMBER];
    int student_number;
    int school_number;
    FILE *student_file;
    FILE *school_file;
    char student_filename[MAX_FILENAME];
    char school_filename[MAX_FILENAME];

    memset(all_student_list, 0, sizeof(all_student_list));
    memset(all_school_list, 0, sizeof(all_school_list));

    printf("Enter the filename of students\' data list: "); scanf("%s", student_filename);
    printf("Enter the filename of schools\' data list: "); scanf("%s", school_filename);

    if ((student_file = fopen(student_filename, "r")) == NULL)
    {
        printf("[ERROR] Error(s) occurred while opening the students\' data file!\n");
        return 0;
    }

    if ((school_file = fopen(school_filename, "r")) == NULL)
    {
        printf("[ERROR] Error(s) occurred while opening the schools\' data file!\n");
        return 0;
    }

    // 测试代码：打印已经导入的学生的信息
    printf("Successfully imported data of %d student(s)!\n", import_student_info(student_file, &student_number, all_student_list));
    for (int i = 0; i < student_number; i++)
    {
        printf("ID: %d, Name: %s, Score: %d\n", all_student_list[i].stu_id,all_student_list[i].stu_name, all_student_list[i].stu_score);
        int j = 0;
        while (all_student_list[i].stu_wishes[j].wish_enabled)
        {
            printf("\tWish No.%d: School: %d, Major(s): ", j + 1, all_student_list[i].stu_wishes[j].wish_sch_id);
            int k = 0;
            while (all_student_list[i].stu_wishes[j].wish_sub[k])
                printf("%d ", all_student_list[i].stu_wishes[j].wish_sub[k++]);
            printf(", Exchange: %d\n", all_student_list[i].stu_wishes[j].wish_exchange);
            j++;
        }
    }

    //测试代码：打印已经导入的学校的信息
    printf("Successfully imported data of %d schools!\n", import_school_info(school_file, &school_number, all_school_list));
    for (int i = 0; i < school_number; i++)
    {
        printf("ID: %d, Name: %s\n", all_school_list[i].sch_id, all_school_list[i].sch_name);
        for (int j = 0; j < all_school_list[i].sch_sub_number; j++)
        {
            printf("\tSubject No.%d: ID: %d, Plan: %d\n", j + 1, all_school_list[i].sch_planned_number[j][0], all_school_list[i].sch_planned_number[j][1]);
        }
    }
    return 0;
}