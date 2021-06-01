#pragma once
#ifndef LinkedList_H
#define LinkedList_H

#include<iostream>
#include<vector>
#include <stdlib.h>
#include <cstdlib>


template <typename T>
class List;

//put Node inside LinkedList
template <typename T>
struct Node {
	T value;
	Node<T>* next;
	Node<T>* prev;
	Node() : value(), prev{ nullptr }, next{ nullptr } {}
	explicit Node(const T& val) : value{ val }, next{ nullptr }, prev{ nullptr } {}
};

/*
template <typename T>
class ListIterator {
	Node<T>* currentElem;
public:

	ListIterator(const Node<T>* ptr) : currentElem(ptr) {}
	///////
	/*
	Node<T> operator->() {
		return currentElem;
	}*/
	/*
		bool operator!=(const ListIterator<T>& right) {
			if (currentElem != right)
				return true;
			else
				return false;
		}
		/*
		ListIterator<T>& operator++(ListIterator<T>& right) {
			right.currentElem = right.currentElem->next;
			return *right;
		}
		*/
		//};

template <typename T>
class List {
	Node<T>* head{ nullptr };
	Node<T>* tail{ nullptr };
	std::size_t size = 0;
	void releaseList();
public:

	class const_iterator {
		const Node<T>* ptr;

	public:
		const_iterator(const Node<T>* ptr_ = nullptr) : ptr(ptr_) {};

		const const_iterator& operator++() {
			if (ptr != nullptr) {
				ptr = ptr->next;
			}

			return *this;
		}

		const const_iterator& operator--() {
			if (ptr != nullptr) {
				ptr = ptr->prev;
			}

			return *this;
		}

		const Node<T>& operator*() const { return *ptr; }
		const Node<T>* operator->() const { return ptr; }

		friend bool operator==(const const_iterator& l, const const_iterator& r) {
			return l.ptr == r.ptr;
		}

		friend bool operator!=(const const_iterator& l, const const_iterator& r) {
			return l.ptr != r.ptr;
		}

	};

	// write iterator
	// replace all accesses by iterator


	List() = default;
	List(const List& newElem); // works
	List(std::initializer_list<T> val); // works
	~List(); // works

	template<typename T>
	friend void swap(List<T>& first, List<T>& second); // works -- make it friend, and name it swap, not swapList
	static List& copyList(List& destination, const List& right); // works - should not be static and should be in private

	void push(const T& value); // works
	void pop(); // works
	void deleteElement_byIndex(const int index, bool reverseIterator); // works
	void deleteElement_byIndex(std::vector<int> values); // works
	void deleteElement_byValue(const int& val, bool allElem); // works
	Node<T>* findElement_byIndex(const int index, bool reverseIterator); // works
	std::vector<int> findElement_byValue(const T& val) const; // works
	std::size_t sizef() const; // works
	void reverse(); // works
	void printElements() const; // works

	List& operator+=(const List& x); // works
	bool operator==(const List& right) const; // works
	bool operator!=(const List& right) const; // works
	List operator+(const List<T>& right); // works
	List& operator=(const List& right); // works
	List& operator=(List&& right) noexcept;

	
	T operator[](const int index); // works // return type is wrong
	
	void* operator new(const size_t count); // seems to work
	void operator delete(void* p); // doeas not work
	//List& operator*(List* ptr); // seems to work

	List(List&& moveElem) noexcept;

	//const_iterator begin() { return const_iterator(head); }
	//const_iterator end() { return const_iterator(tail); }
	Node<T> * begin() { return head; }
	const Node<T>* begin() const { return head; }
	Node<T>* end() { return tail->next; }
	const Node<T>* end() const { return tail->next; }

	void testPrint() {
		if (head != nullptr) {
			
			for (const_iterator Iterator = begin(); Iterator != end(); ++Iterator) {
				std::cout << " test   ";
				std::cout <<  "VALUE *: " << (*Iterator).value <<std::endl;
				std::cout <<  "VALUE ->: " << Iterator->value << std::endl;
			}
			std::cout << std::endl;
			
		}
	}
	
	// --------- does not work ------------------------------------------------------------
	friend std::ostream& operator<<(std::ostream& ost, const List<T>& list) {
		if (list.head != nullptr) {
			for (const_iterator Iterator = list.begin(); Iterator != list.end(); ++Iterator) {
				std::cout << Iterator->value << ",";
			}
			std::cout << std::endl;
		}
		return ost;
	}
};

#include "LinkedList.cpp"

#endif