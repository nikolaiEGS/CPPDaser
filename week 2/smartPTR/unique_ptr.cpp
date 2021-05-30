#include "unique_ptr_.h"


namespace smart_ptr {
	/*
	template<class T, class F>
	void unique_ptr_<T[], F>::reset(T* ptr_) {
		this->ptr = ptr_;
	}
	*/
	/*
	template <typename T, typename F>
	class unique_ptr_ : public smart_ptr_<T, F>{
		using custom_deleter_function = F;
	public:
		unique_ptr_(T* ptr_, custom_deleter_function custom_deleter_ = [](T* p) { delete p; std::cout << "deleted: " << p; }) : smart_ptr_<T, F>(ptr_, custom_deleter_) {}

		void reset(T* ptr_) override {
			this->ptr = ptr_;
		}
	};
	

	template <typename T, typename F>
	class unique_ptr_<T[], F> : public smart_ptr_<T[], F> {
		using custom_deleter_function = F;
	public:
		unique_ptr_(T* ptr_, custom_deleter_function custom_deleter_ = [](T* p) { delete[] p; std::cout << "deleted[]: " << p; }) : smart_ptr_<T, F>(ptr_, custom_deleter_) {}

		void reset(T* ptr_) override {
			this->ptr = ptr_;
		}
	};
	*/
	/*
	template <typename T, typename F >
	class unique_ptr_<T[], F> : public smart_ptr_<T[], F> {
		using custom_deleter_function = F;
	public:
		unique_ptr_(T* ptr_, custom_deleter_function custom_deleter_ = [](T* p) { delete[] p; std::cout << "deleted[]: " << p; }) : smart_ptr_<T[], F>(ptr_, custom_deleter_) {}

		void reset(T* ptr_) override {
			this->ptr = ptr_;
		}
	};
	*/



}