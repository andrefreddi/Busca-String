#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
# include <conio.h>
# include <time.h>

void forcabruta();
void rabinkarp();
void menu();
void menudeop();

int main(){
	
	//Corzinha ui ui
	system("color 3");
	printf(" > Busca em Strings < \n\n\n");
	menu();
}

void menu(){
	
	setlocale(LC_ALL, "Portuguese");

    //Defina aqui qual eh o arquivo que vc quer abrir!
    char nomeArquivo[30];
    printf(" > Qual sera o arquivo que deseja abrir?\n > ");
    fgets(nomeArquivo, 30, stdin);
    nomeArquivo[strcspn(nomeArquivo, "\n")] = 0;
    //Aqui vai ficar o nome do arquivo digitado
    
    system("@cls||clear");//deixa eu limpa sua tela vai
    
    //Aqui vai abrir o tal arquivo!
    char palavras[9999];
    FILE *arq;
    arq = fopen(nomeArquivo, "r");
    
    
    //Se der erro da isso ai
    
    
    if(arq == NULL){
	
		printf(" > Erro 404\n");
		system("pause");
		system("@cls||clear");
		printf(" > Tente novamente <\n\n\n");
		menu();
		
	
	}else{
	

    while( (fgets(palavras, sizeof(palavras), arq))!=NULL )
	
   		fclose(arq);
		//nao podemos esquecer de fechar ne
    	printf("\n > O arquivo carregado contem:\n > %s\n\n\n", palavras);
    }
    
		
    //Digite por gentileza se nao for imcomodo a frase
    char frase[50];
    printf(" > Digite uma frase que deseja buscar:\n > ");
    fgets(frase, 50, stdin);
    frase[strcspn(frase, "\n")] = 0;
    //Frase salva
    
    menudeop(palavras, frase);
}
 
 	//AQUI INICIA UM MENU PROPRIO
    
    void menudeop(char palavras[], char frase[]){
	
    static int opcao;
    do
    {
    	system("@cls||clear");
    	printf(" > De que forma voce deseja buscar a sua palavra?\n\n");
    	printf(" > 1 < Forca Bruta\n");
    	printf(" > 2 < Rabin Karp");
    	printf("\n > 3 < Sair");
    	printf("\n > ");
        scanf("%d%*c", &opcao);
		
        switch(opcao)
        {
            case 1:
                forcabruta(palavras, frase);
            break;
            
            case 2:
            	rabinkarp(palavras, frase);
           break;
           
            
        }
		
	}while(opcao!=3);

}

	//FIM DE MENU PROPRIO

	//INICIA A FORCA BRUTA
	
	
void forcabruta(char palavras[], char frase[])
{
	
	// Mo bagunca deixa eu limpa sua tela
	system("@cls||clear");
	
	
	printf(" > Forca bruta < \n\n\n");
	
	
	
	int tPalavra = strlen(palavras); //Define tamanho da string
    int tFrase = strlen(frase); //Define tamanho da frase que busca
    
    int cont = 0; //Contador para conclusÃ£o
    int k = 0; //contador usado na string e na frase
    int j = 0; //Contador usado na frase
    int i = 0; //Contador usado na string

    for (i=0;  i < tPalavra - tFrase; i++) { //Define o tamanho da string qual ainda Ã© valido tentar a comparaÃ§Ã£o, e define primeira letra da string.
        k=i;  cont=1;
        for(j=0 ; j < tFrase; j++) { //Define primeira letra da string
            if ((palavras[k]==frase[j])  && (cont != tFrase)){ //Compara primeira letra da frase com a posiÃ§Ã£o atual da string
            cont++;k++; //Se igual soma o contador para conclusÃ£o e a posiÃ§Ã£o da string (k)
            }//Ao retornar para o for soma a posiÃ§Ã£o da frase (j)
        }//Ao retornar para o primeiro for soma a posiÃ§Ã£o da string (i)
            if (cont == tFrase){ //Se o tamanho do contador de conclusÃ£o somar ate chegar ao tamanho da frase quer dizer que a string foi encontrada.
                printf(" > A frase mencionada comeca na posicao %d e termina na posicao %d do array.\n > ", i, k); //Imprimi a posicao de inicio e fim
                for (i; i <= k; i++){ //Imprimir cada letra
                    printf("%c", palavras[i]);
                }
                printf("\n\n\n");
                system("pause");
               
            } 
    }
    printf(" > Frase nao foi encontrada.\n");
    system("pause");
    return 0; //Finaliza com o resultado NUll OK
	
}

	//FIM FORCA BRUTA
	
void rabinkarp(char palavras[], char frase[]){
	
	system("@cls||clear");
	printf(" > Rabin Karp < \n\n\n");
	
	
    int d = 256, q = 29;
    int tPalavra = strlen(palavras); //Define tamanho da string
    int tFrase = strlen(frase); //Define tamanho da frase que busca
    int i, h = 1;
    int hPalavra = 0; //Hash (tamanho) para string
    int hFrase = 0; //Hash (tamanho) para frase

    for (i = 0; i < tFrase - 1; i++)
        h = d * h % q;
    //Calcula o valor do hash da frase e o primeiro da string (palavra)
    for (i = 0; i < tFrase; i++)
    {
        hFrase = (d * hFrase + frase[i]) % q;
        hPalavra = (d * hPalavra + palavras[i]) % q;
    }

    for (i = 0; i <= tPalavra - tFrase; i++)
    {
        if (hFrase == hPalavra) //Compara o hash da string atual com o hash da frase, se for igual ele compara cada caractere para garantir que a frase corresponde a string.
        {
            int j;
            for (j = 0; j < tFrase; j++)
            {
                if (frase[j] != palavras[i + j])
                    break;
            }
            if (tFrase == j){ //Se o tamanho da String (tFrase) for do mesmo tamanho do (j) quer dizer que a string foi encontrada.
                int k = i + tFrase -1; //Calcula posiÃ§Ã£o final da frase para imprimir na tela
                printf(" > A frase mencionada comeca na posicao %d e termina na posicao %d do array.\n > ", i, k); //Imprimi a posicao de inicio e fim
                for (i; i <= k; i++){ //Imprimir cada letra
                    printf("%c", palavras[i]);
                }
                
                printf("\n\n\n");
                system("pause");
                return 0; //Finaliza
            }
        }
        hPalavra = (d * (hPalavra - palavras[i] * h) + palavras[i + tFrase]) % q;
        if (hPalavra < 0)
            hPalavra = hPalavra + q;
    }
    printf(" > Frase nao foi encontrada.\n");
    system("pause");
    return 0; //Finaliza com o resultado NUll OK.
	
	
}
