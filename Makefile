# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/11 23:23:38 by ozamora-          #+#    #+#              #
#    Updated: 2025/02/22 18:53:18 by ozamora-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
# DIRECTORIES
SRC_DIR			:= src/
INC_DIR			:= inc/
OBJ_DIR			:= obj/
LIB_DIR			:= lib/

LIBFT_DIR		:= $(LIB_DIR)libft/
LIBFT_INC_DIR	:= $(LIBFT_DIR)inc/

# **************************************************************************** #
# PROJECT
NAME		:= pipex
LIBFT		:= $(LIBFT_DIR)libft.a

# **************************************************************************** #
# FILES
SRC_FILES			:= checks commands exit init main

# INCLUDE FILES
INC_FILES	:= $(NAME)

# GENERAL FILES
SRCS	:= $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJS	:= $(SRCS:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)
DEPS	:= $(SRCS:$(SRC_DIR)%.c=$(OBJ_DIR)%.d)
INCS	:= $(addprefix $(INC_DIR), $(addsuffix .h, $(INC_FILES)))
INCS	+= $(LIBFT_INC_DIR)libft.h

# **************************************************************************** #
# COMPILER
CC		:= cc
CFLAGS	:= -Wall -Wextra -Werror
CFLAGS	+= -MMD -MP
IFLAGS	:= -I$(INC_DIR) -I$(LIBFT_INC_DIR)
LDFLAGS	:= -L$(LIBFT_DIR) -lft

# DEBUG MODE
BUILD_MODE_FILE := .build_mode

ifeq ($(DEBUG),1)
	CFLAGS += -g3 -fsanitize=address
	LDFLAGS += -fsanitize=address
endif

# VALGRIND MODE
ifeq ($(VALGRIND),1)
	CFLAGS += -g3
endif

# **************************************************************************** #
# COLOURS: BOLD RGBYW
BR	= \033[1;31m
BG	= \033[1;32m
BB	= \033[1;34m
BY	= \033[1;33m
BW	= \033[1;37m

# NO COLOR and CLEAR LINE
NC	= \033[0;39m
CL	= \033[2K

# **************************************************************************** #
# ESSENTIAL RULES

# Default rule to create the program
all: libft $(NAME)

# Rule to create the program
$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(IFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)
	@printf "%b" "$(CL) -> $(BW)[$(NAME)]:\t\t$(BG)Compilation success\t✅$(NC)\n"
	@echo "─────────────────────────────────────────────────────$(BY)"
	@echo "           ▗▄▄▖▗▄▄▄▖▗▄▄▖ ▗▄▄▄▖▗▖  ▗▖";
	@echo "           ▐▌ ▐▌ █  ▐▌ ▐▌▐▌    ▝▚▞▘ ";
	@echo "           ▐▛▀▘  █  ▐▛▀▘ ▐▛▀▀▘  ▐▌  ";
	@echo "           ▐▌  ▗▄█▄▖▐▌   ▐▙▄▄▖▗▞▘▝▚▖ by ozamora-$(NC)";
	@echo "─────────────────────────────────────────────────────"

# Rule to compile object files from source files
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	@printf "%b" "$(CL) -> $(BW)[$(NAME)]:\t\t$(NC)$<\r"
	@$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

# Rule to make the library Libft
libft: $(LIBFT)
$(LIBFT):
	@$(MAKE) -sC $(LIBFT_DIR)

# Rule to clean generated files
clean:
	@rm -rf $(OBJ_DIR)*.o $(OBJ_DIR)*.d $(OBJ_DIR)
	@rm -rf $(BUILD_MODE_FILE)
	@$(MAKE) clean -sC $(LIBFT_DIR)
	@printf "%b" "$(CL) -> $(BW)[$(NAME)]:\t\t$(BG)Object files cleaned\t❎$(NC)\n"

# Rule to clean generated files and the executablle
fclean: 
	@$(MAKE) clean > /dev/null
	@$(MAKE) fclean -sC $(LIBFT_DIR)
	@rm -rf $(NAME)
	@printf "%b" "$(CL) -> $(BW)[$(NAME)]:\t\t$(BG)Exe and objects cleaned\t❎$(NC)\n"

# Rule to recompile from zero. 
re: fclean all

# **************************************************************************** #
# NORM AND DEBUG RULES

# Rule to check if the files pass norminette
norm:
	@norminette $(SRCS) $(INCS)

# Rule to compile object files from source files with debug flags
debug:
	@if [ ! -f $(BUILD_MODE_FILE) ] || ! grep -q "DEBUG=1" $(BUILD_MODE_FILE); then \
		$(MAKE) fclean -s; \
	fi
	@echo "DEBUG=1" > $(BUILD_MODE_FILE)
	@$(MAKE) -s DEBUG=1
	@echo " -> $(BW)[Debug]:\t\t$(BB)Debug mode enabled\t🟦$(NC)"
	-@if [ ! -z "$(ARGS)" ]; then ./$(NAME) $(ARGS); fi

# Rule to compile with valgrind debug flags
valgrind:
	@if [ ! -f $(BUILD_MODE_FILE) ] || ! grep -q "VALGRIND=1" $(BUILD_MODE_FILE); then \
		$(MAKE) fclean -s; \
	fi
	@echo "VALGRIND=1" > $(BUILD_MODE_FILE)
	@$(MAKE) -s VALGRIND=1
	@echo " -> $(BW)[Valgrind]:\t\t$(BB)Valgrind mode enabled\t🟦$(NC)"
	-@if [ ! -z "$(ARGS)" ]; then \
		valgrind -s --leak-check=full --show-leak-kinds=all --track-origins=yes --trace-children=yes --track-fds=yes \
		./$(NAME) $(ARGS); \
	fi

-include $(DEPS) 
.PHONY: all clean fclean re norm debug valgrind
.DEFAULT_GOAL := all

# **************************************************************************** #