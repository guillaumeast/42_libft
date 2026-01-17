long	power(int a, int b)
{
	long	res;

	if (b < 0)
		return (0);
	if (b == 0)
		return (1);
	res = 1;
	if (a == 2)
		return (1L << b);
	while (b-- > 0)
		res *= a;
	return (res);
}
