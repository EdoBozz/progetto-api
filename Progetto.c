#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <limits.h>

#define LEN 17 //lunghezza massima del comando scritto
#define VALORE_BASE 1 //valore della cella al'inizializzazione
#define VALORE_MAX 100 //valore massimo del costo dell'esagono
#define INF INT_MAX

typedef struct adiacenti{

    int x;
    int y;
    int flag;
    struct adiacenti * next;

}adj_t;

typedef struct map{

    int val;
    adj_t * adj;

}Nodo;

typedef struct coda{

    int id;
    int dist;
    struct coda * next;

}coda_t;

typedef struct{

    int * heap_id; //cambia
    int * distance; //resta fisso
    int * visited;
    int heap_size;
    int qty;

}min_heap;

typedef struct entry{

    int key;
    struct entry * next;

}entry_t;

typedef struct{

    entry_t ** bucket;
    int size;

}hash_t;

Nodo * init(int, int, Nodo *);
adj_t * crea_adj(int, int, int, int);
void aggiungi_adj(adj_t **, int, int, int, int, int);
//void change_cost(Nodo *, int, int, int, int, int, int);
//coda_t * add_nodo(coda_t **, coda_t **, int, int);
//coda_t * preleva_coda(coda_t **, coda_t **);
void change_cost(Nodo *, int, int, int, int, int, int);
coda_t * insert(coda_t *, int, int);
coda_t * pick(coda_t **);
int conta_rotte(Nodo *, int, int, int);
int somma_rotte(Nodo *, int, int, int);
void air_route(Nodo *, int, int, int, int, int, int);
int travel_cost(Nodo *, int, int, int, int);
min_heap * initialize_heap(min_heap *, int);
int pop(min_heap *);
void bubble_up(min_heap *, int);
void heapify_down(min_heap *, int);
void swap(min_heap *, int, int);
void push(min_heap *, int);
int destro(int);
int sinistro(int);
int padre(int);
int nodo_in_map(int, int, int, int);
void free_heap(min_heap *);
static int hash_function(int, int);
hash_t * create(int);
int visited_contains(hash_t *, int);
void visited_free(hash_t *);
void visited_insert(hash_t *, int);

/*
int travel_cost(Nodo *, int, int, int, int, int, int);
min_heap * init_heap(min_heap *, int);
void push(min_heap *, int, int[]);
int pop(min_heap *, int[]);
int sinistro(int);
int destro(int);
int padre(int);
void swap(min_heap *, int, int);
void bubble_up(min_heap *, int, int[]);
void heapify(min_heap *, int, int[]);
 */

int main(){

    char command[LEN];
    int start = 0, col, row, i, num;
    int x, y, v, raggio;
    int x1, y1, x2, y2;
    Nodo * map = NULL;
    adj_t * temp, * curr;

    do{

        if(fscanf(stdin, "%s", command) != 1)
            ;

        if(strcmp(command,"init") == 0){

            //cancella la memoria se viene richiamato init e non sono alla prima volta prima di rileggere row e col
            if(start != 0) {
                num = row * col;
                for(i = 0; i < num; i++){
                    curr = map[i].adj;
                    while(curr != NULL){
                        temp = curr;
                        curr = curr->next;
                        free(temp);
                    }
                    map[i].adj = NULL;
                }
                free(map);
            }

            start++;

            if (fscanf(stdin, "%d", &col) != 1) { ; }
            if (fscanf(stdin, "%d", &row) != 1) { ; }

            map = init(col, row, NULL);
            printf("OK\n");

        }
        else{
            if(strcmp(command, "change_cost") == 0){

                if (fscanf(stdin, "%d", &x) != 1) { ; }
                if (fscanf(stdin, "%d", &y) != 1) { ; }
                if (fscanf(stdin, "%d", &v) != 1) { ; }
                if (fscanf(stdin, "%d", &raggio) != 1) { ; }

                if(start != 0) {
                    //printf("x: %d, y: %d, row: %d, col: %d\n",x,y,row,col);
                    if (nodo_in_map(x, y, row, col) == 1 && raggio > 0 && (v >= -10 && v <= 10)) {
                        change_cost(map, x, y, v, raggio, row, col);
                        printf("OK\n");
                    }
                    else{
                        printf("KO\n");
                    }
                }
                else{
                    printf("KO\n");
                }
            }
            else{
                if(strcmp(command, "toggle_air_route") == 0){

                    if (fscanf(stdin, "%d", &x1) != 1) { ; }
                    if (fscanf(stdin, "%d", &y1) != 1) { ; }
                    if (fscanf(stdin, "%d", &x2) != 1) { ; }
                    if (fscanf(stdin, "%d", &y2) != 1) { ; }

                    if(start != 0) {
                        if (nodo_in_map(x1, y1, row, col) && nodo_in_map(x2, y2, row, col) &&
                            conta_rotte(map, x1, y1, col) < 5) {

                            air_route(map, x1, y1, col, x2, y2, row);
                            printf("OK\n");

                        }
                        else{
                            printf("KO\n");
                        }
                    }
                    else{
                        printf("KO\n");
                    }
                }
                else{
                    if(strcmp(command, "travel_cost") == 0){

                        if (fscanf(stdin, "%d", &x1) != 1) { ; }
                        if (fscanf(stdin, "%d", &y1) != 1) { ; }
                        if (fscanf(stdin, "%d", &x2) != 1) { ; }
                        if (fscanf(stdin, "%d", &y2) != 1) { ; }

                        if(start != 0) {
                            if (nodo_in_map(x1, y1, row, col) == 1 && nodo_in_map(x2, y2, row, col) == 1
                            && (x1 != x2 || y1 != y2)) {

                                //num = travel_cost(map, x1, y1, x2, y2, col, row);
                                int id1 = y1 * col + x1;
                                int id2 = y2 * col + x2;
                                int qty = col * row;
                                num = travel_cost(map, id1, id2, qty, col);
                                printf("%d\n", num);

                            }
                            else {
                                if (x1 == x2 && y1 == y2) {
                                    printf("0\n");
                                }
                                else{
                                    printf("-1\n");
                                }
                            }
                        }
                        else{
                            printf("-1\n");
                        }
                    }
                }
            }
        }

        command[0] = '\0';

    }while(!feof(stdin));

    num = row * col;
    for(i = 0; i < num; i++){
        curr = map[i].adj;
        while(curr != NULL){
            temp = curr;
            curr = curr->next;
            free(temp);
        }
        map[i].adj = NULL;
    }
    free(map);

    return 0;

}

/**
 * INIZIALIZZA LA MAPPA
 */
Nodo * init(int col, int row, Nodo * map){

    int i, j, id;
    int num = row * col;

    map = malloc(num * sizeof(Nodo));

    for(j = 0; j < row; j++){
        for(i = 0; i < col; i++) {
            id = j * col + i;
            map[id].val = VALORE_BASE;
            map[id].adj = crea_adj(i, j, row, col);
        }
    }

    return map;

}

/**
 * CREA LA LISTA DI ADIACENTI PER OGNI NODO
 */
adj_t * crea_adj(int x, int y, int row, int col){

    adj_t * head = NULL;
    adj_t * pointer = head;

    //se la riga è pari
    if (y % 2 == 0) {

        //nord-est
        aggiungi_adj(&pointer, x, y + 1, -1, row, col);
        //est
        aggiungi_adj(&pointer, x + 1, y, -1, row, col);
        //sud-est
        aggiungi_adj(&pointer, x, y - 1, -1, row, col);
        //sud-ovest
        aggiungi_adj(&pointer, x - 1, y - 1, -1, row, col);
        //ovest
        aggiungi_adj(&pointer, x - 1, y, -1, row, col);
        //nord-ovest
        aggiungi_adj(&pointer, x - 1, y + 1, -1, row, col);
    }

    else {
        //nord-est
        aggiungi_adj(&pointer, x + 1, y + 1, -1, row, col);
        //est
        aggiungi_adj(&pointer, x + 1, y, -1, row, col);
        //sud-est
        aggiungi_adj(&pointer, x + 1, y - 1, -1, row, col);
        //sud-ovest
        aggiungi_adj(&pointer, x, y - 1, -1, row, col);
        //ovest
        aggiungi_adj(&pointer, x - 1, y, -1, row, col);
        //nord-ovest
        aggiungi_adj(&pointer, x, y + 1, -1, row, col);
    }

    head = pointer;

    return head;

}

/**
 * AGGIUNGE IL NODO ADIACENTE ALLA LISTA
 */
void aggiungi_adj(adj_t ** head, int x, int y, int flag, int row, int col){

    if(nodo_in_map(x, y, row, col) == 1) {
        adj_t *new = malloc(sizeof(adj_t));
        new->x = x;
        new->y = y;
        new->flag = flag;
        new->next = NULL;
        if (*head == NULL) {
            *head = new;
        } else {
            adj_t *curr = *head;
            while (curr->next != NULL) {
                curr = curr->next;
            }
            curr->next = new;
        }
    }

}

/**
 * MODIFICA IL COSTO DEL NODO
 */
void change_cost(Nodo * map, int x, int y, int v, int raggio, int row, int col){

    coda_t * head = NULL, * ext;
    int id = y * col + x; //qty = col * row;
    int max_visit = 1 + 3 * raggio * (raggio + 1);
    hash_t * visited = create(max_visit);
    //int * visitati = calloc(max_visit, sizeof(int));
    int dist = 0;
    //isited_count = 0;
    int incremento, id_t;

    head = insert(head, id, dist);
    visited_insert(visited, id);
    //visitati[visited_count++] = id;

    while(head != NULL){

        ext = pick(&head);
        //visitati[ext->id] = 1;

        //printf("LOOP, x: %d y: %d v: %d raggio: %d\n",x,y,v,raggio);
        //printf("ext.id: %d\n",ext->id);

        incremento = (int)floorf((float) v * fmaxf(0.0f, (float)(raggio - ext->dist) / (float) raggio));
        map[ext->id].val = map[ext->id].val + incremento;

        //printf("v: %d\traggio: %d\tdistanza: %d\tincremento: %d\n",v,raggio,ext->dist,incremento);

        if(incremento != 0) {
            if (map[ext->id].val < 0) map[ext->id].val = 0;
            else if (map[ext->id].val > VALORE_MAX) map[ext->id].val = VALORE_MAX;

            for (adj_t *p = map[ext->id].adj; p != NULL; p = p->next) {

                id_t = p->y * col + p->x;

                if (visited_contains(visited, id_t) == 0) {
                    visited_insert(visited, id_t);
                    if (p->flag == -1) {
                        head = insert(head, id_t, ext->dist + 1);
                    } else {
                        p->flag = map[ext->id].val;
                    }
                }
            }
        }
        else{
            free(ext);
            break;
        }
    }

    //free(visitati);
    visited_free(visited);
    if(head != NULL){
        coda_t * tmp;
        while(head != NULL){
            tmp = head;
            head = head->next;
            free(tmp);
        }
    }
}
//inserisce in testa
coda_t * insert(coda_t * head, int id, int dist){

    coda_t * new = malloc(sizeof(coda_t));
    new->id = id;
    new->dist = dist;
    new->next = head;

    return new;
}

coda_t * pick(coda_t ** head){

    coda_t * tmp, * p = * head;

    if(p->next != NULL) {
        while (p->next != NULL) {
            tmp = p;
            p = p->next;
        }

        if (tmp != NULL) {
            tmp->next = NULL;
        } else {
            * head = NULL;
        }
    }
    else{
        * head = NULL;
    }

    return p;

}

static int hash_function(int key, int size){

    return key % size;

}

hash_t * create(int size){

    hash_t * table = malloc(sizeof(hash_t));
    table->size = size;
    table->bucket = calloc(size, sizeof(entry_t));

    return table;
}

int visited_contains(hash_t * table, int key) {
    int h = hash_function(key, table->size);
    entry_t * p = table->bucket[h];
    while (p != NULL) {
        if (p->key == key) return 1;
        p = p->next;
    }
    return 0;
}

void visited_insert(hash_t * table, int key) {
    if (visited_contains(table, key)) return;
    int h = hash_function(key, table->size);
    entry_t * new_entry = malloc(sizeof(entry_t));
    new_entry->key = key;
    new_entry->next = table->bucket[h];
    table->bucket[h] = new_entry;
}

void visited_free(hash_t * table) {
    for (int i = 0; i < table->size; i++) {
        entry_t *p = table->bucket[i];
        while (p) {
            entry_t *tmp = p;
            p = p->next;
            free(tmp);
        }
    }
    free(table->bucket);
    free(table);
}

/**
 * CONTA QUANTE ROTTE AEREE ESCONO DAL NODO
 */
int conta_rotte(Nodo * map, int x, int y, int col){

    int id = y * col + x;
    int count = 0;

    for(adj_t * p = map[id].adj; p != NULL; p = p->next){
        if(p->flag != -1){
            count++;
        }
    }

    return count;

}

/**
 * SOMMATORIA DEI COSTI DELLE ROTTE AEREE USCENTI
 */
int somma_rotte(Nodo * map, int x, int y, int col){

    int count = 0, id = y * col + x;

    for(adj_t * p = map[id].adj; p != NULL; p = p->next){
        if(p->flag != -1){
            count = count + p->flag;
        }
    }

    return count;
}

/**
 * CREA O RIMUOVI CONNESIONE AEREA
 */
void air_route(Nodo * map, int x1, int y1, int col, int x2, int y2, int row){

     int id1 = y1 * col + x1;
     adj_t * p = map[id1].adj, * tmp = NULL;
     int costo;

     while(p != NULL){

         if(p->x == x2 && p->y == y2){
            if(p == map[id1].adj){
                map[id1].adj = p->next;
            }
            else{
                tmp->next = p->next;
            }
            free(p);
            return;
         }

         tmp = p;
         p = p->next;
     }

     costo = (somma_rotte(map, x1, y1, col) + map[id1].val) / (conta_rotte(map, x1, y1, col) + 1);
     aggiungi_adj(&map[id1].adj, x2, y2, costo, row, col);

}

/**
 * CALCOLA LA DISTANZA MINIMA CON DIJKSTRA
 */
int travel_cost(Nodo * map, int id1, int id2, int qty, int col){

    int id, dist, id_temp, costo;
    min_heap * head = initialize_heap(NULL, qty);

    head->distance[id1] = 0;
    push(head, id1);

    while(head->heap_size > 0){

        id = pop(head);
        if(head->visited[id] != 1) {
            head->visited[id] = 1;

            if (id == id2) {
                break;
            }

            if (map[id].val != 0) {
                for (adj_t *pointer = map[id].adj; pointer != NULL; pointer = pointer->next) {

                    id_temp = pointer->y * col + pointer->x;
                    dist = head->distance[id] + map[id].val;

                    if (head->distance[id_temp] > dist) {

                        head->distance[id_temp] = dist;
                        push(head, id_temp);

                    }
                }
            }
        }
    }

    if(head->distance[id2] == INF){
        costo = -1;
    }
    else{
        costo = head->distance[id2];
    }

    free_heap(head);


    return costo;

}

min_heap * initialize_heap(min_heap * head, int qty){

    head = malloc(sizeof(min_heap));
    head->qty = qty;
    head->heap_size = 0;
    head->heap_id = malloc(qty * sizeof(int));
    head->distance = malloc(qty * sizeof(int));
    head->visited = malloc(qty * sizeof(int));

    for(int i = 0; i < qty; i++){
        head->distance[i] = INF;
        head->heap_id[i] = INF;
        head->visited[i] = 0;
    }

    return head;
}

int pop(min_heap * head){

    if(head->heap_size == 0){
        printf("aiuto\n");
    }

    int id = head->heap_id[0];
    head->heap_size--;
    head->heap_id[0] = head->heap_id[head->heap_size];
    heapify_down(head, 0);

    return id;
}

void bubble_up(min_heap * head, int size){

    while(size > 0 && head->distance[head->heap_id[size]] < head->distance[head->heap_id[padre(size)]]){
        swap(head, size, padre(size));
        size = padre(size);
    }
}

void heapify_down(min_heap * head, int index){

    int min = index;
    int sx = sinistro(index), dx = destro(index);

    if(sx < head->heap_size && head->distance[head->heap_id[sx]] < head->distance[head->heap_id[min]]){
        min = sx;
    }
    if(dx < head->heap_size && head->distance[head->heap_id[dx]] < head->distance[head->heap_id[min]]){
        min = dx;
    }
    if(min != index){
        swap(head, index, min);
        heapify_down(head, min);
    }
}

int destro(int index){
    return (2 * index) + 2;
}
int sinistro(int index){
    return (2 * index) + 1;
}
int padre(int index){
    return (index - 1) / 2;
}

void swap(min_heap * head, int index1, int index2){

    int tmp = head->heap_id[index1];
    head->heap_id[index1] = head->heap_id[index2];
    head->heap_id[index2] = tmp;

}

void push(min_heap * head, int id){

    head->heap_id[head->heap_size] = id;
    bubble_up(head, head->heap_size);
    head->heap_size++;

}

int nodo_in_map(int x, int y, int row, int col){

    int check = 0;

    if(!(x >= col || x < 0 || y < 0 || y >= row)){
        check = 1;
    }

    return check;

}

void free_heap(min_heap * head){

    free(head->heap_id);
    free(head->distance);
    free(head->visited);
    free(head);

}

//DA RISCRIVERE
/*
void change_cost(Nodo * map, int x, int y, int v, int raggio, int num_col, int num_row){

    int qty = num_row * num_col;
    int * visitati = malloc(qty * sizeof(int)), * distanza = malloc(qty * sizeof(int)), * coda = malloc(qty * sizeof(int));
    int head = 0, tail = 0;

    for(int i = 0; i < qty; i++){

        visitati[i] = 0;
        distanza[i] = -1;

    }

    int id0 = y * num_col + x;

    coda[tail] = id0;
    tail = tail + 1;
    visitati[id0] = 1;
    distanza[id0] = 0;

    map[id0].val = map[id0].val + v;
    if(map[id0].val < 0){
        map[id0].val = 0;
    }
    else{
        if(map[id0].val > VALORE_MAX){
            map[id0].val = VALORE_MAX;
        }
    }

    while(head < tail){

        int id = coda[head];
        head = head + 1;
        adj_t * p = map[id].adj;

        //printf("dentro while\n");
        //printf("id: %d\tdistanza[id]: %d\thead: %d\ttail: %d\tqty: %d\n",id,distanza[id],head, tail,qty);

        if(distanza[id] < raggio) {

            while (p != NULL) {

                int id_n = p->y * num_col + p->x;

                if (p->flag == -1) {

                    if (visitati[id_n] == 0 && distanza[id] + 1 <= raggio) {

                        visitati[id_n] = 1;
                        distanza[id_n] = distanza[id] + 1;
                        float fattore = (float) (raggio - distanza[id_n]) / (float) raggio;
                        int incremento = (int) floorf((float) v * (float) fmaxf(0.0f, fattore));

                        if(incremento > 0) {
                            map[id_n].val = map[id_n].val + incremento;
                            if (map[id_n].val < 0) {
                                map[id_n].val = 0;
                            } else {
                                if (map[id_n].val > VALORE_MAX) {
                                    map[id_n].val = VALORE_MAX;
                                }
                            }

                            coda[tail] = id_n;
                            tail = tail + 1;
                        }
                    }

                } else {
                    p->flag = map[id].val;
                }

                p = p->next;

            }
        }
    }

    free(visitati);
    free(distanza);
    free(coda);
}

void change_cost(Nodo * map, int x, int y, int v, int raggio, int num_col, int num_row){

    int qty = num_col * num_row;
    int * visitati = calloc(qty, sizeof(int)), id = y * num_col + x;
    int dist, aumento, id_t;

    coda_t * head = NULL;
    head = add_nodo(&head, id, 0);

    while(head != NULL){

        coda_t * tmp = preleva_coda(&head);
        dist = tmp->dist;
        id = tmp->id;
        visitati[id] = 1;
        aumento = (int) floorf((float) v * max(0.0, ((float)(raggio - dist) / (float)raggio)));
        map[id].val = map[id].val + aumento;
        if(map[id].val > VALORE_MAX){
            map[id].val = VALORE_MAX;
        }
        if(map[id].val < 0){
            map[id].val = 0;
        }

        for(adj_t * p = map[id].adj; p != NULL; p = p->next){

            if (p->flag == -1) {

                id_t = p->y * num_col + p->x;

                if(visitati[id_t] != 1) {

                    tail = add_nodo(&head, &tail, id_t, dist + 1);
                    visitati[id_t] = 1;

                }
            }
            else{
                p->flag = map[id].val;
            }
        }
        free(tmp);
    }
    free(visitati);
}
//aggiunge in coda
coda_t * add_nodo(coda_t * head, int id, int dist, int flag){

    coda_t * new = malloc(sizeof(coda_t));
    new->id = id;
    new->dist = dist;
    new->next = NULL;


    else{
        * head = new;
    }

    * tail = new;

    return new;

}
coda_t * preleva_coda(coda_t * head){

    if(* head == NULL){
        return NULL;
    }

    coda_t * tmp = * head;
    * head = tmp->next;
    if(* head == NULL){
        * tail = NULL;
    }

    tmp->next = NULL;

    return tmp;
}
*/