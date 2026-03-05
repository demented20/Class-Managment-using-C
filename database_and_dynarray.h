#ifndef DATABASE_AND_DYNARRAY__H
#define DATABASE_AND_DYNARRAY__H
#include "student.h"
#include <stdlib.h>
typedef struct 
{
    Students *items;
    size_t capacity ;
    int count ;
}Header;

Header * make_array(int init_capacity);
Students* _array_push(Students *pointer_to_first_student , Students student_tobe_pushed);
int get_length(Header * meta_data);
int get_capacity(Header *meta_data);
Header* array_delete_element(Header* meta_data,long int student_id); 
void free_the_array(Header* meta_data);

#endif