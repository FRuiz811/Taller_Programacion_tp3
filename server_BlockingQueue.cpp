#include "server_BlockingQueue.h"
#include <utility>
#include <iostream>

BlockingQueue::BlockingQueue() : isClosed(false) {}

uint BlockingQueue::pop() {
	std::unique_lock<std::mutex> lock(m);
	while(blocking_queue.empty()){
		if(isClosed){
			throw std::exception();
		}
		cv.wait(lock);
	}
	uint value = blocking_queue.front();
	blocking_queue.pop();
	return value;
}

void BlockingQueue::push(uint value) {
	std::unique_lock<std::mutex> lock(m);
	blocking_queue.push(value);
	cv.notify_all();
}

void BlockingQueue::close() {
	std::unique_lock<std::mutex> lock(m);
	isClosed = true;
	cv.notify_all();
}

bool BlockingQueue::is_open() const {
	std::unique_lock<std::mutex> lock(m);
	return !this->isClosed;
}

bool BlockingQueue::empty() const {
	std::unique_lock<std::mutex> lock(m);
	return this->blocking_queue.empty();
}


BlockingQueue::BlockingQueue(BlockingQueue &&other) {
	std::unique_lock<std::mutex> lock(m);
    this->blocking_queue = std::move(other.blocking_queue);
}

BlockingQueue& BlockingQueue::operator=(BlockingQueue &&other) {
	std::unique_lock<std::mutex> lock(m);
    this->blocking_queue = std::move(other.blocking_queue);
    return *this;
}

BlockingQueue::~BlockingQueue(){}
