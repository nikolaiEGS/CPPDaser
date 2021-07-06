#pragma once
#include<functional>

template <typename T, typename F = std::function<void(T*)>>
class shared_ptr {
	T* ptr;
	F delete_ptr;
	std::size_t* count_ptr;
public:
	shared_ptr(T* ptr_ = nullptr, F delete_ptr_ = [](T* ptr_) { delete ptr_; }) :
		count_ptr{ (ptr_ == nullptr) ? new std::size_t(0) : new std::size_t(1) },
		ptr{ ptr_ }, delete_ptr{ delete_ptr_ }{}
	~shared_ptr() noexcept;
	shared_ptr(const shared_ptr& copy);
	shared_ptr(shared_ptr&& move_ptr) noexcept;
	constexpr std::size_t count() const;
	shared_ptr& operator=(shared_ptr& assign);
	shared_ptr& operator=(shared_ptr&& move_ptr) noexcept;
	T* operator->() { return ptr; }
	T& operator*() { return *ptr; }

	template <typename T, typename F>
	friend void swap(shared_ptr<T,F>& left, shared_ptr<T,F>& right);
};
