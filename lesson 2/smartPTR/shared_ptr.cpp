#pragma once
#ifndef _SMART_PTR_H_
#define _SMART_PTR_H_

#include "shared_ptr.h"

namespace SMART_PTR {

	template <typename TT, typename FF>
	std::size_t shared_ptr<TT, FF>::ref_count = 0; /// failed solution

	template <typename TT, typename FF>
	constexpr void swap<TT, FF>(shared_ptr<TT, FF>& l, shared_ptr<TT, FF>& r) {
		std::swap(l.custom_deleter, r.custom_deleter);
		std::swap(l.ptr, r.ptr);
	}

	template<typename T, typename F>
	constexpr shared_ptr<T, F>::shared_ptr(shared_ptr<T>&& r) noexcept {
		swap(*this, r);
	}


	template<typename T, typename F>
	constexpr shared_ptr<T>& shared_ptr<T, F>::operator=(shared_ptr<T>&& r) noexcept {
		shared_ptr tmp(std::move(r));
		swap(*this, tmp);
		return *this;
	}

	template<typename T, typename F>
	void shared_ptr<T, F>::reset(T* ptr_) {
		__release__();
		this->ptr = ptr_;
	}
}
#endif