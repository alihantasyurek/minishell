/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmodogl <rootkalixox@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 05:24:08 by atasyure          #+#    #+#             */
/*   Updated: 2024/03/24 02:23:27 by emmodogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "message.h"

typedef struct s_env
{
	char			*key;
	char			*value;
}					t_env;

typedef struct s_data
{
	char			*read_data;
}					t_data;

typedef struct s_lexer
{
	t_list			*lex;
}					t_lexer;

typedef struct s_parse
{
	char			*cmd;
	char			**text;
	int				type;
	int				outfile;
	int				infile;
	int				fd;
	int				pid;
	int				control;
	int				std_in;
	struct s_parse	*next;
}					t_parse;

typedef struct s_mini
{
	t_list			*env;
	char			*cmd;
	t_lexer			*lex_list;
	t_parse			*parse;
	char			*heredoc;
	int				exec_status;
}					t_mini;

extern int			g_heredoc_sig;

int		execute_builtin_command(t_parse *parse, t_mini *m_mini);
void	edit_env(t_list *node, char *key, char *value, t_mini *m_mini);
void	exec_cd1(char *str, t_parse *data, t_mini *m_mini);
void	exec_cd(t_parse *data, t_mini *m_mini);
void	run_echo(t_parse *data, int *i);
void	exec_echo(t_parse *data, t_mini *m_mini);
void	exec_env(t_mini *m_mini);
void	edit_env_(t_list *node, char *key, char *value, t_mini *m_mini);
char	*get_home(t_mini *m_mini);
void	builtin_exit(t_mini **m_mini);
int		exec_export(t_parse *data, t_mini *m_mini);
void	change_old(char *str, t_mini *m_mini);
void	change_pwd(t_parse *data, t_mini *m_mini);
void	exec_pwd(t_parse *data, t_mini *m_mini);
void	exec_unset(t_parse *data, t_mini *m_mini, int i, int x);
int		cmd_is_valid(t_lexer *lex_list, int i);
int		quote_control(char *data);
int		check(t_mini *mini);
t_parse	*_next_command(t_parse **parse);
int		pipe_counter(t_mini *m_mini);
void	multi_command_next(t_parse **parse);
void	multi_command(char **env, t_parse *parse, t_mini *m_mini);
void	exec(char **env, t_mini *m_mini);
void	run_execve(t_parse *parse, char **env, int *fd, t_mini *m_mini);
void	exec_others(t_parse *parse, char **env, int *fd, t_mini *m_mini);
char	**get_args(t_parse *parse, int j);
int		check_quote(char *before, char *after);
char	*get_env(t_list *env, char *our_env);
void	expander(t_mini *mini);
void	expand_dollar_variable(t_mini *mini, t_list *lex,
			char **temp, char *before);
void	expand_question_mark(t_mini *mini, t_list *lex,
			char **temp, char *before);
void	expander_tilde(t_mini *mini, t_list *lex, char *content);
void	handle_relative_path(char **pwd, t_parse *current_parse);
int		create_in_files_meta(t_parse *parse, t_mini *mini);
int		create_files_for_meta(t_mini *m_mini);
void	_create_dup(t_mini *m_mini);
void	create_dup(t_mini *m_mini, t_parse *parse);
void	create_dup_one(t_parse *parse, int *fd);
void	create_dup_two(t_parse *parse, int *fd);
void	free_(t_mini *m_mini);
void	free_loop(int control, t_mini *m_mini);
void	execve_child_free(char **str, t_mini *m_mini);
void	free_text(char **text);
void	free_parser(t_mini *m_mini);
void	free_init_check(t_mini *mini);
int		*create_pipe(void);
void	killer(int sig);
void	set_heredoc(int sig);
void	heredoc(t_parse *parse, t_mini *m_mini);
void	loop_heredoc(t_mini *m_mini);
int		init(t_mini **mini);
void	proper_free(t_list **node);
void	lexer(char *cmd, t_lexer **lex_list);
void	parser(t_mini *mini, char **env, int control);
void	parse_text_m(t_parse *parse, char *str, int *j);
void	flag_free(t_parse *parse);
void	tokenize_type_for_meta(t_parse **parse, const char *str);
t_parse	*parse_init(size_t len);
int		pre_parser(t_mini *m_mini);
void	signals(int sig);
void	signals_control(void);
int		env_get(char **env, t_mini **mini);
void	wait_all(t_mini *m_mini);
void	clear_pipe(int *fd);
void	ft_newlstiter(t_list *lst, void (*f)(void *, t_mini *), t_mini *mini);
int		print_error(void);
int		is_space(char *cmd);
void	get_readline(t_mini *mini);

#endif
