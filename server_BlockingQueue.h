#ifndef SERVER_BLOCKING_QUEUE_H
#define SERVER_BLOCKING_QUEUE_H
#include <mutex>
#include <condition_variable>
#include <queue>

//La clase Blocking Queue permite un acceso controlado a los recursos
//encolados para que cada uno de los consumidores saquen un recurso a la vez.
class BlockingQueue {
private:
	std::queue<uint> blocking_queue;
    std::mutex m;
    std::condition_variable cv;
    bool isClosed = false;
    
public:
	//Constructores para la clase Blocking Queue, se permite el constructor
	//por movimiento, no asi por copia dado que no nos interesa que una queue
	//sea copiada.
	BlockingQueue();
	BlockingQueue(BlockingQueue &&other);
    BlockingQueue& operator=(BlockingQueue&& other);
	
	//Se realiza el pop del primer elemento de la queue y lo retorna. En caso 
	//de que esté vacía, se queda esperando a que aparezca una nueva unidad
	//del recurso. En caso de que la queue esté cerrada se retorna \0.
	uint pop();

	//Se pushea el value en la cola bloqueante. Luego notifica a todos aquellos
	//que estén esperando.
	void push(uint value);
	
	void close();
	
	bool is_open() const;
	
	bool empty() const;

	~BlockingQueue();

	BlockingQueue(const BlockingQueue&) = delete;
    BlockingQueue &operator=(const BlockingQueue&) = delete;
};

#endif
