#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct Pedaco {
float trechoDaBr;
char tipo;
int upvotes;
struct Pedaco *proximo;
} Trecho;

typedef struct Rua {
int br;
Trecho *inicioTrecho;
struct Rua *proximo;
} Estrada;

void carregarArquivo(char nomeArquivo[]);
void carregarConsolidado(char nomeConsolidado[]);
void processarArquivo (Estrada **estradasPonteiro, Estrada *estradas, int br, float trechoDaBr, char tipo);
void compararArquivos (Estrada *estradas, Estrada *dados);
void salvarArquivo(Estrada *estrada, char nomeConsolidado[]);

void main(){
char nomeArquivo[] = "alertas_100000_1.csv";
char nomeConsolidade[] = "dadosConsolidados.csv";
carregarArquivo (nomeArquivo);
carregarConsolidado(nomeConsolidade);
}

void carregarArquivo (char nomeArquivo[]){
FILE* carregado = fopen(nomeArquivo, "r");
if (carregado == NULL){
    printf("Nao foi possivel abrir o arquivo");
    return;
}
int lixo1, lixo2, br;
float trechoDaBr;
char tipo;
int controle = 0;
Estrada *estradas = NULL;
while (fscanf (carregado, "%d;%d;%d;%f;%c", &lixo1, &lixo2, &br, &trechoDaBr, &tipo) == 5){
    if (controle == 0) {
        controle++;
        continue;
    }
    float parteInteira = floorf(trechoDaBr);
    float parteFracionaria = trechoDaBr - parteInteira;
    if (parteFracionaria < 0.5) {
        trechoDaBr = parteInteira;
    } else {
        trechoDaBr = parteInteira + 0.5;
    }
    processarArquivo(&estradas, estradas, br, trechoDaBr, tipo);
}
controle = 0;
fclose(carregado);
}

void processarArquivo (Estrada **estradasPonteiro, Estrada *estradas, int br, float trechoDaBr, char tipo) {
int controle = 0;
Estrada *copia = estradas;
if (copia != NULL) {Trecho *copia2 = copia->inicioTrecho; Trecho *copia3;
while (copia != NULL){
    if (br == copia->br){
        while(copia2 != NULL){
            if (trechoDaBr == copia2->trechoDaBr){
                copia2->upvotes++;
                break;
            }
            if (copia2->proximo == NULL){
                copia3 = copia2;
            }
            copia2 = copia2->proximo;}
        if (copia2 == NULL){
            Trecho *noTrecho = (Trecho*) malloc(sizeof(Trecho));
            copia3->proximo = noTrecho;
            noTrecho->tipo = tipo;
            noTrecho->trechoDaBr = trechoDaBr;
            noTrecho->upvotes = 1;
            noTrecho->proximo = NULL;
        }
    }
    copia = copia->proximo;
    if (copia !=NULL) {
    copia2 = copia->inicioTrecho;
    }}}
if (*estradasPonteiro == NULL){controle++;}
else if (copia != NULL && copia->proximo == NULL){controle = 2;}
if (controle != 0) {
    Estrada *noBR = (Estrada*) malloc(sizeof(Estrada));
    if (noBR == NULL) {
        printf("Erro");
        return;
    }
    noBR->br = br;
    noBR->proximo = NULL;
    Trecho *noTrecho = (Trecho*) malloc(sizeof(Trecho));
    if (noTrecho == NULL) {
        printf("Erro");
        return;
    }
    noBR->inicioTrecho = noTrecho;
    noTrecho->tipo = tipo;
    noTrecho->trechoDaBr = trechoDaBr;
    noTrecho->upvotes = 1;
    if (controle == 1){
    *estradasPonteiro = noBR;
    } else {
    if (copia != NULL){
    copia->proximo = noBR;
    }}
    return;
}
}

void carregarConsolidado(char nomeConsolidado[]){
FILE *consolidado = fopen(nomeConsolidado, "r");
if (consolidado == NULL) {
    printf("Nao existe arquivos anteriormente salvo\n");
    printf("Um novo arquivo sera criado\n");
    return;
}
Estrada *dados = NULL;
int controle = 0;
int br, upvotes;
float trecho;
char tipo;
Estrada *copia = dados;
while (fscanf(consolidado, "%d;%f;%c;%d", &br, &trecho, &tipo, &upvotes) == 4){
if (controle == 0){
    controle++;
    continue;
}
int controle2 = 0;
if (dados == NULL){
    controle2 = 1;
}
if (controle2 == 0){
while(1){
if (copia->br == br){
    controle2 = 3;
    break;
}
else if (copia->proximo == NULL){
    controle2 = 2;
    break;
}
copia = copia->proximo;

}}
else{
if (controle2 == 1 || controle2 == 2){
Estrada *noBR = (Estrada*) malloc(sizeof(Estrada));
noBR->br = br;
noBR->proximo = NULL;
Trecho *noTrecho = (Trecho*) malloc(sizeof(Trecho));
noBR->inicioTrecho = noTrecho;
noTrecho->trechoDaBr = trecho;
noTrecho->upvotes = upvotes;
noTrecho->proximo = NULL;
if (controle2 == 1){
dados = noBR;
copia = dados;
}
else if (controle2 == 2){
    copia->proximo = noBR;
    copia = dados;
}
else {
Trecho *trecho2 = copia->inicioTrecho;
while(1){
    if (trecho2->proximo == NULL){
        Trecho *noTrecho = (Trecho*) malloc(sizeof(Trecho));
        noTrecho->trechoDaBr = trecho;
        noTrecho->upvotes = upvotes;
        noTrecho->proximo = NULL;
        trecho2->proximo = noTrecho;
    }
    trecho2 = trecho2->proximo;
}
}}
}
}
}

void salvarArquivo(Estrada *estrada, char nomeConsolidado[]){
FILE *salvo = fopen(nomeConsolidado, "w");
if (salvo == NULL){
    printf("Erro ao salvar arquivo");
    return;
}
Estrada *copia = estrada;
Trecho *copia2 = copia->inicioTrecho;
fprintf(salvo, "br;trecho;tipo;upvotes");
while (copia->inicioTrecho != NULL){
    fprintf(salvo, "%d;%f;%c;%d\n", copia->br, copia2->trechoDaBr, copia2->tipo, copia2->upvotes);
    copia2 = copia2->proximo;
    copia = copia->proximo;
}
printf("Arquivo salvo com sucesso!");
fclose(salvo);
}

