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

#include <stdarg.h>
#include "libft/libft.h"
#include "libftprintf.h"

int	ft_printf(const char *format, ...)
{
	va_list args;
	char	*str;

	if (!format)
		return (-1);
	va_start(args, format);
	while (*format)
	{
		if(*format == '%')
		{
			if (*(++format) == '%')
				ft_putchar(*format);
			else if (*format == 'd' || *format == 'd')
				ft_putnbr(va_arg(args, int));
			else if (*format == 'u')
				ft_putnbr(va_arg(args, unsigned int));
			else if (*format == 'o')
				ft_putnbr_base(va_arg(args, int), OCT);
			else if (*format == 'x')
				ft_putnbr_base(va_arg(args, int), HEXL);
			else if (*format == 'X')
				ft_putnbr_base(va_arg(args, int), HEXU);
			else if (*format == 'c')
				ft_putchar((char)va_arg(args, int));
			else if (*format == 's')
			{
				str = va_arg(args, char *);
				if (!str)
					ft_putstr("(null)");
				else
					ft_putstr(str);
			}
			else if (*format == 'p')
			{
				if (!va_arg(args, char *))
					ft_putstr("(nil)");
				else
				{
					ft_putstr("0x");
					ft_putnbr_base((long int)va_arg(args, void *), HEXL);
				}
			}
			else
				return (-1);
		}
		else
			ft_putchar(*format);
		format++;
	}
	va_end(args);
	return (0);
}
