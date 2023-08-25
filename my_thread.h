#ifndef _MYTHREAD_H_
#define _MYTHREAD_H_

#include <pthread.h>
#include <semaphore.h>

#pragma comment(lib, "pthreadVC2.lib")

#undef main

sem_t sem;

pthread_t thGameNext,thGameInit,thActorMove,thBackgroundMove;

extern void *theadGameLast(void *argvpm);/*{
	
	return NULL;
}*/

extern void *threadBackgroundMove(void *argvpm);
extern void *threadActorMove(void *argvpm);

extern void *threadGameInit(void *argvpm);

#endif

