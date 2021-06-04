#pragma once
#include<functional>

template <typename T, typename F = std::function<void(T*)>>
class unique_ptr {
	T* ptr;
	F delete_ptr;
public:
	unique_ptr(T* ptr_ = nullptr, F delete_ptr_ = [](T* ptr_) { delete ptr_; }) : ptr(ptr_), delete_ptr(delete_ptr_) {}
	~unique_ptr();
	unique_ptr(const unique_ptr& copy) = delete;
	unique_ptr& operator=(const unique_ptr& copyAss) = delete;
	unique_ptr(unique_ptr&& move_ptr) noexcept;
	unique_ptr& operator=(unique_ptr&& move_ptr) noexcept;
	constexpr void swap(unique_ptr& left, unique_ptr& right); // friend
	T* operator->() { return ptr; }
	T& operator*() { return *ptr; }
	void reset(T* t = nullptr);
};



