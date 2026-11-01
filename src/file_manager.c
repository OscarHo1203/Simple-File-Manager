#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#include "file_manager.h"
#include "input.h"

#define MAX_FILENAME 256
#define MAX_CONTENT 100000
#define READ_BUFFER 1024

// Internal helper functions
static int fileExists(const char *filename);
static int getFilename(char *filename, size_t size);
static void printFileHeader(const char *title);


// Check whether a file exists
static int fileExists(const char *filename) {
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        return 0;
    }

    fclose(file);

    return 1;
}


// Get filename from user
static int getFilename(char *filename, size_t size) {
    getString("Enter filename: ", filename, size);

    if (filename[0] == '\0') {
        printf("Filename cannot be empty.\n");
        return 0;
    }

    return 1;
}


// Display section header
static void printFileHeader(const char *title) {
    printf("\n========== %s ==========\n", title);
}


// CREATE FILE
void newFile(void) {
    char filename[MAX_FILENAME];
    char content[MAX_CONTENT];

    printFileHeader("FILE CREATION");

    if (!getFilename(filename, sizeof(filename))) {
        return;
    }

    FILE *file = fopen(filename, "wx");

    if (file == NULL) {
        perror("Could not create file");
        return;
    }

    getString("Enter file content: ", content, sizeof(content));

    if (fprintf(file, "%s\n", content) < 0) {
        printf("Error writing to file.\n");
    } else {
        printf("File created successfully!\n");
    }

    fclose(file);

    pauseMenu();
}


// READ FILE
void readFile(void) {
    char filename[MAX_FILENAME];
    char buffer[READ_BUFFER];

    printFileHeader("FILE READING");

    if (!getFilename(filename, sizeof(filename))) {
        return;
    }

    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        perror("Could not open file");
        return;
    }

    printf("\n---------- FILE CONTENT ----------\n");

    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        printf("%s", buffer);
    }

    if (ferror(file)) {
        printf("\nError reading file.\n");
    }

    printf("\n----------------------------------\n");

    fclose(file);

    pauseMenu();
}


// EDIT FILE
void editFile(void) {
    char filename[MAX_FILENAME];
    char content[MAX_CONTENT];

    int choice;

    printFileHeader("FILE EDITING");

    printf("[1] Append Content\n");
    printf("[2] Overwrite Content\n");
    printf("[0] Back\n");

    printf("\nEnter command: ");

    choice = getChoice();

    if (choice == 0) {
        return;
    }

    if (choice != 1 && choice != 2) {
        printf("Invalid choice.\n");
        pauseMenu();
        return;
    }

    if (!getFilename(filename, sizeof(filename))) {
        return;
    }

    if (!fileExists(filename)) {
        printf("File does not exist.\n");
        pauseMenu();
        return;
    }

    const char *mode = (choice == 1) ? "a" : "w";

    FILE *file = fopen(filename, mode);

    if (file == NULL) {
        perror("Could not open file");
        return;
    }

    getString("Enter new content: ", content, sizeof(content));

    if (fprintf(file, "%s\n", content) < 0) {
        printf("Error writing content.\n");
    } else {
        printf(
            choice == 1
                ? "Content appended successfully!\n"
                : "File overwritten successfully!\n"
        );
    }

    fclose(file);

    pauseMenu();
}


// DELETE FILE
void deleteFile(void) {
    char filename[MAX_FILENAME];

    printFileHeader("FILE DELETION");

    if (!getFilename(filename, sizeof(filename))) {
        return;
    }

    if (remove(filename) == 0) {
        printf("File successfully deleted.\n");
    } else {
        perror("Unable to delete file");
    }

    pauseMenu();
}


// SEARCH FILE
void searchFile(void) {
    char filename[MAX_FILENAME];

    int found = 0;

    printFileHeader("FILE SEARCH");

    if (!getFilename(filename, sizeof(filename))) {
        return;
    }

    DIR *directory = opendir(".");

    if (directory == NULL) {
        perror("Cannot open directory");
        return;
    }

    struct dirent *entry;

    while ((entry = readdir(directory)) != NULL) {

        if (
            strcmp(entry->d_name, ".") == 0 ||
            strcmp(entry->d_name, "..") == 0
        ) {
            continue;
        }

        if (strcmp(entry->d_name, filename) == 0) {
            printf("\n[FOUND] %s\n", entry->d_name);

            found = 1;
            break;
        }
    }

    closedir(directory);

    if (!found) {
        printf("\nFile not found!\n");
    }

    pauseMenu();
}


// LIST FILES
void listFiles(void) {
    printFileHeader("FILE EXPLORER");

    DIR *directory = opendir(".");

    if (directory == NULL) {
        perror("Cannot open directory");
        return;
    }

    struct dirent *entry;

    int count = 0;

    while ((entry = readdir(directory)) != NULL) {

        if (
            strcmp(entry->d_name, ".") == 0 ||
            strcmp(entry->d_name, "..") == 0
        ) {
            continue;
        }

        printf("[%d] %s\n", ++count, entry->d_name);
    }

    if (count == 0) {
        printf("Directory is empty.\n");
    }

    printf("\nTotal entries: %d\n", count);

    closedir(directory);

    pauseMenu();
}