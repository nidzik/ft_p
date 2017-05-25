/* HEADER */

#include "libft.h"

char *ft_str_sub_until(char *str, int n)
{
	int i;
	int j;
	char *ret = malloc(sizeof(char) * ft_strlen(str));

	j = 0;
	if (n == 0 || str == NULL )
		return (NULL);
	i = 0;
	while (str[i] != '\0')
		{
			if (i >= n)
				{
					ret[j] = str[i];
					j++;
				}
			i++;
		}
	ret[i] = '\0';
	if (ret == NULL || ft_strcmp(ret, "") == 0)
		return (NULL);
	return (ret);
}
