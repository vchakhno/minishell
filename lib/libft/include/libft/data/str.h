/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 03:58:20 by vchakhno          #+#    #+#             */
/*   Updated: 2023/10/14 10:57:08 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STR_H
# define STR_H
# include "libft/data/str.h"
# undef STR_H
#else
# ifndef LIBFT_STR_H
#  define LIBFT_STR_H

#  include <stdbool.h>
#  include "libft/arithmetic/fixed_types.h"
#  include "libft/data/iter.h"
#  include "libft/io/output.h"

typedef struct s_str
{
	char	*c_str;
	t_u32	len;
}	t_str;

/******************************************************************************/
/* C_STR																	  */
/******************************************************************************/

t_u32		ft_c_str_len(const char *c_str);
void		ft_c_str_ncopy(char *dest, const char *src, t_u32 len);

/******************************************************************************/
/* PRINTING																	  */
/******************************************************************************/

bool		ft_c_str_print(char *c_str);
bool		ft_c_str_println(char *c_str);
bool		ft_c_str_oprint(char *c_str, t_output *output);
bool		ft_c_str_oprintln(char *c_str, t_output *output);

bool		ft_str_print(t_str str);
bool		ft_str_println(t_str str);
bool		ft_str_oprint(t_str str, t_output *output);
bool		ft_str_oprintln(t_str str, t_output *output);

/******************************************************************************/
/* CREATION																	  */
/******************************************************************************/

t_str		ft_str(char *c_str);
t_str		ft_c_str_get_slice__unchecked(char *c_str, t_u32 start, t_u32 len);
t_str		ft_c_str_get_slice(char *c_str, t_u32 start, t_u32 len);
t_str		ft_str_get_slice__unchecked(t_str str, t_u32 start, t_u32 len);
t_str		ft_str_get_slice(t_str str, t_u32 start, t_u32 len);

/******************************************************************************/
/* CHECKING																	  */
/******************************************************************************/

bool		ft_str_is_alnum(t_str str);
bool		ft_str_is_alpha(t_str str);
bool		ft_str_is_ascii(t_str str);
bool		ft_str_is_blank(t_str str);
bool		ft_str_is_digit(t_str str);
bool		ft_str_is_lower(t_str str);
bool		ft_str_is_print(t_str str);
bool		ft_str_is_upper(t_str str);

/******************************************************************************/
/* COMPARISON																  */
/******************************************************************************/

t_i32		ft_str_compare_c_str(t_str str1, char *str2);
bool		ft_str_equal_c_str(t_str str1, char *str2);
bool		ft_str_starts_with_c_str(t_str str, char *prefix);
bool		ft_str_ends_with_c_str(t_str str, char *suffix);

t_i32		ft_str_compare_str(t_str str1, t_str str2);
bool		ft_str_equal_str(t_str str1, t_str str2);
bool		ft_str_starts_with_str(t_str str, t_str prefix);
bool		ft_str_ends_with_str(t_str str, t_str suffix);

/******************************************************************************/
/* SEARCH																	  */
/******************************************************************************/

/*
	Could be prototyped in a lot of ways:
	
	1)
	Prototype:
		t_i32	ft_str_find_char(t_str *haystack, char c);

	Usage:
		t_i32	index;

		index = ft_str_find_char(str, c);
		if (index == -1)
		{
			// Error goes here
		}

	Notes:
		[+] Pretty classic.
		[-] Separates the call out of the if.
		[-] Doesn't give a pointer.
		[+] Can be used inline if the result is known to be true.
	
	2)
	Prototype:
		t_maybe_char_pos	ft_str_find_char(t_str *haystack, char c);

	Usage:
		t_maybe_char_pos	maybe_pos;

		maybe_pos = ft_str_find_char(str, c);
		if (!maybe_pos.exists)
		{
			// Error goes here
		}
	
	Notes:
		[-] Needs to use a custom type.
		[+] Can be used inline if the result is known to be true.
		[+] Gives out a pointer too.
		[-] Separates the call out of the if.

	3) (Best one for now)
	Prototype:
		bool	ft_str_find_char(t_str *haystack, char c, t_u32 *index);
	
	Usage:
		t_u32	index;
		
		if (!ft_str_find_char(str, c, &index))
		{
			// Error goes here
		}
	
	Notes:
		[+] Coherent with the rest of the library.
		[+] Merges with the if
		[-] Doesn't give a pointer
		[-] Cannot be used inline

	And other experimental prototypes.
	(?) t_find_char_option that takes optionnal pointers
	(?) Callback that takes an int
*/

bool		ft_str_contains_char(t_str haystack, char c);
bool		ft_str_find_char(t_str haystack, char c, t_u32 *index);
bool		ft_str_rfind_char(t_str haystack, char c, t_u32 *index);
t_u32		ft_str_count_char(t_str haystack, char c);

bool		ft_str_contains_str(t_str haystack, t_str needle);
bool		ft_str_find_str(t_str haystack, t_str needle, t_u32 *index);
bool		ft_str_rfind_str(t_str haystack, t_str needle, t_u32 *index);
t_u32		ft_str_count_str(t_str haystack, t_str needle);

bool		ft_str_contains_c_str(t_str haystack, char *needle);
bool		ft_str_find_c_str(t_str haystack, char *needle, t_u32 *index);
bool		ft_str_rfind_c_str(t_str haystack, char *needle, t_u32 *index);
t_u32		ft_str_count_c_str(t_str haystack, char *needle);

/******************************************************************************/
/* SPLITTING																  */
/******************************************************************************/

typedef struct s_str_iter	t_str_iter;
typedef bool				(*t_str_iter_next)(t_str_iter *iter, t_str *word);

typedef struct s_str_iter
{
	union {
		t_str_iter_next		next;
		t_iter				iter;
	};
	t_str					remaining;
	t_str					delim;
}	t_str_iter;

t_str_iter	ft_str_split_by_str(t_str str, t_str delim);
t_str_iter	ft_str_split_by_c_str(t_str str, char *delim);

t_str_iter	ft_str_rsplit_by_str(t_str str, t_str delim);
t_str_iter	ft_str_rsplit_by_c_str(t_str str, char *delim);

/*
	Example usage:

		t_str_split_iter	iter;
		t_str_slice			word;
		
		ft_str_split_by_c_str(str, ", ", &iter);
		while (ft_iter_next(&iter, &word))
		{
			
		}

	Example 2:
	
		t_str_split_iter	iter;
		t_vec				words;

		ft_str_split_by_c_str(str, ", ", &iter);
		if (!ft_vec_collect(&words, sizeof(t_str_slice), &iter))
		{
			// Error goes here
		}
		// ...
		ft_vec_free(words);
*/

/******************************************************************************/
/* CASING																	  */
/******************************************************************************/

void		ft_str_to_upper(t_str str);
void		ft_str_to_lower(t_str str);
void		ft_str_title(t_str str);
void		ft_str_swap_case(t_str str);

# endif
#endif