#include <stdio.h>
#include <string.h>

struct Student {
    char name[50];
    int age;
    float grade;
};

void display_student(struct Student student) {
    printf("Name: %s\n", student.name);
    printf("Age: %d\n", student.age);
    printf("Grade: %.2f\n", student.grade);
}

int main(void) {
    struct Student student;

    strcpy(student.name, "Mohammed");
    student.age = 20;
    student.grade = 15.5f;

    display_student(student);

    return 0;
}
