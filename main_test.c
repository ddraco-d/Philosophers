#include <pthread.h>
#include <unistd.h>

//потоковая функция
void* threadFunc(void* thread_data){
	for (size_t i = 0; i < 5; i++)
	{
		write(1, "hi\n", 3);
		usleep(100000);
	}
	
	pthread_exit(0);
}

void threadFunc1(void* thread_data){
	for (size_t i = 0; i < 5; i++)
	{
		write(1, "hi1\n", 4);
		usleep(100000);
	}
	
	// pthread_exit(0);
}
 
int main(){
 
	//какие то данные для потока (для примера)
	void* thread_data = NULL;
 
	//создаем идентификатор потока
	pthread_t thread;
 
	//создаем поток по идентификатору thread и функции потока threadFunc
	//и передаем потоку указатель на данные thread_data
	pthread_create(&thread, NULL, threadFunc, thread_data);
	threadFunc1(thread_data);
	pthread_join(thread, NULL);
	//ждем завершения потока
 
	return 0;
}