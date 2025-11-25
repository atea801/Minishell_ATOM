/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_1_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 16:44:42 by aautret           #+#    #+#             */
/*   Updated: 2025/11/25 17:15:10 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

int	skip_dollar_before_quote(const char *s, int i)
{
	if (s[i] == '$' && s[i + 1] && (s[i + 1] == '"' || s[i + 1] == '\''))
		return (i + 1);
	return (i);
}

void	commit_buffer(t_token **token, t_tok_buf *tb)
{
	char	*res;
	int		qtype;

	if (tb->buf_i <= 0 && !tb->saw_single && !tb->saw_double)
		return ;
	tb->buf[tb->buf_i] = '\0';
	res = ft_strdup(tb->buf);
	qtype = 0;
	if (tb->saw_single && !tb->saw_double && !tb->saw_unquoted)
		qtype = 1;
	else if (tb->saw_double && !tb->saw_single && !tb->saw_unquoted)
		qtype = 2;
	put_token_with_quote(token, res, qtype);
	tb->buf_i = 0;
	tb->saw_single = 0;
	tb->saw_double = 0;
	tb->saw_unquoted = 0;
}
