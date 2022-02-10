#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Veiculo {
	
	char modelo[15];
	int quantidade;
	float valor;
	int test_drive;
	
}tipoVeiculo;

tipoVeiculo *aloca(int num);

void main(){
	int quantLinhas1 = 0, quantLinhas2 =0;
	
	FILE *arquivo1, *arquivo2;
	
	//Arquivo 1
	
	arquivo1 = fopen("bcx_pg1.txt", "r");
	
	if(arquivo1 == NULL){
		printf("Nao foi possivel abrir o arquivo 1!\n");
		return;
	}
	
	quantLinhas1 = contaLinhas(arquivo1);
	
	tipoVeiculo *concessionaria1 = aloca(quantLinhas1);
	
	rewind(arquivo1);
	
	preencheVeiculos(arquivo1, concessionaria1, quantLinhas1);
	
	fclose(arquivo1);
	
	//Arquivo 2
	
	arquivo2 = fopen("bcx_pg2.txt", "r");
	
	if(arquivo2 == NULL){
		printf("Nao foi possivel abrir o arquivo 2!\n");
		return;
	}
	
	quantLinhas2 = contaLinhas(arquivo2);
	
	tipoVeiculo *concessionaria2 = aloca(quantLinhas2);
	
	rewind(arquivo2);
	
	preencheVeiculos(arquivo2, concessionaria2, quantLinhas2);
	
	fclose(arquivo2);
	
	// Unificar
	
	tipoVeiculo *concessionaria3 =  aloca(quantLinhas2+quantLinhas1);
	
	unificar(concessionaria1, concessionaria2, concessionaria3, quantLinhas1, quantLinhas2);
	
	printf("\n\n\n");
	
	
	for(int i = 0; i<quantLinhas1+quantLinhas2; i++){
		printf("%s %d %.3f %d\n", (concessionaria3+i)->modelo, (concessionaria3+i)->quantidade, (concessionaria3+i)->valor, (concessionaria3+i)->test_drive);
	}
	
}

void unificar(tipoVeiculo *concessionaria1, tipoVeiculo *concessionaria2, tipoVeiculo *concessionaria3, int quantLinhas1, int quantLinhas2){
	
	if(quantLinhas1 >= quantLinhas2){
		for(int i = 0; i<quantLinhas1+quantLinhas2; i++){
			if( i <= quantLinhas1 ){
				
				strcpy((concessionaria3+i)->modelo, (concessionaria1+i)->modelo);
				(concessionaria3+i)->quantidade = (concessionaria1+i)->quantidade;
				(concessionaria3+i)->valor = (concessionaria1+i)->valor;
				(concessionaria3+i)-> test_drive =  (concessionaria1+i)->test_drive;
				
				for(int j = 0; j<quantLinhas2; j++){
					
					if(strcmp((concessionaria1+i)->modelo, (concessionaria2+j)->modelo) == 0){
						(concessionaria3+i)->quantidade += (concessionaria2+j)->quantidade;
						if((concessionaria3+i)->test_drive == 0 && (concessionaria2+j)->test_drive == 1) (concessionaria3+i)->test_drive = (concessionaria2+j)->test_drive;
						
						strcpy((concessionaria2+j)->modelo, "x");
						(concessionaria2+j)->quantidade = 0;
						(concessionaria2+j)->valor =  0;
						(concessionaria2+j)->test_drive =  0;
					}	
				}	
			}
			else{
				
				if(strcmp((concessionaria2+i-quantLinhas1)->modelo, "x") != 0){
					strcpy((concessionaria3+i)->modelo, (concessionaria2+i-quantLinhas1)->modelo);
					(concessionaria3+i)->quantidade = (concessionaria2+i-quantLinhas1)->quantidade;
					(concessionaria3+i)->valor = (concessionaria2+i-quantLinhas1)->valor;
					(concessionaria3+i)->test_drive = (concessionaria2+i-quantLinhas1)->test_drive;
				}
			}	
		}
	}
	else{
		for(int i = 0; i<quantLinhas2+quantLinhas1; i++){
			if( i <= quantLinhas2 ){
				
				strcpy((concessionaria3+i)->modelo, (concessionaria2+i)->modelo);
				(concessionaria3+i)->quantidade =  (concessionaria2+i)->quantidade;
				(concessionaria3+i)->valor = (concessionaria2+i)->valor;
				(concessionaria3+i)-> test_drive =  (concessionaria2+i)->test_drive;
				
				for(int j = 0; j<quantLinhas1; j++){
					
					if(strcmp((concessionaria2+i)->modelo, (concessionaria1+j)->modelo) == 0){
						(concessionaria3+i)->quantidade += (concessionaria1+j)->quantidade;
						if((concessionaria3+i)->test_drive == 0 && (concessionaria1+j)->test_drive == 1) (concessionaria3+i)->test_drive = (concessionaria1+j)->test_drive;
						
						strcpy((concessionaria1+j)->modelo, "x");
						(concessionaria1+j)->quantidade = 0;
						(concessionaria1+j)->valor =  0;
						(concessionaria1+j)->test_drive =  0;
					}		
				}	
			}
			else{
				
				if(strcmp((concessionaria1+i-quantLinhas1)->modelo, "x") != 0){
					strcpy((concessionaria3+i)->modelo, (concessionaria1+i-quantLinhas1)->modelo);
					(concessionaria3+i)->quantidade = (concessionaria1+i-quantLinhas1)->quantidade;
					(concessionaria3+i)->valor = (concessionaria1+i-quantLinhas1)->valor;
					(concessionaria3+i)->test_drive = (concessionaria1+i-quantLinhas1)->test_drive;
				}	
			}	
		}
	}
}

tipoVeiculo *aloca(int num){
	
	tipoVeiculo *p;
    p = (tipoVeiculo*)malloc(num*sizeof(tipoVeiculo));

    if(p == NULL) printf("Erro de alocação!\n");

    return p;
	
}

int contaLinhas(FILE *arquivo){
	
	char c, barran = '\n';
	int quantLinhas = 0;
	
	while(fread (&c, sizeof(char), 1, arquivo)) {
        if(c == barran) {
            quantLinhas++;
        }
    }
    
    return quantLinhas+1;
}

void preencheVeiculos(FILE *arquivo, tipoVeiculo *concessionaria, int num){
	
	while(!feof(arquivo)){
		
		for(int i; i<num; i++){
			
			fscanf(arquivo, "%s %d %f %d", (concessionaria+i)->modelo, &(concessionaria+i)->quantidade, &(concessionaria+i)->valor, &(concessionaria+i)->test_drive);
			printf("%s %d %.3f %d\n", (concessionaria+i)->modelo, (concessionaria+i)->quantidade, (concessionaria+i)->valor, (concessionaria+i)->test_drive);
		}
	}
}
