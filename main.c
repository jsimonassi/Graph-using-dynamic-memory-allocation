#include <stdio.h>
#include <stdlib.h>

typedef struct viz{
    int no_viz;
    struct viz *prox_viz;
}TV;

typedef struct grafo{
    int no;
    struct grafo *prox;
    TV * prim;
}TG;

TG *inicializa(){
    return NULL;
}

void imprime(TG *g){
    if(!g)
        return;
    TV * aux = g->prim;
    while(g){
        printf("No: %d\n", g->no);
        printf("Vizinhos: ");
        while(aux){
            printf("%d ->", aux->no_viz);
            aux = aux->prox_viz;
        }
        g = g->prox;
    }
}

TG* busca_no(TG* g, int x){ // Rec
    if((!g) || (g->no == x))
        return g;

    return busca_no(g->prox, x);
}

TG * ins_no(TG *p, int x){

    TG * g = busca_no(p, x);
    if(!g){

        TG * novo = (TG *) malloc(sizeof(TG));
        novo->no = x;
        novo->prim = NULL;

        if(!p){
            novo->prox = NULL;
            return novo;
        }

        novo->prox = g;
        p = novo;
    }
    return p;
}

TG * insere_sentido(TG * g, int no1, int no2){
    TG * aux = busca_no(g,no1);
    if(!aux)
        return aux;

    TV * novo = (TV *) malloc(sizeof(TV));
    novo->no_viz = no2;
    if(!aux->prim){ // Lista de vizinhos vazia
        novo->prox_viz = NULL;
        aux->prim = novo;
        return g;
    }
    novo->prox_viz = aux->prim;
    aux->prim = novo;
    return g;
}

TV * busca_aresta(TG *g, int no1, int no2){
    TG * aux = busca_no(g, no1), *aux1 = busca_no(g, no2);
    if((!aux) || (!aux1))
        return NULL;

    TV * aux2 = aux->prim;
    while((aux2->no_viz != no2) && (aux2))
        aux2 = aux2->prox_viz;

    return aux2;
}

void ins_aresta(TG *g, int no1, int no2){
    TV * aux = busca_aresta(g,no1,no2); //Testa se já existe aresta
    if(aux)
        return;
    insere_sentido(g,no1,no2);
    insere_sentido(g,no2,no1);
}

void libera_vizinhos(TV * prim_vizinho){
    if(!prim_vizinho)
        return;
    if(prim_vizinho->prox_viz)
        libera_vizinhos(prim_vizinho->prox_viz);

    free(prim_vizinho);
}

void libera(TG *g){
    if(!g)
        return;
    if(g->prox)
        libera(g->prox);
    libera_vizinhos(g->prim);
    free(g);
}


int main()
{
    TG * g = inicializa();

    while(1){
        printf("\n\nINSERIR NO ------- 1\n");
        printf("INSERIR ARESTA --- 2\n");
        printf("LIBERA ----------- 3\n");
        printf("BUSCA NO --------- 4\n");
        printf("IMPRIME GRAFO ---- 5\n");
        printf("Saiir ------------ 6\n");
        int op;
        scanf("%d", &op);

        if(op == 1){
            int x;
            printf("\n\n Digite um numero para inserir: ");
            scanf("%d", &x);
            g = ins_no(g, x);
            printf("\n Inserido!");
        }
        else if( op == 2){
            int no1, no2;
            printf("\n\n Digite dois numeros pra colocar a aresta: ");
            scanf("%d %d", &no1, &no2);
            ins_aresta(g, no1, no2);
            printf("\n Feito!");
        }
        else if( op == 3){
            libera(g);
            printf("\n Liberado!");
        }
        else if( op == 4){
            int x;
            printf("\n O que voce quer?? ");
            scanf("%d", &x);
            TG * aux = busca_no(g, x);
            if(aux)
                printf("\n%d esta no grafo", aux->no);
            else
                printf("\nAchei nao");
        }
        else if( op == 5){
            printf("Ok, imprimindo!\n\n");
            imprime(g);
        }
        else if (op == 6){
            exit(0);
        }
    }
    return 0;
}
