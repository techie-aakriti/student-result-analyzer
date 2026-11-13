#include <stdio.h>
#include <string.h>

#define SUBJECTS 5
#define PASS_MARK 40

/* Structure to store student data */
struct Student
{
    char name[30];
    int roll;
    int marks[SUBJECTS];
    int total;
    float percentage;
    char grade;
    char result[10];
};

/* Function declarations */
void inputStudent(struct Student *s);
void calculateResult(struct Student *s);
void displayStudent(struct Student s);
void searchStudent(struct Student s[], int n);
void findTopper(struct Student s[], int n);
void classAverage(struct Student s[], int n);
void subjectTopper(struct Student s[], int n);

int main()
{
    struct Student students[50];

    int n, i, choice;

    printf("Enter number of students: ");
    scanf("%d", &n);

    /* Input all students */
    for (i = 0; i < n; i++)
    {
        printf("\n--- Student %d ---\n", i + 1);

        inputStudent(&students[i]);
        calculateResult(&students[i]);
    }

    /* Menu */
    do
    {
        printf("\n===== STUDENT RESULT ANALYZER =====\n");
        printf("1. Display All Students\n");
        printf("2. Search Student\n");
        printf("3. Find Class Topper\n");
        printf("4. Class and Subject Average\n");
        printf("5. Subject-wise Topper\n");
        printf("6. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:

                for (i = 0; i < n; i++)
                {
                    displayStudent(students[i]);
                }

                break;

            case 2:

                searchStudent(students, n);
                break;

            case 3:

                findTopper(students, n);
                break;

            case 4:

                classAverage(students, n);
                break;

            case 5:

                subjectTopper(students, n);
                break;

            case 6:

                printf("Program Ended.\n");
                break;

            default:

                printf("Invalid choice!\n");
        }

    } while (choice != 6);

    return 0;
}


/* -------- INPUT FUNCTION -------- */

void inputStudent(struct Student *s)
{
    int i;

    printf("Enter name: ");
    scanf(" %29[^\n]", s->name);

    printf("Enter roll number: ");
    scanf("%d", &s->roll);

    printf("Enter marks of 5 subjects:\n");

    for (i = 0; i < SUBJECTS; i++)
    {
        do
        {
            printf("Subject %d: ", i + 1);
            scanf("%d", &s->marks[i]);

            if (s->marks[i] < 0 || s->marks[i] > 100)
            {
                printf("Marks must be 0 to 100.\n");
            }

        } while (s->marks[i] < 0 || s->marks[i] > 100);
    }
}


/* -------- CALCULATE RESULT -------- */

void calculateResult(struct Student *s)
{
    int i;
    int fail = 0;

    s->total = 0;

    for (i = 0; i < SUBJECTS; i++)
    {
        s->total = s->total + s->marks[i];

        if (s->marks[i] < PASS_MARK)
        {
            fail = 1;
        }
    }

    s->percentage = s->total / 5.0;

    if (fail == 1)
    {
        strcpy(s->result, "FAIL");
        s->grade = 'F';
    }
    else
    {
        strcpy(s->result, "PASS");

        if (s->percentage >= 90)
            s->grade = 'A';

        else if (s->percentage >= 75)
            s->grade = 'B';

        else if (s->percentage >= 60)
            s->grade = 'C';

        else if (s->percentage >= 50)
            s->grade = 'D';

        else
            s->grade = 'E';
    }
}


/* -------- DISPLAY STUDENT -------- */

void displayStudent(struct Student s)
{
    int i;

    printf("\nName       : %s\n", s.name);
    printf("Roll       : %d\n", s.roll);

    printf("Marks      : ");

    for (i = 0; i < SUBJECTS; i++)
    {
        printf("%d ", s.marks[i]);
    }

    printf("\nTotal      : %d / 500\n", s.total);
    printf("Percentage : %.2f%%\n", s.percentage);
    printf("Grade      : %c\n", s.grade);
    printf("Result     : %s\n", s.result);
}


/* -------- SEARCH STUDENT -------- */

void searchStudent(struct Student s[], int n)
{
    int roll, i;
    int found = 0;

    printf("Enter roll number: ");
    scanf("%d", &roll);

    for (i = 0; i < n; i++)
    {
        if (s[i].roll == roll)
        {
            displayStudent(s[i]);
            found = 1;
            break;
        }
    }

    if (found == 0)
    {
        printf("Student not found.\n");
    }
}


/* -------- CLASS TOPPER -------- */

void findTopper(struct Student s[], int n)
{
    int i;
    int top = 0;

    for (i = 1; i < n; i++)
    {
        if (s[i].total > s[top].total)
        {
            top = i;
        }
    }

    printf("\n===== CLASS TOPPER =====\n");

    printf("Name       : %s\n", s[top].name);
    printf("Roll       : %d\n", s[top].roll);
    printf("Total      : %d\n", s[top].total);
    printf("Percentage : %.2f%%\n", s[top].percentage);
}


/* -------- CLASS AND SUBJECT AVERAGE -------- */

void classAverage(struct Student s[], int n)
{
    int i, j;
    int classTotal = 0;

    float subjectSum[SUBJECTS] = {0};
    float average;

    for (i = 0; i < n; i++)
    {
        classTotal += s[i].total;

        for (j = 0; j < SUBJECTS; j++)
        {
            subjectSum[j] += s[i].marks[j];
        }
    }

    average = (float)classTotal / n;

    printf("\nClass Average Total = %.2f / 500\n", average);

    printf("\nSubject Averages:\n");

    for (j = 0; j < SUBJECTS; j++)
    {
        printf("Subject %d = %.2f\n",
               j + 1, subjectSum[j] / n);
    }
}


/* -------- SUBJECT-WISE TOPPER -------- */

void subjectTopper(struct Student s[], int n)
{
    int i, j, top;

    printf("\n===== SUBJECT-WISE TOPPERS =====\n");

    for (j = 0; j < SUBJECTS; j++)
    {
        top = 0;

        for (i = 1; i < n; i++)
        {
            if (s[i].marks[j] > s[top].marks[j])
            {
                top = i;
            }
        }

        printf("Subject %d: %s - %d marks\n",
               j + 1,
               s[top].name,
               s[top].marks[j]);
    }
}