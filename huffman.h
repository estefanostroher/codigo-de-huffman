//huffman.h
#ifndef HUFFMAN_H
#define HUFFMAN_H

typedef struct no{
	unsigned char caracter;
	int frequencia;
	struct no *proximo;
	struct no *esquerda;
	struct no *direita;
}No;

typedef struct{
	No *inicio;
	int tam;
}Lista;

//FUNCOES TABELA DE FREQUENCIA
void iniciar_tabela_freq(unsigned int *tabela);
void preencher_tabela_freq(unsigned int *tabela, unsigned char *str);
void imprimir_tabela_ascii(unsigned int *tabela);
void imprimir_tabela_freq(unsigned int *tabela);

//FUNCOES LISTA ENCADEADA
void inicializa_lista(Lista *lista);
void inserir_na_lista(No *no, Lista *lista);
void preencher_lista(Lista *lista, unsigned int *tabela);
void imprimir_lista(Lista *lista);
No* remover_da_lista(Lista *lista);
void libera_lista(Lista* lista);

//FUNCOES ARVORE
No* criar_arvore(Lista *lista);
void imprimir_arvore(No *raiz, int altura_no);
int altura_da_arvore(No *raiz);
void libera_arvore(No* raiz);


//FUNCOES DICIONARIO
char** aloca_dicionario(int colunas);
void criar_dicionario(char **dicionario, No *raiz, char *caminho, int coluna);
void imprimir_dicionario(char **dicionario);
void libera_dicionario(char** dicionario);

//FUNCOES CODIFICACAO E DECODIFICACAO
int tamanho_da_string(char **dicionario, unsigned char *str);
char *codificacao(char **dicionario, unsigned char *str);
char *decodificacao(No *raiz, unsigned char *str);

//FUNCOES PARA COMPACTAÇÃO E DESCOMPACTAÇÃO
void compactacao(unsigned char *str);
unsigned int eh_bit_um(unsigned char byte, int i);
int descobrir_tamanho_arquivo_bin(No* raiz);
void escrever_no_arquivo(char *string);
void descompactar(No *raiz);
int descobrir_tamanho_arquivo_txt(char nome_arquivo[]);
void ler_arquivo_txt(unsigned char *texto, char nome_arquivo[]);
unsigned char* aloca_memoria_texto(char nome_arquivo[]);
void menu();

#endif
