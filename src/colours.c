#include "fdf.h"
#include "libft.h"
#include <stdint.h>

/*
 * Confirms a valid hex string. If the hex is invalid we just set the colour
 * to white rather than throwing an error.
 */
static int	validate_hex(char *hex)
{
	size_t	i;

	i = 0;
	while (hex[i])
	{
		if (!ft_strchr(VALID_HEX_CHARS, hex[i]))
		{
			return (FALSE);
		}
		i++;
	}
	if (i != 6 && i != 8)
	{
		return (FALSE);
	}
	return (TRUE);
}

/*
 * We use some bitwise magic to go from str to 32bit int.
 */
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

/*
 * The last byte of the number is for the alpha value or opacity.
 * This is not present in the hex strings from some test maps, so
 * in this scenario we assume 100% opacity.
 */
static uint32_t	handle_last_byte(size_t len, uint32_t val)
{
	if (len != 6)
	{
		return (val);
	}
	return ((val << 8) + 255);
}

/*
 * Validates the hexadecimal from the map file if there is one present, then
 * converts it into an integer so that it can be passed to the plot pixel
 * function.
 */
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
