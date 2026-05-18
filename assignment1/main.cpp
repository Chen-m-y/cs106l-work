/*
 * CS106L Assignment 1: SimpleEnroll
 * Created by Fabio Ibanez with modifications by Jacob Roberts-Baca.
 *
 * Welcome to Assignment 1 of CS106L! Please complete each STUDENT TODO
 * in this file. You do not need to modify any other files.
 *
 * Students must implement: parse_csv, write_courses_offered,
 * write_courses_not_offered
 */

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

const std::string COURSES_OFFERED_PATH = "student_output/courses_offered.csv";
const std::string COURSES_NOT_OFFERED_PATH = "student_output/courses_not_offered.csv";

/**
 * Represents a course a student can take in ExploreCourses.
 * You must fill in the types of the fields in this struct.
 * Hint: Remember what types C++ streams work with?!
 */
struct Course {
  std::string title;
  std::string number_of_units; //单元数
  std::string quarter; // 季度
};

/**
 * (STUDENT TODO) Look at how the main function (at the bottom of this file)
 * calls `parse_csv`, `write_courses_offered`, and `write_courses_not_offered`.
 * Modify the signatures of these functions so that they work as intended, and then delete this
 * comment!
 */

/**
 * Note:
 * We need to #include utils.cpp _after_ we declare the Course struct above
 * so that the code inside utils.cpp knows what a Course is.
 * Recall that #include literally copies and pastes file contents.
 */

#include "utils.cpp"

/**
 * This function should populate the `courses` vector with structs of type
 * `Course`. We want to create these structs with the records in the courses.csv
 * file, where each line is a record!
 *
 * Hints:
 * 1) Take a look at the split function we provide in utils.cpp
 * 2) Each LINE is a record! *this is important, so we're saying it again :>)*
 * 3) The first line in the CSV defines the column names, so you can ignore it!
 *
 * @param filename The name of the file to parse.
 * @param courses  A vector of courses to populate.
 */
void parse_csv(const std::string filename, std::vector<Course>& courses) {//必须引用操作外部变量
  
  std::ifstream file(filename); // 创建文件流对象,并调用构造函数传入filename
  if(! file){
    std::cerr << "fail to open the file" << filename << std::endl;
    return;  
  }

  std::string header;
  std::getline(file, header);  // 扔掉第一行
  std::string line;
  for(int i = 0; std::getline(file, line); ++i){ //getline自动清除
    //courses[i-1]. = split(line, ','); 类型不匹配
    /*courses.emplace_back(
      split(line, ',')[0], 
      std::stoi(split(line, ',')[1]), 
      split(line, ',')[2]
    );*/
    auto tokens = split(line, ',');
    courses.emplace_back(tokens[0], tokens[1], tokens[2]);
  }
  
}

/**
 * 此函数有两个要求。
 *
 * 1) 将提供的课程写入文件
 * "student_output/courses_offered.csv"
 *
 * 2) 从 `all_courses` 向量中删除已提供的课程。
 * 重要提示：在写入文件后再执行此操作！
 *
 * 提示：
 * 1) 记录需要删除的课程！
 * 2) 使用我们提供的 delete_elem_from_vector 函数！
 * 3) 记得在输出开始时写入 CSV 列标题！
 *    参考 courses.csv。
 *
 * @param all_courses 通过调用 `parse_csv` 获得的所有课程的向量。
 *                    此向量将通过删除所有已提供课程进行修改。
 */
void write_courses_offered(std::vector<Course>& all_courses) {
  std::ofstream file(COURSES_OFFERED_PATH);
  if(!file){
    std::cerr << "Can not output file\n";
    return;
  }
  file << "Title,Number of Units,Quarter\n";
  //遍历容器的现代写法：
  for(const auto& course : all_courses){
    //在范围 for 中每次循环把当前元素绑定到变量 course，因此应该通过 course 访问字段。
    if(course.quarter != "null"){
      file << course.title << ','
      << course.number_of_units << ','
      << course.quarter << '\n';
    }

  }
  

  /*all_courses.erase(
    std::remove_if(all_courses.begin(), all_courses.end(),
                   [](const Course& c){ return c.quarter != "null"; }),
    all_courses.end());
  */
  // 倒着来！从最后一个元素往前数
  for (int i = all_courses.size() - 1; i >= 0; --i) {
      if (all_courses[i].quarter != "null") {
          delete_elem_from_vector(all_courses, all_courses[i]);
      }
  }
}

/**
 * This function writes the courses NOT offered to the file
 * "student_output/courses_not_offered.csv".
 *
 * This function is ALWAYS called after the `write_courses_offered` function.
 * `unlisted_courses` will trivially contain classes that are not offered
 * since you delete offered classes from `all_courses` in the
 * `write_courses_offered` function.
 *
 * HINT: This should be VERY similar to `write_courses_offered`
 *
 * @param unlisted_courses A vector of courses that are not offered.
 */
void write_courses_not_offered(const std::vector<Course>& unlisted_courses) {
  std::ofstream file(COURSES_NOT_OFFERED_PATH);
  if(!file){
    std::cerr << "Can not open file!\n";
    return;
  }

  //the first line
  file << "Title,Number of Units,Quarter\n";
  for(const auto& course: unlisted_courses){
    file << course.title << ','
    << course.number_of_units << ','
    << course.quarter << '\n';
  }
}

int main() {
  /* Makes sure you defined your Course struct correctly! */
  static_assert(is_valid_course<Course>, "Course struct is not correctly defined!");

  std::vector<Course> courses; // 动态数组容器（堆）
  parse_csv("courses.csv", courses);

  /* Uncomment for debugging... */
  //print_courses(courses);

  write_courses_offered(courses);
  write_courses_not_offered(courses);

  return run_autograder();
}