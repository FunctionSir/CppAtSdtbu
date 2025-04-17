#ifndef __EMPLOYEE_HPP_INCLUDED__
#define __EMPLOYEE_HPP_INCLUDED__

#include "date.hpp"
#include <string>

using namespace std;

class employee {
  public:
    employee(string Id = "", bool Sex = false, Date BirthDate = Date(), string Pin = "");
    void from_string(string str);
    string to_string(void) const;
    static int count(void);
    ~employee();

  private:
    string id;
    bool sex;
    Date birth_date;
    string PIN;
    static int total;
};

#endif
