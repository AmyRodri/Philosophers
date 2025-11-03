# ---------- Configurações ----------
NAME        = philo

GREEN       = \033[0;32m
YELLOW      = \033[0;33m
NC          = \033[0m

CC          = cc
CFLAGS      = -Wall -Wextra -Werror
INCLUDE     = -I include

RM          = rm -rf

# Diretórios
SRCSDIR     = srcs
OBJDIR      = objs

# Fontes
SRCS 		= main.c		\
			  validate.c	\
			  setup.c		\
			  utils.c

# Adiciona prefixo do diretório
SRCS := $(addprefix $(SRCSDIR)/, $(SRCS))

# Objetos
OBJS = $(addprefix $(OBJDIR)/, $(notdir $(SRCS:.c=.o)))


# ---------- Regras ----------
all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(INCLUDE) $(OBJS) $(LIBFT) -o $(NAME)
	@printf "$(GREEN)🎉 Executável $(NAME) criado com sucesso!$(NC)\n"

# Compilar objetos
$(OBJDIR)/%.o: $(SRCSDIR)/%.c | $(OBJDIR)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
	@printf "$(YELLOW)⚙️ Compilando %s -> %s$(NC)\n" "$<" "$@"

# Criar pasta objs se não existir
$(OBJDIR):
	@mkdir -p $(OBJDIR)

# ---------- Limpeza ----------
clean:
	@$(RM) $(OBJDIR)
	@printf "$(YELLOW)🧹 Objetos limpos$(NC)\n"

fclean: clean
	@$(RM) $(NAME)
	@printf "$(YELLOW)🗑️ Executável removido$(NC)\n"

re: fclean all

.PHONY: all clean fclean re
