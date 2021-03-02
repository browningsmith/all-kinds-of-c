#pragma once

#ifndef LG_H
#define LG_H

#include <stddef.h>

typedef enum {

    NO_LGOBJECT,
    NOTOPEN,
    OPENFAILED,
    OPEN

} LgStatus;

typedef struct {

    LgStatus status;

} LgObject;

static LgObject* main_lg_object_ = NULL;

LgStatus lg_open(void);
int lg_exists(void);
LgStatus lg_getStatus(void);
int lgc(const char* text);

#endif /* LG_H */
