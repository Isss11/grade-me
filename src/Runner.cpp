#include "../include/header.h"

// Accepts menu options and runs program functions
void Runner::run(Calculator calculator) {
    // Create input loop for GPA analysis
    string input;

    while (strcmp(input.c_str(), "q") != 0) {
        cout << "Menu Options: s (search), c (compute cGPA), cs (compute GPA by subject), ce (compute GPA by semester), q (quit)\n";
        cout << ">> ";
        cin >> input;

        if (strcmp(input.c_str(), "s") == 0) {
            string course_code;
            int course_mark;

            cout << "Enter a course code (i.e. CIS*1300): ";
            cin >> course_code;
            cout << "\n";

            course_mark = calculator.get_grade_by_course_code(course_code);

            // Input validation
            if (course_mark < 0) {
                cout << "The course with the code '" << course_code << "', does not exist. No mark was retrieved.\n";
            } else {
                cout << course_mark << "%\n";
            }
        } else if (strcmp(input.c_str(), "c") == 0) {
            float cgpa;
            Course_Conditions conditions;

            cgpa = calculator.compute_gpa(conditions);

            cout << "The student's cGPA is: " << fixed << setprecision(2) << cgpa << "%.\n";
        } else if (strcmp(input.c_str(), "cs") == 0) {
            string subject_code;
            float gpa;

            cout << "Enter a subject code (i.e. 'MATH'): ";
            cin >> subject_code;

            gpa = calculator.compute_subject_gpa(subject_code);
            cout << "The student's subject specific GPA for '" << subject_code << "' courses is: " << fixed << setprecision(2) << gpa << "%.\n";
        } else if (strcmp(input.c_str(), "ce") == 0) {
            string semester_code;
            float gpa;

            cout << "Enter a semester code (i.e. F25): ";
            cin >> semester_code;

            gpa = calculator.compute_semester_gpa(semester_code);
            cout << "The student's " << semester_code << " semester GPA is: " << fixed << setprecision(2) << gpa << "%.\n";
        } else {
            if (strcmp(input.c_str(), "q") != 0) {
                cout << "Invalid option entered.\n";
            }
        }
    }
}

int main(int argc, char* argv[]) {
    cout << "Loading... " << argv[1] << "\n";

    Runner runner = Runner();
    Calculator calculator = Calculator();

    if (calculator.load_courses_from_file(argv[1]) != 0) {
        cout << "There was an error reading the file, '" << argv[1] << "'. Please check if it exists or if it is in the proper (CSV) format.\n";
    }

    cout << "File loaded and ready for analysis.\n";

    runner.run(calculator);

    cout << "Exited program.\n";

    return 0;
}

