# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/11 23:23:38 by ozamora-          #+#    #+#              #
#    Updated: 2025/02/25 19:37:14 by ozamora-         ###   ########.fr        #
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

SRC_BONUS_DIR	:= src/bonus/
INC_BONUS_DIR	:= inc/bonus/
OBJ_BONUS_DIR	:= obj/bonus/

# **************************************************************************** #
# PROJECT
NAME		:= pipex
BONUS_NAME	:= .pipex_bonus
LIBFT		:= $(LIBFT_DIR)libft.a

# **************************************************************************** #
# FILES
SRC_FILES		:= main exit init checks commands
SRC_BONUS_FILES	:= main_bonus exit_bonus init_bonus checks_bonus commands_bonus \
					pipex_bonus

INC_FILES		:= pipex
INC_BONUS_FILES	:= pipex_bonus


# GENERAL FILES
SRCS	:= $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJS	:= $(SRCS:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)
DEPS	:= $(SRCS:$(SRC_DIR)%.c=$(OBJ_DIR)%.d)
INCS	:= $(addprefix $(INC_DIR), $(addsuffix .h, $(INC_FILES)))
INCS	+= $(LIBFT_INC_DIR)libft.h

SRCS_BONUS	:= $(addprefix $(SRC_BONUS_DIR), $(addsuffix .c, $(SRC_BONUS_FILES)))
OBJS_BONUS	:= $(SRCS_BONUS:$(SRC_BONUS_DIR)%.c=$(OBJ_BONUS_DIR)%.o)
DEPS_BONUS	:= $(SRCS_BONUS:$(SRC_BONUS_DIR)%.c=$(OBJ_BONUS_DIR)%.d)
INCS_BONUS	:= $(addprefix $(INC_BONUS_DIR), $(addsuffix .h, $(INC_BONUS_FILES)))
INCS_BONUS	+= $(LIBFT_INC_DIR)libft.h

# **************************************************************************** #
# COMPILER
CC		:= cc
CFLAGS	:= -Wall -Wextra -Werror
CFLAGS	+= -MMD -MP
IFLAGS	:= -I$(INC_DIR) -I$(LIBFT_INC_DIR)
LDFLAGS	:= -L$(LIBFT_DIR) -lft

IFLAGS_BONUS:= -I$(INC_BONUS_DIR) -I$(LIBFT_INC_DIR)

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
-include $(DEPS) $(DEPS_BONUS)

# Default rule to create the program
all: libft $(NAME)

# Rule to create the program
$(NAME): $(OBJS) $(LIBFT)
	@rm -f $(BONUS_NAME)
	@$(CC) $(CFLAGS) $(IFLAGS) $^ $(LDFLAGS) -o $(NAME)
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
	@rm -rf $(NAME) $(BONUS_NAME)
	@printf "%b" "$(CL) -> $(BW)[$(NAME)]:\t\t$(BG)Exe and objects cleaned\t❎$(NC)\n"

# Rule to recompile from zero. 
re: fclean all

# **************************************************************************** #
# BONUS RULES

bonus: libft $(BONUS_NAME)
$(BONUS_NAME): $(OBJS_BONUS)
	@$(CC) $(CFLAGS) $(IFLAGS_BONUS) $(OBJS_BONUS) $(LDFLAGS) -o $(NAME) 
	@touch $(BONUS_NAME)
	@printf "%b" "$(CL) -> $(BW)[$(NAME)]:\t\t$(BG)Bonus compiled\t\t✅$(NC)\n"

$(OBJ_BONUS_DIR):
	@mkdir -p $(OBJ_BONUS_DIR)
$(OBJ_BONUS_DIR)%.o: $(SRC_BONUS_DIR)%.c | $(OBJ_BONUS_DIR)
	@mkdir -p $(dir $@)
	@printf "%b" "$(CL) -> $(BW)[$(NAME)]:\t\t$(NC)$<\r"
	@$(CC) $(CFLAGS) $(IFLAGS_BONUS) -c $< -o $@

# **************************************************************************** #
# NORM AND DEBUG RULES

# Rule to check if the files pass norminette
norm:
	@norminette $(SRC_DIR) $(INC_DIR)

# Rule to compile object files from source files with debug flags
debug:
	@if [ ! -f $(BUILD_MODE_FILE) ] || ! grep -q "DEBUG=1" $(BUILD_MODE_FILE); then \
		$(MAKE) clean -s; \
	fi
	@echo "DEBUG=1" > $(BUILD_MODE_FILE)
	@$(MAKE) bonus -s DEBUG=1
	@$(MAKE) -s DEBUG=1
	@echo " -> $(BW)[Debug]:\t\t$(BB)Debug mode enabled\t🟦$(NC)"
	-@if [ ! -z "$(ARGS)" ]; then ./$(NAME) $(ARGS); fi

# Rule to compile with valgrind debug flags
valgrind:
	@if [ ! -f $(BUILD_MODE_FILE) ] || ! grep -q "VALGRIND=1" $(BUILD_MODE_FILE); then \
		$(MAKE) clean -s; \
	fi
	@echo "VALGRIND=1" > $(BUILD_MODE_FILE)
	@$(MAKE) bonus -s VALGRIND=1
	@$(MAKE) -s VALGRIND=1
	@echo " -> $(BW)[Valgrind]:\t\t$(BB)Valgrind mode enabled\t🟦$(NC)"
	-@if [ ! -z "$(ARGS)" ]; then \
		valgrind -s --leak-check=full --show-leak-kinds=all --track-origins=yes --trace-children=yes --track-fds=yes \
		./$(NAME) $(ARGS); \
	fi

# **************************************************************************** #
# ADDITIONAL RULES

# Rule to show compilation and linking commands
show:
	@echo "$(BY)Compilation command:$(NC)\t"\
		"$(CC) $(CFLAGS) $(IFLAGS) -c $(SRC_DIR)$(NAME).c -o $(OBJ_DIR)$(NAME).o"
	@echo "$(BY)Linking command:$(NC)\t"\
		"$(CC) $(CFLAGS) $(IFLAGS) $(OBJS) -o $(NAME) $(LDFLAGS)"
	@echo "$(BY)Cleaning command:$(NC)\t rm -rf $(NAME) $(BONUS_NAME)"\
		"$(OBJ_DIR)*.o $(OBJ_DIR)*.d $(OBJ_DIR) $(BUILD_MODE_FILE)"

# Rule to show all variables being used
info:
	@echo "$(BY)\nozamora's Project:$(NC)"
	@echo "$(BB)NAME: $(NC)$(NAME)"
	@echo "$(BB)LIBFT: $(NC)$(LIBFT)"
	@echo "$(BB)BONUS_NAME: $(NC)$(BONUS_NAME)"
	@echo "$(BY)\nCompiler:$(NC)"
	@echo "$(BB)CC: $(NC)$(CC)"
	@echo "$(BB)CFLAGS: $(NC)$(CFLAGS)"
	@echo "$(BB)IFLAGS: $(NC)$(IFLAGS)"
	@echo "$(BB)LDFLAGS: $(NC)$(LDFLAGS)"
	@echo "$(BY)\nDirectories:$(NC)"
	@echo "$(BB)SRC_DIR: $(NC)$(SRC_DIR)"
	@echo "$(BB)INC_DIR: $(NC)$(INC_DIR)"
	@echo "$(BB)OBJ_DIR: $(NC)$(OBJ_DIR)"
	@echo "$(BB)LIB_DIR: $(NC)$(LIB_DIR)"
	@echo "$(BB)LIBFT_DIR: $(NC)$(LIBFT_DIR)"
	@echo "$(BB)LIBFT_INC_DIR: $(NC)$(LIBFT_INC_DIR)"
	@echo "$(BY)\nFiles:$(NC)"
	@echo "$(BB)NAME: $(NC)$(NAME)"
	@echo "$(BB)SRC_FILES: $(NC)$(SRC_FILES)"
	@echo "$(BB)INC_FILES: $(NC)$(INC_FILES)"
	@echo "$(BB)SRCS: $(NC)$(SRCS)"
	@echo "$(BB)OBJS: $(NC)$(OBJS)"
	@echo "$(BB)DEPS: $(NC)$(DEPS)"
	@echo "$(BB)INCS: $(NC)$(INCS)"
	@echo "$(BY)\nBonus:$(NC)"
	@echo "$(BB)BONUS_NAME: $(NC)$(BONUS_NAME)"
	@echo "$(BB)SRC_BONUS_FILES: $(NC)$(SRC_BONUS_FILES)"
	@echo "$(BB)INC_BONUS_FILES: $(NC)$(INC_BONUS_FILES)"
	@echo "$(BB)SRCS_BONUS: $(NC)$(SRCS_BONUS)"
	@echo "$(BB)OBJS_BONUS: $(NC)$(OBJS_BONUS)"
	@echo "$(BB)DEPS_BONUS: $(NC)$(DEPS_BONUS)"
	@echo "$(BB)INCS_BONUS: $(NC)$(INCS_BONUS)"
	@echo "$(BB)IFLAGS_BONUS: $(NC)$(IFLAGS_BONUS)"

.PHONY: all clean fclean re bonus norm debug valgrind show info
.DEFAULT_GOAL := all

# **************************************************************************** #