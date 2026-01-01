#include "../include/header.h"

Course::Course() {
            code = "";
            semester = "";
            subject_code = "";
            mark = 0;
            weight = 0.0;
        }

        Course::Course(string code_init, string semester_init, int mark_init, float weight_init) {
            code = code_init;
            semester = semester_init;
            subject_code = get_extracted_subject_code();
            mark = mark_init;
            weight = weight_init;
        };


bool Course::is_course_valid(Course_Conditions conditions) {
    bool is_subject_valid = false;
    bool is_semester_valid = false;

    if (conditions.subject == nullopt || conditions.subject.value().compare(subject_code) == 0) {
        is_subject_valid = true;
    }

    if (conditions.semester == nullopt || conditions.semester.value().compare(semester) == 0) {
        is_semester_valid = true;
    }

    return is_subject_valid && is_semester_valid;
}


// Obtain subject code from the course code
string Course::get_extracted_subject_code() {
    // For 3 character subject codes i.e. CIS*1300
    if (code[3] == '*') {
        return code.substr(0, 3);
    }

    // Assuming rest are 4 character subject codes (i.e. MATH*1210)
    return code.substr(0, 4);
}