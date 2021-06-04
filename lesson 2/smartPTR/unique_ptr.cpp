/*
#pragma once
#include "unique_ptr.h"

namespace SMART_PTR {
	template <typename TT, typename FF>
	void swap<TT, FF>(unique_ptr<TT, FF>& l, unique_ptr<TT, FF>& r) {
		std::swap(l.custom_deleter, r.custom_deleter);
		std::swap(l.ptr, r.ptr);
	}

	template<typename T, typename F>
	inline unique_ptr<T, F>::unique_ptr(unique_ptr<T>&& r) noexcept {
		swap(*this, r);
	}


	template<typename T, typename F>
	inline unique_ptr<T>& unique_ptr<T, F>::operator=(unique_ptr<T>&& r) noexcept {
		unique_ptr tmp(std::move(r));
		swap(*this, tmp);
		return *this;
	}

	template<typename T, typename F>
	inline void unique_ptr<T, F>::reset(T* ptr_) {
		this->ptr = ptr_;
	}
};

*/
//namespace SMART_PTR {
	/*
	template <typename T, typename F = SMART_PTR::default_deleter<T>>
	class unique_ptr;
	template <typename T, typename F = SMART_PTR::default_deleter<T>>
	void swap(unique_ptr<T, F>&, unique_ptr<T, F>&);
	*/
	/*
	template <typename TT, typename FF>
	void swap<TT, FF>(unique_ptr<TT, FF>& l, unique_ptr<TT, FF>& r) {
		std::swap(l.custom_deleter, r.custom_deleter);
		std::swap(l.ptr, r.ptr);
	}

	template<typename T, typename F>
	inline unique_ptr<T, F>::unique_ptr(unique_ptr<T>&& r) noexcept {
		swap(*this, r);
	}


	template<typename T, typename F>
	inline unique_ptr<T>& unique_ptr<T, F>::operator=(unique_ptr<T>&& r) noexcept {
		unique_ptr tmp(std::move(r));
		swap(*this, tmp);
		return *this;
	}

	template<typename T, typename F>
	inline void unique_ptr<T, F>::reset(T* ptr_) {
		this->ptr = ptr_;
	}
	*/
	/*
	template <typename TT, typename FF>
	void SMART_PTR::swap<TT, FF>(SMART_PTR::unique_ptr<TT, FF>& l, SMART_PTR::unique_ptr<TT, FF>& r) {
		std::swap(l.custom_deleter, r.custom_deleter);
		std::swap(l.ptr, r.ptr);
	}

	template<typename T, typename F>
	inline SMART_PTR::unique_ptr<T, F>::unique_ptr(SMART_PTR::unique_ptr<T>&& r) noexcept {
		swap(*this, r);
	}


	template<typename T, typename F>
	inline SMART_PTR::unique_ptr<T>& SMART_PTR::unique_ptr<T, F>::operator=(SMART_PTR::unique_ptr<T>&& r) noexcept {
		unique_ptr tmp(std::move(r));
		swap(*this, tmp);
		return *this;
	}

	template<typename T, typename F>
	inline void SMART_PTR::unique_ptr<T, F>::reset(T* ptr_) {
		this->ptr = ptr_;
	}

	*/
//};
