#ifndef STUDENT_H
#define STUDENT_H

/// xxxxxxxxxxxxxxxxxx Students struct xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
typedef struct  
{
    //data members:
    long int stud_id;
    float grades_array[5];
    char name[30];
    char letter_based_grade ;
    int adding_number ;

}Students;

/// xxxxxxxxxxxxxxxxxx Functions xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx


void display_student_info(Students * student);

void display_all_student_info(Students * student);

char make_letter_grade_class (int mark);

float calculate_average(float mark_arr[5]);

#endif