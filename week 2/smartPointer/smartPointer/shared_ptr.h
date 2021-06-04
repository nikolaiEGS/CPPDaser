#pragma once
#include<functional>

template <typename T, typename F = std::function<void(T*)>>
class shared_ptr {
	T* ptr;
	F delete_ptr;
	std::size_t* count_ptr;
public:
	// ----------- works -------------------------------------------------
	shared_ptr(T* ptr_ = nullptr, F delete_ptr_ = [](T* ptr_) { delete ptr_; }) :
		ptr(ptr_), delete_ptr(delete_ptr_);
	~shared_ptr() noexcept;
	shared_ptr(const shared_ptr& copy) : ptr(copy.ptr), delete_ptr(copy.delete_ptr), count_ptr(copy.count_ptr);
	shared_ptr(shared_ptr&& move_ptr) noexcept : shared_ptr(); // works, but problem is arising  becouse of definition outside of the class
	constexpr std::size_t count() const;
	shared_ptr& operator=(shared_ptr& assign);
	shared_ptr& operator=(shared_ptr&& move_ptr) noexcept;
	T* operator->() { return ptr; }
	T& operator*() { return *ptr; }
	template <typename T, typename F = std::function<void(T*)>>
	friend void swap(shared_ptr<T,F>& left, shared_ptr<T,F>& right);
};
