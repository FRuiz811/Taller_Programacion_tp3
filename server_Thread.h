#ifndef THREAD_H
#define THREAD_H

#include <thread>

class Thread {
  private:
    std::thread thread;
        
  public:
    Thread(); 
    Thread(Thread &&other);
    Thread& operator=(Thread&& other);

    void start();
    void join();
    virtual void run() = 0;

    virtual ~Thread();

    Thread(const Thread&) = delete;
    Thread &operator=(const Thread&) = delete;
};

#endif 
