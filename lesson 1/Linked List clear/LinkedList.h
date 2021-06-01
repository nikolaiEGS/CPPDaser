#pragma once
#ifndef LinkedList_H
#define LinkedList_H

#include<iostream>
#include<vector>
#include <stdlib.h>
#include <cstdlib>


template <typename T>
class List;

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

		const Node<T>& operator*() { return *ptr; }
		const Node<T>* operator->() { return ptr; }

		friend bool operator==(const const_iterator& l, const const_iterator& r) {
			return l.ptr == r.ptr;
		}

		friend bool operator!=(const const_iterator& l, const const_iterator& r) {
			return l.ptr != r.ptr;
		}

	};




	List() = default;
	List(const List& newElem); // works
	List(std::initializer_list<T> val); // works
	~List(); // works

	static void swapList(List& first, List& second); // works
	static List& copyList(List& destination, const List& right); // works

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
	List& operator=(List right); // works
	List& operator=(List&& right) noexcept;
	T operator[](const int index); // works
	void* operator new(const size_t count); // seems to work

	//void operator delete(const void* p); // doeas not work
	//List& operator*(List* ptr); // seems to work

	List(List&& moveElem) noexcept;

	const_iterator begin() { return const_iterator(head); }
	const_iterator end() { return const_iterator(tail); }

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
	/*std::ostream& operator<<(std::ostream& ost, const List<T>& list) {
		for (const Node* currentElem = list.head; currentElem != nullptr; currentElem = currentElem->next) {
			ost << currentElem->value << "  ,  " << std::flush;
		}
		return ost;
	}*/
};

#include "LinkedList.cpp"

#endif