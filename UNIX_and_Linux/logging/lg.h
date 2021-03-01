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

#endif /* LG_H */
