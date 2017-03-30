#include<stdio.h>
#define CAP 5

//Funções do primeiro menu.
int verificar (int conj[], int quantidade, int valor)
{
	int i;
	
	for(i=0; i<quantidade; i++)
	{
		if(conj[i] == valor)
		{
			return 1;
		}
	}
	
	return 0;
}

void inserir (int conj[], int *quantidade, int valor)
{
	int i, j, aux, cont=0;
	
	for(i=0; cont == 0; i++)
	{
		if(conj[i] > valor)
		{
			(*quantidade)++;
			
			//Após encontrar um valor maior que o desejado, puxa todos depois dele para direita e insere no espaço "vazio".
			for(j=(*quantidade); j!=i; j--)
			{
				conj[j] = conj[j-1];
			}
			
			conj[i] = valor;
			
			//Contador para parar quando colocar o valor e não precisar passar pelo resto.
			cont++;
		}
	}
}

void remover (int conj[], int *quantidade, int valor)
{
	int i, j, cont=0;
	
	for(i=0; cont == 0; i++)
	{
		if(conj[i] == valor)
		{
			for(j=i; j<*quantidade; j++)
			{
				conj[j] = conj[j+1];
			}
			
			(*quantidade)--;
			
			cont++;
		}
	}
}

void alterarValor (int conj[], int quantidade, int numero1, int numero2)
{
	int i, j, aux, cont=0;
	
	for(i=0; cont == 0; i++)
	{
		if(conj[i] == numero1)
		{
			//Sai o primeiro número e entra o segundo.
			conj[i] = numero2;
			
			//Coloca o número inserido no lugar certo.
			for(i=0; i<quantidade; i++)
			{
				for(j=0; j<quantidade; j++)
				{
					if(conj[i] < conj[j])
					{
						aux = conj[j];
						
						conj[j] = conj[i];
						
						conj[i] = aux;
					}
				}
			}
			cont++;
		}
	}
}

void exibir (int conj[], int quantidade)
{
	int i;
	
	printf("\n\n");
	for(i=0; i<quantidade; i++)
	{
		printf("%d, ", conj[i]);
	}
	printf("\n\n");
}

//Funções do segundo menu.
int uniao (int conjA[], int quantA, int conjB[], int quantB, int conjC[], int quantC)
{
	int i=0, j, k, aux, cont=0;
	
	//Junta os dois.
	while(i < quantA)
	{
		conjC[i] = conjA[i];
		
		i++;
	}
	
	for(i=0; i < quantB; i++)
	{
		conjC[i+quantA] = conjB[i];
	}
	
	//Ordena o conjunto união.
	for(i=0; i<quantC; i++)
	{
		for(j=0; j<quantC; j++)
		{
			if(conjC[i] < conjC[j])
			{
				aux = conjC[j];
				
				conjC[j] = conjC[i];
				
				conjC[i] = aux;
			}
		}
	}
	
	//Agora retira as repetições, se houverem.
	for(i=0; i<quantC; i++)
	{
		for(j=0; j<quantC; j++)
		{
			if(conjC[i] == conjC[j])
			{
				cont++;
				
				//Como a união está ordenada e não há repetição dentro dos conjuntos, se houver repetição entre eles, ela estará logo após o número repetido.
				if(cont == 2)
				{
					remover (conjC, &quantC, conjC[i]);
				}
			}	
		}
		cont = 0;
	}
	
	return quantC;
}

int interseccao (int conjA[], int quantA, int conjB[], int quantB, int conjC[], int quantC)
{
	int i, j;
	
	quantC = 0;
	
	for(i=0; i<quantA; i++)
	{
		for(j=0; j<quantB; j++)
		{
			if(conjA[i] == conjB[j])
			{	
				conjC[quantC] = conjA[i];
				
				quantC++;
			}
		}
	}
	
	return quantC;
}

int diferenca (int conjA[], int quantA, int conjB[], int quantB, int conjC[], int quantC)
{
	int i, j, cont=0;
	
	quantC = 0;
	
	for(i=0; i<quantA; i++)
	{
		for(j=0; j<quantB; j++)
		{
			if(conjA[i] == conjB[j])
			{	
				cont++;
			}
		}
		
		if(cont == 0)
		{
			conjC[quantC] = conjA[i];
					
			quantC++;
		}
		else
		{
			cont = 0;
		}
	}
	
	return quantC;
}

int apoioParaContidoEContem (int conj1[], int quant1, int conj2[], int quant2)
{
	int i, j, cont=0;
	
	for(i=0; i<quant1; i++)
	{
		for(j=0; j<quant1; j++)
		{
			if(conj1[i] == conj2[j])
			{
				cont++;
			}
		}
	}
	
	return cont;
}

int contido (int conj1[], int quant1, int conj2[], int quant2)
{	
	int cont = apoioParaContidoEContem (conj1, quant1, conj2, quant2);

	if(cont == quant1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int contem (int conj1[], int quant1, int conj2[], int quant2)
{
	int cont = apoioParaContidoEContem (conj1, quant1, conj2, quant2);
	
	if(cont == quant2)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int igualdade (int conj1[], int quant1, int conj2[], int quant2)
{
	int i, j, cont=0;
	
	for(i=0; i<quant1; i++)
	{
		for(j=0; j<quant2; j++)
		{
			if(conj1[i] == conj2[j])
			{
				cont++;
			}
		}
	}
	
	if((cont == quant1) && (cont == quant2))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int main ()
{	
	//Primeiro menu:
	char cConjunto;
	int Opcao, ConjuntoA[CAP], ConjuntoB[CAP], ContA=0, ContB=0, Cont5=0;
	int Colocar; // Função inserir.
	int Retirar; // Função remover.
	int RetirarPosicao; // Função removerPosicao.
	int Num1, Num2; // Função alterarValor.
	int NumBusca; // Função buscar.
	//Segundo menu:
	int ContC;
	int ConjuntoUniao[ContC], ContUniao;
	int ConjuntoInterseccao[ContC], ContInterseccao;
	int ConjuntoDiferenca[ContC], ContDiferenca;
	
	do
	{
		printf("\nEscolha uma das opcoes a seguir:\n1) Inserir novo numero; \n2) Remover determinado valor; \n3) Alterar um valor por outro; \n4) Exibir todos os elementos do vetor. \n5) Passar para o proximo menu. \n");
		scanf("%d", &Opcao);
		
		//Para não deixar escolher outra opção senão 1 ou 5 quando os vetores estiverem vazios.
		if((((ContA != 0) || (ContB != 0)) && (Opcao != 5)) || (((ContA == 0) && (Opcao == 1)) || ((ContB == 0) && (Opcao == 1))))
		{
			fflush(stdin);
			printf("\nDigite o conjunto a ser trabalhado (A ou B):\n");
			scanf("%c", &cConjunto);
			
			switch(Opcao)
			{
				case 1 :
					if((cConjunto == 'A') && (ContA < CAP))
					{
						printf("Digite o valor a ser inserido: ");
						scanf("%d", &Colocar);
						
						if(verificar (ConjuntoA, ContA, Colocar) == 0)
						{
							inserir (ConjuntoA, &ContA, Colocar);
							
							printf("\nValor inserido no vetor %c.\n", cConjunto);
						}
						else
						{
							printf("\nEste valor ja existe no vetor.\n");
						}
					}
					else
					{
						if((cConjunto == 'B') && (ContB < CAP))
						{
							printf("Digite o valor a ser inserido: ");
							scanf("%d", &Colocar);
							
							if(verificar (ConjuntoB, ContB, Colocar) == 0)
							{
								inserir (ConjuntoB, &ContB, Colocar);
								
								printf("\nValor inserido no vetor %c.\n", cConjunto);
							}
							else
							{
								printf("\nEste valor ja existe no vetor.\n");
							}
						}
						else
						{
							printf("\n\nNao eh possivel colocar mais valores no vetor.\n\n");
						}							
					}
				break;
				
				case 2 :
					printf("Digite o valor a ser retirado: ");
					scanf("%d", &Retirar);
					
					if(cConjunto == 'A')
					{
						//Recebe o Vetor e o Cont por parâmetro e 1 por return caso o valor exista.
						if(verificar (ConjuntoA, ContA, Retirar) == 1)
						{
							remover (ConjuntoA, &ContA, Retirar);
							
							printf("\n\nO valor foi removido.\n\n");
						}
						else
						{
							printf("\n\nO valor digitado nao existe no vetor.\n\n");
						}
					}
					else
					{
						if(cConjunto == 'B')
						{
							if(verificar (ConjuntoB, ContB, Retirar) == 1)
							{
								remover (ConjuntoB, &ContB, Retirar);
								
								printf("\n\nO valor foi removido.\n\n");
							}
							else
							{
								printf("\n\nO valor digitado nao existe no vetor.\n\n");
							}
						}
					}
				break;
				
				case 3 :
					printf("Digite qual numero sera retirado e depois o que sera inserido: ");
					scanf("%d %d", &Num1, &Num2);
					
					if(cConjunto == 'A')
					{
						if((verificar (ConjuntoA, ContA, Num1) == 1) && (verificar (ConjuntoA, ContA, Num2) == 0))
						{
							alterarValor(ConjuntoA, ContA, Num1, Num2);
							
							printf("\n\nOs valores foram trocados.\n\n");
						}
						else
						{
							if(verificar (ConjuntoA, ContA, Num1) == 0)
							{
								printf("\n\nO valor a ser retirado nao existe.\n\n");
							}
							else
							{
								if(verificar (ConjuntoA, ContA, Num2) == 1)
								{
									printf("\n\nO valor a ser inserido ja existe.\n\n");
								}
							}
						}
					}
					else
					{
						if(cConjunto == 'B')
						{
							if((verificar (ConjuntoB, ContB, Num1) == 1) && (verificar (ConjuntoB, ContB, Num2) == 0))
							{
								alterarValor(ConjuntoB, ContB, Num1, Num2);
								
								printf("\n\nOs valores foram trocados.\n\n");
							}
							else
							{
								if(verificar (ConjuntoB, ContB, Num1) == 0)
								{
									printf("\n\nO valor a ser retirado nao existe.\n\n");
								}
								else
								{
									if(verificar (ConjuntoB, ContB, Num2) == 1)
									{
										printf("\n\nO valor a ser inserido ja existe.\n\n");
									}
								}
							}
						}
					}
				break;
				
				case 4 :
					if(cConjunto == 'A')
					{
						exibir (ConjuntoA, ContA);
					}
					else
					{
						if(cConjunto == 'B')
						{
							exibir (ConjuntoB, ContB);
						}
					}
				break;
			}
		}
		else
		{
			if(Opcao != 5)
			{
				printf("\n\nO(s) vetor(es) ainda nao possui(em) valores. Tente a opcao (1)\n\n");
			}
			else
			{
				if((ContA == 0) || (ContB == 0))
				{
					printf("\n\nUm dos conjuntos nao esta completo.\n\n");
				}
				else
				{
					Cont5++;
				}
			}
		}
	}
	while(Cont5 == 0);
	
	ContC = ContA + ContB;
	
	do
	{
		printf("\nEscolha uma das operacoes com os conjuntos: \n1) Uniao; \n2) Interseccao; \n3) Diferenca; \n4) Se um esta contido no outro; \n5) Se um contem o outro; \n6) Verificar se sao iguais; \n7) Sair.\n");
		scanf("%d", &Opcao);
		
		//Se forem iguais não precisa chamar as funções pois o conjunto derivado será igual ao ConjuntoA e o ConjuntoB.
		
		switch(Opcao)
		{
			case 1 :
				if(igualdade(ConjuntoA, ContA, ConjuntoB, ContB) == 0)
				{
					ContUniao = uniao (ConjuntoA, ContA, ConjuntoB, ContB, ConjuntoUniao, ContC);
					printf("\n\nUniao:");
					exibir (ConjuntoUniao, ContUniao);
				}
				else
				{
					printf("\n\nUniao:");
					exibir (ConjuntoA, ContA);
				}
			break;
			
			case 2 :
				if(igualdade(ConjuntoA, ContA, ConjuntoB, ContB) == 0)
				{
					ContInterseccao = interseccao (ConjuntoA, ContA, ConjuntoB, ContB, ConjuntoInterseccao, ContC);
					printf("\n\nInterseccao:");
					exibir (ConjuntoInterseccao, ContInterseccao);
				}
				else
				{
					printf("\n\nInterseccao:");
					exibir (ConjuntoA, ContA);
				}
			break;
			
			case 3 :
				if(igualdade(ConjuntoA, ContA, ConjuntoB, ContB) == 0)
				{
					printf("\n\n(1) = A - B\n(2) = B - A : ");
					scanf("%d", &Opcao);
					
					if(Opcao == 1)
					{
						if(ContA > ContB)
						{
							ContDiferenca = diferenca (ConjuntoA, ContA, ConjuntoB, ContB, ConjuntoDiferenca, ContC);
							printf("\n\nDiferenca A - B:");
							exibir (ConjuntoDiferenca, ContDiferenca);
						}
						else
						{
							printf("\n\nO conjunto A eh menor que o conjunto B.\n\n");
						}
					}
					else
					{
						if(Opcao == 2)
						{
							if(ContB > ContA)
							{
								ContDiferenca = diferenca (ConjuntoB, ContB, ConjuntoA, ContA, ConjuntoDiferenca, ContC);
								printf("\n\nDiferenca B - A:");
								exibir (ConjuntoDiferenca, ContDiferenca);
							}
							else
							{
								printf("\n\nO conjunto B eh menor que o conjunto A.\n\n");
							}
						}
					}
				}
				else
				{
					printf("\n\nNao eh possivel fazer diferenca.\n\n");
				}
			break;
			
			case 4 :
				printf("\n\n(1) Se A esta contido em B.\n(2) Se B esta contido em A.\n");
				scanf("%d", &Opcao);
				
				if(Opcao == 1)
				{
					if(ContA <= ContB)
					{
						if(contido (ConjuntoA, ContA, ConjuntoB, ContB) == 1)
						{
							printf("\n\nO conjunto A esta contido em B.\n\n");						
						}
						else
						{
							printf("\n\nO conjunto A nao esta contido em B.\n\n");
						}
					}
					else
					{
						printf("\n\nO conjunto A nao esta contido em B.\n\n");
					}
				}
				else
				{
					if(ContB <= ContA)
					{
						if(contido (ConjuntoB, ContB, ConjuntoA, ContA) == 1)
						{
							printf("\n\nO conjunto B esta contido em A.\n\n");
						}
						else
						{
							printf("\n\nO conjunto B nao esta contido em A.\n\n");
						}
					}
					else
					{
						printf("\n\nO conjunto B nao esta contido em A.\n\n");
					}
				}
			break;
			
			case 5 :
				printf("\n\n(1) Se A contem B.\n(2) Se B contem A.\n");
				scanf("%d", &Opcao);
				
				if(Opcao == 1)
				{
					//Se A >= B, existe possibilidade de A conter B.
					if(ContA >= ContB)
					{
						if(contem (ConjuntoA, ContA, ConjuntoB, ContB) == 1)
						{
							printf("\n\nO conjunto A contem o B.\n\n");		
						}
						else
						{
							printf("\n\nO conjunto A nao contem o B.\n\n");
						}
					}
					//Se A < B, não existe essa possibilidade.
					else
					{
						printf("\n\nO conjunto A nao contem o B.\n\n");
					}
				}
				else
				{
					if(ContB >= ContA)
					{
						if(contem (ConjuntoB, ContB, ConjuntoA, ContA) == 1)
						{
							printf("\n\nO conjunto B contem o A.\n\n");
						}
						else
						{
							printf("\n\nO conjunto B nao contem o A.\n\n");
						}
					}
					else
					{
						printf("\n\nO conjunto B nao contem o A.\n\n");
					}
				}
			break;
			
			case 6 :
				if(igualdade(ConjuntoA, ContA, ConjuntoB, ContB) == 1)
				{
					printf("\n\nOs conjuntos sao iguais.\n\n");
				}
				else
				{
					printf("\n\nO conjuntos nao sao iguais.\n\n");
				}
			break;
		}
	}
	while(Opcao != 7);
}
