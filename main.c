/*
 * Project: T nine
 * Author:  Behari Youssef
 * Date:    21 October 2024
 * Version: 1.0
 *
 * Description:
 * T9 algorithm analog. Finding data in contacts by 9 numbers.
 */
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LENGTH 101
#define MAX_CONTACTS 50

typedef struct contact {
    char name[MAX_LENGTH];
    char phone_number[MAX_LENGTH];
    char name_coded[MAX_LENGTH];
} Contact;

void to_lower_case(char *str) {
    for (int string_iterator = 0; string_iterator < (int)strlen(str); string_iterator++) {
        str[string_iterator] = tolower(str[string_iterator]);
    }
}

void code_name(char *name, char *coded) {
    char table[][5] = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
    int coded_iterator = 0;
    for (int name_iterator = 0; name_iterator < (int)strlen(name); name_iterator++) {
        for (int table_iterator = 0; table_iterator < (int)(sizeof(table)/sizeof(table[0])); table_iterator++) {
            if (strchr(table[table_iterator], name[name_iterator])) {
                coded[coded_iterator] = table_iterator + '0';
                coded_iterator++;
            }
        }
    }
}

void clear_criterion(char *criterion, char *new_criterion, int crit_len) {
    int new_crit_idx = 0;
    for (int crit_idx = 0; crit_idx < crit_len; crit_idx++) {
        if (criterion[crit_idx] != '0') {
            new_criterion[new_crit_idx] = criterion[crit_idx];
            new_crit_idx++;
        }
    }
}

int search_contact(Contact contacts[], int contacts_lenght, char* criterion) {
    Contact found_contacts[MAX_CONTACTS];
    char cleared_criterion[MAX_LENGTH] = "";
    clear_criterion(criterion, cleared_criterion, (int)strlen(criterion));

    int index = 0;
    for (int iterator = 0; iterator < contacts_lenght; iterator++) {
        if (criterion[0] == '0') {criterion[0] = '+';}
        if (strstr(contacts[iterator].phone_number, criterion) || strcmp(criterion, "-1") == 0) {
            strcpy(found_contacts[index].name, contacts[iterator].name);
            strcpy(found_contacts[index].phone_number, contacts[iterator].phone_number);
            index++;
            continue;
        }
        if (strstr(contacts[iterator].name_coded, cleared_criterion)) {
            strcpy(found_contacts[index].name, contacts[iterator].name);
            strcpy(found_contacts[index].phone_number, contacts[iterator].phone_number);
            index++;
        }
    }

    if (!index) {
        printf("Not found\n");
        return 0;
    }

    for (int fount_iterator = 0; fount_iterator < index; fount_iterator++) {
        printf("%s, %s\n", found_contacts[fount_iterator].name, found_contacts[fount_iterator].phone_number);
    }
    return 1;
}

int main(const int argc, char** argv) {
    char temp[MAX_LENGTH+1];
    Contact contacts[MAX_CONTACTS];

    int added_contacts = 0;
    int iterator = 0;

    while (scanf("%102[^\n]%*c", temp) == 1) {
        to_lower_case(temp);
        if (strlen(temp) > 101) {
            printf("Too long\n");
            break;
        }
        if (!iterator) {
            code_name(temp, contacts[added_contacts].name_coded);
            strcpy(contacts[added_contacts].name, temp);
            iterator = 1;
        }
        else {
            strcpy(contacts[added_contacts].phone_number, temp);
            added_contacts++;
            iterator = 0;
        }
    }

    if (argc == 2) {
        for (int crit_iterator = 0; crit_iterator < (int)strlen(argv[1]); crit_iterator++) {
            if (!isdigit(argv[1][crit_iterator])) {
                fprintf(stderr, "Criterition is not digit\n");
                return 1;
            }
        }
        search_contact(contacts, added_contacts, argv[1]);
    }
    else if (argc == 1) {
        search_contact(contacts, added_contacts, "-1");
    }
    else {
        fprintf(stderr, "Too many arguments\n");
        return 1;
    }
    return 0;
}
