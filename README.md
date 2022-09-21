# codigo-de-huffman
Código de Huffman
	
No nosso dia a dia, é comum armazenarmos arquivos de texto, fotos, vídeos, e muitas das vezes esses arquivos acabam tendo tamanhos enormes, o que faz com que seja necessário comprimirmos esses dados no intuito de reduzir o uso de espaço de armazenamento no nosso HD ou SSD, por exemplo.
	
Sendo assim, um algoritmo muito conhecido e usado para a compressão de texto sem perda é o Algoritmo de Huffman ou Código de Huffman, no qual se reduz significativamente o tamanho do texto desejado.
	
O algoritmo possui alguns passos, sendo:

- Saber a frequência com que cada caracter no texto se repete;
- Criar uma lista com os caracteres digitados e quantas vezes cada um se repete;
- Criar uma arvóre binária e agrupar os símbolos de acordo com a frequência;
- Depois, percorrer a árvore tanto para codificar quanto para decodificar os dados.


Execução do algoritmo:

Para executar o algoritmo deve-se passar um arquivo texto como argumento na execução do programa.

Por ex.: "./codigo_de_huffman_final nome_do_arquivo.txt"


Este código foi realizado para um trabalho na cadeira de Organização de arquivos e dados, no qual o código origal pertence a Wagner Gaspar. Foram feitas algumas modificações no código, sendo a principal delas a alocação dinâmica de memória que não estava presente no código original.

Link do chttps://www.youtube.com/c/ProgrameseufuturoComWagnerGaspar/featured
