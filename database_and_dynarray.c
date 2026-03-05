#include <stdio.h>
#include "database_and_dynarray.h"

//macros
#define MIN_CAPACITY 32
#define FREE_UNNECESSARY_CAPACITY


//xxxxxxxxxxxxxxxxxxxxxxxxxxxxx function implementationsxxxxxxxxxxxxxxxxxxxxxxxx    

    Header *make_array(int init_capacity){

    if (init_capacity <= 0)
        init_capacity= MIN_CAPACITY;

    Header *header = malloc(sizeof(Header) + sizeof(Students) * init_capacity);
    if (header == NULL) return NULL;
        //initialize the meta data
        header->capacity = init_capacity;
        header->count= 0;
        header->items = (Students*)(header+ 1);

    return header;
    }

    Students* _array_push(Students* pointer_to_first_student , Students student_tobe_pushed){
        if (pointer_to_first_student == NULL) return NULL;
        
        Header * header = ((Header*)pointer_to_first_student)-1;
        //allocate more memory if the allocated memory is full
        if (header->count >= header->capacity){
            int new_capacity = header->capacity * 1.5;
            Header  *new_header = realloc(header, sizeof(Header) + sizeof(Students) * new_capacity);
            if (new_header == NULL) return pointer_to_first_student;     
            //we update the meta data         
            new_header->capacity = new_capacity;
            new_header->items= (Students*)(new_header+ 1);
            header = new_header;
        }
        //push the student at the end of the array
        ((Students *)(header+ 1))[header->count++] = student_tobe_pushed;
        return (Students *)(header + 1);  
    }

    int get_length(Header* meta_data){
        if (meta_data == NULL) return -1 ;//for failure 
        return meta_data->count;
    }

    int get_capacity(Header * meta_data){
        if (meta_data == NULL) return -1;//for failure 
        return meta_data->capacity;
        }

    Header* array_delete_element(Header* meta_data,long int student_id){
        if (meta_data==NULL) return NULL; //handles invalid pointer 
        if (meta_data->count == 0 ) return NULL;// handles empty arrays 

        int index = -1; //way of simulating the boolean and at the same time returning the index if student id is found found
        for (int i = 0; i < meta_data->count; i++){
        
            if (((Students *)(meta_data+ 1))[i].stud_id == student_id){
                index = i;//recording the index of the element we want to delete
                break;
            }
        } 
        if (index == -1) return meta_data;
                //swwapping with the last element
                if (index != meta_data->count - 1) ((Students *)(meta_data + 1))[index] = ((Students *)(meta_data + 1))[meta_data->count - 1];
                //upadate meta data 
                meta_data->count--;

                //this part of the code is added to shrink if the count of the elements is less than the half of the array capacity
                // this is a good way to keep your memory usage minimal and ur code optimized 
                //it can be omited by undefining or commenting it
                #ifdef FREE_UNNECESSARY_CAPACITY

                if (meta_data->count < (meta_data->capacity / 2) &&( meta_data->capacity > MIN_CAPACITY)){

                    int new_capacity =meta_data->capacity / 2;
                    if (new_capacity< MIN_CAPACITY) new_capacity = MIN_CAPACITY;
                    //this allows us to handle the array with few elements ,
                    //because we increase the capacity be x1.5 (and this might cause problems when it comes to 0 and 1 elements and we want to push)
                    //this way we dont allow the array to go bellow 32 elements        

                    //__________________________________________________________________________________________________________________________________
                    
                    //these following lines reallocate memory for an array using the pointer in the parameters and the new size (half of the precious size)
                    Header *new_array = realloc(meta_data,sizeof(Header) +sizeof(Students) *new_capacity);

                    if (new_array == NULL) return meta_data; //if the operation fails we still have the pointer to the metadata
                    //meta data update
                    new_array->capacity = new_capacity;
                    new_array->items = (Students*)(new_array+ 1);
                    return new_array;
                }
                #endif

            return meta_data;
        
    }

    void free_the_array(Header *meta_data){
        if (meta_data ==NULL) return;
        free(meta_data);
    }
  