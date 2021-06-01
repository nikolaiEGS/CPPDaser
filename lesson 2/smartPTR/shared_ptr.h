#pragma once
#ifndef SMART_PTR_H
#define SMART_PTR_H

#include "smart_ptr.h"
#include <utility>

namespace SMART_PTR {

	template <typename T, typename F = SMART_PTR::default_deleter<T>>
	class shared_ptr;
	template <typename T, typename F = SMART_PTR::default_deleter<T>>
	constexpr void swap(shared_ptr<T, F>&, shared_ptr<T, F>&);


	template <typename T, typename F>
	class shared_ptr : public smart_ptr<T> {
		using custom_deleter_function = F;
		custom_deleter_function custom_deleter;
		static std::size_t ref_count;
		constexpr void __release__() noexcept { custom_deleter(this->ptr); }
	public:

		friend constexpr void swap<T, F>(shared_ptr<T, F>&, shared_ptr<T, F>&);

		constexpr shared_ptr(T* ptr_ = nullptr, const custom_deleter_function& custom_deleter_ = SMART_PTR::default_deleter<T>()) : smart_ptr<T>(ptr_), custom_deleter(custom_deleter_) { ++ref_count; printRefCount(); }

		constexpr shared_ptr(const shared_ptr<T>& r) : smart_ptr<T>(r.ptr), custom_deleter(r.custom_deleter) {
			++ref_count;
			printRefCount();
		}

		constexpr shared_ptr& operator=(const shared_ptr&);

		constexpr shared_ptr(shared_ptr<T>&&) noexcept;

		constexpr shared_ptr<T>& operator=(shared_ptr<T>&&) noexcept;

		virtual ~shared_ptr() noexcept { 
			if (--ref_count == 0) {
				custom_deleter(this->ptr);
			}
		}

		void reset(T* ptr_ = nullptr) override;

		constexpr void printRefCount() const { std::cout << "ref count: " << ref_count << std::endl; }
	};
}


#include "shared_ptr.cpp"

#endif