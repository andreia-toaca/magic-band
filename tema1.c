/*Toaca Andreia - 311CC*/
#include "utilites.h"

#define MAX 20
#define FIVE 5
#define SIX 6

Banda initBanda();
Tlista createCelula(char info);
void move_right(Banda banda);
void move_left(Banda banda);
void freeBanda(Banda banda);
void move_right_char(Banda banda, char x);
void addInstruction(Coada *coada, int identificator, char x);
void extractInstruction(Coada *coada, int *identificator, char *x);
void move_left_char(Banda banda, char x, FILE *output);
void insert_left(Banda banda, char x, FILE *output);
void insert_right(Banda banda, char x);
void write(Banda banda, char x);
void show_current(Banda banda, FILE *output);
void show(Banda banda, FILE *output);
void execute(Banda banda, Coada *instructions, FILE *output);

int main() {
    FILE *input = fopen("tema1.in", "r");
    FILE *output = fopen("tema1.out", "w");
    Banda banda = initBanda();
    Coada instrucions = NULL;
    int n = 0;
    char *instr = calloc(MAX, sizeof(char)), x = 0;
    fscanf(input, "%d ", &n);
    for (int i = 0; i < n; i++) {
        fscanf(input, "%s ", instr);
        if (!strcmp(instr, "MOVE_LEFT")) {
            addInstruction(&instrucions, 0, 0);
        } else if (!strcmp(instr, "MOVE_RIGHT")) {
            addInstruction(&instrucions, 1, 0);
        } else if (!strcmp(instr, "MOVE_LEFT_CHAR")) {
            fscanf(input, "%c ", &x);
            addInstruction(&instrucions, 2, x);
        } else if (!strcmp(instr, "MOVE_RIGHT_CHAR")) {
            fscanf(input, "%c ", &x);
            addInstruction(&instrucions, 3, x);
        } else if (!strcmp(instr, "WRITE")) {
            fscanf(input, "%c ", &x);
            addInstruction(&instrucions, 4, x);
        } else if (!strcmp(instr, "INSERT_LEFT")) {
            fscanf(input, "%c ", &x);
            addInstruction(&instrucions, FIVE, x);
        } else if (!strcmp(instr, "INSERT_RIGHT")) {
            fscanf(input, "%c ", &x);
            addInstruction(&instrucions, SIX, x);
        } else if (!strcmp(instr, "SHOW_CURRENT")) {
            show_current(banda, output);
        } else if (!strcmp(instr, "SHOW")) {
            show(banda, output);
        } else if (!strcmp(instr, "EXECUTE")) {
            execute(banda, &instrucions, output);
        }
    }
    free(instr);
    fclose(input);
    fclose(output);
    freeBanda(banda);
    return 0;
}

void execute(Banda banda, Coada *instructions, FILE *output) {
    int identidicator = 0;
    char x = 0;
    extractInstruction(instructions, &identidicator, &x);
    if (identidicator == 0) {
        move_left(banda);
    } else if (identidicator == 1) {
        move_right(banda);
    } else if (identidicator == 2) {
        move_left_char(banda, x, output);
    } else if (identidicator == 3) {
        move_right_char(banda, x);
    } else if (identidicator == 4) {
        write(banda, x);
    } else if (identidicator == FIVE) {
        insert_left(banda, x, output);
    } else if (identidicator == SIX) {
        insert_right(banda, x);
    }
}

Banda initBanda() {  // initializeaza banda
    Banda b = calloc(1, sizeof(*b));
    b->my_list = createCelula(0);  // santinela
    b->my_list->pre = NULL;
    b->my_list->urm = createCelula('#');
    b->my_list->urm->pre = b->my_list;
    b->my_list->urm->urm = NULL;
    b->current_poz = b->my_list->urm;
    return b;
}

Tlista createCelula(char info) {  // creeaz celula
    Tlista cel = calloc(1, sizeof(struct list));
    cel->info = info;
    return cel;
}

void move_right(Banda banda) {  // deplasare la dreapta cu o pozitie
    if (banda->current_poz->urm == NULL) {
        banda->current_poz->urm = createCelula('#');
        banda->current_poz->urm->urm = NULL;
        banda->current_poz->urm->pre = banda->current_poz;
    }
    banda->current_poz = banda->current_poz->urm;
}

void move_left(Banda banda) {  // deplasare la stanga cu o pozitie
    if (banda->current_poz->pre != banda->my_list) {
        banda->current_poz = banda->current_poz->pre;
    }
}

void move_right_char(Banda banda, char x) {  // deplasare la dreapta pana la  x
    Tlista aux = NULL;
    for (aux = banda->current_poz; aux->info != x
    && aux->urm != NULL; aux = aux->urm) {}
    if (aux->info != x) {
        aux->urm = createCelula('#');
        aux->urm->pre = aux;
        banda->current_poz = aux->urm;
    } else {
        banda->current_poz = aux;
    }
}

void move_left_char(Banda banda, char x, FILE *output) {
    Tlista aux = NULL;
    for (aux = banda->current_poz; aux->info != x
    && aux->pre != banda->my_list; aux = aux->pre) {}
    if (aux->info == x) {
        banda->current_poz = aux;
    } else {
        fprintf(output, "ERROR\n");  // printeaza eroarea
    }
}

void insert_left(Banda banda, char x, FILE *output) {  // deplasarea degetului
    if (banda->current_poz->pre == banda->my_list) {
        fprintf(output, "ERROR\n");
    } else {
        Tlista new = createCelula(x);
        new->urm = banda->current_poz;
        new->pre = banda->current_poz->pre;
        banda->current_poz->pre->urm = new;
        banda->current_poz->pre = new;
        banda->current_poz = new;
    }
}

void insert_right(Banda banda, char x) {  // deplasarea degetului, poz noua
    Tlista new = createCelula(x);
    new->pre = banda->current_poz;
    if (banda->current_poz->urm != NULL) {
        new->urm = banda->current_poz->urm;
        banda->current_poz->urm->pre = new;
    } else {
        new->urm = NULL;
    }
    banda->current_poz->urm = new;
    banda->current_poz = new;
}

void write(Banda banda, char x) {  // scrie caracterul x
    banda->current_poz->info = x;
}

void show_current(Banda banda, FILE *output) {  // poz curenta
    fprintf(output, "%c\n", banda->current_poz->info);
}

void show(Banda banda, FILE *output) {
    for (Tlista aux = banda->my_list->urm; aux != NULL; aux = aux->urm) {
        if (aux != banda->current_poz) {
            fprintf(output, "%c", aux->info);
        } else {
            fprintf(output, "|%c|", aux->info);
        }  // afiseaza pozitia degetului
    }
    fprintf(output, "\n");
}

void freeBanda(Banda banda) {  // eliberez memoria
    for (Tlista aux = banda->my_list->urm; ; aux = aux->urm) {
        free(aux->pre);
        if (aux->urm == NULL) {
            free(aux);
            break;
        }
    }
    free(banda);
}

void addInstruction(Coada *coada, int identificator, char x) {
    if (*coada == NULL) {  // o singura celula
        *coada = calloc(1, sizeof(**coada));
        (*coada)->pre = *coada;
        (*coada)->urm = *coada;
        (*coada)->identificator = identificator;
        (*coada)->x = x;
    } else {  // creeaz o noua celula
        Coada new = calloc(1, sizeof(**coada));
        new->identificator = identificator;
        new->x = x;
        new->urm = *coada;
        new->pre = (*coada)->pre;
        (*coada)->pre->urm = new;
        (*coada)->pre = new;
    }
}

void extractInstruction(Coada *coada, int *identificator, char *x) {
    if (*coada != NULL) {  // daca nu-i o singura celula
        *identificator = (*coada)->identificator;
        *x = (*coada)->x;
        Coada aux = *coada;  // fac copie
        if ((*coada)->urm != *coada && (*coada)->pre != *coada) {
            (*coada)->urm->pre = (*coada)->pre;
            (*coada)->pre->urm = (*coada)->urm;
            *coada = (*coada)->urm;

        } else {
            *coada = NULL;
        }
        free(aux);
    }
}
