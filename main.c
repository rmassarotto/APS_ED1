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
void imprimirDatabase(Database* db){
    printf("Database: %s\n", db->nome);
    printf("TABELAS \n");
    for (int i = 0; i < db->qtdeTabelas; i++){
        imprimirTabela(db->tabelas[i]);
    }
}

void imprimirTabela(Tabela* table){
    printf("Tabela: %s\n", table->nome);
    //imprime o cabecalho da tabela
    NoAtributo* aux = table->atributos->dir;
    while(aux != table->atributos){
        printf("%s\t", aux->nome);
        aux = aux->dir;
    }
    //imprime os dados
    for (int i = 0; i < table->qtdeTuplas; i++){
        imprimirTupla(table->tuplas[i], table->atributos);
    }
    printf("\n\n");
}

void imprimirTupla(NoDado* sentinelaTupla, NoAtributo* sentinelaAtributo){

    NoDado* auxDado = sentinelaTupla->dir;
    NoAtributo* auxAtributo = sentinelaAtributo->dir;
    while(auxDado != sentinelaTupla){
        printDado(auxDado->dado, auxAtributo->tipo);
        auxDado = auxDado->dir;
        auxAtributo = auxAtributo->dir;
    }

}

void printDado(void* dado, char* tipo){
    /*if(strcmp(tipo,"string")==0){
        printf("%s\t", *(char*)dado);
    } else if (strcmp(tipo,"integer")==0){
        printf("%d\t", *(int*)dado);
    } else if (strcmp(tipo,"float")==0){
        printf("%.2f\t", *(float*)dado);
    }*/
    printf("%s\n", *(char*)dado);

}

//----------------------------------------------------------------------------------------------

Database* criarDatabase(char* nome){
    Database* db = (Database*) malloc(sizeof(Database));
    strcpy(db->nome, nome);
    db->tabelas = calloc(4,sizeof(Tabela));
    db->tamTabelas = 4;
    db->qtdeTabelas = 0;
}

void criarTabela(Database* db, char* nome, char** atributos, char** tipos, int qtdeAtributos){

    NoAtributo* auxNovo;

    db->tabelas[db->qtdeTabelas] = (Tabela*) malloc(sizeof(Tabela));
    strcpy(db->tabelas[db->qtdeTabelas]->nome, nome);
    db->tabelas[db->qtdeTabelas]->atributos = malloc(sizeof(NoAtributo)); //Atributos Sentinela
    db->tabelas[db->qtdeTabelas]->atributos->esq = db->tabelas[db->qtdeTabelas]->atributos;
    db->tabelas[db->qtdeTabelas]->atributos->dir = db->tabelas[db->qtdeTabelas]->atributos;

    for (size_t i = 0; i < qtdeAtributos; i++) {

        auxNovo = (NoAtributo*) malloc(sizeof(NoAtributo));
        strcpy(auxNovo->nome, atributos[i]);
        strcpy(auxNovo->tipo, tipos[i]);
        auxNovo->valores = malloc(sizeof(NoAtributo)); //Sentinela Valores Atributos
        auxNovo->valores->cima = auxNovo->valores;
        auxNovo->valores->baixo = auxNovo->valores;
        //Aloca na ultima posicao de atributos
        auxNovo->esq = db->tabelas[db->qtdeTabelas]->atributos->esq;
        auxNovo->dir = db->tabelas[db->qtdeTabelas]->atributos->esq->dir; //Direita do ultimo para o Sentinela
        db->tabelas[db->qtdeTabelas]->atributos->esq->dir = auxNovo;
        db->tabelas[db->qtdeTabelas]->atributos->esq = auxNovo;

    }
    db->tabelas[db->qtdeTabelas]->tamTuplas = 5;
    db->tabelas[db->qtdeTabelas]->qtdeTuplas = 0;
    db->tabelas[db->qtdeTabelas]->tuplas = calloc(5,sizeof(NoDado));
    db->qtdeTabelas++;
}

void insereTabela(Database* db, char* nome, char** valores, int qtdeTuplas){

    NoDado* auxTupla;
    NoAtributo* auxAtributo;
    int count = 0;

    for (size_t i = 0; i < db->qtdeTabelas; i++) {
        if (strcmp(db->tabelas[i]->nome, nome) == 0) {
            db->tabelas[i]->tuplas[db->tabelas[i]->qtdeTuplas] = malloc(sizeof(NoDado));//Sentinela Tupla
            db->tabelas[i]->tuplas[db->tabelas[i]->qtdeTuplas]->esq = db->tabelas[i]->tuplas[db->tabelas[i]->qtdeTuplas];
            db->tabelas[i]->tuplas[db->tabelas[i]->qtdeTuplas]->dir = db->tabelas[i]->tuplas[db->tabelas[i]->qtdeTuplas] ;

            auxTupla = db->tabelas[i]->tuplas[db->tabelas[i]->qtdeTuplas];
            auxAtributo = db->tabelas[i]->atributos->dir;

            while (auxAtributo != db->tabelas[i]->atributos) {
                auxAtributo->valores->cima->baixo = malloc(sizeof(NoDado));

                auxAtributo->valores->cima->baixo->cima = auxAtributo->valores->cima;
                auxAtributo->valores->cima = auxAtributo->valores->cima->baixo;
                auxAtributo->valores->cima->baixo = auxAtributo->valores;

                auxAtributo->valores->cima->dado = malloc(sizeof(void));
                auxAtributo->valores->cima->dado = valores[count];

                auxTupla->dir = auxAtributo->valores->cima;
                auxAtributo->valores->cima->esq = auxTupla;
                auxAtributo->valores->cima->dir = auxTupla;

                auxTupla = auxTupla->dir;
                auxAtributo = auxAtributo->dir;
                count++;
            }
            //return 0;
        }
    }
}

int main(){

    char* atributos[3] = {"ra", "nome", "nota"};
    char* tipos[3] = {"integer", "string", "float"};

    char* atributosProfessor[3] = {"id", "nome", "materia"};
    char* tiposProfessor[3] = {"integer", "string", "string"};

    char* atributosTurma[4] = {"codTurma", "nome", "qtdeAlunos", "codProfessor"};
    char* tiposTurma[4] = {"integer", "string", "integer", "integer"};

    char* valores[3] = {"12345", "Rodrigo", "6"};
    //char* valores2[3] = {"Rodrigo", "Rodrigo", "Rodrigo"};

    Database* db = criarDatabase("Universidade");
    criarTabela(db, "Alunos", atributos, tipos, 3);
    criarTabela(db, "Professores", atributosProfessor, tiposProfessor, 3);
    criarTabela(db, "Turma", atributosTurma, tiposTurma, 4);
    insereTabela(db, "Alunos", valores, 3);
    insereTabela(db, "Professores", valores, 3);
    imprimirDatabase(db);
    //imprimirTabela(db->tabelas[2]);
    //printf("%s\n %d\n %d\n %s", db->nome, db->tamTabelas, db->qtdeTabelas, db->tabelas[0]->atributos->dir->dir->valores->baixo->dado);





    //imprimirDatabase(db);
}
