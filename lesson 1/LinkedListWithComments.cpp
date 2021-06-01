#include<iostream>
using namespace std;

//separate hpp and cpp

template <typename T> class List {
	class Node {
	public:
		T value;
		Node* next;
		Node* prev;
		Node(T val) : value(val), next(nullptr), prev(nullptr) {} //const T&
	};

	Node* head = nullptr;
	Node* tail = nullptr;
	int size = 0;
public:

	List() = default;
	/* ------------------ does not work -----------------------------------
	List(const List& x) {
		cout << "insight List(x)" << endl;
		Node* i = nullptr;
		for (i = x.head; x.head != nullptr; i = x.head->next) {
			this->push(i->value);
		}
	}
	*/
	// --------------- works -------------------------------------------------------
	void push(T value) { // const T&
		cout << "insight push" << endl;
		Node* temp = new Node(value);
		if (head == nullptr) {
			head = temp;
			tail = temp;
		}
		else {
			tail->next = temp;
			temp->prev = tail;
			tail = temp;
		}
		size++;
	}

	T pop() { // change pop to call deleteElement(size-1) - by index
		if (head != NULL) {

			Node* temp = tail;
			if (tail->prev != nullptr) {
				tail->prev->next = nullptr;
				tail = tail->prev;
			}
			else {
				head = tail = nullptr;
			}
			T v = temp->value;
			delete temp;
			--size;

			return v;
			/*
			if (head->next == NULL) {
				Node* temp = head;
				head = nullptr;
				tail = nullptr;
				T v = temp->value;
				delete temp;
				return v;
			}
			else {
				Node* temp = tail;
				tail = tail->prev;
				tail->next = nullptr;
				T v = temp->value;
				delete temp;
				return v; // forgot size--
			}
			*/
		}
//		size--; // if head is null size == -1
	}
	// --------------------------- works ---------------------------------------
	void deleteElement(T val) { // call findElement(val), const T&
		Node* i = nullptr;
		for (i = head; i != nullptr; i = i->next) {
			
			if (i->value == val) {
				if (i->prev != nullptr) {
					i->prev->next = i->next;
				}
				else {
					head = i->next;
				}
				if (i->next != nullptr) {
					i->next->prev = i->prev;
				}
				else {
					tail = nullptr;
				}
				delete i;
				--size;
				break;
			}
			/*
			if (i->value == val) {
				// case if only one element in the List
				if (i->prev == NULL && i->next == NULL) {
					Node* temp = i;
					head = nullptr;
					tail = nullptr;
					delete temp;
					break;
				}
				// case if i is tail -------------------
				else if (i->next == NULL) {
					Node* temp = i;
					tail = tail->prev;
					tail->next = nullptr;
					delete temp;
					break;
				}
				// case if i is head --------------------------
				else if (i->prev == NULL) {
					Node* temp = i;
					head = head->next;
					head->prev = nullptr;
					delete temp;
					break;
				}
				// cas if element bitween Tail and Head --------
				else {
					Node* temp = i;
					i->prev->next = i->next;
					i->next->prev = i->prev;
					delete temp;
					break;
				}
			}
			*/
		}
//		size--; // decrement even if not deleted
	}

	// ---------- works ----------------------------------------------
	bool findElement(T val) {// change findElement to return std::vector<int> - indices of found elements, so that we can use it in delete function; overload (or add another function) of findElement(index) that returns pointer on the elem
		Node* i = nullptr;
		for (i = head; i != nullptr; i = i->next) {
			if (i->value == val) {
				return true;
			}
			else { return false; } // else should not be here 

		}
	}
	// ------------ works ---------------------------------------------
	int sizef() const { return size; } //add const

	// ------------ works (in case of print and if both lists have the same size ---------------------------
	void operator+=(const List& x) { // should return *this; const List& x; this is not +=, this is element-wise +
		if (this->size == x.sizef()) {
			Node* i = nullptr;
			Node* k = nullptr;
			for (i = this->head; i != nullptr; i = i->next) { // why 2 for loops ?
				for (k = x.head; k != nullptr; k = k->next) {
					//cout << "insight += overload ------- 2nd for loop ----------" << endl;
					//cout << "i value == " << i->value << "   k value == " << k->value << endl;
					i->value += k->value;
					//x.head = x.head->next; // why ?  : x is lost, that's why const is necessary
					break;
				}
			}
		}
	}
	//---------------------------------- works ------------------------------------------------
	bool operator==(List& x) { //const x
		if (this->size == x.sizef()) {
			cout << "--------- insight == operator ----------" << endl;
			Node* i = nullptr;
			Node* k = nullptr;
			for (i = this->head; i != nullptr; i = i->next) {
				for (k = x.head; k != nullptr; k = k->next) {
					cout << "i value == " << i->value << "   k value == " << k->value << endl;
					if (i->value != k->value) { return false; }
					x.head = x.head->next; // why ??, x is lost
					break; // wrong
				}
			}
			delete i, k; // delete nullptr ?
			return true;
		}
		else { return false; }



	}
	// ----------------- to do !! ----------------------------------------------------------------------
		//void operator=(List& x){}
	//--------------------------------------------------------------------------------------------------
	void printElements() {
		Node* i = nullptr; // const Node*; inside for loop
		for (i = head; i != nullptr; i = i->next) {
			cout << "--------- insight print ---------" << endl;
			cout << i->value << endl;
		}
		delete i; // why delete nullptr in print function ? 
	}
	// ----------------- to do !! ----------------------------------------------------------------------
	~List() {
	}
};

int main() {
	List <int> x;
	//List <int> y(x);
	List <int> k;
	k.push(4);
	k.push(8);
	k.push(9);
	k.push(2);

	
	x.push(4);
	x.push(8);
	x.push(8);
	x.push(3);
	x.push(9);
	x.printElements();

	//---- test pop function
	cout << " x size " << x.sizef() << endl;
	int help = x.pop();
	cout << "pop == "<< help << endl;
	cout << " x size " << x.sizef() << endl; // same size after pop

	x.printElements();

	
	cout << " --- test deleteElement function ------" << endl;
	x.deleteElement(9);
	x.printElements();
	//---------------------------------------------------------------
	cout << " --- test findElement function ------" << endl;
	bool test = x.findElement(8); // 8 not found
	if (test)
		cout << "element found" << endl;
	else
		cout << "element not found" << endl;
	
	//--------------------------------------------------------------------
	cout << " --- test fsize function ------" << endl;
	int s = x.sizef();
	cout << "size == " << s << endl;
	//-------------------------------------------------------------------
	cout << " --- test += operator ------" << endl;
	cout << "x\n";
	x.printElements();
	cout << "k\n";
	k.printElements();
	x += k;
	cout << "x\n";
	x.printElements();
	cout << "k\n";
	k.printElements();
	
	//--------------------------------------------------------------------
	
	cout << " --- test == operator ------" << endl;
	List <int> u;
	u.push(1);
	u.push(2);
	List <int> p;
	p.push(1);
	p.push(4);
	cout << "PPPPPPPPP\n";
	p.printElements();
	if (u == p) { cout << "equal" << endl; }
	else { cout << "not equal" << endl; }
	cout << "PPPPPPPPP\n";
	p.printElements();
	/*

	//cout << "--------- test ---------" << endl;
	//y.printElements();
	*/
}