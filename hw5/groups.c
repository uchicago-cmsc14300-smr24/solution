#include "map.h"
#include "array-list.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct record {
    char hometown[32];
    char fullname[64];
};

/* Read the next student from file:
 * If the file has no more student records, the record that rec_p points
 * to is untouched and the function returns false; otherwise, this function
 * writes the record to *rec_p, and returns true. If the record stored in the
 * file is invalid, this function aborts the program with an error message.
 */
bool read_record(FILE *file, struct record *rec_p);

/* Strcmp wrapper that has the right type to pass to create */
int string_cmp(void *, void *);

struct map *index_file(FILE *file);

void add_entry(struct map *map, char *hometone, char *fullname);

void print_group(void *key, void *value, void *data);
void free_group(void *key, void *value, void *data);

int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("usage: %s <file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *file;
    if (strcmp(argv[1], "-") == 0) {
        file = stdin;
    } else {
        file = fopen(argv[1], "r");
        if (file == NULL) {
            printf("cannot open '%s'\n", argv[1]);
            return EXIT_FAILURE;
        }
    }

    struct map *table = index_file(file);
    fclose(file);

    map_print(table, stdout);
    map_walk(table, print_group, NULL);
    map_walk(table, free_group, NULL);

    map_free(table);
    return EXIT_SUCCESS;
}

bool read_record(FILE *file, struct record *rec_p)
{
    assert(file != NULL);

    if (feof(file)) {
        /* if the file has nothing more to read, return false */
        return false;
    }

    /* declare and 0 initialize a rec to read into */
    struct record rec = { 0 };

    int n_read = fscanf(file, "%31[^\t]\t%63[^\n]\n",
            rec.hometown, rec.fullname);

    if (n_read != 2) {
        fprintf(stderr, "Invalid data file -- incomplete record\n");
        exit(EXIT_FAILURE);
    }

    *rec_p = rec;
    return true;
}

int string_cmp(void *s1, void *s2)
{
    return strcmp(s1, s2);
}

struct map *index_file(FILE *file)
{
    struct record rec;

    struct map *map = map_create(string_cmp);

    while (read_record(file, &rec)) {
        char *hometown = strdup(rec.hometown);
        char *fullname = strdup(rec.fullname);

        add_entry(map, hometown, fullname);
    }

    return map;
}

void add_entry(struct map *m, char *hometown, char *name)
{
    struct alist *list = map_get(m, hometown);

    if (list == NULL) {
        list = alist_create();
        map_insert(m, hometown, list);
    } else {
        free(hometown);
    }

    alist_append(list, name);
}

void print_group(void *key, void *value, void *data)
{
    (void) data;

    char *hometown = key;
    struct alist *list = value;

    int len = alist_len(list);
    if (len < 2) {
        return;
    }

    printf("%s:\n", hometown);
    for (int i = 0; i < len; i++) {
        char *name = *alist_at(list, i);
        printf("%s\n", name);
    }
    putchar('\n');
}

void free_group(void *key, void *value, void *data)
{
    (void) data;

    struct alist *list = value;

    int len = alist_len(list);
    for (int i = 0; i < len; i++) {
        char *name = *alist_at(list, i);
        free(name);
    }
    alist_free(list);
    free(key);
}
