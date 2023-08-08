#include <locale.h>
#include <stdlib.h>
#include <stdio.h>

//PROJETO PESSOAL PARA REFOR�AR O ESTUDO DE �RVORES BIN�RIAS DE BUSCA (�ROVRES AVL BALANCEADAS)
//Autor: Ian Santos
//Data 07/08/2023

//Primeiramente vou definir o strcut da �rvore
struct arvore_AVL{
	int elemento;
	struct arvore_AVL* left; //Um ponteiro do mesmo tipo da estrututra para filho � esquerda
	struct arvore_AVL* right; //Um ponteiro do mesmo tipo da estrututra para filho � esquerda
};
//Definindo o tipo da estrutura de forma mais simplificada, j� como um ponteiro, afinal � como ponteiro que vamos utiliza-la na maior parte das fun��es
typedef struct arvore_AVL* arvoreAvl;

//Fun��o para criar n� da �rvore
arvoreAvl criaRaiz(int elemento){
	
	arvoreAvl raiz;
	raiz = (arvoreAvl)malloc(sizeof(struct arvore_AVL)); //Alocamos dinamicamente a mem�ria necess�ria para esse struct
	raiz -> left = NULL; //Inicialmente os filhos � direita e � esquerda ser�o nulos, pois ser� o �nico elemento quando essa fun��o for chamada
	raiz -> right = NULL;
	raiz -> elemento = elemento;
	return raiz;
	
}

//Precisaremos de uma fun��o para obter o dado necess�rio para a fun��o criaRaiz. Utilizaremos um ponteiro de ponteiro, para podermos modificar diretamente a estrutura criada na fun��o
void perguntarValorDaRaiz(arvoreAvl *arvorePonteiro){
	
	int elemento;
	
	printf("Voc� est� iniciando uma �rvore bin�ria. Insira um valor para iniciar esta �rvore!!!\n: ");
	scanf("%i", &elemento);
	*arvorePonteiro = criaRaiz(elemento);
	
}

//Caso a �rvore j� possua um ou mais elementos, vamos utilizar outra fun��o para inserir um novo na �rvore, utilizando um algor�timo recursivo para manter o menor sempre � esquerda e o maior sempre � direita
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

//Obten��o do dado para inserir na �rvore bin�ria
void inserirPergunta(arvoreAvl arvore){
	
	int elemento;
	printf("Voc� est� adicionando um novo n� a sua �rvore, qual ser� o novo elemento?\n: ");
	scanf("%i", &elemento);
	insereNo(elemento, arvore);
	
}

//Criarei uma rotina para impress�o do �rvore em forma de �rvore, essa fun��o funciona da seguinte forma
void impressaoEmArvore(arvoreAvl arvore, int lines){
	int i;
	
	//Primeiramente imprimo o n� mais � direita
	if(arvore->right){
		
		impressaoEmArvore(arvore->right, lines+1);
	
	}
	
	//Utilizo a vari�vel lines para representar o n�vel da �rvore que estaremos imprimindo
	for(i=0;i<lines;i++){
		
			printf("           ");
			
	}
		
	printf("[%i]\n", arvore->elemento);
	
	//Ap�s o n� atual, vou imprimir o n� mais � esquerda
	if(arvore->left){
		
		impressaoEmArvore(arvore->left, lines+1);
		
	}
	
}

//C�lculo de altura: esse � o ponto inicial para o balanceamento da �rvore AVL
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

//Irei iniciar a parte de rota��es da �rvore, para quando for necess�rio, balancea-la dessa forma
/*Esse � o movimento que ocorre nessa fun��o:

		[x]								[y]					[x]								[y]
			[y]			- >			[x]		[z]		ou 			[y]			- > 	[x]				[z]
				[z]											[w]		[z]					[w]

Na rota��o � esquerda, o elemento � direita da raiz agora ir� virar raiz, tendo a raiz anterior como seu filho esquerdo
e caso esta j� tenha um filho esquerdo, ele ser�, necess�riamente maior que a raiz anterior, portanto, n�o h� o menor
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

//Irei realizar o mesmo movimento por�m na dire��o oposta, com os seguintes passos:
/*Esse � o movimento que ocorre nessa fun��o:

				[z]							[y]							[z]			
			[y]				- >			[x]		[z]		ou 			[y]			- > 
		[x]														[x]		[w]			

Na rota��o � direita, o elemento � esquerda da raiz agora ir� virar raiz, tendo a raiz anterior como seu filho direito
e caso esta j� tenha um filho direito, ele ser�, necess�riamente menor que a raiz anterior, portanto, n�o h� o menor
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

//H� dois casos especiais de rota��o a tratar
/*

	[x]					    [x]
		[y]		ou		[y]
	[z]					   [z]					

*/

//Vou usar as rota��es duplas para tratar desses casos:
/*

	[x]											[x]														[y]
		[y] -> rota��o � direita no y ->			[y]			-> rota��o � esquerda no x -> 		[x]		[z]
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


//Utilizarei a fun��o de altura para criar uma fun��o que calcule o "fator de balanceamento" e decida se a �rvore precisar� ou n�o de altera��es a partir dele
//Os valores de balancemento (Altura da sub-�rvore direita - Altura da sub-�rvore esquerda) poder� ficar entre -1 e 1

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
	
	//Agora irei repetir o processo recurssivamente em todos os n�s da �rvore
	if((*arvore)->right){
		balanceamento(&((*arvore)->right));
	}	
	
	if((*arvore)->left){
		balanceamento(&((*arvore)->left));
	}
	
}

//Por �ltimo vou disponibilizar as fun��es de exibi��o da �rvore em ordem, pr� ordem e p�s ordem
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

//Para comndensar todas essas fun��es, irei criar um pequeno menu com algumas intera��es
void menu(arvoreAvl *arvore){
	
	int option;
	
	printf("---------- Bem vindo ao menu de �rvores bin�rias!!! ----------\n\n");
	
	if(*arvore == NULL){
		printf("Verificamos que voc� ainda n�o tem uma �rvore criada, vamos redireciona-lo para o menu de cria��o!!!\n\n");
		perguntarValorDaRaiz(arvore);printf("\n\n");
	}
		
		do{
			printf("---------------------- Impress�o da �rvore --------------------\n");
			impressaoEmArvore(*arvore, 0);
			printf("---------------------------------------------------------------\n");
			
			printf("---- Impress�o Pr�-�rdem ----\n[");
			preOrdem(*arvore);printf("]\n");
			
			printf("---- Impress�o Em Ordem ----\n[");
			emOrdem(*arvore);printf("]\n");
			
			printf("---- Impress�o P�s-�rdem ----\n[");
			posOrdem(*arvore,0);printf("]\n\n");
			
			printf("------ Menu de op��es ------\n");
			printf("1 - Inserir na �rvore\n");
			printf("0 - Sair do programa\n:");
			scanf("%i", &option);
			
			switch(option){
				case 1: printf("\n");inserirPergunta(*arvore);balanceamento(arvore);printf("\n"); break;
				case 0: break;
				default: printf("\n\n[!!!!!] -> Insira uma op��o v�lida <-[!!!!!]\n\n\n");
				
			}
		}while(option != 0);
	
}

//Aqui � o programa principal, onde o c�digo ir� rodar
int main (void){
	setlocale(LC_ALL, "portuguese");
	
	arvoreAvl arvore = NULL;
	menu(&arvore);
}
