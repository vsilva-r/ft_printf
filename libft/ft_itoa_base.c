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
		printf("CHECK %d\n", n);
		len += 1;
		n /= base_size;
	}
	return (len);
}

char	*actual_itoa_base(int number, char *base, int base_size)
{
	size_t			len;
	char			*string;
	
	len = get_number_len(number, base_size);
	printf("CHECK LEN %zu\n", len);
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

char	*ft_itoa_base(int n, char *base)
{
	int				base_size;
	int	i;
	int	j;

	i = 0;
	if (!base)
		return (NULL);
	while (base[i])
	{
		if (base[i] == '+' || base[i] == '-')
			return (NULL);
		j = i + 1;
		while (base[j])
		{
			if (base[i] == base[j])
				return (NULL);
			j++;
		}
		i++;
	}
	base_size = &base[i] - base;
	if (base_size < 2)
		return (NULL);
	if (n > 0 || base_size % 8 == 0)
		return(actual_itoa_base((unsigned) n, base, base_size));
	else 
		return(actual_itoa_base(-n, base, base_size));
}
