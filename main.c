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
#include <ctype.h>

void to_lower_case(char *str) {
    for (int i = 0; i < (int)strlen(str); i++) {
        str[i] = tolower(str[i]);
    }
}

void concatenate_string_and_char(char *string, char character) {
    if (character) {}
    string[strlen(string)] = character;
    for (int i = 0; i < (int)strlen(string); i++) {
        printf("%c\n", string[i]);
    }
}

int search_contact(char contacts[50][2][101], int contacts_lenght, char* criterion) {
    char table[10][4] = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
    char valid_chars[5][strlen(criterion)+2];
    char found_contacts[50][2][101];

    for(int iterator = 0; iterator < (int)strlen(criterion); iterator++) {
        int index = criterion[iterator] - '0';
        strcpy(valid_chars[iterator], table[index]);
    }

    int index = 0;
    for (int iterator = 0; iterator < contacts_lenght; iterator++) {
        int found = 0;
        if(strstr(contacts[iterator][1], criterion)) {
            strcpy(found_contacts[index][0], contacts[iterator][0]);
            strcpy(found_contacts[index][1], contacts[iterator][1]);
            found = 1;
            index++;
        }

        if(!found) {
            char found_progression[strlen(contacts[iterator][0])];
            for(int criterions_iterator = 0; criterions_iterator < (int)strlen(criterion); criterions_iterator++) {
                for(int letters_iterator = 0; letters_iterator < (int)strlen(valid_chars[criterions_iterator]); letters_iterator++) {
                    char *letter_in_name = strchr(contacts[iterator][0], valid_chars[criterions_iterator][letters_iterator]);
                    if(letter_in_name != NULL) {
                        concatenate_string_and_char(found_progression, valid_chars[criterions_iterator][letters_iterator]);
                    }
                }
            }
        }
    }

    if (!index) {
        printf("Not found\n");
        return 0;
    }

    for(int iterator = 0; iterator < index; iterator++) {
        printf("%s, ", found_contacts[iterator][0]);
        printf("%s\n", found_contacts[iterator][1]);
    }
    return 1;
}

int main(const int argc, char** argv) {
    char temp[103];
    char contacts[50][2][101];

    int iterator = 0;
    while (scanf("%102[^\n]%*c", temp) == 1) {
        to_lower_case(temp);
        if(strlen(temp) > 101) {
            printf("Too long\n");
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
