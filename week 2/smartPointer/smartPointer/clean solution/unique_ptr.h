#pragma once
#include<functional>

namespace smartPtr{
	/*
	template <typename T, typename F = std::function<void(T*)>>
	class smart_ptr {
		T* ptr;
		F delete_ptr;
		class shared_ptr;
		class unique_ptr;
	public:
		
		smart_ptr(T* ptr_ = nullptr, F delete_ptr_ = [](T* ptr_) { delete ptr_; }) : ptr(ptr_), delete_ptr(delete_ptr_){}
		
		~smart_ptr() { delete_ptr(this->ptr); }
		T* operator->() { return ptr; }
		T& operator*() { return *ptr; }

		void reset() {
			ptr = nullptr;
			delete_ptr = [](T* ptr) { delete ptr; };
		}
	};

	template <typename T, typename F = std::function<void(T*)>>
	class unique_ptr : public smart_ptr<T,F> {

	public:
		unique_ptr(T* ptr_, F delete_ptr_) : smart_ptr<T,F>(ptr_, delete_ptr_){}
		unique_ptr(const unique_ptr& copy) = delete;
		unique_ptr& operator=(const unique_ptr& copyAss) = delete;

		unique_ptr(unique_ptr&& move_ptr) noexcept {
			swap(*this, move_ptr);
			return *this;
		}
		void swap(const unique_ptr& left, const unique_ptr& right) {
			std::swap(left.ptr, right.ptr);
			std::swap(left.delete_ptr, right.delete_ptr);
		}
		unique_ptr& operator=(unique_ptr&& move_ptr) noexcept {
			swap(*this, move_ptr);
			return *this;
		}
		// constexpr, noexept
	};

	template <typename T, typename F = std::function<void(T*)>>
	class shared_ptr : public smart_ptr<T, F> {
		int* count_ptr = nullptr;
	public:
		shared_ptr(): count_ptr(new int(0)), smart_ptr<T, F>(){}
		shared_ptr(T* ptr_, F delete_ptr_) : count_ptr(new int(1)), smart_ptr<T, F>(ptr_, delete_ptr_) {}

		shared_ptr(const shared_ptr& copy_ptr) {
			smart_ptr<T, F>(copy_ptr.ptr, copy_ptr.delete_ptr);
			if (copy_ptr.count_ptr != nullptr) {
				copy_ptr.count_ptr++;
				count_ptr = copy_ptr.count_ptr;
			}
		}
		void swap(const shared_ptr& left, const shared_ptr& right) {
			std::swap(left.ptr, right.ptr);
			std::swap(left.delete_ptr, right.delete_ptr);
		}

		

		/*
		shared_ptr& operator=(const shared_ptr assign) {
			if (this->count_ptr == 1) {
				//reset();
			}
			swap(*this, assign);
			return *this;
		}*/
		/*
		shared_ptr& operator=(shared_ptr&& assign) {
			// case 1: if this->count is 0
			// case 2: if this-> count is 1
			// case 3: if this-> count is larger then 2
			swap_ptr(*this, assign);
			return *this;
		}

	};*/

	template <typename T, typename F = std::function<void(T*)>>
	class unique_ptr {
		T* ptr;
		F delete_ptr;

	public:
		unique_ptr(T* ptr_ = nullptr, F delete_ptr_ = [](T* ptr_) { delete ptr_; }) : ptr(ptr_), delete_ptr(delete_ptr_) {}
		~unique_ptr() { 
			std::cout << "insight unique destructor " << std::endl;
			delete_ptr(this->ptr);
		}
		unique_ptr(const unique_ptr& copy) = delete;
		unique_ptr& operator=(const unique_ptr& copyAss) = delete;

		// ----------------- does not work, can not finde the misstake 
		unique_ptr(unique_ptr&& move_ptr) noexcept {
			std::cout << "insight move constructor " << std::endl;
			swap(*this, move_ptr);
		}
		// ----------------- does not work ---------------------------------- 
		unique_ptr& operator=(unique_ptr&& move_ptr) noexcept {
			std::cout << "insight move assignement " << std::endl;
			unique_ptr<T,F> tmp(move_ptr);//move ctor
			swap(*this, tmp);
			return *this;
		}

		constexpr void swap(unique_ptr& left, unique_ptr& right) {
			std::swap(left.ptr, right.ptr);
			std::swap(left.delete_ptr, right.delete_ptr);
		}
	
		T* operator->() { return ptr; }
		T& operator*() { return *ptr; }

		void reset(T* t = nullptr) {
			delete_ptr(this->ptr);
			ptr = t;
		}
	};


	template <typename T, typename F = std::function<void(T*)>>
	class shared_ptr {
		T* ptr;
		F delete_ptr;
		std::size_t* count_ptr;
	public:
		// ----------- works -------------------------------------------------
		shared_ptr(T* ptr_ = nullptr, F delete_ptr_ = [](T* ptr_) { delete ptr_; }) :
			 ptr(ptr_), delete_ptr(delete_ptr_) {
			count_ptr = ptr_ == nullptr ? new std::size_t(0) : new std::size_t(1);

		}
		//---------- works ----------------------------
		~shared_ptr() noexcept {

			if (--*count_ptr == 0) { 
				delete_ptr(this->ptr); 
				delete (count_ptr);
			}
		}
		// ------- works -----------------------------------
		shared_ptr(const shared_ptr& copy) :ptr(copy.ptr), delete_ptr(copy.delete_ptr), count_ptr (copy.count_ptr) { // const shared_ptr& copy
			std::cout << "------------ COPY CONSTRUCTOR ----------- " << std::endl;
			++* count_ptr;
		}
		// ------------ fails ---------------------------
		shared_ptr(shared_ptr&& move_ptr) noexcept : shared_ptr() {
			swap(*this, move_ptr);
			/*
			if (*move_ptr.count_ptr == 1 || *move_ptr.count_ptr == 0) {
				swap(*this, move_ptr);
			}
			*/
		}
		constexpr std::size_t count() const { return *count_ptr; }
		void showCount() {
			std::cout << "count_ptr == " << *count_ptr << std::endl;
		}
		// ------------ fails ---------------------------
		shared_ptr& operator=(const shared_ptr& assign) { //const shared_ptr&
			std::cout << "------------ inside operator = ----------- "  << std::endl; //not insight but inside

			shared_ptr<T,F> tmp(assign);
			swap(*this, tmp);
			return *this;
		}
		// ------------ fails ---------------------------
		shared_ptr& operator=(shared_ptr&& move_ptr) {

			shared_ptr<T, F> tmp(std::move(move_ptr));
			swap(*this, tmp);
			/*
			if (*move_ptr.count_ptr == 1 || *move_ptr.count_ptr == 0) {
				shared_ptr<T, F> tmp(move_ptr); // why unique_ptr inside shared_ptr ?
				swap(*this, move_ptr);
			}
			*/
			return *this;
			// you must return a value here 
		}
		
		friend void swap(shared_ptr& left, shared_ptr& right) { // why swap takes two arguments but it's not a friend function ? -- by this way swap takes 3 arguments: *this, left, right
			std::swap(left.ptr, right.ptr);
			std::swap(left.delete_ptr, right.delete_ptr);
			std::swap(left.count_ptr, right.count_ptr);
		}

		T* operator->() { return ptr; }
		T& operator*() { return *ptr; }
	};
}
