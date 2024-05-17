/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsilva-r <vsilva-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 12:00:17 by vsilva-r          #+#    #+#             */
/*   Updated: 2024/05/07 17:47:25 by vsilva-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#define FLAGS "-#0+ "
#define LENGTH "hlLz"
#define CONVS "idoxXucsp%"
#define NUMBERS "idoxXu"
#define DIGITS "0123456789"
#define DOT '.'
#define ZEROS "00000000000000000000000000000000000000000000000000000000000000"
/*
	Precision overrides 0
	- overrides 0
	+ overrides [space]
	+ not with o or x/X
	[space] not with o or x/X
	# only with o and x/X

*/

static int	get_field(const char *format)
{
	int	field;

	field = 0;
	while (ft_strchr(FLAGS, *format))
		format++;
	while (ft_strchr(LENGTH, *format))
		format++;
	while (ft_strchr(DIGITS, *format))
	{
		field = field * 10 + (int)(*format - '0');
		format++;
	}
	if (*format == DOT)
		format++;
	while (ft_strchr(DIGITS, *format))
		format++;
	if (ft_strchr(CONVS, *format))
		return (field);
	else
		return (-1);
}

static int	get_precision(const char *format)
{
	int	precision;

	precision = 0;
	while (ft_strchr(FLAGS, *format))
		format++;
	while (ft_strchr(LENGTH, *format))
		format++;
	while (ft_strchr(DIGITS, *format))
		format++;
	if (*format == DOT)
		format++;
	while (ft_strchr(DIGITS, *format))	
	{
		precision = precision * 10 + (int)(*format - '0');
		format++;
	}
	if (ft_strchr(CONVS, *format))
		return (precision);
	else
		return (-1);
}

/*
static int	get_nsize(char *nstr, int field, int precision, char type, int hash, int plus_space, int zero)
{
	int	nsize;
	
	nsize = ft_strlen(nstr);
	if (hash && ft_strchr("oxX", type))
		nsize += 2;
	else if (plus_space && ft_strchr("di", type))
		nsize += 1;
	if (precision > nsize)
		nsize = precision;	
	if (zero && field > nsize)
		nsize = field;
	return (nsize);
}
*/
static char	ft_formattype(const char *format)
{
	while (ft_strchr(FLAGS, *format))
		format++;
	while (ft_strchr(LENGTH, *format))
		format++;
	while (ft_strchr(DIGITS, *format))
		format++;
	if (*format == DOT)
		format++;
	while (ft_strchr(DIGITS, *format))
		format++;
	if (ft_strchr(CONVS, *format))
		return (*format);
	else
		return (0);
}

static int	ft_formatchr(const char *format, char chr)
{
	while (ft_strchr(FLAGS, *format))
	{
		if (*format == chr)
			return (1);
		format++;
	}
	while (ft_strchr(LENGTH, *format))
	{
		if (*format == chr)
			return (1);
		
		format++;
	}
	while (ft_strchr(DIGITS, *format))
		format++;
	if (*format == DOT)
		format++;
	while (ft_strchr(DIGITS, *format))
		format++;
	if (ft_strchr(CONVS, *format) && *format == chr)
		return (1);
	else
		return (0);
}
/*
static int	do_hashplusspace(char *format, char conv, va_list args)
{
	int	written;
	int	nbr;

	if (ft_formatchr(format, '#'))
	{
		if (conv == 'o')
			ft_putstr("0"), written++;
		else if (conv == 'x')
			ft_putstr("0x"), written += 2;
		else if (conv == 'X')
			ft_putstr("0X"), written += 2;
	}
	else if (ft_formatchr(format, '+') && ft_strchr("di", conv))
	{
		nbr = va_arg(args, int);
		if (nbr >= 0)
			ft_putchar('+'), written++;
	}
	else if (ft_formatchr(format, ' ') && ft_strchr("di", conv))
	{
		nbr = va_arg(args, int);
		if (nbr >= 0)
			ft_putchar(' '), written++;
	}
}
*/

static int	read_hash(const char *format, char conv, int nbr)
{
	int	hash;
	int	plus_space;

	plus_space = ft_formatchr(format, '+') ||  ft_formatchr(format, ' ');
	hash = ft_formatchr(format, '#');
	if (conv == 'o' && hash)
		return (1);
	if (ft_strchr("xX", conv) && hash)
		return (2);
	if (nbr < 0)
		return (1);
	else if (ft_strchr("di", conv) && plus_space)
		return (1);
	else
		return (0);
}
static size_t	get_printsize(const char *format, char conv, char *nstr, int nbr)
{
	int	field;
	int	precision;
	int	len;

	field = get_field(format);
	precision = get_precision(format);
	len = ft_strlen(nstr) + read_hash(format, conv, nbr);
	if (precision < len)
		precision = len;
	if (field < precision)
		field = precision;
	return (field);
}

static char	*get_intstr(const char *format, char *str, int nbr, int precision, int field)
{
	char	*nstr;
	int	nsize;

	ft_putstr("CHECKPT 0\n");
	if (nbr < 0)
	{
		str = "-";
		nbr = -nbr; // fix for limits later
	}
	else if (ft_formatchr(format, '+'))
		ft_strlcat(str, "+", 1);
	else if (ft_formatchr(format, ' '))
		ft_strlcat(str, " ", 1);
	ft_putstr("CHECKPT 1\n");
	nstr = ft_itoa(nbr);
	ft_putstr("CHECKPT 2\n");
	nsize = ft_strlen(nstr);
	ft_putstr("CHECKPT 3\n");
	if (precision < 0)
	{
		if (ft_formatchr(format, '0') && !ft_formatchr(format, '-'))
			precision = field - nsize;
		else
			precision = 0;
	}
	else if (precision >= nsize)
		precision -= nsize;
	ft_putstr("CHECKPT 4\n");
	while (ft_strlen(str) < (size_t) precision)
		ft_strlcat(str, ZEROS, precision + 1);
	str = ft_strjoin(str, nstr);
	free(nstr), nstr = NULL;
	return (str);
}

static char	*get_uintstr(const char *format, char *str, unsigned nbr, int precision, int field)
{
	char	*nstr;
	int	nsize;

	nstr = ft_itoa(nbr);
	nsize = ft_strlen(nstr);
	if (precision < 0)
	{
		if (ft_formatchr(format, '0') && !ft_formatchr(format, '-'))
			precision = field - nsize;
		else
			precision = 0;
	}
	else if (precision >= nsize)
		precision -= nsize;
	while (ft_strlen(str) < (size_t) precision)
		ft_strlcat(str, "0", precision + 1);
	str = ft_strjoin(str, nstr);
	free(nstr), nstr = NULL;
	return (str);
}

static char	*get_octstr(const char *format, char *str, int nbr, int precision, int field)
{
	char	*nstr;
	int	nsize;

	if (ft_formatchr(format, '#'))
		ft_strlcat(str, "0", 1);
	nstr = ft_itoa_base(nbr, OCT);
	nsize = ft_strlen(nstr);
	if (precision < 0)
	{
		if (ft_formatchr(format, '0') && !ft_formatchr(format, '-'))
			precision = field - nsize;
		else
			precision = 0;
	}
	else if (precision >= nsize)
		precision -= nsize;
	while (ft_strlen(str) < (size_t) precision)
		ft_strlcat(str, "0", precision + 1);
	str = ft_strjoin(str, nstr);
	free(nstr), nstr = NULL;
	return (str);
}

static char	*get_hexstr(const char *format, char *str, int nbr, int precision, int field)
{
	char	*nstr;
	int	nsize;
	int	X;

	X = ft_formatchr(format, 'X');
	if (ft_formatchr(format, '#'))
	{
		if (X)
			ft_strlcat(str, "0X", 1);
		else
			ft_strlcat(str, "0x", 1);
	}
	if (X)
		nstr = ft_itoa_base(nbr, HEXU);
	else
		nstr = ft_itoa_base(nbr, HEXL);
	nsize = ft_strlen(nstr);
	if (precision < 0)
	{
		if (ft_formatchr(format, '0') && !ft_formatchr(format, '-'))
			precision = field - nsize;
		else
			precision = 0;
	}
	else  if (precision >= nsize)
		precision -= nsize;
	while (ft_strlen(str) < (size_t) precision)
		ft_strlcat(str, "0", precision);
	str = ft_strjoin(str, nstr);
	free(nstr), nstr = NULL;
	return (str);
}

static int	minus_print(char *str, int len, int field, int minus)
{
	int	written;

	written = 0;
	if (minus)
		ft_putstr(str), written += len;
	while (field-- > len)
		ft_putchar(' '), written++;
	if (!minus)
		ft_putstr(str), written += len;
	return (written);
}

int	ft_printf_bonus(const char *format, ...)
{
	va_list args;
	char	*str;
	char	conv;
	int	field;
	int	precision;
	int	nbr;
	int	written;
	
	if (!format)
		return (-1);
	va_start(args, format);
	while (*format)
	{
		if(*format == '%')
		{
			conv = ft_formattype(++format);
			field = get_field(format);
			precision = get_precision(format);
			str = "";
			if (*format == '%')
			{
				ft_putchar('%'), written++;
				continue;
			}
			else if (conv == 'd' || conv == 'i')
			{
				nbr = va_arg(args, int);
				str = get_intstr(format, str, nbr, precision, field);
			}
			else if (conv == 'u')
			{	
				nbr = va_arg(args, unsigned int);
				str = get_uintstr(format, str, nbr, precision, field);
			}
			else if (conv == 'o')
			{	
				nbr = va_arg(args, int);
				str = get_octstr(format, str, nbr, precision, field);
			}
			else if (conv == 'x')
			{
				nbr = va_arg(args, int);
				str = get_hexstr(format, str, nbr, precision, field);
			}
			else if (conv == 'X')
			{
				nbr = va_arg(args, int);
				str = get_hexstr(format, str, nbr, precision, field);
			}
			else if (conv == 'c')
				ft_putchar((char)va_arg(args, int)), written++;
			else if (conv == 's')
			{
				str = va_arg(args, char *);
				if (!str)
					str = ft_strdup("(null)");
				else
					str = ft_strdup(va_arg(args, char *));
			}
			else if (conv == 'p')
			{
				if (!va_arg(args, char *))
					str = ft_strdup("(nil)");
				else
				{
					str = ft_itoa_base((long int)va_arg(args, void *), HEXL);
					str = ft_strjoin("0x", (free(str), str));
				}
			}
			else
				return (-1);
			written = minus_print(str, ft_strlen(str), field, ft_formatchr(format, '-'));
			while (*format != conv)
				format++;
			if (str)
				str = (free(str), NULL);
		}
		else
			ft_putchar(*format), written++;
		format++;
	}
	va_end(args);
	return (0);
}
