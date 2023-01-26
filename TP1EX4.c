#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSIZE 8192

typedef struct {
    FILE *fp;
    char buf[BUFSIZE];
    int pos;
    int end;
} FICHIER;

FICHIER* my_open(const char *path, const char *mode) {
    FICHIER *f = (FICHIER *) malloc(sizeof(FICHIER));
    if (f == NULL) {
        perror("Erreur lors de l'allocation de mémoire pour FICHIER");
        return NULL;
    }

    f->fp = fopen(path, mode);
    if (f->fp == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        free(f);
        return NULL;
    }

    f->pos = 0;
    f->end = 0;
    return f;
}

int my_getc(FICHIER *f) {
    if (f->pos >= f->end) {
        f->end = fread(f->buf, 1, BUFSIZE, f->fp);
        f->pos = 0;
        if (f->end == 0) {
            return EOF;
        }
    }

    return f->buf[f->pos++];
}

int my_putc(int c, FICHIER *f) {
    if (f->pos >= BUFSIZE) {
        if (fwrite(f->buf, 1, BUFSIZE, f->fp) != BUFSIZE) {
            perror("Erreur lors de l'écriture dans le fichier");
            return EOF;
        }
        f->pos = 0;
    }

    f->buf[f->pos++] = c;
    return c;
}

int my_close(FICHIER *f) {
    if (f->pos > 0) {
        if (fwrite(f->buf, 1, f->pos, f->fp) != f->pos) {
            perror("Erreur lors de l'écriture dans le fichier");
            return EOF;
        }
    }

    if (fclose(f->fp) == EOF) {
        perror("Erreur lors de la fermeture du fichier");
        free(f);
        return EOF;
    }

    free(f);
    return 0;
}