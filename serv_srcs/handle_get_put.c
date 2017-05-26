/*	HEADER	*/

#include "ft_p.h"

int handle_get(char *cmd, t_env *e)
{
    int r;
    char buf[BUFSIZE];
    int file;

    ft_putendl("ft_get");
    ft_bzero(buf,BUFSIZE);
    r = 0;
    if ((file = open(ft_strtrim(ft_str_sub_until(cmd, 4)), O_RDONLY)) > 0){
        while (( r  = read(file, buf,BUFSIZE)) != EOF)
            {
            if (r < 0)
                exit_error("Erorr reading buf");
            write(SK, buf, r);
            ft_bzero(buf,BUFSIZE);
            if (r != BUFSIZE)
                break;
            r = 0;
        }
    }
return (0);
}

int handle_put(char *cmd, t_env *e)
{
    int file;
    int r;
    char buf[BUFSIZE];
    char *namefile;

    namefile = ft_strtrim(ft_str_sub_until(cmd, 4));
  ft_putendl(namefile);
    if ((file = open(ft_strtrim(ft_str_sub_until(cmd, 4)), O_WRONLY | O_CREAT, S_IRUSR | \
S_IWUSR)) < 0 )
    {
        ft_putendl("ERROR can't open the file");
        return(1);
    }
    ft_bzero(buf,BUFSIZE);
	write(SK,"OK\0",3);
    ft_putchar('.');
	while ((r = read(SK, buf, BUFSIZE)) >= 0 )
	write(file, buf, r);
	if (r < 0)
	ft_putendl("eror read ");
    close(file);
    ft_putendl("closing file oklm");
	return (0);
}
