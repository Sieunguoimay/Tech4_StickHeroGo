#include<iostream>
#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

template<class T>
struct ListNode {
	ListNode(ListNode<T>*prev, ListNode<T>*next,T data) 
		:prev(prev),next(next),data(data){}
		
	ListNode<T>*next;
	ListNode<T>*prev;
	T data;
};

//list implemented by doubly linked list
template<class T>
class List {
public:
	List() {
		head = new ListNode<T>(NULL, NULL, (T)0);
		tail = new ListNode<T>(head, NULL, (T)0);
		head->next = tail;
		n = 0;
	}
	~List() {
		//what if type of data is a dynamic pointer
		clear();
	
		delete head;
		delete tail;
		head = NULL;
		tail = NULL;
		n = 0;
	}

	ListNode<T>* erase(ListNode<T>*pointer) {
		
		ListNode<T>*temp = pointer->prev;
		
		pointer->next->prev = pointer->prev;
		pointer->prev->next = pointer->next;
		
		pointer->next = NULL;
		pointer->prev = NULL;
		
		delete pointer;
		pointer = NULL;
		n--;
		return temp;	
	}
		//insert after a given ListNode
	void insert(ListNode<T>*pointer, T data) {
		ListNode<T>*newListNode = new ListNode<T>(pointer, pointer->next, data);
		newListNode->next->prev = newListNode;
		newListNode->prev->next = newListNode;
		n++;
	}
	
	inline void push_back(T data) {insert(tail->prev, data);}
	inline void push_front(T data) {insert(head, data);}
	inline void pop_front() {if (head->next != tail)erase(head->next);}
	inline void pop_back() {if (tail->prev != head) erase(tail->prev);}
	bool clear() {
		for (ListNode<T>*iter = head->next; iter != tail; iter = iter->next)
			iter = erase(iter);
		return true;
	}

	inline bool empty(){return(n == 0);}
	inline int size()const {return this->n;}

	inline ListNode<T>*first() { return head->next; }
	inline ListNode<T>*last() { return tail->prev; }

	//two controling ListNodes
	ListNode<T>*head;
	ListNode<T>*tail;
	int n;
};

#endif // !DOUBLY_LINKED_LIST_H
