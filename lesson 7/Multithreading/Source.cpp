#include <iostream>
#include <thread>
#include <string>
#include <mutex>
#include <fstream>


class Logger {
	std::ofstream os;
	std::mutex mu;

public:
	Logger() {
		os.open("log.txt");
	}
	void print_m(const std::string& m, std::thread::id id, int i) {
		std::lock_guard<std::mutex> l(mu);
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