#include <iostream>
#include <string>
#include <stdlib.h>
#include <set>
#include <vector>
#include <locale.h>
using namespace std;

string resp[99999];

int main()
{
	int jogadores,ctime[999],jogo=1,cor[5]{0,0,0,0,0};
	string dica,palavra,time[999],regras;
	set<int> vertime; 
	setlocale(LC_ALL,"");
 
	cout<<"Você deseja ler as regras antes?\nDigite sim ou nao\n";
	cin>>regras;
	
	if(regras=="sim"|| regras=="Sim")
	{
		cout<<"É dado uma dica e um numero de \' _ \' indicando quantas letras tem sua palavra\n";
		cout<<"voce pode digitar apenas uma letra ou a palavra completa porém se você escrever \n";
		cout<<"toda a palavra errada o contador conta um  erro para cada letra errada,mesmo que ela se repita.\n";
	}
	
	else
	{
		cout<<"tem certeza?\nDigite sim ou nao\n";
		cin>>regras;
		
		if(regras=="nao"|| regras=="Nao" || regras=="não" || regras=="Não")
		{
			cout<<"É dado uma dica e um numero de \' _ \' indicando quantas letras tem sua palavra\n";
			cout<<"voce pode digitar apenas uma letra ou a palavra completa porém se você escrever \n";
			cout<<"toda a palavra errada o contador conta um  erro para cada letra errada,mesmo que ela se repita.\n";
		}	
	}
	cout<<"Digite quantas pessoas vão jogar, maximo 5 pessoas"<<endl;
	scanf("%d",&jogadores);
	while(jogadores>5 || jogadores<1)
	{
		printf("numero invalido,digite novamente\n");
		scanf("%d",&jogadores);
	}
	
	for(int k=1;k<=jogadores;k++)
		{
			system("cls");
			printf("Jogador %d escolha seu time\n\n",k);
			
			if(cor[0]==0)
			{
				cout<<"Digite 1 para verde-claro"<<endl;
			}
			if(cor[1]==0)
			{
				cout<<"Digite 2 para vermelho"<<endl;
			}
			if(cor[2]==0)
			{
				cout<<"Digite 3 para rosa"<<endl;
			}
			if(cor[3]==0)
			{
				cout<<"Digite 4 para amarelo"<<endl;
			}
			if(cor[4]==0)
			{
				cout<<"Digite 5 para branco"<<endl;	
			}
	
	
			cin>>ctime[k];
			
			while(vertime.find(ctime[k]) != vertime.end())
			{
				cout<<"Este time ja foi escolhido escolha outro\n";
				
				cin>>ctime[k];
			}
			
			vertime.insert(ctime[k]);
			
			while(ctime[k]>5 || ctime[k]<1)
			{
			cout<<"Numero invalido,digite novamente"<<endl;
			cin>>ctime[k];
			}
			
			cor[ctime[k]-1]=1;
			
			
			system("cls");
		}
	
	for(int j=1;j<=jogadores;j++)
	{		
		if(ctime[j]==1)
			{
				system("color a");
				time[j]="Verde-claro";
			}
			if(ctime[j]==2)
			{
				system("color c");
				time[j]="Vermelho";
			}
			if(ctime[j]==3)
			{
				system("color d");
				time[j]="Rosa";		
			}
			if(ctime[j]==4)
			{
				system("color e");
				time[j]="Amarelo";
			}
			if(ctime[j]==5)
			{
				system("color f");
				time[j]="branco";
			}
			
		system("cls");
		
		cout<<"\n\nvez do jogador "<<time[j]<<endl;
	
	cout<<    "=========="<<endl;
	cout<<    "=========="<<endl;
	
	
	if(jogo==1)
	{
		palavra="soldado";
		dica="Guerra";
	}
	if(jogo==2)
	{
		palavra="historiador";
		dica="Profissao";
	}
	if(jogo==3)
	{
		palavra="guatemala";
		dica="pais";
	}
	if(jogo==4)
	{
		palavra="tampico";
		dica="bebida";
	}
	if(jogo==5)
	{
		palavra="cabide";
		dica="objeto";
	}
	
	cout<<"Erros= 0"<<endl;
	cout<<"A dica eh: "<<dica<<endl;
	
	for(int i=0;i<(int)palavra.size();i++)
	{
		cout<<"_ ";
	}
	cout<<endl;
	
	                                               	int erro=0,nerro=0;
	                                               	char chute;
		
													vector<char> usada;
	
	while(true)
	{
		
		if(jogo==1)
		{
			palavra="soldado";
			dica="Guerra";
		}
	if(jogo==2)
	{
		palavra="historiador";
		dica="profissao";
	}
	if(jogo==3)
	{
		palavra="guatemala";
		dica="pais";
	}
	if(jogo==4)
	{
		palavra="tampico";
		dica="bebida";
	}
	if(jogo==5)
	{
		palavra="cabide";
		dica="objeto";
	}
		
		
		cin>>chute;	
		
		usada.push_back(chute);
		
		
		system("cls");
		
		for(int t=0;t<(int)usada.size();t++)
			cout<<usada[t]<<" ";	
		
		cout<<endl<<endl;
		bool acert=false;
		
		for(int i=0;i<(int)palavra.size();i++)
		{	
			if(chute==palavra[i])
			{
				resp[i]=chute;
				acert=true;
				break;
			}
		}

		if(acert==false)
		{
			erro++;
			nerro++;
		}
		cout<<"vez do jogador "<<time[j]<<endl;
		cout<<    "=========="<<endl;
		if(nerro>=1)
			cout<<"=   O    ="<<endl;	
		if(nerro==2)
			cout<<"=   |    ="<<endl;
		if(nerro==3)
			cout<<"= / |    ="<<endl;
		if(nerro>=4)
			printf("= / | \\  =\n");
		if(nerro==5)
			cout<<"=  /     ="<<endl;
		if(nerro>=6)
			cout<<"=  / \\   ="<<endl;
			
		cout<<    "=========="<<endl;
				

		int fim=(int)palavra.size();

		if(erro==7)
		{
			system("cls");
			cout<<"Voce Perdeu"<<endl;
			jogo++;
			system("pause");
			break;
		}

		if(erro>=0)
		{
			cout<<"Erros= "<<erro<<endl;
		}
	
		else
			cout<<"Erros= 0"<<endl;
	
		cout<<"A dica eh: "<<dica<<endl;


		
		for(int i=0;i<(int)palavra.size();i++)
		{

			if(chute==palavra[i])
			{
				resp[i]=chute;
			}

			if(resp[i]!="")
			{
				cout<<resp[i]<<" ";
				fim--;
			}
			else if(palavra[i]==' ')
			{
				cout<<"- ";
			}
	
			else
				cout<<"_ ";

		}
	
		if(fim==0)
		{
			system("cls");	
			cout<<endl<<"Voce ganhou,parabens =)"<<endl;
			jogo++;
			system("pause");
			
			for(int y=0;y<(int)palavra.size();y++)
				resp[y]="";
			break;
		}	

		cout<<endl;	
	}
	}
}

