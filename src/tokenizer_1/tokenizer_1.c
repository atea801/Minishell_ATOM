/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 16:39:47 by aautret           #+#    #+#             */
/*   Updated: 2025/11/25 16:47:00 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

static void	commit_buffer(t_token **token, t_tok_buf *tb)
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

static int	handle_single_quote(const char *s, int i, t_tok_buf *tb)
{
	int	j;
	int	k;
	int	len;

	len = ft_strlen(s);
	j = i + 1;
	while (j < len && s[j] != '\'')
		j++;
	k = i + 1;
	while (k < j)
	{
		if (s[k] == '$')
			tb->buf[(tb->buf_i)++] = CHAR_PLACEHOLDER;
		else
			tb->buf[(tb->buf_i)++] = s[k];
		k++;
	}
	tb->saw_single = 1;
	if (j < len)
		return (j + 1);
	return (j);
}

static int	handle_double_quote(const char *s, int i, t_tok_buf *tb)
{
	int	j;
	int	k;
	int	len;

	len = ft_strlen(s);
	j = i + 1;
	while (j < len && s[j] != '"')
		j++;
	k = i + 1;
	while (k < j)
	{
		tb->buf[(tb->buf_i)++] = s[k];
		k++;
	}
	tb->saw_double = 1;
	if (j < len)
		return (j + 1);
	return (j);
}

static int	push_operator(t_token **token, const char *s, int i, t_tok_buf *tb)
{
	char	*op;
	int		len;

	len = ft_strlen(s);
	commit_buffer(token, tb);
	if (s[i] == '<' && i + 2 < len && s[i + 1] == '<' && s[i + 2] == '<')
	{
		op = malloc(4 * sizeof(char));
		if (!op)
			return (len);
		op[0] = '<';
		op[1] = '<';
		op[2] = '<';
		op[3] = '\0';
		put_token(token, op);
		return (i + 3);
	}
	if (s[i] == '<' && i + 1 < len && s[i + 1] == '>')
	{
		op = malloc(3 * sizeof(char));
		if (!op)
			return (len);
		op[0] = '<';
		op[1] = '>';
		op[2] = '\0';
		put_token(token, op);
		return (i + 2);
	}
	if ((s[i] == '>' && i + 1 < len && s[i + 1] == '>') || (s[i] == '<' && i
			+ 1 < len && s[i + 1] == '<'))
	{
		op = malloc(3 * sizeof(char));
		if (!op)
			return (len);
		op[0] = s[i];
		op[1] = s[i + 1];
		op[2] = '\0';
		put_token(token, op);
		return (i + 2);
	}
	op = malloc(2 * sizeof(char));
	if (!op)
		return (len);
	op[0] = s[i];
	op[1] = '\0';
	put_token(token, op);
	return (i + 1);
}

static int	process_next(const char *s, int i, t_token **token, t_tok_buf *tb)
{
	int	len;

	len = ft_strlen(s);
	if (s[i] == ' ')
	{
		commit_buffer(token, tb);
		return (i + 1);
	}
	i = skip_dollar_before_quote(s, i);
	if (i >= len)
		return (i);
	if (s[i] == '\'')
		return (handle_single_quote(s, i, tb));
	if (s[i] == '"')
		return (handle_double_quote(s, i, tb));
	if (s[i] == '|' || s[i] == '<' || s[i] == '>')
		return (push_operator(token, s, i, tb));
	tb->buf[tb->buf_i++] = s[i];
	tb->saw_unquoted = 1;
	return (i + 1);
}

/**
 * @brief Tokenizer principal pour la première passe
 *
 * Scinde la ligne d'entrée en tokens (mots et opérateurs) en respectant
 * les règles de quotes. Les fragments adjacents (quoted/non-quoted)
 * sont concaténés dans un seul token. Les dollars présents à l'intérieur
 * de quotes simples sont remplacés par un caractère placeholder pour
 * empêcher leur expansion ultérieure.
 *
 * @param token Pointeur vers la tête de liste de tokens (in/out)
 * @param str Ligne d'entrée déjà préparée (espaces autour des opérateurs)
 */
void	tokenizer(t_token *token, char *str)
{
	int			i;
	t_tok_buf	tb;
	char		*buf;

	if (!str || !token)
		return ;
	i = 0;
	buf = malloc((ft_strlen(str) + 1) * sizeof(char));
	if (!buf)
		return ;
	tb.buf = buf;
	tb.buf_i = 0;
	tb.saw_single = 0;
	tb.saw_double = 0;
	tb.saw_unquoted = 0;
	while (i < (int)ft_strlen(str))
		i = process_next(str, i, &token, &tb);
	commit_buffer(&token, &tb);
	free(buf);
}
