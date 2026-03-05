#include <stdio.h>
#include "other_features.h"

void display_class_averages(Header *meta_data) {
    if (meta_data == NULL || meta_data->count == 0) {
        printf("\nNo students in the class.\n");
        return;
    }
    Students *arr = (Students *)(meta_data + 1);
    float subject_totals[5] = {0};

    for (int i = 0; i < meta_data->count; i++)
        for (int j = 0; j < 5; j++)
            subject_totals[j] += arr[i].grades_array[j];

    printf("\n─────────────────────────────────\n");
    printf("  CLASS AVERAGES PER SUBJECT\n");
    printf("─────────────────────────────────\n");
    for (int j = 0; j < 5; j++)
        printf("  Subject %d : %.2f\n", j + 1, subject_totals[j] / meta_data->count);
    printf("─────────────────────────────────\n");
}

void display_class_stats(Header *meta_data) {
    if (meta_data == NULL || meta_data->count == 0) {
        printf("\nNo students in the class.\n");
        return;
    }
    Students *arr = (Students *)(meta_data + 1);
    float total = 0, highest = -1, lowest = 101;
    int top_i = 0, bot_i = 0;

    for (int i = 0; i < meta_data->count; i++) {
        float avg = calculate_average(arr[i].grades_array);
        total += avg;
        if (avg > highest) { highest = avg; top_i = i; }
        if (avg < lowest)  { lowest  = avg; bot_i = i; }
    }

    printf("\n─────────────────────────────────\n");
    printf("  CLASS STATS\n");
    printf("─────────────────────────────────\n");
    printf("  Students     : %d\n", meta_data->count);
    printf("  Class avg    : %.2f\n", total / meta_data->count);
    printf("  Highest avg  : %.2f  (%s)\n", highest, arr[top_i].name);
    printf("  Lowest avg   : %.2f  (%s)\n", lowest,  arr[bot_i].name);
    printf("─────────────────────────────────\n");
}

void display_ranking(Header *meta_data) {
    if (meta_data == NULL || meta_data->count == 0) {
        printf("\nNo students in the class.\n");
        return;
    }
    Students *arr = (Students *)(meta_data + 1);
    int count = meta_data->count;

    // build index array and sort by average (bubble sort — simple, fine for class sizes)
    // this part of the code is responsible of performing a bubble sort and storing the result in an array
    int indices[count];
    for (int i = 0; i < count; i++) indices[i] = i;

    for (int i = 0; i < count - 1; i++)
        for (int j = 0; j < count - i - 1; j++)
            if (calculate_average(arr[indices[j]].grades_array) <
                calculate_average(arr[indices[j + 1]].grades_array)) {
                int tmp = indices[j];
                indices[j] = indices[j + 1];
                indices[j + 1] = tmp;
            }

    printf("\n─────────────────────────────────────────────────\n");
    printf("  RANKING\n");
    printf("─────────────────────────────────────────────────\n");
    printf("  %-5s %-20s %-10s %-6s\n", "Rank", "Name", "Average", "Grade");
    printf("  ─────────────────────────────────────────────\n");
    //this will iterate and show the ranking based on the array of ranking 
    for (int i = 0; i < count; i++) {
        Students *student = &arr[indices[i]];
        printf("  %-5d %-20s %-10.2f %-6c\n",
            i + 1, student->name,
            calculate_average(student->grades_array),
            student->letter_based_grade);
    }
    printf("─────────────────────────────────────────────────\n");
}
