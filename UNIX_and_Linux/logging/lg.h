#pragma once

#ifndef LG_H
#define LG_H

static short lg_init_tried_ = 0;
static short lg_init_success_ = 0;

int lg_init(void);

void lg(const char* string);

#endif /* LG_H */
