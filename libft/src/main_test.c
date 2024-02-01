

// #include "../includes/libft.h"
// #include <string.h>
// #include <bsd/string.h>

// static size_t	ft_atol(char *nptr)
// {
// 	size_t	num;
// 	int	i;
// 	int	sign;

// 	num = 0;
// 	i = 0;
// 	sign = 0;
// 	while ((nptr[i] >= 9 && nptr[i] <= 13) || (nptr[i] == 32))
// 		i++;
// 	if (nptr[i] == '+' || nptr[i] == '-')
// 	{
// 		if (nptr[i] == '-')
// 			sign = 1;
// 		i++;
// 	}
// 	while (nptr[i] >= '0' && nptr[i] <= '9')
// 	{
// 		num *= 10;
// 		num += (size_t)(nptr[i] - '0');
// 		i++;
// 		// printf("num = %zu\n", num);
// 	}
// 	// printf("num = %zu\n", num);
// 	if (sign == 1)
// 		return (-num);
// 	return (num);
// }

// static void	ft_iteri(unsigned int i, char *str)
// {
// 	(void) i;
// 	*str = 'A';
// }

// static	char ft_mapi(unsigned int i, char c)
// {
// 	(void) i;
// 	return (ft_toupper(c));
// }

// int main(int ac, char **av)
// {
// 	if (!(strcmp(av[ac - 1], "isa")) || !(strcmp(av[ac - 1], "tolower")) || !(strcmp(av[ac - 1], "toupper")))
//     {
//         printf("ft_isalpha(%c) = %d\n", av[1][0], ft_isalpha(av[1][0]));
//         printf("ft_isdigit(%c) = %d\n", av[1][0], ft_isdigit(av[1][0]));
//         printf("ft_isalnum(%c) = %d\n", av[1][0], ft_isalnum(av[1][0]));
//         printf("ft_isascii(%c) = %d\n", av[1][0], ft_isascii(av[1][0]));
//         printf("ft_isprint(%c) = %d\n", av[1][0], ft_isprint(av[1][0]));
//         printf("ft_toupper(%c) = %d\n", av[1][0], ft_isalnum(av[1][0]));
//         printf("ft_toupper(%c) = %c\n", av[1][0], ft_toupper(av[1][0]));
//         printf("ft_tolower(%c) = %c\n", av[1][0], ft_tolower(av[1][0]));
//     }
//     if ((!(strcmp(av[ac - 1], "memcpy"))))
//     {
// 		char	*dst;
// 		dst = av[1];
//         printf("ft_memcpy(%s, %s, %zu) = ", dst, av[2], ft_atol(av[3]));
// 		ft_memcpy(dst, av[2], ft_atol(av[3]));
// 		printf("%s\n", dst);
//     }
// 	if (!(strcmp(av[ac - 1], "memmove")))
// 	{
// 		char	*dst;
// 		dst = av[1];
// 		printf("ft_memmove(%s, %s, %zu) = ", av[1], av[2], ft_atol(av[3]));
// 		ft_memmove(dst, av[2], ft_atol(av[3]));
// 		printf("%s\n", dst);
// 	}
// 	if (!(strcmp(av[ac - 1], "memcmp")))
//         printf("ft_memcmp(%s, %s, %zu) = %d\n", av[1], av[2], ft_atol(av[3]), ft_memcmp(av[1], av[2], ft_atol(av[3])));

// 	if (!(strcmp(av[ac - 1], "strncmp")))
//         printf("ft_strncmp(%s, %s, %zu) = %d\n", av[1], av[2], ft_atol(av[3]), ft_strncmp(av[1], av[2], ft_atol(av[3])));

// 	if (!(strcmp(av[ac - 1], "strnstr")))
//         printf("ft_strnstr(%s, %s, %zu) = %s\n", av[1], av[2], ft_atol(av[3]), ft_strnstr(av[1], av[2], ft_atol(av[3])));

//     if (!(strcmp(av[ac - 1], "memchr")))
// 	{
//         printf("ft_memchr(%s, %d, %zu) = %s\n", av[1], ft_atoi(av[2]), ft_atol(av[3]), (char *) ft_memchr(av[1], ft_atoi(av[2]), ft_atol(av[3])));
// 	}

// 	if (!(strcmp(av[ac - 1], "strchr")))
//         printf("ft_strchr(%s, %s) = %s\n", av[1], av[2], ft_strchr(av[1], (av[2][0])));

// 	if (!(strcmp(av[ac - 1], "strrchr")))
//         printf("ft_strrchr(%s, %s) = %s\n", av[1], av[2], ft_strrchr(av[1], (av[2][0])));

// 	if (!(strcmp(av[ac - 1], "memset")))
//         printf("ft_memset(%s, %d, %zu) = %s\n", av[1], av[2][0], ft_atol(av[3]), (char *) ft_memset(av[1], av[2][0], ft_atol(av[3])));

//     if (!(strcmp(av[ac - 1], "strlen")))
// 		printf("ft_strlen(%s) = %zu\n", av[1], ft_strlen(av[1]));;

//     if (!(strcmp(av[ac - 1], "atoi")))
//         printf("ft_atoi(%s) = %d\n", av[1], ft_atoi(av[1]));

//     if (!(strcmp(av[ac - 1], "strl")))
//     {
//         char    *dst_cpy;
//         dst_cpy = ft_strdup(av[1]);
// 		printf("ft_strlcpy(%s, %s, %zu) = ", dst_cpy, av[2], ft_atol(av[3]));
// 		ft_strlcpy(dst_cpy, av[2], ft_atoi(av[3]));;
// 		printf("%s\n", dst_cpy);
// 		dst_cpy = ft_strdup(av[1]);
// 		printf("strlcpy(%s, %s, %zu) = ", dst_cpy, av[2], ft_atol(av[3]));
// 		strlcpy(dst_cpy, av[2], ft_atoi(av[3]));;
// 		printf("%s\n", dst_cpy);

// 										// STRLCAT //

//         char    *dst_cat;
//         dst_cat = ft_strdup(av[1]);
// 		printf("ft_strlcat(%s, %s, %zu) = ", dst_cat, av[2], ft_atol(av[3]));
// 		ft_strlcat(dst_cat, av[2], ft_atoi(av[3]));;
// 		printf("%s\n", dst_cat);
// 		dst_cat = ft_strdup(av[1]);
// 		printf("strlcat(%s, %s, %zu) = ", dst_cat, av[2], ft_atol(av[3]));
// 		strlcat(dst_cat, av[2], ft_atoi(av[3]));;
// 		printf("%s\n", dst_cat);
//     }
//     if (!(strcmp(av[ac - 1], "strdup")))
//         printf("ft_strdup(%s) = %s\n", av[1], ft_strdup(av[1]));
//     if (!(strcmp(av[ac - 1], "bzero")))
// 	{
//         char *test;
//         test = ft_strdup(av[1]);
// 		ft_bzero(test, ft_atol(av[2]));
//         printf("ft_bzero(%s, %zu) = %s\n", av[1], ft_atol(av[2]), test);
//     }
//     // if (av[ac - 1] == "calloc")
//     // {
//     //     printf("ft_calloc(%s, %s) = %zu\n", av[1], av[2], (size_t) ft_calloc(ft_atoi(av[1]), ft_atoi(av[2])));
//     // }
//     if (!(strcmp(av[ac - 1], "substr")))
//         printf("ft_substr(%s, %zu, %zu) = %s\n", av[1], ft_atol(av[2]), ft_atol(av[3]), ft_substr(av[1], ft_atol(av[2]), ft_atol(av[3])));
//     if (!(strcmp(av[ac - 1], "strjoin")))
//         printf("ft_strjoin(%s, %s) = %s\n", av[1], av[2], ft_strjoin(av[1], av[2]));
//     if (!(strcmp(av[ac - 1], "strtrim")))
//         printf("ft_strtrim(%s, %s) = %s\n", av[1], av[2], ft_strtrim(av[1], av[2]));
//     if (!(strcmp(av[ac - 1], "itoa")))
//         printf("ft_itoa(%s) = %s\n", av[1], ft_itoa(ft_atoi(av[1])));
//     if (!(strcmp(av[ac - 1], "put")))
//     {
// 		// printf("ft_putchar_fd(%c, %d) = ", av[1][0], ft_atoi(av[3]));
//         ft_putchar_fd(av[1][0], ft_atoi(av[3]));
//         printf("\n");

//         // printf("ft_putstr_fd(%s, %d) = ", av[1], ft_atoi(av[3]));
//         ft_putstr_fd(av[1], ft_atoi(av[3]));
// 		printf("\n");

//         // printf("ft_putendl_fd(%s, %d) = ", av[1], ft_atoi(av[3]));
//         ft_putendl_fd(av[1], ft_atoi(av[3]));

//         // printf("ft_putnbr_fd(%d, %d) = ", ft_atoi(av[2]), ft_atoi(av[3]));
//         ft_putnbr_fd(ft_atoi(av[2]), ft_atoi(av[3]));
//         printf("\n");
//     }
// 	if (!(strcmp(av[ac - 1], "split")))
// 	{
// 		printf("ft_split(%s, %c) = \n", av[1], av[2][0]);
// 		char	**tab;
// 		tab = ft_split(av[1], av[2][0]);
// 		while (*tab)
// 			printf("||%s||\n", *tab++);
// 		printf("||%s||\n", *tab);
// 	}
// 	if (!(strcmp(av[ac - 1], "striteri")))
// 	{
// 		char	*test;
// 		test = ft_strdup(av[1]);
// 		ft_striteri(test, ft_iteri);
// 		printf("ft_striteri(%s, ft_iteri) = %s\n", av[1], test);
// 	}
// 	if (!(strcmp(av[ac - 1], "striteri")))
// 	{
// 		char	*test;
// 		test = ft_strdup(av[1]);
// 		ft_striteri(test, ft_iteri);
// 		printf("ft_striteri(%s, ft_iteri) = %s\n", av[1], test);
// 	}
// 	if (!(strcmp(av[ac - 1], "strmapi")))
// 	{
// 		char	*test;
// 		char	*new;
// 		test = ft_strdup(av[1]);
// 		new = ft_strmapi(test, ft_mapi);
// 		printf("ft_strmapi(%s, ft_mapi) = %s\n", av[1], new);
// 	}
// }