// This piece of code implements the producer/consumer problems.
// It uses the semaphore to sync the producer and consumer
// processes. It uses shared memory for inter-process data
// communication.
// This is a 1 producer, multiple consumers impl.

#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>

#define FULL_SEM 0        // Index of the Full semaphore
#define EMPTY_SEM  1      // Index of the Empty semaphore
#define CONSUMER_PTR 2
#define BUFFER_SIZE 128   // Size of the queue

#define SET_SEM_VAL(sem)                              \
    if (semctl(semid, sem, SETVAL, arg) < 0) {   \
      perror("semget fail!\n");                       \
      exit(1);                                        \
    }                                                 \

union semunion {
  int val;
  struct semid_ds *buf;
  unsigned short *array;
};

int sem_init(int key)
{
  int semid;
  semunion arg;

  semid = semget(key, 3, 0660 | IPC_CREAT);
  if (semid < 0) {
    perror("Failed to create semaphore.");
    exit(1);
  }

  arg.val = 0;
  SET_SEM_VAL(FULL_SEM);

  arg.val = BUFFER_SIZE;
  SET_SEM_VAL(EMPTY_SEM);

  arg.val = 1;
  SET_SEM_VAL(CONSUMER_PTR);

  return semid;
}


int sem_wait(int semid, int sub)
{
  struct sembuf buf;
  buf.sem_num = sub;     // the index of the semaphore in the set
  buf.sem_op = -1;       // to decrement value by 1
  buf.sem_flg = SEM_UNDO;

  if (semop(semid, &buf, 1) == -1) {
    perror("Failed to decrement.\n");
    exit(3);
  }

  return 0;
}

int sem_signal(int semid, int sub)
{
  struct sembuf buf;
  buf.sem_num = sub;
  buf.sem_op = 1;
  buf.sem_flg = IPC_NOWAIT;

  if (semop(semid, &buf, 1) == -1) {
    perror("Failed to increment.\n");
    exit(3);
  }

  return 0;
}

void producer(int semid, int* buffer) {
  int i = 0;

  while (true) {
    sem_wait(semid, EMPTY_SEM);

    buffer[i] =  i;
    printf("Parent: producing int :%i\n", buffer[i]);

    i = (i + 1) % BUFFER_SIZE;

    sem_signal(semid, FULL_SEM);
  }
}

void spawn_consumer(int semid, key_t key) {
  // Create child process.  
  int pid;
  while ((pid = fork()) == -1);
  if (pid != 0) {
    return;
  }

  // Create shared memory
  int shmid = shmget(key, 1024, 0666 | IPC_CREAT);
  int *buffer = (int*) shmat(shmid, (void*)0, 0);

  while (true) {
    sem_wait(semid, FULL_SEM);
    // mutex for the consumer ptr, namely buffer[BUFFER_SIZE]
    sem_wait(semid, CONSUMER_PTR);   
    int i = buffer[BUFFER_SIZE];
    printf("Child %i: consuming int :%i\n", getpid(), buffer[i]);
    buffer[BUFFER_SIZE] = (i + 1) % BUFFER_SIZE;
    sem_signal(semid, CONSUMER_PTR);
    sem_signal(semid, EMPTY_SEM);
  }
}


int main(void)
{
  key_t key = ftok("./test.txt", 5);

  // Create semaphore
  int semid = sem_init(key);

  // Create shared memory
  // The first BUFFER_SIZE elements in the buffer will be the actual data.
  // The (BUFFER_SIZE + 1)th element will be the index of the "next"
  // available element to consumer.
  int shmid = shmget(key, 1024, 0666 | IPC_CREAT);
  int* buffer = (int*) shmat(shmid, (void*)0, 0);
  // Set the "current" index for the consumer.
  buffer[BUFFER_SIZE] = 0;

  for (int i = 0; i < 5; i++) {
    spawn_consumer(semid, key);
  }

  producer(semid, buffer);
  return (0);
}