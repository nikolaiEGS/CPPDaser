#include <iostream>
#include <condition_variable>
#include <mutex>
#include <thread>
#include <vector>

std::mutex mtx;
std::condition_variable cv;
bool ready_for_pop = false;

std::vector<int> storage;
bool flag = false;

void consumer() {
	while (1) {
		if (flag && storage.empty()) { break; }

		std::unique_lock<std::mutex> lck(mtx);
		cv.wait(lck, [&] {return ready_for_pop; });

		if (!storage.empty()) {
			storage.pop_back();
			std::cout << "--- pop back ---" << std::endl;
		}
	}
}

void producer() {

	for (int i = 0; i < 1000; ++i) {
		std::unique_lock<std::mutex> lck(mtx);
		storage.push_back(i);

		std::cout << "--- push: "<< i << std::endl;

		ready_for_pop = true;
		cv.notify_all();
	}
	flag = true;
}



int main() {

	std::thread prod(producer);
	std::thread cust(consumer);

	prod.join();
	cust.join();

	return 0;
}