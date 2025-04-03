#ifndef __STUDENT_HPP_INCLUDED__
#define __STUDENT_HPP_INCLUDED__
#include <string>
using namespace std;
class Student {
  public:
    Student(string id, string name, double score = 0);
    // Set new id.
    void ChangeId(string id);
    // Set new name.
    void ChangeName(string name);
    // Set new score.
    void ChangeScore(double score);
    void ChangeScore(int score);
    // Get id.
    string GetId(void);
    // Get name.
    string GetName(void);
    // Get score.
    double GetScore(void);

  private:
    string priv_id;
    string priv_name;
    short priv_score;
};
#endif
