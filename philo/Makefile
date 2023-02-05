# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyeyukim <hyeyukim@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/05 11:45:28 by hyeyukim          #+#    #+#              #
#    Updated: 2023/02/03 20:34:05 by hyeyukim         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
.DEFAULT_GOAL := all

# **************************** command and flags ***************************** #

# compile
CC						=		cc
CFLAGS1					=		-MMD -MP
CFLAGS2					=		-Wall -Wextra -Werror
CFLAGS3					=		-fsanitize=thread -g3
CFLAGS					=		$(CFLAGS1) $(CFLAGS2)

ifdef FSANITIZE_FLAG
	CFLAGS				+=		$(CFLAGS3)
endif

# library archive
AR						=		ar
ARFLAGS					=		crs

# remove
RM						=		rm
RMFLAGS1				=		-f
RMFLAGS2				=		-rf

# ******************************** directory ********************************* #

SRC_DIR					=		src
OBJ_DIR					=		obj
INC_DIR					=		include

# ******************************* header files ******************************* #

# directory path
MAN_INC_PATH			=		$(INC_DIR)

# flags
MAN_INC_FLAG			=		-I./$(MAN_INC_PATH)

# ******************************* object files ******************************* #

# directory path
MAN_OBJ_PATH			=		./$(OBJ_DIR)
MAN_SRC_PATH			=		./$(SRC_DIR)

MAN_FILE				=		error\
								init\
								main\
								monitor\
								parse\
								philo_get_seat\
								philo_routine\
								philo_update\
								philo_utils

# file name(absolute path)
MAN_OBJ					=		$(addprefix $(MAN_OBJ_PATH)/, $(addsuffix .o, $(MAN_FILE)))

# ****************************** dependency files ***************************** #

MAN_DEP					=		$(MAN_OBJ:.o=.d)

# ******************************* basic rules ******************************** #

.PHONY : all bonus
all : $(NAME)
bonus : $(NAME)
$(NAME) : $(MAN_OBJ)
	$(CC) -pthread $(CFLAGS) $(MAN_OBJ) $(LIBFLAGS) -o $@

.PHONY : clean fclean re
clean :
	$(RM) $(RMFLAGS2) $(MAN_OBJ_PATH)

fclean : clean
	$(RM) $(RMFLAGS1) $(NAME)

re :
	make fclean
	make all

# ******************************* assist rules ******************************* #

.PHONY: fsanitize
fsanitize :
	make fclean
	make FSANITIZE_FLAG=1

# **************************** dependency rules ****************************** #

ifeq ($(MAKECMDGOALS), fclean)
else ifeq ($(MAKECMDGOALS), clean)
else
	-include $(MAN_DEP)
endif

# ****************************** compile rules ******************************* #

# mandatory
$(MAN_OBJ_PATH)/%.o : $(MAN_SRC_PATH)/%.c
	@mkdir -p $(MAN_OBJ_PATH)
	$(CC) -c -pthread $(CFLAGS) $< $(MAN_INC_FLAG) -o $@


