Srcfile = $(wildcard *.c)
Target = $(patsubst %.c, %, $(Srcfile))
lib = pthread
all:$(Target)

%:%.c
	gcc $< -o $@ -l$(lib)

.PHONY:all
