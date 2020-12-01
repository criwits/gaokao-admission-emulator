#include "admission_elements.h"


// #define MAX_BUF_LENGTH 256

int import_student_info(FILE *stu_file, int *stu_number, STU *stu_datalist)
{
    int sch_number, wish_number, read = 0;
    fscanf(stu_file, "%d\n", stu_number);

    for (int i = 0; i < *stu_number; ++i)
    {
        fscanf(stu_file, "%d,%d,%d,", &stu_datalist[i].stu_id, &stu_datalist[i].stu_score, &sch_number);
        for (int j = 0; j < sch_number; j++)
        {
            stu_datalist[i].stu_wishes[j].wish_enabled = 1;

            fscanf(stu_file, "%d,%d,%d,", &stu_datalist[i].stu_wishes[j].wish_sch_id, &stu_datalist[i].stu_wishes[j].wish_exchange, &wish_number);
            for (int k = 0; k < wish_number; k++)
            {
                fscanf(stu_file, "%d,", &stu_datalist[i].stu_wishes[j].wish_sub[k]);
            }
        }
        fscanf(stu_file, "%s\n", stu_datalist[i].stu_name);
        read++;
    }
    return read;
}

int import_school_info(FILE *sch_file, int *sch_number, SCH *sch_datalist)
{
    int read = 0;
    fscanf(sch_file, "%d\n", sch_number);

    memset(sch_datalist, 0, sizeof(SCH) * MAX_SCH_NUMBER);
    for (int i = 0; i < *sch_number; ++i)
    {
        fscanf(sch_file, "%d,%d,", &sch_datalist[i].sch_id, &sch_datalist[i].sch_sub_number);
        for (int j = 0; j < sch_datalist[i].sch_sub_number; j++)
            fscanf(sch_file, "%d,%d,", &sch_datalist[i].sch_planned_number[j][0], &sch_datalist[i].sch_planned_number[j][1]);
        fscanf(sch_file, "%s\n", sch_datalist[i].sch_name);
        read++;
    }
    return read;
}

void merge_array(STU *student_list, int first, int mid, int last)
{
    STU temp[MAX_STU_NUMBER];
    int i = first, j = mid + 1;
    int m = mid, n = last;
    int k = 0;
    memset(temp, 0, sizeof(temp));
    while (i <= m && j <= n)
    {
        if (student_list[i].stu_score >= student_list[j].stu_score)
            temp[k++] = student_list[i++];
        else
        {
            temp[k++] = student_list[j++];
        }
    }
    while (i <= m)
        temp[k++] = student_list[i++];
    while (j <= n)
        temp[k++] = student_list[j++];
    for (i = 0; i < k; ++i)
        student_list[first + i] = temp[i];
    return;
}

void merge_sort(STU *student_list, int first, int last)
{
    if (first < last)
    {
        int mid = (first + last) / 2;
        merge_sort(student_list, first, mid);
        merge_sort(student_list, mid + 1,last);
        merge_array(student_list, first, mid, last);
    }
    return;
}

void admission(STU *student_list, SCH *school_list, int stu_number, int sch_number, FILE *output_file)
{
    for (int i = 0; i < stu_number; i++)
    {
        int is_school_existed;
        printf("Processing student %d (ID: %d, Name: %s)...\n", i + 1, student_list[i].stu_id, student_list[i].stu_name);
        int j = 0;
        while (student_list[i].stu_wishes[j].wish_enabled)
        {
            printf("Wish No.%d: Searching for school (ID: %d)...", j + 1, student_list[i].stu_wishes[j].wish_sch_id);
            for (int k = 0; k < sch_number; k++)
            {
                is_school_existed = 0;
                if (student_list[i].stu_wishes[j].wish_sch_id == school_list[k].sch_id)
                {
                    is_school_existed = 1;
                    printf("Success!\n");
                    printf("Checking if can be admitted...");
                    int plan_count = 0;
                    for (int l = 0; l < school_list[k].sch_sub_number; l++)
                        plan_count += school_list[k].sch_planned_number[l][1];
                    if (!plan_count)
                    {
                        printf("No. ");
                        printf("Trying next wish!\n");
                        j++;
                        break;
                    }
                }
            }
            if (!is_school_existed)
            {
                printf("Not exist!\n");
                printf("E: Cannot find the school with ID: %d given by student with ID: %d!\n",
                       student_list[i].stu_wishes[j].wish_sch_id, student_list[i].stu_id);
                return;
            }
            j++;
        }
    }
}