#include <stdio.h>
#include <string.h>

#define MAX_COURSES 5
#define MAX_STUDENTS 3

// Structure to store course information
struct Course {
    char course_id[10]; // Course ID is now a string (alphanumeric)
    char course_name[50];
    float MRP; // Replaced credits with PRICE)
    int available_seats;
};

// Structure to store student information and their course registrations
struct Student {
    int student_id;
    char name[50];
    char registered_courses[MAX_COURSES][10]; // Store course IDs as strings
};

// Function prototypes
void inputCourses(struct Course courses[], int num_courses);
void inputStudents(struct Student students[], int num_students);
void registerCourse(struct Student* student, struct Course courses[], int num_courses);
void viewAvailableCourses(struct Course courses[], int num_courses);
void displayStudentDetails(struct Student students[], int num_students, struct Course courses[], int num_courses);

int main() {
    struct Course courses[MAX_COURSES];
    struct Student students[MAX_STUDENTS];
    int num_courses = MAX_COURSES, num_students = MAX_STUDENTS;

    // Input course details
    inputCourses(courses, num_courses);

    // Input student details
    inputStudents(students, num_students);

    // Register courses for students
    for (int i = 0; i < num_students; i++) {
        registerCourse(&students[i], courses, num_courses);
    }

    // Display student details and their course registrations
    displayStudentDetails(students, num_students, courses, num_courses);

    return 0;
}

// Function to input course details
void inputCourses(struct Course courses[], int num_courses) {
    for (int i = 0; i < num_courses; i++) {
        printf("\nEnter details for Course %d:\n", i + 1);
        printf("Course ID (alphanumeric): ");
        scanf("%s", courses[i].course_id); // Input course ID as string
        getchar();  // Clear newline character
        printf("Course Name: ");
        fgets(courses[i].course_name, sizeof(courses[i].course_name), stdin);
        courses[i].course_name[strcspn(courses[i].course_name, "\n")] = '\0'; // Remove newline character
        printf("PRICE: ");
        scanf("%f", &courses[i].MRP); // Input MRP
        printf("Available Seats: ");
        scanf("%d", &courses[i].available_seats);
    }
}

// Function to input student details
void inputStudents(struct Student students[], int num_students) {
    for (int i = 0; i < num_students; i++) {
        printf("\nEnter details for Student %d:\n", i + 1);
        printf("Student ID: ");
        scanf("%d", &students[i].student_id);
        getchar();  // Clear newline character
        printf("Student Name: ");
        fgets(students[i].name, sizeof(students[i].name), stdin);
        students[i].name[strcspn(students[i].name, "\n")] = '\0'; // Remove newline character
        for (int j = 0; j < MAX_COURSES; j++) {
            students[i].registered_courses[j][0] = '\0'; // Initialize with empty string, meaning no course registered
        }
    }
}

// Function to register courses for a student
void registerCourse(struct Student* student, struct Course courses[], int num_courses) {
    char course_id[10]; // Use a string to input course IDs
    printf("\n\nRegister Courses for Student: %s (ID: %d)\n", student->name, student->student_id);
    viewAvailableCourses(courses, num_courses);
    printf("\nEnter the Course ID to register (enter 'exit' to stop): ");
    while (1) {
        scanf("%s", course_id);
        if (strcmp(course_id, "exit") == 0) {
            break;
        }
        int course_found = 0;
        for (int i = 0; i < num_courses; i++) {
            if (strcmp(courses[i].course_id, course_id) == 0) { // Compare course IDs as strings
                course_found = 1;
                if (courses[i].available_seats > 0) {
                    // Register the course for the student
                    for (int j = 0; j < MAX_COURSES; j++) {
                        if (student->registered_courses[j][0] == '\0') { // Find an empty slot for the course ID
                            strcpy(student->registered_courses[j], course_id);
                            courses[i].available_seats--;
                            printf("Successfully registered for %s.\n", courses[i].course_name);
                            break;
                        }
                    }
                } else {
                    printf("Sorry, no available seats in %s.\n", courses[i].course_name);
                }
                break;
            }
        }
        if (!course_found) {
            printf("Invalid Course ID! Try again.\n");
        }
        printf("\nEnter the Course ID to register (enter 'exit' to stop): ");
    }
}

// Function to display available courses
void viewAvailableCourses(struct Course courses[], int num_courses) {
    printf("\nAvailable Courses:\n");
    for (int i = 0; i < num_courses; i++) {
        printf("Course ID: %s, Name: %s, MRP: %.2f, Available Seats: %d\n",
               courses[i].course_id, courses[i].course_name, courses[i].MRP, courses[i].available_seats);
    }
}

// Function to display student details and their course registrations
void displayStudentDetails(struct Student students[], int num_students, struct Course courses[], int num_courses) {
    printf("\nStudent Registration Summary:\n");
    for (int i = 0; i < num_students; i++) {
        printf("\nStudent ID: %d, Name: %s\n", students[i].student_id, students[i].name);
        printf("Registered Courses:\n");
        int course_found = 0;
        for (int j = 0; j < MAX_COURSES; j++) {
            if (students[i].registered_courses[j][0] != '\0') { // Check if a course is registered
                char* course_id = students[i].registered_courses[j];
                for (int k = 0; k < num_courses; k++) {
                    if (strcmp(courses[k].course_id, course_id) == 0) {
                        printf("Course ID: %s, Name: %s, MRP: %.2f\n",
                               courses[k].course_id, courses[k].course_name, courses[k].MRP);
                        course_found = 1;
                        break;
                    }
                }
            }
        }
        if (!course_found) {
            printf("No courses registered.\n");
        }
    }
}