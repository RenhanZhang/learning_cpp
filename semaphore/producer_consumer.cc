#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>

typedef union semunion {
  int val;
  struct semid_ds *buf;
  unsigned short *array;
} semun;

typedef semun semunion;

int sem_init(int key)
{
  int semid;
  semunion arg;

  printf("key is %d\n", key);
  semid = semget(key, 1, 0660 | IPC_CREAT); //创建一个信号量集，且只有一个信号量，控制的资源key
  if (semid < 0)
  {
    perror("semget fail!\n");
    exit(1);
  }

  arg.val = 2;
  if (semctl(semid, 0, SETVAL, arg) < 0) //设置信号量的参数val
  {
    perror("semget fail!\n");
    exit(2);
  }

  return semid;
}


int sem_pos(int semid)
{
  struct sembuf buf;
  buf.sem_num = 0;
  buf.sem_op = -1; //请求-1的绝对值个资源，
  buf.sem_flg = SEM_UNDO;

  if (semop(semid, &buf, 1) == -1)
  {
    perror("sem_op \n");
    exit(3);
  }
  printf("sem_poss success!\n");

  return 0;
}

int sem_rel(int semid)
{
  struct sembuf buf;
  buf.sem_num = 0; //这个就是信号量集中的信号量元素下标
  buf.sem_op = 1; //释放1 个资源，
  buf.sem_flg = IPC_NOWAIT;

  if (semop(semid, &buf, 1) == -1)
  {
    perror("sem_op \n");
    exit(3);
  }
  printf("sem_rel success!\n");

  return 0;
}

int sem_rmv(int semid)
{

  if (semctl(semid, 0, IPC_RMID) < 0)
  {
    perror("semctl\n");
    exit(3);
  }
  return 0;
}


int main(void)
{

  //获得关键字，这就是信号量实际控制的资源
  key_t key = ftok("./test.txt", 5);
  int semid = sem_init(key);

  if (semid < 0)
  {
    perror("semget fail!\n");
    exit(1);
  }

  int pid, n;
  char str[80];

  // 读写方式，如果文件不存在则新建，打开之后指针定位在文件尾部
  int fd = open("./test.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
  while ((pid = fork()) == -1); //创建子进程
  if (pid == 0) //child process
  {
    sleep(1); //睡眠1s
    sem_pos(semid);
    lseek(fd, SEEK_SET, 0); //定位文件
    read(fd, str, sizeof(str)); //读文件
    sem_rel(semid); //释放操作
    printf("child:read str from test file:%s\n", str);
    exit(0);
  }
  else //parent process
  {
    sem_pos(semid); //     P操作
    printf("parent:please enter a str for test file(strlen<80):\n");
    gets(str);        //输入
    n = strlen(str); // 长度
    lseek(fd, SEEK_SET, 0);   //定位
    write(fd, str, n);      //写
    sem_rel(semid); //释放
    wait(0);
    close(fd); //关闭文件
    sem_rmv(semid); //删除信号量
    exit(0);
  }
  return (0);
}