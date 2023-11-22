cc = gcc
target = matmul_test

c_srcs = main.c matmul.c
objects = $(c_srcs:.c=.o)

c_flags = -Wall -Werror -std=c99 -O1 -Wno-unused-result
ld_flags =

all: $(target)

$(target):      $(objects)
	        $(cc) $(ld_flags) $(objects) -o $(target) ./matmul_TA.so

.c.o:
	        $(cc) $(c_flags) -c $< -o $@

clean:
	        rm -f $(objects) $(target)

