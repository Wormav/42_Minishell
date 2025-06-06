# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/06 09:17:45 by stetrel           #+#    #+#              #
#    Updated: 2025/02/21 15:14:54 by jlorette         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= minishell

SRCS_DIR	:= src

OBJS_DIR	:= .objs

CC			:= cc

CFLAGS		:= -Wall -Wextra -Werror -g

IFLAGS		:= -I ./includes

SRCS		:=	main.c \
				tokenizer/tokenizer.c \
				tokenizer/token/token_init.c \
			   	tokenizer/token/token_listsize.c \
			   	tokenizer/token/token_push.c \
			   	tokenizer/token/token_free.c \
			   	tokenizer/tokenizer_utils.c \
				debug/debug.c \
				ast/ast.c \
				ast/ast_utils.c \
				ast/ast_token_split.c \
				parser/parser_identify.c \
				parser/parser_identify_space.c \
				parser/parser_token_check.c \
				parser/parser_define_priority.c \
				parser/parser_join.c \
				parser/parser_join_utils.c \
				parser/parser_quotes.c\
				parser/parser_clean_quotes.c \
				parser/parser_dquotes.c \
				parser/parser_errors_syntax.c \
				parser/parser_expand_var_env.c \
				parser/parser_expend_var_env_utils.c \
				errors/token_errors.c \
				errors/error_odd_quotes.c \
				errors/error_not_supported.c \
				utils/clean.c \
				utils/ft_ltoa.c \
				utils/ft_atol.c \
				utils/reduce_spaces.c \
				utils/trunc_orders_fds.c \
				utils/split_export.c \
				utils/cmd_filter_params.c \
				utils/handle_bad_option.c \
				utils/has_equal_sign.c \
				utils/count_params_size.c \
				utils/check_heredoc.c \
				utils/exit_and_clear_history.c \
				utils/filter_tab.c \
				utils/save_return.c \
				env/env_parsing.c \
				env/env_print.c \
				env/env_get_env.c \
				env/env_join.c \
				env/env_list_create.c \
				env/env_utils.c \
				cmd/echo/echo.c \
				cmd/pwd/pwd.c \
				cmd/unset/unset.c \
				cmd/cd/cd.c \
				cmd/cd/cd_utils.c \
				cmd/exit/exit.c \
				cmd/exit/exit_utils.c \
				cmd/export/export.c \
				cmd/export/export_utils.c \
				cmd/export/export_process_args.c \
				cmd/env/env.c \
				exec/exec.c \
				exec/exec_execve.c \
				exec/exec_ast.c \
				exec/exec_ast_utils.c \
				exec/exec_create_cmd.c \
				exec/exec_utils.c \
				exec/exec_identify_fd.c \
				exec/exec_parsing.c \
				exec/exec_heredoc.c \
				exec/exec_handle_pipe.c \
				exec/exec_error_fd.c \
				exec/exec_others_commands.c \
				data/data.c \
				signals/signals.c \


SRCS		:= $(addprefix $(SRCS_DIR)/, $(SRCS))

OBJS		:= $(addprefix $(OBJS_DIR)/, $(SRCS:%.c=%.o))

RM			:= rm -rf

DIR_UP		= mkdir -p $(@D)

LIBFT_PATH	= ./libft

MAKEFLAGS	+= --no-print-directory

################################################################################

all: $(NAME)

debug: CFLAGS += -D DEBUG=1
debug: all

$(NAME):	$(LIBFT_PATH)/libft.a $(OBJS)
		@$(CC) $(CFLAGS) $(OBJS) $(LIBFT_PATH)/libft.a -o $@ -lreadline

$(OBJS_DIR)/%.o: %.c
	@$(DIR_UP)
	@echo -n "$(YELLOW)Compiling $<...$(RESET)\r"
	@$(CC) $(CFLAGS) $(IFLAGS) -o $@ -c $<

$(LIBFT_PATH)/libft.a:
	@echo -n "$(YELLOW)Compiling Libft...$(RESET)\r"
	@make -C $(LIBFT_PATH) -s
	@echo -n "$(GREEN)Libft Successfully created !$(RESET)\n"

clean:
	@$(RM) $(OBJS_DIR)
	@$(RM) $(OBJS)
	@make clean -C $(LIBFT_PATH) -s
	@echo -n "$(RED)objs removed$(RESET)\r"
	@echo -n "$(RED)Libft objs removed$(RESET)\n"

fclean: clean
	@echo -n "$(RED)$(NAME) removed\n"
	@make fclean -C $(LIBFT_PATH) -s
	@$(RM) $(NAME)

re:
	@$(MAKE) fclean
	@$(MAKE) all

################################################################################

RED			= \033[31;49m

YELLOW		= \033[0;33m

GREEN		= \033[0;32m

RESET		= \033[0m

################################################################################
