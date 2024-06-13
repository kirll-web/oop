#pragma once

#include <iostream>
#include "CWorker.h"
#include "CTeacher.h"
#include "CPupil.h"
#include "CStudent.h"
#include "CAdvancedStudent.h"


int main()
{
    CWorker worker{"jack", "london", "pertrovich", "Chavaina", "Writer"};

    std::cout << worker.GetName() << std::endl;
    std::cout << worker.GetSpecialty() << std::endl;

    std::cout << std::endl;

    CTeacher teacher{ "teacher", "london", "pertrovich1", "Chavaina1", "Math"};

    std::cout << teacher.GetName() << std::endl;
    std::cout << teacher.GetCourse() << std::endl;

    std::cout << std::endl;

    CPupil pupil{ "pupil", "london", "pertrovich2", "Chavaina2", "Licei 28", "9g"};

    std::cout << pupil.GetName() << std::endl;
    std::cout << pupil.GetNameSchool() << std::endl;
    std::cout << pupil.GetGrade() << std::endl;

    std::cout << std::endl;

    CStudent student{ "student", "london", "pertrovich3", "Chavaina3", "PGTU", 1210501071 };

    std::cout << student.GetName() << std::endl;
    std::cout << student.GetNameUniversity() << std::endl;
    std::cout << student.GetStudentIDNumber() << std::endl;

    std::cout << std::endl;

    CAdvancedStudent advancedStudent{ "advancedStudent", "london", "pertrovich4", "Chavaina4", "PGTU1111", 121, "OOP"};

    std::cout << advancedStudent.GetName() << std::endl;
    std::cout << advancedStudent.GetNameUniversity() << std::endl;
    std::cout << advancedStudent.GetStudentIDNumber() << std::endl;
    std::cout << advancedStudent.GetDissertationTopic() << std::endl;
}