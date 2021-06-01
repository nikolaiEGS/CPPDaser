
#pragma once
#ifndef _SMART_PTR_H_
#define _SMART_PTR_H_

#include "unique_ptr.h"

namespace SMART_PTR {

	template <typename TT, typename FF>
	constexpr void swap<TT, FF>(unique_ptr<TT, FF>& l, unique_ptr<TT, FF>& r) {
		std::swap(l.custom_deleter, r.custom_deleter);
		std::swap(l.ptr, r.ptr);
	}

	template<typename T, typename F>
	constexpr unique_ptr<T, F>::unique_ptr(unique_ptr<T>&& r) noexcept {
		swap(*this, r);
	}


	template<typename T, typename F>
	constexpr unique_ptr<T>& unique_ptr<T, F>::operator=(unique_ptr<T>&& r) noexcept {
		unique_ptr tmp(std::move(r));
		swap(*this, tmp);
		return *this;
	}

	template<typename T, typename F>
	void unique_ptr<T, F>::reset(T* ptr_) {
		__release__();
		this->ptr = ptr_;
	}
}
#endif