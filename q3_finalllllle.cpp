#include <chrono>
#include <iostream>
#include <vector>
#include <thread>
#include <random>


// I added a reference counter to hold the amount of consumers
// once the last thread decreased this ref counter to zero , I will delete the Payload and it will only happen once

struct Payload {

	Payload(uint64_t id_) :
		id(id_),
		veryLargeVector(1000 * 1000),
		ref_counter(0)
	{}
	void inc_ref_counter() {
		ref_counter++;
	}
	void dec_ref_counter() {
		ref_counter--;
		if (ref_counter == 0)
		{
			delete(this);
		}
	}
	uint64_t id;
	size_t ref_counter;
	std::vector<int> veryLargeVector;
};


void operation1(Payload* payload) {
	payload->inc_ref_counter();
	std::cout << "Performing operation1 on payload " << payload->id << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(5 + (std::rand() % (12 - 5 + 1))));  //Simulate some heavy work
	std::cout << "Operation1 Performed" << std::endl;
	payload->dec_ref_counter();
}

void operation2(Payload* payload) {
	payload->inc_ref_counter();
	std::cout << "Performing operation2 on payload " << payload->id << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(5 + (std::rand() % (12 - 5 + 1))));  //Simulate some heavy work
	std::cout << "Operation2 Performed" << std::endl;
	payload->dec_ref_counter();
}

void dispacher_thread(Payload* payload) {
	std::this_thread::sleep_for(std::chrono::seconds(2));  //Simulate some heavy work
	std::thread wt1(&operation1, payload);
	std::thread wt2(&operation2, payload);
	//Waiting for wt1 & wt2 to finish is not allowed, dispacher_thread should exit after creating wt1 and wt2
	wt1.detach();
	wt2.detach();
}

int main(int argc, char** argv)
{
	Payload* payload = new Payload(1);
	std::cout << "Calling dispatcher thread" << std::endl;
	std::thread t(&dispacher_thread, payload);
	t.join();

	std::cout << "Press enter to exit" << std::endl;
	getchar();
	return 0;
}