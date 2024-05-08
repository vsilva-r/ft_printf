/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsilva-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 17:59:02 by vsilva-r          #+#    #+#             */
/*   Updated: 2024/05/07 17:59:02 by vsilva-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

# include "libft/libft.h"
# include <stdarg.h>
# define OCT "01234567"
# define HEXU "0123456789ABCDEF"
# define HEXL "0123456789abcdef"

#endif

int	ft_printf(const char *format, ...);
