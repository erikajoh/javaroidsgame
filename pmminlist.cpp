#include "score.h"
#include "pmminlist.h"

/**
 * Default Constructor
 */
PMMinList::PMMinList() : slist_()
{

}

/**
 * Destructor
 */
PMMinList::~PMMinList()
{

}

/**
 * Adds a Score* to the internal list in sorted
 * order from smallest to largest
 * @param pm Score* to add to the sorted Score* list
 */
void PMMinList::push(Score* s)
{
  std::list<Score*>::iterator it = slist_.begin();
 
  //---- Add your implementation to iterate through the list
  //---- to find the correct location to insert s and then
  //---- use the insert() method of std::List to insert it
  //---- See http://www.cplusplus.com/reference/list/list/insert/

  if (slist_.empty()){
    slist_.insert(it,s);
    return;
  }

  for (it=slist_.begin(); it != slist_.end(); ++it){
    if (*s < **it){
      slist_.insert(it,s);
      return;
    }
  }

  slist_.push_back(s);
}

/**
 * Removes Score* from beginning of sorted Score* list (i.e.
 * minimum-scored Score*)
 */
void PMMinList::pop()
{
  slist_.pop_front();
}

/**
 * Gets PuzzleMove* from beginning of sorted PuzzleMove* list
 * @return reference to the minimum-scored PuzzleMove*
 */
Score* PMMinList::top()
{
  return slist_.front();
}

bool PMMinList::isEmpty()
{
  return slist_.empty();
}
