#pragma once

#ifndef LG_H
#define LG_H

#include <stddef.h>

/***************************************
 * enum LgStatus
 * 
 * Different states that the LgObject
 * can be in
 ***************************************/
typedef enum {

    NO_LGOBJECT, // Means the LgObject does not exist, I.E. main_lg_object_ is NULL
    NOTOPEN, // LgObject exists but has not yet opened the log file stream
    OPENFAILED, // LgObject attempted to open the file stream, but failed
    OPEN // LgObject successfully has the file stream open

} LgStatus;

/*******************************************************
 * LgObject
 * 
 * An object that contains data pertaining to the open
 * log, such as status, the open log filestream, etc.
 *******************************************************/
typedef struct {

    LgStatus status;

} LgObject;

/********************************************************
 * static LgObject* main_lg_object_
 * 
 * A global LgObject used by the process and it's threads
 * for logging to the same file
 ********************************************************/
static LgObject* main_lg_object_ = NULL;

/********************************************************
 * lg_open
 * 
 * Arguments: None
 * Returns: LgStatus
 * 
 * This function opens the log for the process. Must be
 * called before the process or any of its threads can
 * write to the log.
 * 
 * Returns NO_LGOBJECT if unable to allocate space for the
 * LgObject, or if the global LgObject already exists
 * Otherwise it returns the status of the newly created
 * LgObject
 ********************************************************/
LgStatus lg_open(void);

/********************************************************
 * lg_exists
 * 
 * Arguments: None
 * Returns: int
 * 
 * This function checks to see if the global LgObject for
 * this process is open.
 * 
 * Returns 0 if the object does not exist, or 1 if it does
 ********************************************************/
int lg_exists(void);

/********************************************************
 * lg_getStatus
 * 
 * Arguments: None
 * Returns: LgStatus
 * 
 * This function returns the status of the global LgObject
 * 
 * Returns NO_LGOBJECT if the object does not exist
 * Otherwise returns the status of the LgObject
 * **********************************************************/
LgStatus lg_getStatus(void);

/************************************************************
 * lgc
 * 
 * Arguments: const char* text
 * Returns: int
 * 
 * This function prints the given text to stdout, as well as
 * logs it to the open log with a timestamp
 * 
 * If an error occurs writing to the log, returns -1 and prints
 * error message to stdout.
 * 
 * Returns 0 on success
 * **********************************************************/
int lgc(const char* text);

#endif /* LG_H */
