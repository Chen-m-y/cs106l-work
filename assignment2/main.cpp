/*
 * CS106L Assignment 2: Marriage Pact
 * Created by Haven Whitney with modifications by Fabio Ibanez & Jacob Roberts-Baca.
 *
 * Welcome to Assignment 2 of CS106L! Please complete each STUDENT TODO
 * in this file. You do not need to modify any other files.
 *
 */

#include <cctype>
#include <cstddef>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <unordered_set>

std::string kYourName = "Chen Mingyang"; // Don't forget to change this!

/**
 * Takes in a file name and returns a set containing all of the applicant names as a set.
 *
 * @param filename  The name of the file to read.
 *                  Each line of the file will be a single applicant's name.
 * @returns         A set of all applicant names read from the file.
 *
 * @remark Feel free to change the return type of this function (and the function
 * below it) to use a `std::unordered_set` instead. If you do so, make sure
 * to also change the corresponding functions in `utils.h`.
 */
std::set<std::string> get_applicants(std::string filename) {
  std::ifstream file(filename);
  if(! file){
    std::cerr << "Cannot open file: " << filename << '\n';
    return {}; 
  }
  std::string line;
  std::set<std::string> return_set;
  while(std::getline(file, line)){
    return_set.insert(line);
  }
  return return_set;
}

std::string get_initials(const std::string& full_name){
  std::string initials;
  std::istringstream ss(full_name);
  std::string token;
  while(ss >> token){
    initials += std::toupper(token[0]);
  }
  return initials;
}

/**
 * Takes in a set of student names by reference and returns a queue of names
 * that match the given student name.
 *
 * @param name      The returned queue of names should have the same initials as this name.
 * @param students  The set of student names.
 * @return          A queue containing pointers to each matching name.
 */
std::queue<const std::string*> find_matches(std::string name, std::set<std::string>& students) {
  std::queue<const std::string*> queue;
  // s 本身是引用，它是集合里那个字符串对象的“外号/别名”
  for(const auto& s : students){
    if(get_initials(s) == get_initials(name)){
      queue.push(&s);
    }
  }
  return queue;
}


int get_love(const std::string& name){
  int sum = 0;
  /* for(size_t i = 0; i < name.size(); ++i){
  *  sum += name[i];
  }*/
  for(char c : name){
    sum += c;
  }
  return sum;
}


/**
 * Takes in a queue of pointers to possible matches and determines the one true match!
 *
 * You can implement this function however you'd like, but try to do something a bit
 * more complicated than a simple `pop()`.
 *
 * @param matches The queue of possible matches.
 * @return        Your magical one true love.
 *                Will return "NO MATCHES FOUND." if `matches` is empty.
 */
std::string get_match(std::queue<const std::string*>& matches) {
  // queue是容器适配器，故意隐藏了迭代能力，只暴露受限接口
  while(!matches.empty()){
    if(get_love(*matches.front()) == get_love(kYourName)){ //func(a)
      return *matches.front();
    }
    else {
      matches.pop();
    }
    //return *matches.front();
  }
  return "NO MATCHES FOUND.";
}



/* #### Please don't remove this line! #### */
#include "autograder/utils.hpp"
