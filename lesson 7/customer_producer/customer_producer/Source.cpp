#include <iostream>
#include <condition_variable>
#include <mutex>
#include <thread>
#include <vector>
#include <chrono>

std::mutex mtx;
std::condition_variable cv_consumer, cv_producer;
bool ready_for_pop = false;

std::vector<int> storage;
bool flag = false;
int value = 0;

void consumer() {
	while (1) {

		std::unique_lock<std::mutex> lck(mtx);
		cv_producer.wait(lck, [&] {return ready_for_pop; });

		if (!storage.empty()) {
			storage.pop_back();
			--value;
			std::cout << "--- pop back ---  " << std::endl;
			ready_for_pop = false;
			//cv_consumer.notify_all();
			std::this_thread::sleep_for(std::chrono::microseconds(30));
		}
	}
}

void producer() {
	
	while (1){
	//	

		std::unique_lock<std::mutex> lck(mtx);
		//cv_consumer.wait(lck, [&] {return (!ready_for_pop); });
		std::this_thread::sleep_for(std::chrono::microseconds(20));

		if (storage.size() != 1000) {
			storage.push_back(value++);
			std::cout << "--- push: " << value << std::endl;
		}

		ready_for_pop = true;
		cv_producer.notify_all();
	}
}



int main() {

	std::thread prod(producer);
	std::thread cust(consumer);

	prod.join();
	cust.join();

	return 0;
}