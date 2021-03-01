#include "lg.h"

#include <stdio.h>
#include <stdlib.h>

LgStatus lg_open(void)
{
    if (main_lg_object_ != NULL)
    {
        printf("There is already a log open\n");
        return OPENFAILED;
    }

    // Allocate space for log object
    main_lg_object_ = malloc(sizeof(LgObject));
    if (main_lg_object_ == NULL) // malloc returns NULL on error
    {
        perror("Unable to create space for log object");
        return OPENFAILED;
    }

    // Populate LgObject values
    main_lg_object_->status = NOTOPEN;

    return main_lg_object_->status;
}
