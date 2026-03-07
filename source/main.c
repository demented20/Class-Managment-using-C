#include <stdio.h>
#include <string.h>
#include "student.h"
#include "database_and_dynarray.h"
#include "other_features.h"

//xxxxxxxxxxxxxxxxxxxx Global variables and macros xxxxxxxxxxxxxxxxxxxxxxxx
#define MIN_CAPACITY 32

//xxxxxxxxxxxxxxxxxxxx Functions xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

// Clear leftover input from stdin buffer
void clear_input() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void print_main_menu() {
    printf("\n═════════════════════════════════\n");
    printf("   CLASS MANAGEMENT SYSTEM\n");
    printf("═════════════════════════════════\n");
    printf("  1. Add student\n");
    printf("  2. Delete student\n");
    printf("  3. Display one student\n");
    printf("  4. Display all students\n");
    printf("  5. Class stats\n");
    printf("  6. Ranking\n");
    printf("  7. Averages per subject\n");
    printf("  0. Exit\n");
    printf("═════════════════════════════════\n");
    printf("  user_input : ");
}

// Initialize a new class with minimum capacity
Header * Make_a_class()
{
    Header *pointeur = make_array(MIN_CAPACITY);
    return pointeur;
}

// Collect and validate student information from user input
Students fill_student_info() {
    Students student;
    int input_result;
    
    // Validate student ID (must be positive)
    do {
        printf("\n  Enter student ID   : ");
        input_result = scanf("%ld", &student.stud_id);
        if (input_result != 1) {
            clear_input();
            printf("  ✗ Invalid input. Please enter a valid ID.\n");
            student.stud_id = 0;
        } else {
            clear_input();
            if (student.stud_id <= 0) {
                printf("  ✗ Student ID must be positive. Try again.\n");
            }
        }
    } while (student.stud_id <= 0);

    // Validate student name (must not be empty)
    do {
        printf("  Enter student name : ");
        fgets(student.name, sizeof(student.name), stdin);
        student.name[strcspn(student.name, "\n")] = '\0';  // Remove newline
        if (strlen(student.name) == 0) {
            printf("  ✗ Name cannot be empty. Try again.\n");
        }
    } while (strlen(student.name) == 0);

    // Validate grades (must be 0-100)
    printf("  Enter 5 grades (space separated) : ");
    for (int i = 0; i < 5; i++) {
        input_result = scanf("%f", &student.grades_array[i]);
        if (input_result != 1) {
            clear_input();
            printf("  ✗ Invalid grade input. Re-enter grade %d: ", i + 1);
            i--;  // Retry this grade
            continue;
        }
        if (student.grades_array[i] < 0 || student.grades_array[i] > 100) {
            printf("  ✗ Grade must be between 0-100. Re-enter grade %d: ", i + 1);
            i--;  // Retry this grade
        }
    }
    clear_input();

    float avg = calculate_average(student.grades_array);
    student.letter_based_grade = make_letter_grade_class((int)avg);
    student.adding_number = 0;

    return student;
}

// Prompt user to create a class
void first_prompt(){
    printf("\n  You first need to create a class.\n");
    printf("  Enter 1 to create a class: ");
}
//xxxxxxxxxxxxxxxxxxxx Main Function xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int main (){
    // Class creation loop - validate input
    int user_input = 0;
    int input_result;
    while(user_input != 1){
        first_prompt();
        input_result = scanf("%d", &user_input);
        if (input_result != 1) {
            clear_input();
            printf("  ✗ Invalid input. Please enter 1.\n");
            user_input = 0;
        }
    }
    
    // Create and initialize the class
    Header * Class = Make_a_class();
    if (Class == NULL) {
        printf("\n  ✗ Failed to create class. Exiting.\n");
        return 1;
    }
    printf("\n  ✓ Class created successfully!\n");

    // Main menu loop
    while (1) {
        print_main_menu();
        input_result = scanf("%d", &user_input);
        if (input_result != 1) {
            clear_input();
            printf("\n  ✗ Invalid input. Please try again.\n");
            continue;
        }
        clear_input();

        switch (user_input) {

            case 1: {
                Students student = fill_student_info();
                
                // Verify class is valid
                if (Class == NULL) {
                    printf("\n  ✗ Class is invalid. Exiting.\n");
                    return 1;
                }
                
                // Check for duplicate student ID
                Students *arr = (Students *)(Class + 1);
                int duplicate = 0;
                for (int i = 0; i < Class->count; i++) {
                    if (arr[i].stud_id == student.stud_id) {
                        duplicate = 1;
                        break;
                    }
                }
                
                if (duplicate) {
                    printf("\n  ✗ Student ID already exists. Cannot add duplicate.\n");
                } else {
                    Students *new_ptr = _array_push((Students *)(Class + 1), student);
                    // update class pointer in case realloc moved the block
                    Class = ((Header *)new_ptr) - 1;
                    printf("\n  ✓ Student added. (%d/%d)\n", Class->count, (int)Class->capacity);
                }
                break;
            }

            case 2: {
                long int id;
                printf("\n  Enter student ID to delete : ");
                input_result = scanf("%ld", &id);
                if (input_result != 1) {
                    clear_input();
                    printf("  ✗ Invalid ID format.\n");
                    break;
                }
                clear_input();
                int prev = Class->count;
                Class = array_delete_element(Class, id);
                if (Class->count < prev)
                    printf("\n  ✓ Student deleted.\n");
                else
                    printf("\n  Student ID not found.\n");
                break;
            }

            case 3: {
                long int id;
                printf("\n  Enter student ID : ");
                input_result = scanf("%ld", &id);
                if (input_result != 1) {
                    clear_input();
                    printf("  ✗ Invalid ID format.\n");
                    break;
                }
                clear_input();
                Students *arr = (Students *)(Class + 1);
                int found = 0;
                for (int i = 0; i < Class->count; i++) {
                    if (arr[i].stud_id == id) {
                        display_all_student_info(&arr[i]);
                        found = 1;
                        break;
                    }
                }
                if (!found) printf("\n  Student ID not found.\n");
                break;
            }

            case 4: {
                if (Class->count == 0) { printf("\n  No students in the class.\n"); break; }
                Students *arr = (Students *)(Class + 1);
                printf("\n─────────────────────────────────\n");
                for (int i = 0; i < Class->count; i++) {
                    printf("  [%d]", i + 1);
                    display_student_info(&arr[i]);
                    printf("\n");
                }
                printf("─────────────────────────────────\n");
                break;
            }

            case 5:
                display_class_stats(Class);
                break;

            case 6:
                display_ranking(Class);
                break;

            case 7:
                display_class_averages(Class);
                break;

            case 0:
                if (Class != NULL) free_the_array(Class);
                printf("\n  ✓ Goodbye!\n\n");
                return 0;

            default:
                printf("\n  Invalid user_input.\n");
        }
    }
    return 0;
}
