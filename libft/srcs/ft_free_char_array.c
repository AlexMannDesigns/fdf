
#include "libft.h"

void	ft_free_char_array(char ***char_array)
{
	int	i;
	char	**arr;

	if (!char_array || !*char_array)
		return ;
	arr = *char_array;
	i = 0;
	while (arr[i])
	{
		ft_strdel(&(arr[i]));
		i++;
	}
	free(arr);
}
