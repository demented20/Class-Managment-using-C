#include <stdio.h>
#include "database_and_dynarray.h"

// Configuration macros
#define MIN_CAPACITY 32
#define FREE_UNNECESSARY_CAPACITY  // Enable memory shrinking when many elements are deleted

// Create and initialize a dynamic array with initial capacity
Header *make_array(int init_capacity){
    if (init_capacity <= 0)
        init_capacity = MIN_CAPACITY;

    Header *header = malloc(sizeof(Header) + sizeof(Students) * init_capacity);
    if (header == NULL) return NULL;
    
    // Initialize metadata
    header->capacity = init_capacity;
    header->count = 0;
    header->items = (Students*)(header + 1);

    return header;
}

    Students* _array_push(Students* pointer_to_first_student , Students student_tobe_pushed){
        if (pointer_to_first_student == NULL) return NULL;
        
        Header * header = ((Header*)pointer_to_first_student)-1;
        // Allocate more memory if the allocated memory is full
        if (header->count >= (int)header->capacity){
            int new_capacity = (int)(header->capacity * 1.5);
            Header *new_header = realloc(header, sizeof(Header) + sizeof(Students) * new_capacity);
            // Return NULL so caller can detect allocation failure safely.
            if (new_header == NULL) return NULL;
            // Update metadata after realloc
            new_header->capacity = new_capacity;
            new_header->items = (Students*)(new_header + 1);
            header = new_header;
        }
        // Push the student at the end of the array
        ((Students *)(header + 1))[header->count++] = student_tobe_pushed;
        return (Students *)(header + 1);  
    }

    int get_length(Header* meta_data){
        if (meta_data == NULL) return -1;  // Return -1 on NULL pointer
        return meta_data->count;
    }

    int get_capacity(Header * meta_data){
        if (meta_data == NULL) return -1;  // Return -1 on NULL pointer
        return meta_data->capacity;
    }

    Header* array_delete_element(Header* meta_data, long int student_id){
        if (meta_data == NULL) return NULL;  // Handle NULL pointer
        if (meta_data->count == 0) return meta_data;  // Handle empty array

        int index = -1;  // -1 indicates student not found
        for (int i = 0; i < meta_data->count; i++){
            if (((Students *)(meta_data + 1))[i].stud_id == student_id){
                index = i;  // Record index of element to delete
                break;
            }
        } 
        if (index == -1) return meta_data;  // Student ID not found
        
        // Swap with last element
        if (index != meta_data->count - 1) {
            ((Students *)(meta_data + 1))[index] = ((Students *)(meta_data + 1))[meta_data->count - 1];
        }
        // Update metadata
        meta_data->count--;

        // Optional: Shrink array if memory usage is too high
        // This reduces memory waste when many elements are deleted
        #ifdef FREE_UNNECESSARY_CAPACITY

        if (meta_data->count < (int)(meta_data->capacity / 2) && (meta_data->capacity > MIN_CAPACITY)){
            int new_capacity = meta_data->capacity / 2;
            if (new_capacity < MIN_CAPACITY) new_capacity = MIN_CAPACITY;
            
            // Reallocate memory to smaller size
            Header *new_array = realloc(meta_data, sizeof(Header) + sizeof(Students) * new_capacity);
            if (new_array == NULL) return meta_data;  // Realloc failed, return original metadata
            
            // Update metadata
            new_array->capacity = new_capacity;
            new_array->items = (Students*)(new_array + 1);
            return new_array;
        }
        #endif

        return meta_data;
        
    }

    void free_the_array(Header *meta_data){
        if (meta_data == NULL) return;  // Handle NULL pointer
        free(meta_data);
    }
  
