#include "lg.h"

#include <stdio.h>
#include <stdlib.h>

LgStatus lg_open(void)
{
    if (lg_exists())
    {
        printf("There is already a log open\n");
        return NO_LGOBJECT;
    }

    // Allocate space for log object
    main_lg_object_ = malloc(sizeof(LgObject));
    if (main_lg_object_ == NULL) // malloc returns NULL on error
    {
        perror("Unable to create space for log object");
        return NO_LGOBJECT;
    }

    // Populate LgObject values
    main_lg_object_->status = OPEN;

    return main_lg_object_->status;
}

int lg_exists(void)
{
    if (main_lg_object_ == NULL)
    {
        return 0;
    }

    return 1;
}

LgStatus lg_getStatus(void)
{
    if (!lg_exists())
    {
        return NO_LGOBJECT;
    }

    return main_lg_object_->status;
}

int lgc(const char* text)
{
    printf("%s", text);

    if (lg_getStatus() != OPEN)
    {
        printf("Unable to log \"%s\"\n", text);
        return -1;
    }

    return 0;
}
