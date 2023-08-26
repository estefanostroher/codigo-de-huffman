#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "huffman.h"

#define TAM 256

//FUNCOES TABELA DE FREQUENCIA

// Inicia a tabela de frequência com 0 em todas as posições do vetor.
void iniciar_tabela_freq(unsigned int *tabela){
	int i = 0;						   
	
	for(i = 0; i < TAM; i++){
		tabela[i] = 0;
	}
}

// Enquanto str for diferente do fim do vetor, conta quantas vezes cada caracter se repete.
void preencher_tabela_freq(unsigned int *tabela, unsigned char *str){
	int i = 0;

	iniciar_tabela_freq(tabela);
	while(str[i] != '\0'){
		tabela[str[i]]++; // Conta as repetições de cada caracter.
		i++;
	}
}

//FUNCOES LISTA ENCADEADA

// Inicia a lista com o início NULL e o tamanho igual a 0.
void inicializa_lista(Lista *lista){
	lista->inicio = NULL;
	lista->tam = 0;
}

// Função para inserir ordenado na lista.
void inserir_na_lista(No *no, Lista *lista){
	No *aux;
	// Se a minha lista for vazia, então insere no início.
	if(lista->inicio == NULL){   
		lista->inicio = no;   
		lista->tam++;
	}
	// Se a frequência do novo caracter é menor que a frequência do caracter do início.
	else if(no->frequencia < (lista)->inicio->frequencia){ 
		no->proximo = lista->inicio;	   
		lista->inicio = no;
		lista->tam++;			   
	}
	
	else{
		aux = lista->inicio;
		// Se o próximo nó existir e a frequência do novo caracter for maior que a frequência do próximo caracter, anda pela lista.
		while(aux->proximo && no->frequencia >= aux->proximo->frequencia){
			aux = aux->proximo;
		}
		no->proximo = aux->proximo;
		aux->proximo = no;
		lista->tam++;
	}
}

// Função para preencher a lista.
void preencher_lista(Lista *lista, unsigned int *tabela){
	No *novo;
	int i = 0;

	for(i = 0; i < TAM; i++){
		if(tabela[i] > 0){ // Só vai preencher a lista se a frequẽncia for maior que 0.
			novo = calloc(1, sizeof(No));
			novo->caracter = i; // Caracter é representado pelo i.
			novo->frequencia = tabela[i]; // Número de freq. de cada caracter da tabela.
			novo->esquerda = NULL;
			novo->direita = NULL;
			novo->proximo = NULL;
			inserir_na_lista(novo, lista); // Inserindo na lista.
		}
	}
}

// Função para remover as duas primeiras freq. da lista que já estão ordenadas e colocar na árvore.
No* remover_da_lista(Lista *lista){
	No *remover = NULL;

	if(lista->inicio){ // Se a lista não for nula entra aqui.
		remover = lista->inicio; // Removo o início da lista.
		lista->inicio = remover->proximo; // O início da lista recebe o remover->proximo.
		lista->tam--;
	}
	return remover; //retorna o nó removido ou NULL, caso a lista esteja vazia.
}

//desaloca memoria da lista encadeada
void libera_lista(Lista* lista){
	No* aux = lista->inicio;
	No* aux2;
	while(aux!=NULL){
		aux2 = aux->proximo;
		free(aux);
		aux = aux2;
	}
}

//FUNCOES ARVORE

// Função para criar a árvore de huffman.
No* criar_arvore(Lista *lista){
	No *novo, *aux, *primeiro, *segundo;

	while(lista->tam >= 2){
		primeiro = remover_da_lista(lista); // O ponteiro "primeiro" remove o inicio da lista(primeiro).
		segundo = remover_da_lista(lista);  // O ponteiro "segundo" remove o início da lista(segundo).
		novo = calloc(1, sizeof(No));
		novo->caracter = 'P'; // Nó intermediário, nó pai recebe 'P'.
		novo->frequencia = primeiro->frequencia + segundo->frequencia; // Soma das frequências removidas.
		novo->esquerda = primeiro; // Novo elemento da esquerda aponta pro primeiro nó removido.
		novo->direita = segundo; // Novo elemento da direita aponta pro segundo nó removido.
		novo->proximo = NULL;
		inserir_na_lista(novo, lista); // Insere ordenado.
	}
	return lista->inicio; // Entra aqui quando o tamanho da lista for menor que 2, ou seja, retorna apenas o lista->inicio.
}

// Função para descobrir qual o caminho mais distante entre a raiz e a última folha.
int altura_da_arvore(No *raiz){
    int esquerda, direita;

    if(raiz == NULL){
        return -1;
    }
    else{
        esquerda = altura_da_arvore(raiz->esquerda) + 1;
        direita = altura_da_arvore(raiz->direita) + 1;

        if(esquerda > direita){ // Se a esquerda é o maior caminho.
            return esquerda;
        }
        else{
            return direita; // Se a direita é o maior caminho.
        }
    }
}

//desaloca memoria da arvore
void libera_arvore(No* raiz){
	if(raiz->esquerda == NULL && raiz->direita == NULL){
		free(raiz);
	}
	else{
		libera_arvore(raiz->esquerda);
		libera_arvore(raiz->direita);
	}
}

//FUNCOES DICIONARIO

// Função para alocar dinamicamente o dicionário.
char** aloca_dicionario(int colunas){
	int i;
	char** dicionario;

    dicionario = calloc(TAM, sizeof(char*));
    
    for(i = 0; i < TAM; i++){
        dicionario[i] = calloc(colunas, sizeof(char)); // Alocando memória em todas as posições da matriz de string(dicionario).
    }
    return dicionario;
}

// Função para criar o dicionário, percorrendo a árvore e concatenando o caminho com a direção.
void criar_dicionario(char **dicionario, No *raiz, char *caminho, int coluna){
    char esquerda[coluna], direita[coluna];
    if(raiz->esquerda == NULL && raiz->direita == NULL){ // Se cair aqui, cheguei no nó folha, então o código que for criado 
        strcpy(dicionario[raiz->caracter], caminho);     // ao percorrer a árvore(0110, por ex.) eu vou copiar para o dicionário.
    }

    else{
        strcpy(esquerda, caminho); // A cada vez que eu percorro a esquerda da árvore é acrescentado um "0" ao código.
        strcpy(direita, caminho);  // A cada vez que eu percorro a direita da árvore é acrescentando um "1" ao código.

        strcat(esquerda, "0"); // Concatena a string vazia com "0".
        strcat(direita, "1");  // Concatena a string vazia com "1".

        criar_dicionario(dicionario, raiz->esquerda, esquerda, coluna);
        criar_dicionario(dicionario, raiz->direita, direita, coluna);
    }
}

//desaloca memoria do dicionario
void libera_dicionario(char** dicionario){
	int i;

	for(i = 0; i < TAM; i++)
		free(dicionario[i]);
	free(dicionario);
}

//FUNCOES CODIFICACAO E DECODIFICACAO

// Função para calcular o tamanho da string, para cada caracter de "str" será procurado o código no dicionário e somado a quantidade.
int tamanho_da_string(char **dicionario, unsigned char *str){
    int i = 0, tam = 0;

    while(str[i] != '\0'){ // Enquanto não for o fim de str.
        tam += strlen(dicionario[str[i]]); // tam recebe a quantidade de caracteres.
        i++; // Incrementa o i.
    }
    return tam + 1; //tamanho da string + '\0'
}

// Função para codificar o texto.
char *codificacao(char **dicionario, unsigned char *str){
    char *texto_codificado;

	texto_codificado = calloc(tamanho_da_string(dicionario, str)+2, sizeof(char));

    int i = 0; 

    while(str[i] != '\0'){ // Enquanto não for o fim de "str".
        strcat(texto_codificado, dicionario[str[i]]); // Concateno a string "texto_codificado" com a string de "str", só que eu irei concatenar o código delas presente no dicionário.
        i++;
    }
    return texto_codificado; 
}

char *decodificacao(No *raiz, unsigned char *str){
    No *aux = NULL;
    aux = raiz;
    char aux2[2], *texto_decodificado;
    int i = 0;

	texto_decodificado = calloc(strlen(str), sizeof(char));

    while(str[i] != '\0'){ // Enquanto não for o fim de "str".
        if(str[i] == '1'){ // Se na minha codificação for "1", ando a direita da árvore, senão vou para a esquerda.
            aux = aux->direita;
        }

        else{
            aux = aux->esquerda; // Se na minha codificação for "0", ando a esquerda da árvore.
        }

        if(aux->esquerda == NULL && aux->direita == NULL){ // Se entrar aqui, então eu cheguei em um nó folha.
            aux2[0] = aux->caracter; // Recebo o caracter que está no nó folha.
            aux2[1] = '\0'; // Recebo o fim de string.
            strcat(texto_decodificado, aux2); // Vou concatenando os caracteres que vão sendo decodificados.
            aux = raiz; // Auxiliar volta novamente ao topo da árvore.
        }
        i++; 
    }
    return texto_decodificado;
}

//FUNCOES PARA COMPACTAÇÃO E DESCOMPACTAÇÃO

//compactar arquivo
void compactacao(unsigned char *str){
	FILE *arquivo = fopen("compactado.bin", "wb"); // Aqui será feito a escrita(compactação) em um arquivo binário.
	unsigned char byte = 0, deslocamento;
	int i = 0, j = 7;

	if(!arquivo){
		printf("\nNao foi possivel criar o arquivo!\n");
	}

	else{
		while(str[i] != '\0'){ // Vou pegar apenas os caracteres do arquivo/string.
			deslocamento = 1; // Usado para o deslocamento.
			if(str[i] == '1'){
				deslocamento = deslocamento << j; // Mascara será deslocado 7 vezes(10000000).
				byte = byte | deslocamento; // Operação entre máscara e byte, se mascara é 1, então o byte é 10000000.  
			}
			j--; // Decremento o j.

			if(j < 0){ // Se cair aqui, já foi percorrido 8 bits.
				fwrite(&byte, sizeof(unsigned char), 1, arquivo); // Escrevo no arquivo o conteúdo compactado(byte).
				byte = 0; // Começo novamente a operação para compactar os bits setando o byte = 0.
				j = 7; // Começo novamente a operação para compactar os bits setando o j = 7.
			}
			i++;
		}
		if(j != 7){ // Se caso não for formado 1 byte inteiro.
			fwrite(&byte, sizeof(unsigned char), 1, arquivo); // Escrevo no arquivo o conteúdo compactado(byte).
		}
		fclose(arquivo);
	}
}

//DESCOMPACTACAO

//verifica se o bit é um ou zero
unsigned int eh_bit_um(unsigned char byte, int i){
    unsigned char deslocamento = (1 << i);//desloca o bit 1 "i" vezes para frente, ou seja, o bit 00000001 se descolado 7 vezes sera 10000000
    return byte & deslocamento; //operacao and entre byte e a mascara
}

//conta a quantidade de chars encontrados em um arquivo binario
int descobrir_tamanho_arquivo_bin(No* raiz){
    FILE *arquivo = fopen("compactado.bin", "rb");
    No *aux = raiz;
    unsigned char byte;
    int i;
    int tamanho = 0;

    if(arquivo){
        while(fread(&byte, sizeof(unsigned char), 1, arquivo)){//enquanto nao for o fim do arquivo
            for(i = 7; i >= 0; i--){
                if(eh_bit_um(byte, i))//se for bit 1
                    aux = aux->direita;
                else//se for bit 0
                    aux = aux->esquerda;

                if(aux->esquerda == NULL && aux->direita == NULL){//se for nó folha
                    tamanho++;
                    aux = raiz;//retorna a raiz da arvore
                }
            }
        }
        fclose(arquivo);
    }
    else
        printf("\nErro ao abrir arquivo em descobrir_tamanho_arquivo_bin\n");

    return tamanho;
}

//escreve ou cria um arquivo txt com a string passada por parametro
void escrever_no_arquivo(char *string){
    FILE* arquivo = fopen("teste2.txt", "w");
    fprintf(arquivo, "%s", string);
    fclose(arquivo);
}

//descompacta um arquivo binario, percorrendo a arvore e ate encontrar um no folha
//apos encontrar, armazena o char do no folha na string criada
void descompactar(No *raiz){
    FILE *arquivo = fopen("compactado.bin", "rb");
    No *aux = raiz;
    unsigned char byte;
    int i;
    char *string;
    int tamanho = descobrir_tamanho_arquivo_bin(raiz);//conta o numero de caracteres codificados no arquivo binario
    int j = 0;

    string = calloc(tamanho + 2,sizeof(unsigned char));//aloca memoria de acordo com o numero de caracteres contados

    if(arquivo){
        while(fread(&byte, sizeof(unsigned char), 1, arquivo)){//enquanto nao dor o fim do arquivo
            for(i = 7; i >= 0; i--){
                if(eh_bit_um(byte, i))//eh bit 1
                    aux = aux->direita;
                else
                    aux = aux->esquerda;//eh bit 0

                if(aux->esquerda == NULL && aux->direita == NULL){//chegou em um no folha
                    string[j] = aux->caracter;//guarda o caracter do no folha na string
                    aux = raiz;//volta para a raiz da arvore
                    j++;
                }
            }
        }
        fclose(arquivo);
        escrever_no_arquivo(string);//escreve a string no arquivo de saida
    }
    else
        printf("\nErro ao abrir arquivo em descompactar\n");
}

//conta o numero de caracteres em um arquivo
int descobrir_tamanho_arquivo_txt(char nome_arquivo[]){
    FILE *arquivo = fopen(nome_arquivo, "r");
    int tamanho = 0;

    if(arquivo){
        while(fgetc(arquivo) != -1)
            tamanho++;
        fclose(arquivo);
    }
    else
        printf("\nErro ao abrir arquivo em descobrir_tamanho\n");
    return tamanho;
}

// função para ler um texto de um arquivo texto
void ler_arquivo_txt(unsigned char *texto, char nome_arquivo[]){
    FILE *arquivo = fopen(nome_arquivo, "r");
    unsigned char letra;
    int i = 0;

    if(arquivo){
        while(!feof(arquivo)){
            letra = fgetc(arquivo);
            if(letra != -1){
                //printf("%d: %c\n", letra, letra);
                texto[i] = letra;
                i++;
            }
        }
        fclose(arquivo);
    }
    else
        printf("\nErro ao abri arquivo em ler_texto\n");
}

//aloca memoria para a string q recebera o conteudo do arquivo txt
unsigned char* aloca_memoria_texto(char nome_arquivo[]){
	unsigned char* texto;
	int tamanho = descobrir_tamanho_arquivo_txt(nome_arquivo);
	texto = calloc(tamanho + 2, sizeof(unsigned char));//quantidade alocacada de acordo com o tamanho do arquivo
	return texto;
}

// Imprime toda a tabela ascii
void imprimir_tabela_ascii(unsigned int *tabela){
	int i = 0;
	
	printf("\nTabela ASCII:\n Ind:  Carac:\n");
	for(i = 0; i < TAM; i++){
		printf("%3d\t%c\n", i, i);
	}
}

// Imprime apenas os caracteres que o estao presentes no arquivo e suas repetições caso existam.
void imprimir_tabela_freq(unsigned int *tabela){
	int i = 0;
	
	printf("\nTabela de frequencia:\nRepeticao   Caracter\n");
	for(i = 0; i < TAM; i++){
		if(tabela[i] > 0){
			printf("%5d\t%8c\n", tabela[i], i);
		}
	}
	// Quando o "i" é inteiro, ele vai imprimir os índices da tabela, quando o meu "i" for do tipo char, ele vai imprimir os símbolos correspodentes da tabela ascii. Por fim, a "tabela_freq[i]" mostra quantas repetições existem de cada caracter.
}

// Função para imprimir a lista ordenada.
void imprimir_lista(Lista *lista){
	No *aux;
	
	aux = lista->inicio;
	
	printf("\nLista Encadeada Ordenada:\n");
	printf("Frequencia  Caracter\n");
	while(aux){
		printf("%5d%11c\n", aux->frequencia, aux->caracter);
		aux = aux->proximo;
	}
}

// Função para imprimir a árvore de huffman.
void imprimir_arvore(No *raiz, int altura_no){
	if(raiz->esquerda == NULL && raiz->direita == NULL){ //caso seja nó folha
		printf("%4d%10c\n", altura_no, raiz->caracter);
	}

	else{ // Senão, vou percorrendo a árvore.
		imprimir_arvore(raiz->esquerda, altura_no + 1);
		imprimir_arvore(raiz->direita, altura_no + 1);
	}
}

// Função para imprimir o dicionário.
void imprimir_dicionario(char **dicionario){
    int i = 0;

    for(i = 0; i < TAM; i++){
        if(strlen(dicionario[i]) > 0){ // Imprime apenas os códigos dos caracteres existentes.
            printf("%4c\t\t%s\n", i, dicionario[i]);
        }
    }
}

//menu do programa
void menu(){
	printf("\n\tAlgoritmo de Huffman\n\n");
	printf("0-Encerrar programa\n1- Compactar\n2- Descompactar\n\n");
	printf("\tOpcoes adicionais:\n\n3- Tabela ASCII\n4- Tabela de Frequencia\n5- Lista ordenada\n6- Arvore Huffman\n7- Dicionario\n8- Codificacao\n9- Decodificacao\n\n");
	printf("Escolha: ");
}
