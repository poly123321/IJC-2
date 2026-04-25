# Makefile
# Jan Polasek, FSI VUT, IJC-DU2

CC = gcc
CFLAGS = -std=c11 -pedantic -Wall -Wextra -g
LDFLAGS =


HTAB_OBJS = htab_init.o htab_free.o htab_clear.o htab_size.o \
            htab_bucket_count.o htab_find.o htab_lookup_add.o \
            htab_erase.o htab_for_each.o htab_hash_function.o


HTAB_OBJS_PIC = htab_init_pic.o htab_free_pic.o htab_clear_pic.o htab_size_pic.o \
                htab_bucket_count_pic.o htab_find_pic.o htab_lookup_add_pic.o \
                htab_erase_pic.o htab_for_each_pic.o htab_hash_function_pic.o

.PHONY: all clean check

all: tac maxwordcount maxwordcount-dynamic libhtab.a libhtab.so

# --- tac ---
tac: tac.o
	$(CC) $(CFLAGS) $^ -o $@

# --- staticka knihovna ---
libhtab.a: $(HTAB_OBJS)
	ar rcs $@ $^

# --- dynamicka knihovna ---
libhtab.so: $(HTAB_OBJS_PIC)
	$(CC) -shared $^ -o $@

# objekty bez -fPIC (pro statickou)
$(HTAB_OBJS): %.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# objekty s -fPIC (pro dynamickou)
htab_%_pic.o: htab_%.c
	$(CC) $(CFLAGS) -fPIC -c $< -o $@

# --- maxwordcount (staticka) ---
maxwordcount: maxwordcount.o io.o libhtab.a
	$(CC) $(CFLAGS) maxwordcount.o io.o -L. -lhtab -o $@

# --- maxwordcount-dynamic (dynamicka) ---
maxwordcount-dynamic: maxwordcount.o io.o libhtab.so
	$(CC) $(CFLAGS) maxwordcount.o io.o -L. -lhtab -o $@

# --- check ---
check: all
	echo "hello world hello" | ./maxwordcount
	echo "hello world hello" | LD_LIBRARY_PATH=. ./maxwordcount-dynamic
	echo "line1\nline2\nline3" | ./tac

# --- clean ---
clean:
	rm -f *.o tac maxwordcount maxwordcount-dynamic libhtab.a libhtab.so