#include <stdio.h>

#include "menu.h"
#include "file_manager.h"
#include "input.h"

static void displayMenu(void);

static void displayMenu(void) {
    printf("============================\n");
    printf("          C-STORAGE         \n");
    printf("============================\n");

    printf("[1] Create File\n");
    printf("[2] Read File\n");
    printf("[3] Edit File\n");
    printf("[4] Delete File\n");
    printf("[5] List Files\n");
    printf("[6] Search Files\n");
    printf("[0] Exit\n");

    printf("\nEnter command: ");
}

void process(void) {
    int isRunning = 1;

    while (isRunning) {
        displayMenu();

        int choice = getChoice();

        switch (choice) {

            case 1:
                newFile();
                break;

            case 2:
                readFile();
                break;

            case 3:
                editFile();
                break;

            case 4:
                deleteFile();
                break;

            case 5:
                listFiles();
                break;

            case 6:
                searchFile();
                break;

            case 0:
                isRunning = 0;
                printf("Closing C-Storage...\n");
                break;

            default:
                printf("Invalid input! Enter a number from 0 to 6.\n");
                pauseMenu();
                break;
        }

        printf("\n");
    }
}