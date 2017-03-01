/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lweinste <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 10:28:54 by lweinste          #+#    #+#             */
/*   Updated: 2017/03/01 11:49:22 by lweinste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>
#include <libft.h>


/*
** Free bonuses:
** -A is just -a without printing . and ..
** -Bbw : just choosing how to represent non-printable characters [(oct), (oct if no escp), (raw)]
** -c	: literally just switches your file's "time" to "last changed"... I can't find a difference...
** -d   : directories listed in argv are simply read like files, not recursed (EVEN WITH -dR or -Rd)
** -m   : Literally just put a comma and a spcae between names. l overrides m, m overrides l, whichever
**		  is second gets priority. See ORDER OF EVENTS
** -1   : Prints list as forced one name per line (like non-bonus) See ORDER OF EVENTS
**
**	
*/

/*
** Harder:
** -C: Force multi column output; (this is default when output is to a terminal)
**
** -c: Use time when file status was last changed for sotring (-t) or long printing (-l)

*/
struct	s_ls_flags
{
	/*
	** Capital
	** (double letter)
	*/
	int		aa;
	int		rr;
	
	/*
	** Lower-Case
	** (single letter)
	*/
	int		a;
	int		f;
	int		l;
	int		r;
	int		t;

	/*
	** Printing of non printable characters options.
	**
	**		-B as \xxx, where xxx is the numeric value in octal
	**		-b same as -B, but use c escape codes whenever possible.
	*/		
	int		bb;
	int		b;
	int		w;
}

/*
** Arguments passed in from argv
** read links as what they direct to,
** whereas links therein are read simply
** as links unless otherwise specified.
*/
