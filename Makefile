# Copyright 2021-2022 Omer Tarik Ilhan 314CA
CFLAGS=-g -Wall -Wextra

build:
	gcc $(CFLAGS) -o image_editor image_editor.c apply_image.c load_image.c save_image.c exit_image.c select_image.c utils.c crop_image.c rotate_image.c -lm
clean:
	rm image_editor
