#include <stdio.h>
#include <stdbool.h>

#define NUM_CLASSES 4
#define NUM_SEMESTERS 2

typedef struct {
    float cc[4];
    float exam;
    float td;
    float tp;
} Class;

typedef struct {
    Class classes[NUM_CLASSES];
} Semester;

typedef struct {
    Semester semesters[NUM_SEMESTERS];
} Module;

float compute_final_mark(Class class) {
    float final_mark;

    if (class.td == -1 && class.tp == -1) {
        final_mark = 0.5 * (class.cc[0] + class.cc[1] + class.cc[2] + class.cc[3]) / 4 + 0.5 * class.exam;
    } else if (class.tp == -1) {
        final_mark = 0.4 * ((class.cc[0] + class.cc[1] + class.cc[2] + class.cc[3]) / 4) + 0.6 * class.exam;
    } else {
        final_mark = 0.4 * ((class.cc[0] + class.cc[1] + class.cc[2] + class.cc[3]) / 4) + 0.6 * class.exam;
    }

    return final_mark;
}

float compute_semester_average(Semester semester) {
    float semester_total = 0;

    for (int i = 0; i < NUM_CLASSES; i++) {
        semester_total += compute_final_mark(semester.classes[i]);
    }

    return semester_total / NUM_CLASSES;
}

bool is_valid_input(float input) {
    return input >= 0 && input <= 20;
}

void input_marks(Semester *semester, const char *semester_name) {
    printf("Enter marks for %s semester:\n", semester_name);
    for (int i = 0; i < NUM_CLASSES; i++) {
        printf("Class %d:\n", i + 1);
        for (int j = 0; j < 4; j++) {
            float mark;
            do {
                printf("Enter CC%d mark: ", j + 1);
                scanf("%f", &mark);
                if (!is_valid_input(mark)) {
                    printf("Please enter a value between 0 and 20.\n");
                }
            } while (!is_valid_input(mark));
            semester->classes[i].cc[j] = mark;
        }
        float exam;
        do {
            printf("Enter Exam mark: ");
            scanf("%f", &exam);
            if (!is_valid_input(exam)) {
                printf("Please enter a value between 0 and 20.\n");
            }
        } while (!is_valid_input(exam));
        semester->classes[i].exam = exam;
        float td;
        do {
            printf("Enter TD mark: ");
            scanf("%f", &td);
            if (!is_valid_input(td)) {
                printf("Please enter a value between 0 and 20.\n");
            }
        } while (!is_valid_input(td));
        semester->classes[i].td = td;
        float tp;
        do {
            printf("Enter TP mark: ");
            scanf("%f", &tp);
            if (!is_valid_input(tp)) {
                printf("Please enter a value between 0 and 20.\n");
            }
        } while (!is_valid_input(tp));
        semester->classes[i].tp = tp;
    }
}

int main() {
    Module modules[NUM_SEMESTERS];
    float semester_averages[NUM_SEMESTERS];
    float annual_average;

    // Input marks for Semester 1
    input_marks(&modules[0].semesters[0], "first");

    // Calculate average for Semester 1
    semester_averages[0] = compute_semester_average(modules[0].semesters[0]);
    printf("Average for Semester 1: %.2f\n", semester_averages[0]);

    // Input marks for Semester 2
    input_marks(&modules[1].semesters[0], "second");

    // Calculate average for Semester 2
    semester_averages[1] = compute_semester_average(modules[1].semesters[0]);
    printf("Average for Semester 2: %.2f\n", semester_averages[1]);

    // Calculate annual average
    annual_average = (semester_averages[0] + semester_averages[1]) / NUM_SEMESTERS;

    // Check if the student passed the entire academic year
    if (annual_average >= 10) {
        printf("The student passed the entire academic year with an average of %.2f.\n", annual_average);
    } else {
        printf("The student failed the entire academic year with an average of %.2f.\n", annual_average);
        printf("The student needs a support test.\n");

        float support_test_total = 0;
        int num_classes_tested = 0;

        // Input support test marks for failed classes
        for (int i = 0; i < NUM_CLASSES; i++) {
            if (compute_final_mark(modules[0].semesters[0].classes[i]) < 10) {
                printf("Enter support test mark for Class %d in Semester 1: ", i + 1);
                float support_test_mark;
                do {
                    scanf("%f", &support_test_mark);
                    if (!is_valid_input(support_test_mark)) {
                        printf("Please enter a value between 0 and 20.\n");
                    }
                } while (!is_valid_input(support_test_mark));
                support_test_total += support_test_mark;
                num_classes_tested++;
            }
        }

        // Determine if the student passed or failed the support test
        if (support_test_total / num_classes_tested >= 10) {
            printf("Congratulations! The student passed the support test.\n");
        } else {
            printf("Good luck next year. The student failed the support test.\n");
        }
    }

    return 0;
}
