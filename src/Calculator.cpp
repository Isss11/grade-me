#include "../include/header.h"
/*
TODO:
2. Turn the calculator functionality into a class.
3. Create instances of the Courses and the Calculator in a runner file, and call them from there.
*/

int Calculator::load_courses_from_file(char * file_name) {
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
        float weight = stof(line.substr(course_code_len + mark_len + 2, 4)); // Assuming a fixed length of 4 characters for weights
        string semester = line.substr(course_code_len + mark_len + 7, 3);

        courses.push_back({course_code, semester, mark, weight});
    }

    // Close the file
    fp.close();
    
    return 0;
}


// Obtains the grade by course code
int Calculator::get_grade_by_course_code(string course_code) {
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

// Computes the GPA based on conditions provided
float Calculator::compute_gpa(Course_Conditions conditions) {
    float gpa = 0;
    int n_courses = courses.size();
    float total_weightage = 0; // courses that validate the specified conditions

    for (int i = 0; i < n_courses; ++i) {
        if (courses[i].is_course_valid(conditions)) {
            gpa += courses[i].mark * courses[i].weight;
            total_weightage += courses[i].weight;
        }
    }

    gpa /= total_weightage;
    
    return gpa;
}

// Computes the GPA for a specific course subject type (i.e. Mathematics)
float Calculator::compute_subject_gpa(string subject_code) {
    Course_Conditions conditions;
    conditions.subject = subject_code;

    return compute_gpa(conditions);
}

// Computes semester GPA
float Calculator::compute_semester_gpa(string semester_code) {
    Course_Conditions conditions;
    conditions.semester = semester_code;

    return compute_gpa(conditions);
}