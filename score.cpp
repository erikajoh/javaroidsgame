#include "score.h"

Score::Score(string n, int s){
  username_ = n;
  score_ = s;
}

bool Score::operator<(const Score& s) const
{
  if( score_ < s.score_ ){
    return true;
  }
  else {
     return false;
  }
}

bool Score::operator>(const Score& s) const
{
  if( score_ > s.score_ ){
    return true;
  }
  else {
     return false;
  }
}
