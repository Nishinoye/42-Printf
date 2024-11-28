/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedcarpi <tedcarpi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 16:02:46 by tedcarpi          #+#    #+#             */
/*   Updated: 2024/11/28 14:39:37 by tedcarpi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//

#include "ft_printf.h"

int	ft_putunsnbr(unsigned int nb)
{
	int	count;

	count = 0;
	if (nb > 9)
		count += ft_putunsnbr(nb / 10);
	count += ft_putchar(nb % 10 + 48);
	return (count);
}

int	ft_putptr(void *ptr)
{
	int	count;

	count = 0;
	if (!ptr)
		return (ft_putstr("(nil)"));
	count += ft_putstr("0x");
	count += ft_puthex((unsigned long)ptr, 0);
	return (count);
}

int	ft_verify(const char *str, va_list args)
{
	int	count;

	count = 0;
	if (*str == 'c')
		count += ft_putchar(va_arg(args, int));
	if (*str == 's')
		count += ft_putstr(va_arg(args, char *));
	if (*str == 'p')
		count += ft_putptr(va_arg(args, void *));
	if (*str == 'd' || *str == 'i')
		count += ft_putnbr(va_arg(args, int));
	if (*str == 'u')
		count += ft_putunsnbr(va_arg(args, unsigned int));
	if (*str == 'x')
		count += ft_puthex(va_arg(args, unsigned int), 0);
	if (*str == 'X')
		count += ft_puthex(va_arg(args, unsigned int), 1);
	if (*str == '%')
		count += ft_putchar('%');
	return (count);
}

int	ft_printf(const char *str, ...)
{
	int		count;
	va_list	args;

	count = 0;
	va_start(args, str);
	while (*str)
	{
		if (*str == '%' && *(str + 1))
		{
			str++;
			count += ft_verify(str, args);
		}
		else
			count += ft_putchar(*str);
		str++;
	}
	va_end(args);
	return (count);
}
