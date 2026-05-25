/*
 * CS106L Assignment 5: TreeBook
 * Created by Fabio Ibanez with modifications by Jacob Roberts-Baca.
 */

#include <iostream>
#include <ostream>
#include <string>

class User
{
public:
  User(const std::string& name);
  void add_friend(const std::string& name);
  std::string get_name() const;
  size_t size() const;
  void set_friend(size_t index, const std::string& name);

  /** 
   * STUDENT TODO:
   * Your custom operators and special member functions will go here!
   */
  friend std::ostream&
  operator<<(std::ostream& os,const User& ur);
  /*不写返回类型
    没有参数
    一个类只能有一个析构函数*/
  ~User();
  User(const User& user);
  User& operator=(const User& user);
  // 禁止移动语义
  User(User&& user) = delete;
  User& operator=(User&& user) = delete;

private:
  std::string _name;
  std::string* _friends; // 指向字符串的指针
  size_t _size;
  size_t _capacity;
};