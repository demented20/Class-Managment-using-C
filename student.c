#include <stdio.h>
#include "student.h"

float calculate_average(float mark_arr[5]){
    float sum=0;
    for (int i =0;i<5;i++){
        sum+=mark_arr[i];
    }
    return sum/5;
}
void display_student_info(Students * student){
    printf("\nstudent Name : %s",student->name);
    printf("\nstudent ID : %ld",student->stud_id);
    printf("\nstudent Average Grade : %f",calculate_average(student->grades_array));
}
void display_all_student_info(Students * student){
    printf("\nstudent Name : %s",student->name);
    printf("\nstudent ID : %ld",student->stud_id);
    printf("\nstudent Average Grade : %f",calculate_average(student->grades_array));
    printf("\nstudent Grades : %.2f , %.2f , %.2f , %.2f , %.2f",student->grades_array[0],student->grades_array[1],student->grades_array[2],student->grades_array[3],student->grades_array[4]);
    printf("\nstudent Letter Grade : %c",student->letter_based_grade);
}
char make_letter_grade_class (int mark){
    if (mark>= 90) {
        return 'A';
    } else if (mark >= 80) {
        return 'B';
    } else if (mark >= 70) {
        return 'C';
    } else if (mark >= 60) {
        return 'D';
    } else {
        return 'F';
    }
}

