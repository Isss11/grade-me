#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <vector>
#include <iomanip>
#include <optional>
using namespace std;

// Using 'struct' strategy to deal with many parameters that may/may not be defined
struct Course_Conditions {
    optional <string> subject;
    optional <string> semester;
};

class Course {
    public:
        string code;
        string semester;
        string subject_code;
        int mark;
        float weight;

        Course();
        Course(string code_init, string semester_init, int mark_init, float weight_init);


        bool is_course_valid(Course_Conditions conditions);
    private:
        string get_extracted_subject_code();
    };

class Calculator {
    public:
        vector<Course> courses;

        int load_courses_from_file(char * file_name);
        int get_grade_by_course_code(string course_code);
        float compute_gpa(Course_Conditions conditions);
        float compute_subject_gpa(string subject_code);
        float compute_semester_gpa(string semester_code);
};

class Runner {
    public:
        void run(Calculator calculator);
};