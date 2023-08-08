#include <locale.h>
#include <stdlib.h>
#include <stdio.h>

//PROJETO PESSOAL PARA REFORÇAR O ESTUDO DE ÁRVORES BINÁRIAS DE BUSCA (ÁROVRES AVL BALANCEADAS)
//Autor: Ian Santos
//Data 07/08/2023

//Primeiramente vou definir o strcut da árvore
struct arvore_AVL{
	int elemento;
	struct arvore_AVL* left; //Um ponteiro do mesmo tipo da estrututra para filho à esquerda
	struct arvore_AVL* right; //Um ponteiro do mesmo tipo da estrututra para filho à esquerda
};
//Definindo o tipo da estrutura de forma mais simplificada, já como um ponteiro, afinal é como ponteiro que vamos utiliza-la na maior parte das funções
typedef struct arvore_AVL* arvoreAvl;

//Função para criar nó da árvore
arvoreAvl criaRaiz(int elemento){
	
	arvoreAvl raiz;
	raiz = (arvoreAvl)malloc(sizeof(struct arvore_AVL)); //Alocamos dinamicamente a memória necessária para esse struct
	raiz -> left = NULL; //Inicialmente os filhos à direita e à esquerda serão nulos, pois será o único elemento quando essa função for chamada
	raiz -> right = NULL;
	raiz -> elemento = elemento;
	return raiz;
	
}

//Precisaremos de uma função para obter o dado necessário para a função criaRaiz. Utilizaremos um ponteiro de ponteiro, para podermos modificar diretamente a estrutura criada na função
void perguntarValorDaRaiz(arvoreAvl *arvorePonteiro){
	
	int elemento;
	
	printf("Você está iniciando uma árvore binária. Insira um valor para iniciar esta árvore!!!\n: ");
	scanf("%i", &elemento);
	*arvorePonteiro = criaRaiz(elemento);
	
}

//Caso a árvore já possua um ou mais elementos, vamos utilizar outra função para inserir um novo na árvore, utilizando um algorítimo recursivo para manter o menor sempre à esquerda e o maior sempre à direita
void insereNo(int elemento, arvoreAvl arvore){
	
	arvoreAvl novoNo;
	novoNo = criaRaiz(elemento);
	
	
	if(elemento > arvore->elemento){
		
		if(arvore->right){
			insereNo(elemento, arvore->right);
		}
		else{
			arvore->right = novoNo;
		}
		
	}
	
	else{
		
		if(arvore->left){
			insereNo(elemento, arvore->left);
		}
		else{
			arvore->left = novoNo;
		}
		
	}
	
}

//Obtenção do dado para inserir na árvore binária
void inserirPergunta(arvoreAvl arvore){
	
	int elemento;
	printf("Você está adicionando um novo nó a sua árvore, qual será o novo elemento?\n: ");
	scanf("%i", &elemento);
	insereNo(elemento, arvore);
	
}

//Criarei uma rotina para impressão do árvore em forma de árvore, essa função funciona da seguinte forma
void impressaoEmArvore(arvoreAvl arvore, int lines){
	int i;
	
	//Primeiramente imprimo o nó mais à direita
	if(arvore->right){
		
		impressaoEmArvore(arvore->right, lines+1);
	
	}
	
	//Utilizo a variável lines para representar o nível da árvore que estaremos imprimindo
	for(i=0;i<lines;i++){
		
			printf("           ");
			
	}
		
	printf("[%i]\n", arvore->elemento);
	
	//Após o nó atual, vou imprimir o nó mais à esquerda
	if(arvore->left){
		
		impressaoEmArvore(arvore->left, lines+1);
		
	}
	
}

//Cálculo de altura: esse é o ponto inicial para o balanceamento da árvore AVL
int altura(arvoreAvl arvore){
	
	int alturaEsquerda = 0;
	int alturaDireita = 0;
	
	if(arvore->left){
		
		alturaEsquerda = 1 + altura(arvore->left);
		
	}
	
	if(arvore->right){
		
		alturaDireita = 1 + altura(arvore->right);
		
	}

	if(alturaEsquerda > alturaDireita){
		
		return alturaEsquerda;
		
	}
	
	else{
		
		return alturaDireita;
		
	}
}

//Irei iniciar a parte de rotações da árvore, para quando for necessário, balancea-la dessa forma
/*Esse é o movimento que ocorre nessa função:

		[x]								[y]					[x]								[y]
			[y]			- >			[x]		[z]		ou 			[y]			- > 	[x]				[z]
				[z]											[w]		[z]					[w]

Na rotação à esquerda, o elemento à direita da raiz agora irá virar raiz, tendo a raiz anterior como seu filho esquerdo
e caso esta já tenha um filho esquerdo, ele será, necessáriamente maior que a raiz anterior, portanto, não há o menor
problema em inseri-lo como filho a direita da antiga raiz
*/

arvoreAvl rotacaoAEsquerda(arvoreAvl arvore){
	
	arvoreAvl ponteiroAuxiliar = NULL;
	arvoreAvl ponteiroAuxiliar2 = arvore->right;
	
	if(arvore->right->left){
		ponteiroAuxiliar = arvore->right->left;
	}
	
	arvore->right->left = arvore;
	
	if(ponteiroAuxiliar){
		arvore->right = ponteiroAuxiliar;
	}
	else{
		arvore->right = NULL;
	}

	return ponteiroAuxiliar2;
	
}

//Irei realizar o mesmo movimento porém na direção oposta, com os seguintes passos:
/*Esse é o movimento que ocorre nessa função:

				[z]							[y]							[z]			
			[y]				- >			[x]		[z]		ou 			[y]			- > 
		[x]														[x]		[w]			

Na rotação à direita, o elemento à esquerda da raiz agora irá virar raiz, tendo a raiz anterior como seu filho direito
e caso esta já tenha um filho direito, ele será, necessáriamente menor que a raiz anterior, portanto, não há o menor
problema em inseri-lo como filho a esquerda da antiga raiz
*/

arvoreAvl rotacaoADireita(arvoreAvl arvore){
	
	arvoreAvl ponteiroAuxiliar = NULL;
	arvoreAvl ponteiroAuxiliar2 = arvore->left;
	
	if(arvore->left->right){
		ponteiroAuxiliar = arvore->left->right;
	}
	
	arvore->left->right = arvore;
	
	if(ponteiroAuxiliar){
		arvore->left = ponteiroAuxiliar;
	}
	else{
		arvore->left = NULL;
	}
	
	return ponteiroAuxiliar2;
}

//Há dois casos especiais de rotação a tratar
/*

	[x]					    [x]
		[y]		ou		[y]
	[z]					   [z]					

*/

//Vou usar as rotações duplas para tratar desses casos:
/*

	[x]											[x]														[y]
		[y] -> rotação à direita no y ->			[y]			-> rotação à esquerda no x -> 		[x]		[z]
	[z]													[z]

E da mesma forma com a esquerda
*/
arvoreAvl rotacaoDuplaAEsquerda(arvoreAvl arvore){
	
	arvore->right = rotacaoADireita(arvore->right);
	return rotacaoAEsquerda(arvore);
	
}

arvoreAvl rotacaoDuplaADireita(arvoreAvl arvore){
	
	arvore->left = rotacaoAEsquerda(arvore->left);
	return rotacaoADireita(arvore);
	
}


//Utilizarei a função de altura para criar uma função que calcule o "fator de balanceamento" e decida se a árvore precisará ou não de alterações a partir dele
//Os valores de balancemento (Altura da sub-árvore direita - Altura da sub-árvore esquerda) poderá ficar entre -1 e 1

int fatbal(arvoreAvl arvore){
	
	int alturaE=0, alturaD=0;
	
	if(arvore->right){
		
		alturaD = 1+altura(arvore->right);
		
	}
	
	if(arvore->left){
		
		alturaE = 1+altura(arvore->left);
		
	}
	
	return alturaD - alturaE;
}

void balanceamento(arvoreAvl *arvore){
	
	if(fatbal(*arvore) < -1){
		
		if((*arvore)->left	&&	fatbal((*arvore)->left) > 0){
			
			*arvore = rotacaoDuplaADireita(*arvore);
			
		}
		else if ((*arvore)->left){
			
			*arvore = rotacaoADireita(*arvore);
			
		}
		
	}
	
	
	else if (fatbal((*arvore)) > 1){
		
		if((*arvore)->right	&&	fatbal((*arvore)->right) < 0){
			
			*arvore = rotacaoDuplaAEsquerda(*arvore);
			
		}
		
		else if ((*arvore)->right){
			
			*arvore = rotacaoAEsquerda(*arvore);
			
		}
		
	}
	
	//Agora irei repetir o processo recurssivamente em todos os nós da árvore
	if((*arvore)->right){
		balanceamento(&((*arvore)->right));
	}	
	
	if((*arvore)->left){
		balanceamento(&((*arvore)->left));
	}
	
}

//Por último vou disponibilizar as funções de exibição da árvore em ordem, pré ordem e pós ordem
void preOrdem(arvoreAvl arvore){
	
	printf("%i",arvore->elemento);
	
	if(arvore->left){
		printf(", ");
		preOrdem(arvore->left);
	}
	if(arvore->right){
		printf(", ");
		preOrdem(arvore->right);
	}
	
}

void emOrdem(arvoreAvl arvore){
	
	if(arvore->left){
		emOrdem(arvore->left);
		printf(", ");
	}
	
	printf("%i",arvore->elemento);
	
	if(arvore->right){
		printf(", ");
		emOrdem(arvore->right);
	}
	
}

void posOrdem(arvoreAvl arvore, int init0){
	
	if(arvore->right){
		posOrdem(arvore->right, init0+1);
	}
	
	if(arvore->left){
		posOrdem(arvore->left,init0+1);
	}
	
	printf("%i",arvore->elemento);
	
	if(init0 != 0){
		printf(", ");
	}
	
}

//Para comndensar todas essas funções, irei criar um pequeno menu com algumas interações
void menu(arvoreAvl *arvore){
	
	int option;
	
	printf("---------- Bem vindo ao menu de árvores binárias!!! ----------\n\n");
	
	if(*arvore == NULL){
		printf("Verificamos que você ainda não tem uma árvore criada, vamos redireciona-lo para o menu de criação!!!\n\n");
		perguntarValorDaRaiz(arvore);printf("\n\n");
	}
		
		do{
			printf("---------------------- Impressão da árvore --------------------\n");
			impressaoEmArvore(*arvore, 0);
			printf("---------------------------------------------------------------\n");
			
			printf("---- Impressão Pré-Órdem ----\n[");
			preOrdem(*arvore);printf("]\n");
			
			printf("---- Impressão Em Ordem ----\n[");
			emOrdem(*arvore);printf("]\n");
			
			printf("---- Impressão Pós-Órdem ----\n[");
			posOrdem(*arvore,0);printf("]\n\n");
			
			printf("------ Menu de opções ------\n");
			printf("1 - Inserir na Árvore\n");
			printf("0 - Sair do programa\n:");
			scanf("%i", &option);
			
			switch(option){
				case 1: printf("\n");inserirPergunta(*arvore);balanceamento(arvore);printf("\n"); break;
				case 0: break;
				default: printf("\n\n[!!!!!] -> Insira uma opção válida <-[!!!!!]\n\n\n");
				
			}
		}while(option != 0);
	
}

//Aqui é o programa principal, onde o código irá rodar
int main (void){
	setlocale(LC_ALL, "portuguese");
	
	arvoreAvl arvore = NULL;
	menu(&arvore);
}
