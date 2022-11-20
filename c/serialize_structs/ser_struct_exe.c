#include <stdio.h> /* FILE *, printf */
#include <string.h> /* memcmp, memset */
#include <assert.h> /* assert */
#include "serialization.h" 

#define FIRST_NAME_SIZE 20
#define LAST_NAME_SIZE 30
#define FAIL -1
#define SUCCESS 0

typedef struct student student_ty;
typedef struct humon_grades grade_ty;
typedef struct real_grades real_grade_ty;

struct humon_grades
{
	int literature_grade;
	int sociology_grade;
};
struct real_grades
{
	int physics_grade;
	int math_grade;
};
struct student
{
	char first_name[FIRST_NAME_SIZE];
	char last_name[LAST_NAME_SIZE];
	grade_ty student_h_grades;
	real_grade_ty student_r_grades;
};
student_ty CreateStudent(void);

int main(void)
{
	FILE *fptr = NULL;
	student_ty new_student = CreateStudent();
	student_ty revived_student = {0};
	
	puts(new_student.first_name);
	puts(new_student.last_name);
	
	fptr = fopen("structfile.bin", "ab");
	if (NULL == fptr)
	{
		return (FAIL);
	}
	Serialization(&new_student,sizeof(student_ty), fptr);
	fclose(fptr);
	
	fptr = fopen("structfile.bin", "rb");
	if (NULL == fptr)
	{
		return (FAIL);
	}
	
	DeSerialization(&revived_student, sizeof(student_ty), fptr);
	printf("\n\nafter serialzation \n\n");
	puts(revived_student.first_name);
	puts(revived_student.last_name);
	assert(100 == revived_student.student_r_grades.physics_grade);
	assert(95 == revived_student.student_r_grades.math_grade);
	assert(88 == revived_student.student_h_grades.sociology_grade);
	assert(70 == revived_student.student_h_grades.literature_grade);
	
	fclose(fptr);

	return (0);
}

student_ty CreateStudent(void)
{
	student_ty first_student ={0};
	
	strcpy(first_student.first_name, "Assaf");
	strcpy(first_student.last_name, "Ainhoren-tesler");
	
	
	first_student.student_r_grades.physics_grade = 100;
	first_student.student_r_grades.math_grade = 95;
	first_student.student_h_grades.sociology_grade = 88;
	first_student.student_h_grades.literature_grade= 70;

	return (first_student);
}
