#include <stdarg.h>
#include <unistd.h>


static void	ft_putstr(const char *s, int *count)
{
	if (!s)
		s = "(null)";
	while (*s)
	{
		write(1, s++, 1);
		(*count)++;
	}
}

static void	ft_putnbr(int n, int *count)
{
	char	c;

	if (n == -2147483648)
	{
		ft_putstr("-2147483648", count);
		return ;
	}
	if (n < 0)
	{
		write(1, "-", 1);
		n = -n;
		(*count)++;
	}
	if (n > 9)
		ft_putnbr(n / 10, count);
	c = (n % 10) + '0';
	write(1, &c, 1);
	(*count)++;
}
static void	ft_puthex(unsigned int n, int *count)
{
	char	*hex;

	hex = "0123456789abcdef";
	if (n >= 16)
		ft_puthex(n / 16, count);
	write(1, &hex[n % 16], 1);
	(*count)++;
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		count;

	va_start(args, format);
	while (*format)
	{
		if (*format == '%' && *(format + 1))
		{
			format++;
			if (*format == 's')
				ft_putstr(va_arg(args, char *), &count);
			else if (*format == 'd')
				ft_putnbr(va_arg(args, int), &count);
			else if (*format == 'x')
				ft_puthex(va_arg(args, unsigned int), &count);
			else
			{
				write(1, format, 1);
				count++;
			}
		}
		else
		{
			write(1, format, 1);
			count++;
		}
		format++;
	}
	va_end(args);
	return (count);
}
/*
int	main(void)
{
	ft_printf("String is %s\n", "slovoo");

	ft_printf("Number is %d\n and then not ordinary number is %d\n", 42,
		-2147483648);
	ft_printf("HEX is %x\n", 16);
    	ft_printf("String is %%\n", "");

}
*/