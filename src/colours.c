#include "fdf.h"
#include "libft.h"
#include <stdint.h>

static int	validate_hex(char *hex)
{
	size_t	i;

	i = 0;
	while (hex[i])
	{
		if (!ft_strchr("0123456789abcdefABCDEF", hex[i]))
		{
			return (FALSE);
		}
		i++;
	}
	return (TRUE);
}
	
static size_t	hex_conversion_loop(char *hex, uint32_t *val)
{
	size_t	i;
	uint8_t	byte;

	i = 0;
	while (hex[i])
	{
		byte = hex[i];
		if (byte >= '0' && byte <= '9')
		{
			byte = byte - '0';
		}
		else if (byte >= 'A' && byte <='F')
		{
			byte = byte - 'A' + 10;
		}
		*val = (*val << 4) | (byte & 0xF);
		i++;
	}
	return (i);
}

static uint32_t	handle_last_byte(size_t len, uint32_t val)
{
	if (len != 6)
	{
		return (val);
	}
	return ((val << 8) + 255);
}

uint32_t	get_colour(char *hex)
{
	uint32_t	val;
	size_t		len;

	if (!validate_hex(hex))
	{
		return (COLOUR);
	}
	val = 0;
	len = hex_conversion_loop(hex, &val);
	return (handle_last_byte(len, val));
}

