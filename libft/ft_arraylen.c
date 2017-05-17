#include "libft.h"

int	ft_arraylen(char **a)
{
    int i;
	
	i = 0;
    while (*a!= NULL)
    {
        i++;
		a++;
    }
    return(i);
}
