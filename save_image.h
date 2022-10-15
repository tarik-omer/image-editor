// Copyright 2021-2022 Omer Tarik Ilhan 314CA
#ifndef SAVE_IMAGE_H
#define SAVE_IMAGE_H

#include "definition.h"

void save_details(img pic, FILE * saved);
void save_binary(img pic, char save_as[1000]);
void save_text(img pic, char save_as[1000]);
void save_binary_RGB(img pic, char save_as[1000]);
void save_text_RGB(img pic, char save_as[1000]);
void save_the_world(img *pic_address);

#endif
