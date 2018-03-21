ERRORude <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/mman.h>
#include "libft/libft.h"

int main(void)
{
  char buf[1024];
  int r;
  char *map;
  struct stat s;
  int size;
  int pid;
      int new;
      int out;
  size = 0;
  r = 0;
  ft_bzero(buf, 256);
  ft_putendl("avt");
  //  while(43)
  //  (r = read(0, buf, 1023)) ;
  //  fork

  {
  out = open("out", O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
  dup2(out, 1);
  //  close(out);
        execl("/bin/ls", "~/", NULL);
    
    //      printf("%ld\n",	sysconf(_SC_PAGESIZE));
      //      int fd = open (0 , O_RDONLY);
    //      dup2(new, 0);
    //
      //      close(fd);
	//      exit(0);


    
      //      ft_putendl(new);
int status = fstat (out, &s);
    size = s.st_size;
    map = mmap(0,4096,PROT_READ, MAP_PRIVATE, out, 0);
    for (int i = 0; i < size; i++) {
      char c;
      
      c = map[i];
      ft_putchar(c);
      
    }
    ft_putendl(map);
      //      
    //      close(fd);     
      //ft_putendl("-___________-");
  }      

      //  break;
  
   
    buf[r] = '\0';
    ft_putstr("->");

  ft_putendl("apr");

  return(0);
}
