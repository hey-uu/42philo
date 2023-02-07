# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyeyukim <hyeyukim@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/05 11:45:28 by hyeyukim          #+#    #+#              #
#    Updated: 2023/02/07 16:06:48 by hyeyukim         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
NAME_BONUS = philo_bonus
.DEFAULT_GOAL := bonus

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
MAN_DIR					=		philo
BON_DIR					=		philo_bonus

# ******************************* header files ******************************* #

# directory path
BON_INC_PATH			=		$(INC_DIR)

# flags
BON_INC_FLAG			=		-I./$(BON_INC_PATH)

# ******************************* object files ******************************* #

# directory path
BON_OBJ_PATH			=		./$(OBJ_DIR)
MAN_OBJ_PATH			=		../$(MAN_DIR)/$(OBJ_DIR)
BON_SRC_PATH			=		./$(SRC_DIR)

BON_FILE				=		error\
								init\
								main\
								monitor\
								parse\
								philo_get_seat\
								philo_routine\
								philo_update\
								philo_utils

# file name(absolute path)
BON_OBJ					=		$(addprefix $(BON_OBJ_PATH)/, $(addsuffix .o, $(BON_FILE)))

# ****************************** dependency files ***************************** #

BON_DEP					=		$(BON_OBJ:.o=.d)

# ******************************* basic rules ******************************** #

.PHONY : all bonus
all : $(NAME)
$(NAME) :
	make -C ../$(MAN_DIR);

bonus : $(NAME_BONUS)
$(NAME_BONUS) : $(BON_OBJ)
	$(CC) -pthread $(CFLAGS) $(BON_OBJ) $(LIBFLAGS) -o $@

.PHONY : clean fclean re
clean :
	$(RM) $(RMFLAGS2) $(MAN_OBJ_PATH)
	$(RM) $(RMFLAGS2) $(BON_OBJ_PATH)

fclean : clean
	$(RM) $(RMFLAGS1) $(NAME_BONUS) ../$(MAN_DIR)/$(NAME)

re :
	make fclean
	make

# ******************************* assist rules ******************************* #

.PHONY: fsanitize
fsanitize :
	make fclean
	make FSANITIZE_FLAG=1

# **************************** dependency rules ****************************** #

ifeq ($(MAKECMDGOALS), fclean)
else ifeq ($(MAKECMDGOALS), clean)
else
	-include $(BON_DEP)
endif

# ****************************** compile rules ******************************* #

# mandatory
$(BON_OBJ_PATH)/%.o : $(BON_SRC_PATH)/%.c
	@mkdir -p $(BON_OBJ_PATH)
	$(CC) -c -pthread $(CFLAGS) $< $(BON_INC_FLAG) -o $@


