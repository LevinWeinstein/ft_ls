/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lweinste <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 15:23:34 by lweinste          #+#    #+#             */
/*   Updated: 2017/03/01 16:44:13 by lweinste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define	WSTRING	(x) #x
#define LSTRING	(x)	WSTRING(x)
#define WPRINT ( x, y) x##y
#define LPRINT ( x, y) WPRINT ( x, y)
#define OK_STRLEN(x)	(sizeof(x)/sizeof(x[0]));
#define QPRINT(x)		write (1, x, OK_STRLEN(x) - 1)
#define	QSTRING(x)		(char*)(x)
#define QCONCAT(x, y)	x##y
//#define QDUO(word)		QCONCAT(LSTRING(word), /)	
int	main(int argc, char **argv)
{
	int *n;
	char *str;
	char *str2;


	printf("%s", __STRING(23456));
	str = strdup("turtles");
	LPRINT(
	printf("%s", LSTRING(str));
	//QDUO(str);
	return (0);
}
