#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <vector>
#include <iomanip>
#include <optional>
using namespace std;

struct Course {
    string code;
    string semester;
    int mark;
};

// Using 'struct' strategy to deal with many parameters that may/may not be defined
struct CGPA_Parameters {
    optional <string> subject;
    optional <string> semester;
};

int read_from_file(char * file_name, vector<Course> &courses) {
    string line;
    ifstream fp(file_name);

    // Use a while loop to read CSV file line by line
    while (getline (fp, line)) {
        // Parse line into a course structure
        // Handling for 8 character and 9 character course codes
        int course_code_len;
        int mark_len;

        if (line[8] == ',') {
            course_code_len = 8;
        } else {
            course_code_len = 9;
        }

        string course_code = line.substr(0, course_code_len);

        // Now determine if the mark is listed as 1, 2, or 3 digits (i.e. 0%, 55%, 100%)
        if (line[course_code_len + 2] == ',') {
            mark_len = 1;
        } else if (line[course_code_len + 3] == ',') {
            mark_len = 2;
        // Assuming that this is 100% (3 characters)
        } else {
            mark_len = 3;
        }

        int mark = stoi(line.substr(course_code_len + 1, mark_len));
        string semester = line.substr(course_code_len + mark_len + 2, 3);

        cout << course_code << " " << mark << " " << semester << "\n";

        courses.push_back({course_code, semester, mark});
    }

    // Close the file
    fp.close();
    
    return 0;
}


// Obtains the grade by course code
int get_grade_by_course_code(string course_code, vector<Course> &courses) {
    int mark, i;

    mark = -1;

    // Use linear search to obtain the course mark
    i = 0;

    // Iterates until a mark is found or until all the courses have been iterated through
    while (i < courses.size() && mark < 0) {
        cout << courses[i].code.c_str();
        if (strcmp(courses[i].code.c_str(), course_code.c_str()) == 0) {
            mark = courses[i].mark;
        }
    }

    return mark;
}

bool is_course_valid(Course course, CGPA_Parameters conditions) {
    // TODO: Validate based on course subject (do this after using a class for courses)
    if (conditions.semester == nullopt || strcmp(conditions.semester.value().c_str(), course.semester.c_str()) == 0) {
        return true;
    }

    return false;
}

// Computes the CGPA based on conditions provided
float compute_cgpa(vector<Course> &courses, CGPA_Parameters conditions) {
    float cgpa = 0;
    int n_courses = courses.size();
    int n_valid_courses = 0; // courses that validate the specified conditions

    for (int i = 0; i < n_courses; ++i) {
        if (is_course_valid(courses[i], conditions)) {
            cgpa += courses[i].mark;
            n_valid_courses += 1;
        }
    }

    cgpa /= n_valid_courses;
    
    return cgpa;
}

// Computes the CGPA for a specific course subject type (i.e. Mathematics)
// TODO
float compute_subject_cgpa(string subject_code, vector<Course> &courses) {
    cout << "Compute subject CPGA!\n";
    return 0.0;
}

// Computes semester GPA
float compute_semester_gpa(string semester_code, vector<Course> &courses) {
    CGPA_Parameters conditions = {nullopt, semester_code};

    return compute_cgpa(courses, conditions);
}

// Accepts menu options and runs program functions
void run_menu_options(vector<Course> &courses) {
    // Create input loop for GPA analysis
    string input;

    while (strcmp(input.c_str(), "q") != 0) {
        cout << "Menu Options: s (search), c (compute cGPA), cs (compute cGPA by subject), ce (compute cGPA by semester), q (quit)\n";
        cout << ">> ";
        cin >> input;

        if (strcmp(input.c_str(), "s") == 0) {
            string course_code;
            int course_mark;

            cout << "Enter a course code (i.e. CIS*1300): ";
            cin >> course_code;
            cout << "\n";

            course_mark = get_grade_by_course_code(course_code, courses);

            // Input validation
            if (course_mark < 0) {
                cout << "The course with the code '" << course_code << "', does not exist. No mark was retrieved.\n";
            } else {
                cout << course_mark << "%\n";
            }
        } else if (strcmp(input.c_str(), "c") == 0) {
            float cgpa;
            CGPA_Parameters conditions;

            cgpa = compute_cgpa(courses, conditions);

            cout << "The student's cGPA is: " << fixed << setprecision(2) << cgpa << "%.\n";
        } else if (strcmp(input.c_str(), "cs") == 0) {
            string subject_code;

            cout << "Enter a subject code (i.e. 'MATH'): ";
            cin >> subject_code;

            compute_subject_cgpa(subject_code, courses);
        } else if (strcmp(input.c_str(), "ce") == 0) {
            string semester_code;
            float gpa;

            cout << "Enter a semester code (i.e. F25): ";
            cin >> semester_code;

            gpa = compute_semester_gpa(semester_code, courses);
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

    // Create vector of all the structs of file information
    vector<Course> courses;

    if (read_from_file(argv[1], courses) != 0) {
        cout << "There was an error reading the file, '" << argv[1] << "'. Please check if it exists or if it is in the proper (CSV) format.\n";
    }

    cout << "File loaded and ready for analysis.\n";

    run_menu_options(courses);

    cout << "Exited program.\n";

    return 0;
}