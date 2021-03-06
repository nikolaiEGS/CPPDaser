#pragma once
#include "smart_ptr.h"
#include <utility>

namespace SMART_PTR {
	
	template <typename T, typename F = SMART_PTR::default_deleter<T>>
	class unique_ptr;
	template <typename T, typename F = SMART_PTR::default_deleter<T>>
	constexpr void swap(unique_ptr<T, F>&, unique_ptr<T, F>&);
	

	template <typename T, typename F>
	class unique_ptr : public smart_ptr<T> {
		using custom_deleter_function = F;
		custom_deleter_function custom_deleter;
	
		constexpr void __release__() noexcept { custom_deleter(this->ptr); }
	public:

		friend constexpr void swap<T, F>(unique_ptr<T, F>&, unique_ptr<T, F>&);

		constexpr unique_ptr(T* ptr_ = nullptr, const custom_deleter_function& custom_deleter_= SMART_PTR::default_deleter<T>()) : smart_ptr<T>(ptr_), custom_deleter(custom_deleter_) {}
		
		constexpr unique_ptr(const unique_ptr<T>&) = delete;
		constexpr unique_ptr& operator=(const unique_ptr&) = delete;

		constexpr unique_ptr(unique_ptr<T>&&) noexcept;

		constexpr unique_ptr<T>& operator=(unique_ptr<T>&&) noexcept;

		virtual ~unique_ptr() noexcept { __release__(); }

		constexpr void reset(T* ptr_ = nullptr) override;
	};
	
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
	constexpr unique_ptr<T>& unique_ptr<T,F>::operator=(unique_ptr<T>&& r) noexcept {
		unique_ptr tmp(std::move(r));
		swap(*this, tmp);
		return *this;
	}
	
	template<typename T, typename F>
	constexpr void unique_ptr<T, F>::reset(T* ptr_) {
		__release__();
		this->ptr = ptr_;
	}
	
}