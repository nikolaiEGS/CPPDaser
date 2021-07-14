#include <future>
#include <iostream>
#include <mutex>
#include <thread>
#include <chrono>

int factorial(std::shared_future<int> f) {
	int res = 1;
	int N = f.get();
	for (int i = N; i > 1; --i) {
		res *= i;
	}
	std::cout << "Result is: " << res << std::endl;
	return res;
}

int main() {
	int x;
	//std::thread t1(factorial, 4, std::ref(x));
	//std::future<int> fu = std::async(factorial, 4);
	std::promise<int> p;
	std::future<int> f = p.get_future();
	std::shared_future<int> sf = f.share();

	//std::future<int> fu = std::async(std::launch::async, factorial, std::ref(f)); // only one future

	std::future<int> fu = std::async(std::launch::async, factorial, sf);
	std::future<int> fu2 = std::async(std::launch::async, factorial, sf);
	std::future<int> fu3 = std::async(std::launch::async, factorial, sf);
	// so something else 
	//std::this_thread::sleep_for(std::chrono::milliseconds(20));
	p.set_value(4);

	x = fu.get();

	std::cout << "Get from child: " << x << std::endl;
	return 0;
}