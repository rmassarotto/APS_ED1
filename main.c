#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct noDado{
    void* dado;
    int tamDado;
    struct noDado* dir;
    struct noDado* esq;
    struct noDado* cima;
    struct noDado* baixo;
} NoDado;

typedef struct noAtributo{
    char nome[30];
    char tipo[30];
    NoDado* valores;
    struct noAtributo* dir;
    struct noAtributo* esq;
} NoAtributo;

typedef struct {
    char nome[30];
    NoAtributo* atributos;
    NoDado** tuplas;
    unsigned short int tamTuplas;
    unsigned short int qtdeTuplas;
} Tabela;

typedef struct {
    char nome[30];
    Tabela** tabelas;
    unsigned short int tamTabelas;
    unsigned short int qtdeTabelas;
} Database;

//---------------------------------------------------------------------------------

Database* criarDatabase(char* nome){
    Database* db = (Database*) malloc(sizeof(Database));
    strcpy(db->nome, nome);
    db->tabelas = calloc(4,sizeof(Tabela));
    db->tamTabelas = 4;
    db->qtdeTabelas = 0;
}

void criarTabela(Database* db, char* nome, char* atributos, char* tipos, int qtdeAtributos){

    NoAtributo* aux;
    NoAtributo* auxAnterior;

    db->tabelas[db->qtdeTabelas] = (Tabela*) malloc(sizeof(Tabela));
    strcpy(db->tabelas[db->qtdeTabelas]->nome, nome);
    db->tabelas[db->qtdeTabelas]->atributos = malloc(sizeof(NoAtributo)); //Sentinela Atributos
    for (size_t i = 0; i < qtdeAtributos; i++) {
        aux = (NoAtributo*) malloc(sizeof(NoAtributo));
        aux->valores = malloc(sizeof(NoAtributo)); //Sentinela Valores Atributos
        aux->valores->cima = aux->valores;
        aux->valores->baixo = aux->valores;
        if (i == 0) {
            aux->nome = atributos[0];
            aux->tipo = tipos[0];
            db->tabelas[db->qtdeTabelas]->atributos->dir = aux;
            aux->esq = db->tabelas[db->qtdeTabelas]->atributos->dir
        }else{

        }
    }
}

int main(){

    char* atributos[3] = {"ra", "nome", "nota"};
    char* tipos[3] = {"integer", "string", "float"};

    Database* db = criarDatabase("Universidade");
    criarTabela(db, "Alunos", atributos, tipos, 3);
    printf("%s\n %d\n %d\n %s", db->nome, db->tamTabelas, db->qtdeTabelas, db->tabelas[0]->nome);





    //imprimirDatabase(db);
}
