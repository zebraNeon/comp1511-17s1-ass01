# Makefile

CC=gcc -std=c99 -g
BINS=crack_digit crack_captcha 

all:$(BINS)

crack_captcha: captcha.h read_pbm.o copy_pixels.o get_properties.o print_image.o crack.o get_bounding_boxs.o crack_captcha.o 
crack_digit: captcha.h read_pbm.o copy_pixels.o get_properties.o print_image.o crack.o bounding_box.o crack_digit.o

crack_captcha.o: crack_captcha.c
crack_digit.o: crack_digit.c

bounding_box.o: bounding_box.c
copy_pixels.o: copy_pixels.c
crack.o: crack.c
get_bounding_boxs.o: get_bounding_boxs.c
get_properties.o: get_properties.c
print_image.o: print_image.c
read_pbm.o: read_pbm.c

clean:
	rm -f $(BINS) *.o
