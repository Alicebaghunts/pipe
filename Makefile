MAKEFLAGS       = --no-print-directory

NAME            = pipex

SRC             = ./srcs

BUILD           = ./build

INCLUDES        = -Iincludes

LIBFT_DIR       = ./libft

HEADER          = includes/pipex.h

SRCS            = $(SRC)/pipex_bonus.c \
                  $(SRC)/pipex_utils_bonus.c \
                  $(SRC)/pipex_utils.c \
                  $(SRC)/pipex.c \
                  $(SRC)/pipex_here_doc.c

OBJS            = $(patsubst $(SRC)/%.c, $(BUILD)/%.o, $(SRCS))

CC              = cc
CFLAGS          = -Wall -Wextra -Werror $(INCLUDES)

RESET           = \033[0m
PURPLE          = \033[0;35m
LIGHT_PURPLE    = \033[1;35m
CYAN            = \033[1;36m
RED             = \033[0;31m
BLUE            = \033[0;34m
BRIGHT_BLUE     = \033[1;34m
SOFT_BLUE       = \033[0;94m
ORANGE          = \033[38;5;208m  
BRIGHT_ORANGE   = \033[1;33m          
BOLD_ORANGE     = \033[0;91m 

all: $(BUILD) libft $(NAME)

$(BUILD):
	@mkdir -p $(BUILD)

libft:
	@echo "${LIGHT_PURPLE}Compiling Libft ${RESET}"
	@make -C $(LIBFT_DIR) > /dev/null 2>&1 & i=0; \
	while ps -p $$! > /dev/null; do \
		printf "${PURPLE}✧ ${RESET}"; \
		sleep 0.3; \
	done
	@echo
	@echo "${LIGHT_PURPLE}Done ✔️${RESET}"

$(BUILD)/%.o: $(SRC)/%.c $(HEADER) Makefile
	@printf "${PURPLE}✧ ${RESET}";
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -lft -o $(NAME)
	@echo
	@echo "${LIGHT_PURPLE}Pipex created 🚀${RESET}"
	@echo "$(PURPLE)----------------------------------------------------------$(RESET)"
	@echo "$(PURPLE)| $(LIGHT_PURPLE)Usage$(LIGHT_PURPLE)         $(PURPLE)|$(PURPLE) $(LIGHT_PURPLE)./pipex infile cmd1 cmd2 outfile $(LIGHT_PURPLE)$(PURPLE)      |$(PURPLE)$(RESET)"
	@echo "$(PURPLE)|               $(PURPLE)|$(PURPLE) $(LIGHT_PURPLE)./pipex here_doc LIMITER cmd1 cmd2 out $(PURPLE)|$(PURPLE)$(RESET)"
	@echo "$(PURPLE)----------------------------------------------------------$(RESET)"
	@echo "$(PURPLE)| $(LIGHT_PURPLE)Help$(LIGHT_PURPLE)          $(PURPLE)|$(PURPLE) $(LIGHT_PURPLE)make help$(LIGHT_PURPLE)                              $(PURPLE)|$(PURPLE) $(RESET)"
	@echo "$(PURPLE)----------------------------------------------------------$(RESET)"

clean:
	@rm -rf $(BUILD)
	@make clean -C $(LIBFT_DIR) > /dev/null 2>&1
	@echo "${RED}Everything is clean 🧹${RESET}"

fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(LIBFT_DIR) > /dev/null 2>&1
	@echo "${RED}All files are gone 🧨${RESET}"

re: fclean all

help:
	@echo "$(CYAN)        $(RESET)"
	@echo "$(CYAN)-------------------------------------------------------$(RESET)"
	@echo "$(CYAN)|$(CYAN) $(SOFT_BLUE) Pipex Info$(SOFT_BLUE)                                         $(CYAN)|$(CYAN)$(RESET)"
	@echo "$(CYAN)-------------------------------------------------------$(RESET)"
	@echo "$(CYAN)|$(CYAN)                                                     $(CYAN)|$(CYAN)$(RESET)"
	@echo "$(CYAN)|$(CYAN) $(BLUE)./pipex infile cmd1 cmd2 outfile$(BLUE)                    $(CYAN)|$(CYAN)$(RESET)"
	@echo "$(CYAN)|$(CYAN) $(BLUE)./pipex here_doc LIMITER cmd1 cmd2 outfile$(BLUE)          $(CYAN)|$(CYAN)$(RESET)"
	@echo "$(CYAN)-------------------------------------------------------$(RESET)"
	@echo "$(CYAN)|$(CYAN)                                                     $(CYAN)|$(CYAN)$(RESET)"
	@echo "$(CYAN)|$(CYAN) $(BLUE) Use quotes for commands with args$(BLUE)                  $(CYAN)|$(CYAN)$(RESET)"
	@echo "$(CYAN)|$(CYAN) $(BLUE) Example: ./pipex infile \"ls -l\" \"wc -l\" outfile$(BLUE)    $(CYAN)|$(CYAN)$(RESET)"
	@echo "$(CYAN)-------------------------------------------------------$(RESET)"

.PHONY: all clean fclean re help libft
