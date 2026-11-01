#ifndef INPUT_H
#define INPUT_H

#include <stddef.h>

void clearInputBuffer(void);
void pauseMenu(void);

int getChoice(void);

void getString(
    const char *prompt,
    char *buffer,
    size_t size
);

#endif