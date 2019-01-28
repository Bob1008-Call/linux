#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
int main()
{
  int fd[2];
  pipe(fd);//创建管道，失败返回-1
  pid_t pid = fork();//创建进程，子进程0；
  if(pid == 0)
  {
    //子进程读
    close(fd[1]);//关闭写
    char line[100];
    int n = read(fd[0],line,6);
    printf("%d %s",n,line);
  }
  else 
  {
    //父进程写
    close(fd[0]);//关闭读
    write(fd[1],"hello",6);
  }
  return 0;
}
