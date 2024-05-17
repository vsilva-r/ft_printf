/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsilva-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 11:46:07 by vsilva-r          #+#    #+#             */
/*   Updated: 2024/04/24 11:46:07 by vsilva-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_number_len(int n, int base_size)
{
	size_t	len;

	len = 0;
	if (n <= 0)
		len += 1;
	while (n)
	{
		len += 1;
		n /= base_size;
	}
	return (len);
}

char	*ft_itoa_base(int n, char *base)
{
	size_t			len;
	int				base_size;
	unsigned int	number;
	char			*string;

	base_size = ft_strlen(base);
	//
	// add base checks
	//
	if (n > 0 || base_size % 8 == 0)
		number = (unsigned) n;
	else
		number = -n;
	len = get_number_len(number, base_size);
	string = (char *)ft_calloc(len + 1, sizeof(char));
	if (number == 0)
	{
		string[0] = base[0];
		return (string);
	}
	while (number)
	{
		string[--len] = (char) base[number % base_size];
		number /= base_size;
	}
	if (len > 0)
	{
		string[--len] = '-';
	}
	return (string);
}
