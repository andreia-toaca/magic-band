/*Toaca Andreia - 311CC*/
#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct list {
    char info;
    struct list *urm, *pre;
} *Tlista;

typedef struct {
    Tlista my_list;
    Tlista current_poz;
} *Banda;

typedef struct coada {
    struct coada *urm, *pre;
    int identificator;
    char x;
} *Coada;
