#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "huffman.h"

#define TAM 256

int main(int argc, char *argv[]){

	unsigned char *texto;
	unsigned int tab_frequencia[TAM];
	Lista lista;
	No* arvore;
	char** dicionario;
	char* texto_codificado;
	char* texto_decodificado;

	int opcao, colunas;

	if(argc > 1){

		texto = aloca_memoria_texto(argv[1]);
		ler_arquivo_txt(texto, argv[1]);

		//tabela de frequencia
		preencher_tabela_freq(tab_frequencia, texto);

		//lista
		inicializa_lista(&lista);
		preencher_lista(&lista, tab_frequencia);

		//arvore
		arvore = criar_arvore(&lista);

		//dicionario
		colunas = altura_da_arvore(arvore) + 1;
		dicionario = aloca_dicionario(colunas);
		criar_dicionario(dicionario, arvore, "", colunas);
		
		//codificacao
		texto_codificado = codificacao(dicionario, texto);

		//decodificacao
		texto_decodificado = decodificacao(arvore, texto_codificado);
		
		do{
			menu();	
			scanf("%d", &opcao);
			switch (opcao){
			
			case 0://encerrar programa
				printf("Programa encerrado com sucesso!\n");
				break;

			case 1://compactacao
				compactacao(texto_codificado);
				break;
			
			case 2://descompactacao
				descompactar(arvore);
				break;
			
			case 3://imprimir tabela ascii
				imprimir_tabela_ascii(tab_frequencia);
				break;
			
			case 4://imprimir tabela de frequencia
				imprimir_tabela_freq(tab_frequencia);
				break;
			
			case 5://imprimir lista encadeada
				preencher_lista(&lista, tab_frequencia);
				imprimir_lista(&lista);
				break;
			
			case 6://imprimir arvore
				printf("\nArvore de Huffman:\n");
				printf("Altura     Folha\n");
				imprimir_arvore(arvore, 0);
				break;

			case 7://imprimir dicionario
				printf("\nDicionario:\nCaracter       Codigo\n");
				imprimir_dicionario(dicionario);
				break;

			case 8://imprimir texto codificado
				printf("\nTexto codificado: %s\n", texto_codificado); 
                break;				
			
			case 9://imprimir texto decodificado
				printf("\nTexto decodificado: %s\n", texto_decodificado); 
                break;

			default:
				printf("\nOpcao Invalida\n");
				break;
			}
		}
		while(opcao != 0);

		//liberar memoria
		free(texto);
		free(texto_codificado);
		free(texto_decodificado);
		libera_lista(&lista);
		libera_arvore(arvore);
		libera_dicionario(dicionario);
	}

	else{ //nao foi passado um arquivo como argumento
		printf("Passe um arquivo texto como argumento na execucao do programa\n");
		return -1;
	}

	return 0;
}
