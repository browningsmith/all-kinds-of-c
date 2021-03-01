#pragma once

#ifndef LG_H
#define LG_H

#include <stddef.h>

typedef enum {

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

#endif /* LG_H */
