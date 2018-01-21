#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

struct student{
    int age;
    char name[20];
};

void* print_msg_function(void* msg)
{
    printf("%s\n", (char*)msg);
    return NULL;
}

void* printf_student_function(void* student_info)
{
    struct student *student_ptr = (struct student*)student_info;
    printf("age = %d, name = %s\n", student_ptr->age, student_ptr->name);
    return NULL;
}

int main(){
    pthread_t thread1, thread2;
    int rt1, rt2;
    struct student stu_entry;

    char *msg1 = "thread1";
    stu_entry.age = 20;
    strcpy(stu_entry.name, "amao");

    rt1 = pthread_create(&thread1, NULL, print_msg_function, (void*)msg1);
    rt2 = pthread_create(&thread2, NULL, printf_student_function, (void*)&stu_entry);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("rt1 = %d\n", rt1);
    printf("rt2 = %d\n", rt2);

    return 0;
}
