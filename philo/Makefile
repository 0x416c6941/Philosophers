# Compiler options.
CC = cc
CFLAGS = -I$(INC_DIR)						\
	 -Wall -Wextra -Wsign-conversion -pedantic -Werror	\
	 -g

# Headers.
INC_DIR = include

# Source files.
SRC_DIR = src
SRC_FILES = main.c utils.c init.c time_stuff.c routines/utils.c		\
	    routines/philo_routine.c routines/watchdog_routine.c
SRC_FILES := $(addprefix $(SRC_DIR)/,$(SRC_FILES))

# Object files.
OBJ_DIR = obj
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))

# Name of the resulting binary file.
NAME = philo

# Targets.
all: $(NAME)

$(NAME): $(OBJ_FILES)
	$(CC) $(CFLAGS) $(OBJ_FILES) -o $@ -pthread

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)			# Create the $(OBJ_DIR) if it doesn't exist.
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -rf $(OBJ_DIR)

.PHONY: fclean
fclean: clean
	rm -f $(NAME)

.PHONY: re
re: fclean all
