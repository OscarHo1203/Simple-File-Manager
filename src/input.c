#include <stdio.h>
#include <string.h>
#include "input.h"

void clearInputBuffer(void) {
    int c;

    while ((c = getchar()) != '\n' && c != EOF);
}

void pauseMenu(void) {
    printf("\nPress ENTER to continue...");
    getchar();
}

int getChoice(void) {
    int choice;

    if (scanf("%d", &choice) != 1) {
        clearInputBuffer();
        return -1;
    }

    clearInputBuffer();

    return choice;
}

void getString(
    const char *prompt,
    char *buffer,
    size_t size
) {
    printf("%s", prompt);

    if (fgets(buffer, size, stdin) == NULL) {
        buffer[0] = '\0';
        return;
    }

    buffer[strcspn(buffer, "\n")] = '\0';
}