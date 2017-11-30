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

Database* criarDatabase(char* nome){
  Database* db = (Database*) malloc(sizeof(Database));
  strcpy(db->nome, nome);
  db->tabelas =  NULL;
  db->tamTabelas = 4;
  db->qtdeTabelas = 0;
}

int main(){
    Database* db = criarDatabase("Universidade");
    printf("%s\n %d\n %d", db->nome, db->tamTabelas, db->qtdeTabelas);


    //criarTabela(db, "Alunos", {"ra", "nome", "nota"}, {"integer", "string", "float"}, 3);
    //imprimirDatabase(db);
}
