#ifndef SCORE_H
#define SCORE_H
#include <cstdlib>
#include <string>

using namespace std;

class Score {
 public:
  Score(string n, int s);
  bool operator<(const Score& s) const;
  bool operator>(const Score& s) const;
  string getName() {return username_;}
  int getScore() {return score_;}
 
 private:
  string username_;
  int score_;

};

#endif
