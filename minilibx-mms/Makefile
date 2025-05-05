# MODULE_SRC= mlx_image.swift mlx_window.swift mlx_init.swift
# MODULE_OBJ=$(MODULE_SRC:.swift=.swiftmodule)

# SRC= interface.swift $(MODULE_SRC)
# OBJ=$(SRC:.swift=.o)

# C_SRC= mlx_xpm.c mlx_png.c mlx_string_put.c
# C_OBJ=$(C_SRC:.c=.o)

# NAME=libmlx.dylib

# INC=-I.

# all: $(NAME)

# $(NAME): $(MODULE_OBJ) $(OBJ) $(C_OBJ)
# 	swiftc $(INC) -o $(NAME) -emit-library $(OBJ) $(C_OBJ) -lz


# %.o: %.swift
# 	swiftc $(INC) -parse-as-library -c $< -o $@

# %.swiftmodule: %.swift
# 	swiftc $(INC) -parse-as-library -c $< -o $@ -emit-module -module-name $(patsubst %.swift,%,$<) -module-link-name $(patsubst %.swift,%,$<)

# clean:
# 	rm -f $(NAME) $(OBJ) $(MODULE_OBJ) $(C_OBJ) *.swiftdoc *~

MODULES = mlx_image mlx_window mlx_init
MODULE_SRC = $(addsuffix .swift, $(MODULES))
MODULE_OBJ = $(addsuffix .o, $(MODULES))

SWIFT_CACHE = ./module-cache

SRC = interface.swift
OBJ = $(SRC:.swift=.o)

C_SRC = mlx_xpm.c mlx_png.c mlx_string_put.c
C_OBJ = $(C_SRC:.c=.o)

NAME = libmlx.dylib
INC = -I.
SWIFTC = swiftc
CC = cc

all: $(NAME)

# Step 1: Compile each Swift module (.swift → .swiftmodule + .o)
$(MODULE_OBJ): %.o: %.swift
	$(SWIFTC) $(INC) -parse-as-library -emit-module -emit-object $< \
		-module-name $* \
		-module-link-name $* \
		-module-cache-path $(SWIFT_CACHE) \
		-o $@

# Step 2: Compile interface.swift which imports other modules
interface.o: interface.swift $(MODULE_OBJ)
	$(SWIFTC) $(INC) -parse-as-library -emit-object $< \
		-module-cache-path $(SWIFT_CACHE) \
		-I. -o $@

# Step 3: Compile C files
%.o: %.c
	$(CC) $(INC) -c $< -o $@

# Final link step
$(NAME): interface.o $(MODULE_OBJ) $(C_OBJ)
	$(SWIFTC) $(INC) -emit-library -o $(NAME) interface.o $(MODULE_OBJ) $(C_OBJ) -lz

clean:
	rm -f $(OBJ) *.o *.swiftmodule *.swiftdoc *~; rm -rf $(SWIFT_CACHE)

fclean:
	rm -f $(NAME) *.o *.swiftmodule *.swiftdoc *~; rm -rf $(SWIFT_CACHE)
