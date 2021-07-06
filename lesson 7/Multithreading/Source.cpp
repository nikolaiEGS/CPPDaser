#include <iostream>
#include <thread>
#include <string>
#include <mutex>
#include <fstream>


class Logger {
	std::ofstream os;
	std::mutex mu;
	std::mutex mu2;
public:
	Logger() {
		os.open("log.txt");
	}
	/*
	void print_m(const std::string& m, std::thread::id id, int i) {
		std::lock_guard<std::mutex> l(mu);
		std::lock_guard<std::mutex> l2(mu2);
		os << m << " " << id << " " << i << std::endl;
	}

	void print_m2(const std::string& m, std::thread::id id, int i) {
		std::lock_guard<std::mutex> l2(mu2);
		std::lock_guard<std::mutex> l(mu);
		os << m << " " << id << " " << i << std::endl;
	}
	*/
	void print_m(const std::string& m, std::thread::id id, int i) {
		std::lock(mu, mu2);
		std::lock_guard<std::mutex> l(mu, std::adopt_lock);
		std::lock_guard<std::mutex> l2(mu2, std::adopt_lock);
		os << m << " " << id << " " << i << std::endl;
	}

	void print_m2(const std::string& m, std::thread::id id, int i) {
		std::lock(mu, mu2);
		std::lock_guard<std::mutex> l2(mu2, std::adopt_lock);
		std::lock_guard<std::mutex> l(mu, std::adopt_lock);
		os << m << " " << id << " " << i << std::endl;
	}
};

/*
void print_m(const std::string& m, std::thread::id id, int i) {
	//std::lock_guard<std::mutex> l(mu);
	std::cout << m << " " << id << " " <<i << std::endl;
}
*/

void f(Logger& l) {
	for (int i = 0; i < 100; ++i) {
		l.print_m("from another thread: ", std::this_thread::get_id(), i);
	}
}

int main() {
	Logger ll;
	std::thread t(f, std::ref(ll));

	for (int i = 0; i < 100; ++i) { 
		ll.print_m("from main thread: ", std::this_thread::get_id(), i);
	}

	t.join();
	
	return 0;
}