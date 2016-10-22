# Trabalho-AL1

/*		Determinado banco solicitou o desenvolvimento de
	um módulo de um sistema que permitirá ao cliente
	executar as operações de saque, depósito e
	empréstimo.
		Para isso, ao iniciar a execução, o programa deve
	solicitar ao usuário o saldo inicial de sua conta. E,
	em seguida, será exibido um menu contendo as
	opções: (S)aque, (D)epósito, (E)mpréstimo,
	S(a)ída, respeitando as seguintes regras:
		1) Saque: o valor solicitado para saque deve
	ser descontado do saldo da conta. Caso
	este exceda o saldo disponível, o sistema
	deverá considerar que todo cliente possui
	um limite especial de R$ 1.000,00. Porém,
	caso o limite seja usado, serão cobrados
	juros de 1% sobre o valor utilizado,
	calculado a cada nova operação realizada.
	Na primeira tentativa de realizar um saque
	que ultrapasse o limite especial, o sistema
	deve bloquear as opções de saque e
	empréstimo, até que o saldo volte a ser
	positivo (em função de depósitos
	realizados pelo cliente);
		2) Depósito: o valor deve ser adicionado ao
	saldo atual da conta. Caso o cliente esteja
	utilizando o seu limite especial e o
	depósito cubra o valor utilizado, os juros
	não serão mais calculados; (Tem que cubrir o valor do Juros, não do Limite)
		3) Empréstimo: cada cliente pode solicitar ao
	banco empréstimo limitado a 40% do seu
	saldo. O valor do empréstimo, acrescido
	de 10% de juros, deverá ser pago em 5
	vezes, da seguinte forma: a cada 5
	operações realizadas, uma nova parcela
	será automaticamente descontada do
	saldo do cliente;
		4) Saída do sistema: ao ser selecionada esta
	opção, o sistema deve apresentar o saldo
	final da conta e terminar a execução do
	programa.
*/
//O limite deve ser guardado e somado com o anterior caso a operação seja saque mais de uma vez.
//Testar o que acontece se cliente pegar o limite < 1000 e tentar o saque de novo, pegando ou não do limite outra vez.
//Vou ter que diminuir o limite de 1000 com o antigo p/ dar um novo limite a ser retirado.
//Limite precisa começar com 0 para entrar no primeiro if no começo do programa.

#include<stdio.h>

int main() 
{		   
	int i=0;
	float Saldo=0, Saque=0, Deposito=0, Limite=0, JurosL=0, JurosE=0, Emprestimo=0, Parcela, LimiteE; 
	char operacao;
	
	printf("Digite o saldo inicial de sua conta: ");
	scanf("%f", &Saldo);
	
	do
	{
		if(Emprestimo > 0) //Para pagar o empréstimo.
		{
			if(i % 5 == 0) //A cada 5 operações.
			{
				Saldo -= Parcela;
			}
		}
	
		//Solução para não repetir a pergunta das operações iniciais quando passar o limite.
		if(Limite <= 1000)
		{			
			//Saber qual operação o cliente quer.
			printf("Saque(S), Deposito(D), Emprestimo(E) ou Saida(a)?: ");
			fflush(stdin);
			scanf("%c", &operacao);
			
			switch(operacao)
			{			
				case 'S' :
					printf("Digite o valor do saque desejado: ");
					scanf("%f", &Saque);
					
					if(Saque <= Saldo)
					{
						Saldo = Saldo - Saque;
						printf("Saldo atual: R$%.2f \n\n", Saldo);
					}
					else
					{
						printf("\nVoce possui um limite especial de R$1000,00 alem do valor do saldo.\nSe passar, pagara 1 por cento de juros a cada operacao.\n\n");
							
						if(Limite != 0) //Já vai entrar com Saldo == 0. / Vai entrar a partir do segundo saque.
						{							
							Limite = Limite + Saque;		
							printf("Limite atual: R$%.2f \n\n", Limite);								
							
							JurosL = Limite + (Limite*0.01); 
							printf("Quanto deve(Juros + Limite): R$%.2f \n\n", JurosL);
							
							printf("Saldo atual: R$%.2f \n\n", Saldo);
						}
						else //Só pra calcular o Limite.
						{	//O juros entra na próxima operação.
							Limite = Saque - Saldo; //Saque é maior que o saldo / Calcula um novo limite, se primeira operação, limite original == 0.
							printf("Limite atual: R$%.2f \n\n", Limite);
																	
							Saldo = Saldo + Limite - Saque;
							printf("Saldo atual: R$%.2f \n\n", Saldo);
						}
					}
				break;
					
				case 'D' :					
					printf("Saldo atual: R$%.2f \n\n", Saldo);
					
					printf("Digite o valor do deposito desejado: "); //Deve considerar depósito > 0.
					scanf("%f", &Deposito);
									
					if(Limite = 0) //Pode ser a primeira operação ou não.
					{
						Saldo = Saldo + Deposito;
						printf("Saldo atual1: R$%.2 \n\n", Saldo);
					}
					else //Já passou pelo saque e pegou um valor pro Limite <= 1000.
					{ //Saldo  antigo == 0.			
						JurosL = Limite + (Limite*0.01); // Se pegar um novo limite, o juros do anterior vai sumir.
						
						printf("Quanto deve(Juros + Limite): R$%.2f \n\n", JurosL);
								
						if(Deposito >= JurosL) //Acabar com o juros.
						{
							JurosL = 0;
							
							Limite = 0;
							
							Saldo = Saldo + Deposito;
							printf("Saldo atual2: R$%.2f \n\n", Saldo);
						}
						else
						{							
							Saldo = Saldo + Deposito - JurosL;
							printf("Saldo atual: R$%.2f \n\n", Saldo);														
						}
					}
				break;
						
				case 'E' : // (3)
					LimiteE = 0.4*Saldo;
					
					printf("\nVoce possui R$%.2f para emprestimo. \nDigite quanto deseja: ", LimiteE);
					scanf("%f", &Emprestimo);
					
					if(Emprestimo <= LimiteE)
					{
						JurosE = Emprestimo + (0.1*Emprestimo);
						
						Parcela = JurosE/5;
					}
					else
					{
						printf("Valor digitado superior ao disponivel\n\n");
					}
							
				break;
				
				case 'a' :
					printf("Seu saldo final eh: R$%.2f \n", Saldo);
					
				break;
			}
		}
		else //Só vai entrar se pegar o Limite se passar dos 1000.
		{
			printf("Deposito(D) ou Saida(a)?: ");
			fflush(stdin);
			scanf("%c", &operacao);
				
			switch(operacao)
			{
				case 'D' : // (2) Deve-se considerar que o depósito seja != 0.								
					JurosL = Limite + (Limite*0.01); 
					printf("Quanto deve(Juros + Limite): R$%.2f \n\n", JurosL);
			
					printf("Digite o valor do deposito desejado: ");
					scanf("%f", &Deposito);
			
					if(Deposito >= Saldo) //Acabar com o juros.
					{
						Saldo = (Saldo + Deposito) - JurosL;
						printf("Saldo atual: R$%.2f \n", Saldo);
						
						Limite = 0;
					}
					else //Continua com o juros.
					{
						Saldo = Saldo + Deposito;
						printf("Saldo atual: R$%.2f \n", Saldo);
					}
				break;
				
				case 'a' :
					printf("Seu saldo final eh: R$%.2f \n", Saldo);
				break;
			}
		}
		i++;
	}
	while(operacao != 'a'); // (4)
}
