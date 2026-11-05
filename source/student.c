#include <stdio.h>
#include "student.h"

// Calculate average of 5 grades
float calculate_average(float mark_arr[5]){
    float sum = 0;
    for (int i = 0; i < 5; i++){
        sum += mark_arr[i];
    }
    return sum / 5;
}

// Display basic student info (name, ID, average)
void display_student_info(Students * student){
    printf("\n  Name     : %s", student->name);
    printf("\n  ID       : %ld", student->stud_id);
    printf("\n  Average  : %.2f", calculate_average(student->grades_array));
}

// Display complete student info including all grades and letter grade
void display_all_student_info(Students * student){
    printf("\n  Name        : %s", student->name);
    printf("\n  ID          : %ld", student->stud_id);
    printf("\n  Average     : %.2f", calculate_average(student->grades_array));
    printf("\n  Grades      : %.2f, %.2f, %.2f, %.2f, %.2f", student->grades_array[0], student->grades_array[1], student->grades_array[2], student->grades_array[3], student->grades_array[4]);
    printf("\n  Letter Grade: %c", student->letter_based_grade);
}
// Convert numeric average to letter grade (A=90+, B=80+, C=70+, D=60+, F=below 60)
char make_letter_grade_class (int mark){
    if (mark >= 90) {
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

