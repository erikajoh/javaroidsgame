#ifndef PMMINLIST_H
#define PMMINLIST_H
#include <list>
#include "score.h"

/**
 * PMMinList implements a sorted list of Score*s
 * based on their score (from largest to smallest)
 */
class PMMinList 
{
 public:
  
  PMMinList();
  ~PMMinList();
  /** Returns the size of items in the list */
  int size() const { return slist_.size(); }
  /** Returns true if the list is empty */
  bool empty() const { return slist_.empty(); }
  /** Adds a puzzle move to the sorted list */
  void push(Score* s);
  /** Removes the maximum scored (front) Score */
  void pop();
  /** Returns the Score with the highest score */
  Score* top();
  /** Returns whether the list is empty */
  bool isEmpty();

 private:
  /** sorted list of Score*s */
  std::list<Score*> slist_;
};

#endif
