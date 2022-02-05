/*C Program to read and print the employee details using structure and dynamic memory allocation*/
#include <stdio.h>
#include <stdlib.h>
/*structure to hold the details of an employee*/
typedef struct employee
{
    int empId;
    char Name[100];
    char Designation[100];
    char Dept[10];

}employee_t;
/* Read the employee details using scanf*/
void readData(int n, employee_t* s)
{
    for (int i=0;i<n;i++) {
        printf("\n");
        printf("Enter the employeeID, Name, Designation and Department of Employee %d:\n", i+1);  
        scanf("%d\n%s\n%s\n%s",&(s+i)->empId,(s+i)->Name,(s+i)->Designation,(s+i)->Dept);
    }
}
/* Function to print the employee details*/
void display(int n, employee_t* s)
{
    for (int i=0;i<n;i++) {
    	printf("\n");
	printf("The details of Employee %d:\n", i+1);
    	printf("empId: %d\n", (s+i)->empId);
	printf("Name: %s\n", (s+i)->Name);
	printf("Designation: %s\n", (s+i)->Designation);
	printf("Dept: %s\n", (s+i)->Dept);
    }
}

/*----------Main Program--------*/
int main()

{
    int n;
    printf("Enter the number of employees: ");
    scanf("%d", &n);
    employee_t *s=(employee_t*)malloc(n*sizeof(employee_t));
    readData(n,s);
    display(n,s);
    free(s);   
    return 0;
}

