#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


struct Aviao *lista = NULL;

struct Aviao {
    int HorarioPartida;
    int HorarioChegada;
    int CodigoVoo;
    int CodigoAeroPartida;
    int CodigoAeroChegada;
    struct Aviao *proximo;
};

struct Passagens {
    int CodigoVoos;
    int RGpassageiro;
    struct passagens *proximo;
};

struct Passagens *lista1 = NULL;


int main(void) {
    lerArquivoCSV("voos.csv");
    lerArquivoPassagens("passagens.csv");
    int codigovoo, rg, op, num;
    while (1){
        printf("\n----------------------- UPE VOOS ------------------------\n");
        printf("Digite 1 para gerar o relatoria dos voos:\nDigite 2 para comprar um passagem:\nDigite 3 para gerar relatorio de voos por aeroporto:\nDigite 0 Para encerrar o programa:\n ");
         printf("\n---------------------------------------------------------\n");
        scanf("%i", &op);
        switch (op)
        {
        case 1:
            gerarRelatorio(lista);
            break;
        case 2:
            printf("Digite o codigo do voo: ");
            scanf("%i", &codigovoo);
            if (testeCod(lista,codigovoo)){
                printf("Digite o RG do passageiro:");
                scanf("%i",&rg);
                RealizarVenda(&lista1,codigovoo,rg);
            }else{
                printf("Codigo de voo invalido");
            }
            //imprimirListateste(lista1);
            break;
        case 3:
            num =145;
            printf("\n--------------- Relatorio por Aeroporto -------------------\n");
            while(num<=154){
            imprimirLista(lista,num);
            num+=1;
            }
            break;
    }
    if (op==0){
        escreverArquivo("passagens.csv");
        break; //encerra programa
    }
}}

int addFinal(struct Aviao inicio){
    struct Aviao *novoNo = malloc(sizeof(struct Aviao));
    if (novoNo !=NULL){
        *novoNo = inicio;
        novoNo->proximo = NULL;

    if (lista == NULL){
        lista = novoNo;
    }else{
        struct Aviao *noAtual = NULL;
        noAtual = lista;

        while (noAtual->proximo != NULL){
            noAtual=noAtual->proximo;
        }
        noAtual->proximo=novoNo;
    }
    return 1;
    }else{
    return 0;}
}

void imprimirListateste(struct Passagens *inicio){
    struct Passagens *noAtual = inicio;
    while (noAtual != NULL){
        printf("%i;%i\n",noAtual->CodigoVoos,noAtual->RGpassageiro);
        noAtual = noAtual->proximo;
        }
    }

void lerArquivoCSV(char nomeArquivo[]){
	FILE *pontArquivo = fopen(nomeArquivo,"r");
	if (pontArquivo != NULL) {
        struct Aviao ra;
            while (!feof(pontArquivo)){
                fscanf(pontArquivo, "%i;%i;%i;%i;%i\n", &ra.HorarioPartida, &ra.HorarioChegada, &ra.CodigoVoo, &ra.CodigoAeroPartida, &ra.CodigoAeroChegada);
                addFinal(ra);
		}
		fclose(pontArquivo);
	} else {
		puts("Nao foi possível abrir arquivo");
	}
}

void gerarRelatorio(struct Aviao *inicio) {
   struct Aviao *noAtual = inicio;
   int cod;
   printf("Digite o codigo do voo para gerar o relatorio:\n ");
   scanf("%i",&cod);
   while(noAtual !=NULL){
        if(cod == noAtual->CodigoVoo){
            float diff = difftime(noAtual -> HorarioChegada, noAtual-> HorarioPartida);
            diff=diff/60;
            diff=diff/60;
            printf("Voo: %i\n", noAtual->CodigoVoo);
            printf("Aero partida: %i - Aero Chegada: %i\n",noAtual->CodigoAeroPartida,noAtual->CodigoAeroChegada);
            printf("Duracao: %.2f hs\n",diff);
            printf("Listagem de passageiros (RG's):\n ");
            printf("---------------------------------------------------------\n");
            imprimirListaPassagens(lista1, cod);
        }
    break;
   }
}

void lerArquivoPassagens(char nomeArquivo[]){
	FILE *pontArquivo = fopen(nomeArquivo,"r");
	if (pontArquivo != NULL) {
        struct Passagens ra;
            while (!feof(pontArquivo)){
                fscanf(pontArquivo, "%d;%d\n", &ra.CodigoVoos, &ra.RGpassageiro);
                addFinalPassagens(ra);
		}
		fclose(pontArquivo);
	}
}


int addFinalPassagens(struct Passagens inicio){
    struct Passagens *novoNo = malloc(sizeof(struct Passagens));
    if (novoNo !=NULL){
        *novoNo = inicio;
        novoNo->proximo = NULL;
        imprimirListateste(lista1);//não sei porque adiciona elemento na struct sozinho

    if (lista1 == NULL){
        lista1 = novoNo;
    }else{
        struct Passagens *noAtual = NULL;
        noAtual = lista1;

        while (noAtual->proximo != NULL){
            noAtual=noAtual->proximo;

        }
        noAtual->proximo=novoNo;

    }
    return 1;
    }else{
    return 0;}
}

void testeCod(struct Aviao *inicio,int codigovoo){
    struct Aviao *noAtual = inicio;

    while(noAtual !=NULL){
        if (codigovoo == noAtual->CodigoVoo){
            return 1;
        }
        noAtual = noAtual->proximo;
    }
    return 0;
}


void imprimirListaPassagens(struct Passagens *inicio, int codigo){
    struct Passagens *noAtual = inicio;
    while (noAtual != NULL){
        if (codigo == noAtual->CodigoVoos){
            printf("%i\n",noAtual->RGpassageiro);
        }
     noAtual = noAtual->proximo;
    }
}


int RealizarVenda(struct Passagens **inicio, int valor,int valor2){
    struct Passagens *novoNo = malloc(sizeof(struct Passagens));

    if (novoNo != NULL){
        novoNo->CodigoVoos = valor;
        novoNo->RGpassageiro = valor2;
        novoNo->proximo = NULL;

        if (*inicio == NULL) {
            *inicio = novoNo;
        } else {
            struct Passagens *noAtual = NULL;

            noAtual = *inicio;
            while (noAtual->proximo != NULL){
                noAtual = noAtual->proximo;
            }

            noAtual->proximo = novoNo;
        }

        return 1;
    } else {
        return 0;
    }
}

void imprimirLista(struct Aviao *inicio, int num){
    struct Aviao *noAtual = inicio;
    int contchegada=0, contpartida=0;
    while (noAtual != NULL){
        if (noAtual->CodigoAeroChegada == num){
            contchegada+=1;}
        if (noAtual->CodigoAeroPartida == num){
            contpartida+=1;}
    noAtual = noAtual->proximo;
        }
        printf("Aeroporto: %i --- Partidas: %i, Chegadas: %i\n",num,contpartida,contchegada);
    }

void escreverArquivo(char nomeArquivo[]){
	FILE *pontArquivo = fopen(nomeArquivo,"w");
    struct Passagens *noAtual = NULL;
    noAtual = lista1;
	if (pontArquivo != NULL) {
     while (noAtual != NULL){
      fprintf(pontArquivo, "%i;%i\n",noAtual->CodigoVoos, noAtual->RGpassageiro);
      noAtual=noAtual->proximo;
    }
  }
  fclose(pontArquivo);

}
