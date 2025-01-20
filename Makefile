# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/06 09:17:45 by stetrel           #+#    #+#              #
#    Updated: 2025/01/20 18:21:32 by jlorette         ###   ########.fr        #
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
				parser/parser_dquotes.c \
				errors/token_errors.c \
				errors/error_odd_quotes.c \
				errors/error_not_supported.c \
				utils/clean.c \
				env/env_parsing.c \
				env/env_print.c \
				cmd/pwd/pwd.c \
				cmd/unset/unset.c \
				cmd/cd/cd.c \
				exec/exec.c \
				exec/exec_clean_quotes.c \
				exec/exec_create_cmd.c \
				exec/exec_utils.c \
				exec/exec_identify_fd.c \

SRCS		:= $(addprefix $(SRCS_DIR)/, $(SRCS))

OBJS		:= $(addprefix $(OBJS_DIR)/, $(SRCS:%.c=%.o))

RM			:= rm -rf

DIR_UP		= mkdir -p $(@D)

LIBFT_PATH	= ./libft

MAKEFLAGS	+= --no-print-directory

################################################################################

all: $(NAME)


$(NAME):	$(LIBFT_PATH)/libft.a $(OBJS)
		@$(CC) $(CFLAGS) $(OBJS) $(LIBFT_PATH)/libft.a -o $@

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
