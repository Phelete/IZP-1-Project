/*
 * Project: T nine
 * Author:  Behari Youssef
 * Date:    15 October 2024
 * Version: 1.0
 *
 * Description:
 * T9 algorithm analog. Finding data in contacts by 9 numbers.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int search_contact(char contacts[50][2][101], int contacts_lenght, char* criterion) {
    char table[10][4] = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
    char valid_chars[5][strlen(criterion)+2];
    char not_found_contacts[50][2][101];

    for(int iterator = 0; iterator < (int)strlen(criterion); iterator++) {
        int index = criterion[iterator] - '0';
        strcpy(valid_chars[iterator], table[index]);
    }

    int index = 0;
    for (int iterator = 0; iterator < contacts_lenght && criterion; iterator++) {
        if(strstr(contacts[iterator][1], criterion)) {
            printf("%s ", contacts[iterator][0]);
            printf("%s\n", contacts[iterator][1]);
            continue;
        }
        strcpy(not_found_contacts[index][0], contacts[iterator][0]);
        strcpy(not_found_contacts[index][1], contacts[iterator][1]);
        index++;
    }

    printf("%s\n", "-------------------------------------------------------------------------");

    for(int main_iterator = 0; main_iterator < index; main_iterator++) {
        printf("%s ", not_found_contacts[main_iterator][0]);
        printf("%s\n", not_found_contacts[main_iterator][1]);
    }
    return 0;
}

int main(const int argc, char** argv) {
    char temp[101];
    char contacts[50][2][101];

    int iterator = 0;
    while (scanf("%[^\n]%*c", temp) == 1) {
        if(strlen(temp) >100) {
            break;
        }
        if (iterator % 2 == 0) {
            strcpy(contacts[iterator / 2][0], temp);
        }
        else {
            strcpy(contacts[iterator / 2][1], temp);
        }
        iterator++;
    }
    if (argc == 2) {
        search_contact(contacts, iterator/2, argv[1]);
    }
    else {
        search_contact(contacts, iterator/2, "23456789");
    }

    return 0;
}
