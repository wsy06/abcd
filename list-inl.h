/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

/**
 * Destroys the current List. This function should ensure that
 * memory does not leak on destruction of a list.
 */
template <class T>
List<T>::~List() {
  /// @todo Graded in MP3.1
}

/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <class T>
void List<T>::clear() {
  /// @todo Graded in MP3.1
  ListNode *nowp=head_;
  ListNode *nextp=nowp;
  while (nextp!=NULL){
    nextp=nowp->next;
    delete nowp;
    nowp=nextp;
  }
  length_=0;
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertFront(T const& ndata) {
  /// @todo Graded in MP3.1
    if (empty()){
    ListNode *ins= new ListNode(ndata);
    length_++;  
    tail_ = ins;
    head_ = ins;
    return;
  }
  ListNode *ins = new ListNode(ndata);
  head_->prev = ins;
  ins->next = head_;
  head_ = ins;
  length_++;
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertBack(const T& ndata) {
  /// @todo Graded in MP3.1
    if (empty()){
    ListNode *ins= new ListNode(ndata);
    length_++;  
    tail_ = ins;
    head_ = ins;
    return;
  }
  ListNode *ins = new ListNode(ndata);
  ins->prev = tail_;
  tail_->next = ins;
  tail_ = ins;
  length_++;
}

/**
 * Reverses the current List.
 */
template <class T>
void List<T>::reverse() {
  reverse(head_, tail_);

}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <class T>
void List<T>::reverse(ListNode*& startPoint, ListNode*& endPoint) {
   /// @todo Graded in MP3.1
  ListNode * nown = startPoint;

  ListNode * begin = startPoint->prev;
  ListNode * temp = startPoint->next;
  nown->prev = temp;
  nown->next = endPoint->next;
  nown = temp;

  while (nown != endPoint) {
    temp = nown->next;
    nown->next = nown->prev;
    nown->prev = temp;
    nown = temp;
  }

  endPoint->next = endPoint->prev;
  endPoint->prev = begin;
  if (head_ != startPoint) {begin->next = nown;}
  else {head_ = endPoint;}
  if (tail_ != endPoint) {startPoint->next->prev = startPoint;}
  else  {tail_ = startPoint;}
}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <class T>
void List<T>::reverseNth(int n) {
  /// @todo Graded in MP3.1
    ListNode * endn = head_;
  ListNode * begin = head_;

int cnt;
  while (begin != NULL) {
    int cnt = 1;
    while (cnt < n) {
      if (endn != tail_) {
        endn = endn->next;
      }
      cnt++;
    }
    reverse(begin, endn);
    begin = begin->next;
    endn = begin;
  }
}

/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <class T>
void List<T>::waterfall() {
  /// @todo Graded in MP3.1
  int cnt = 0;
  ListNode  * watern,* nown = head_;


  while (nown != tail_) {
    watern = nown->next;
    if (cnt % 2 != 0) {
      nown->prev->next = nown->next;
      nown->next->prev = nown->prev;

      tail_->next = nown;
      nown->prev = tail_;
      nown->next = NULL;
      tail_ = nown;
    }
    cnt++;
    nown = watern;
  }
}

/**
 * Splits the given list into two parts by dividing it at the splitPoint.
 *
 * @param splitPoint Point at which the list should be split into two.
 * @return The second list created from the split.
 */
template <class T>
List<T> List<T>::split(int splitPoint) {
  if (splitPoint > length_)
        return List<T>();

    if (splitPoint < 0)
        splitPoint = 0;

    ListNode* secondHead = split(head_, splitPoint);

    int oldLength = length_;
    if (secondHead == head_) {
        // current list is going to be empty
        head_ = NULL;
        tail_ = NULL;
        length_ = 0;
    } else {
        // set up current list
        tail_ = head_;
        while (tail_->next != NULL)
            tail_ = tail_->next;
        length_ = splitPoint;
    }

    // set up the returned list
    List<T> ret;
    ret.head_ = secondHead;
    ret.tail_ = secondHead;
    if (ret.tail_ != NULL) {
        while (ret.tail_->next != NULL)
            ret.tail_ = ret.tail_->next;
    }
    ret.length_ = oldLength - splitPoint;
    return ret;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List objects!
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <class T>
typename List<T>::ListNode* List<T>::split(ListNode* start, int splitPoint) {
    /// @todo Graded in MP3.2

    ListNode *ans=start;
    if (splitPoint >= length_) {return head_;}
    for(int i=0;i<splitPoint;i++){
        ans=ans->next;
    }
    tail_=ans->prev;
    ans->prev=NULL;
    tail_->next=NULL;

    return ans;
}

/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <class T>
void List<T>::mergeWith(List<T>& otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <class T>
typename List<T>::ListNode* List<T>::merge(ListNode* first, ListNode* second) {
  /// @todo Graded in MP3.2
  ListNode * ans;
	if (!(first->data < second->data)) {
    ans = second;
		second = second->next;

	}
	else {
    ans = first;
		first = first->next;
	}
	ListNode * nown = ans;
	while (first != NULL && second != NULL) {
		if (!(second->data < first->data)) {
      			nown->next = first;
			first->prev = nown;
			first = first->next;

		}
		else {
      nown->next = second;
			second->prev = nown;
			second = second->next;
		}
		nown = nown->next;
	}
  if (second == NULL && first != NULL) {
		nown->next = first;
		first->prev = nown;
	}
	if (first == NULL && second != NULL) {
		nown->next = second;
		second->prev = nown;
	}

	return ans;
}

/**
 * Sorts the current list by applying the Mergesort algorithm.
 */
template <class T>
void List<T>::sort() {
    if (empty())
        return;
    head_ = mergesort(head_, length_);
    tail_ = head_;
    while (tail_->next != NULL)
        tail_ = tail_->next;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <class T>
typename List<T>::ListNode* List<T>::mergesort(ListNode* start, int chainLength) {
if (start->next != NULL){
  	ListNode * second = split(start, chainLength / 2);
    if(chainLength%2==1)
  	return merge(mergesort(start, chainLength / 2), mergesort(second,  (chainLength / 2)+1));
    else 
    return merge(mergesort(start, chainLength / 2), mergesort(second,  (chainLength / 2)));
    }
else{return start;}
}
