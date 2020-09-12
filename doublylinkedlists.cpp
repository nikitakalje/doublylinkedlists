#include <iostream>

using namespace std;


class ListNode {
private:
  int data;
  ListNode* next;
  ListNode* prev;
public:
  ListNode(int k) : data(k), next(nullptr), prev(nullptr) { };
  ListNode(int k, ListNode* n, ListNode* p) : data(k), next(n), prev(p) { };
  friend class List;
};

class List {
private:
  ListNode* head;
  ListNode* tail;
public:
  List() : head(nullptr), tail(nullptr) { };
  void InsertFront(int n) {
    head = new ListNode(n, head, nullptr);
    if (tail == nullptr) tail = head;
    if (head->next != nullptr) head->next->prev = head;
  };

  void InsertBack(int n) {
    if (tail == nullptr) {
      head = tail = new ListNode(n);
    } else {
      tail->next = new ListNode(n);
      tail->next->prev = tail;
      tail = tail->next;
    }
  };

  void PrintReverse() {
    cout << "Reverse: ";
    for (ListNode* ptr = tail; ptr != nullptr; ptr = ptr->prev) {
      cout << ptr->data << " ";
    }
    cout << endl;
  };

  void PrintForward() {
    cout << "Forward: ";
    for (ListNode* ptr = head; ptr != nullptr; ptr = ptr->next) {
      cout << ptr->data << " ";
    }
    cout << endl;
  };

  void Remove(int n) {
    ListNode* p = head;
    while (p != nullptr) {
      if (p->data == n) {
	if (p->prev != nullptr) {
	  p->prev->next = p->next;
	}
	if (p->next != nullptr) {
	  p->next->prev = p->prev;
	}
	if (p == head) head = p->next;
	if (p == tail) tail = p->prev;
	ListNode* temp = p->next;
	delete p;
	p = temp;
      } else {
	p = p->next;
      }
    }
  };

  // (a) [2 points]
  // Write MakeReverseList. Return a list whose values of the nodes are
  // in reverse order from the calling list. Make sure the nodes are separate.
  // In other words, the two lists should not share the same nodes.
  // For example, a list [1 3 5] MakeReverseList should return [5 3 1].
  // The calling list remains unchanged.
  List MakeReverseList()
  {

    List l;
    ListNode* temp;

    for(temp=head; temp!=nullptr; temp=temp->next)
    {
      l.InsertFront(temp->data);
    }

    return l;


  };

  // (b) [3 points]
  // Write RemoveEveryOther(). Remove every other node. Keep the first node,
  // remove the second, keep the third, etc. So, a list [3 5 2 4] becomes
  // [3 2]. And a list [8 4 2 1 9] becomes [8 2 9].
  void RemoveEveryOther()
  {
    ListNode* p = head;
    int x=1;
    while (p != nullptr)
    {
      if(x%2==0)
      {
        Remove(p->data);
      }

      x++;
      p=p->next;
    }
  };

};

int main() {
  List L;
  L.InsertFront(13);
  L.InsertFront(12);
  L.InsertBack(4);
  L.InsertBack(16);
  L.InsertFront(8);
  L.InsertFront(1);
  L.InsertFront(5);
  L.InsertBack(7);
  L.InsertFront(20);

  //L.PrintForward();//added
  //L.PrintReverse();//added

  List L2;
  L2 = L.MakeReverseList();

  L.PrintForward();
  L2.PrintForward();

  L2.RemoveEveryOther();

  cout << "After remove every other:" << endl;
  L2.PrintForward();
  L2.PrintReverse();

  L2.Remove(7);
  L2.RemoveEveryOther();

  cout << "After remove 7 and remove every other:" << endl;
  L2.PrintForward();
  L2.PrintReverse();

  return 0;
}

/*
Sample output:
Forward: 20 5 1 8 12 13 4 16 7
Forward: 7 16 4 13 12 8 1 5 20
After remove every other:
Forward: 7 4 12 1 20
Reverse: 20 1 12 4 7
After remove 7 and remove every other:
Forward: 4 1
Reverse: 1 4
*/
