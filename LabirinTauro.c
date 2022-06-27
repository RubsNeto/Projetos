#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <locale.h>
#define  FOREGROUND_Yellow 0x0006
#define  FOREGROUND_White 0x0007

/************************************
* USADO PARA O TAMANHO DO LABIRINTO *
*     Deve ser um numero impar      *
************************************/
#define SIZE 23

int line = 1,colum = 1, walk,voltar=-1,bline,bcolum;
bool end = false,Restart = true,wbull = false,win=false;
// ESTRUTURA CELULAR
struct Cell
{
    bool visited;
    bool top_wall;
    bool bot_wall;
    bool left_wall;
    bool right_wall;
    char display;
};

// Uma estrutura para representar uma pilha
struct Stack {
    int top;
    unsigned capacity;
    int* array;
};
// funcao para criar uma pilha de determinada capacidade. Ele inicializa o tamanho de
// empilhar como 0
struct Stack* createStack(unsigned capacity)
{
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (int*)malloc(stack->capacity * sizeof(int));
    return stack;
}

// Declaracao das funcoes
void Initialize(struct Cell Lab[][SIZE]);
void ClearScreen();
void Redraw(struct Cell Lab[][SIZE]);
void GenerateMaze(struct Cell Lab[][SIZE], int posX, int posY, int goalX, int goalY);
int IsFull(struct Stack* stack);
int IsEmpty(struct Stack* stack);
void Push(struct Stack* stack, int item);
int Pop(struct Stack* stack);
void Maze_walk(struct Cell Lab[][SIZE],char walk);
void ChangeColor(int nomeCor);
void congrats();
void screen();
void lost();
void Bull_walk(struct Cell Lab[][SIZE]);



// MAIN
int main() 
{

	setlocale(LC_ALL,"");
    struct Cell Lab[SIZE][SIZE];


    int posX = 0;
    int posY = 0;
    int goalX = 0;
    int goalY = 0;
    char walk;
    bool game_over = false;
    
    screen();

    do{
        if(Restart)
        {
            system("cls");
            Initialize(Lab);
            Redraw(Lab);
            GenerateMaze(Lab, posX, posY, goalX, goalY);
        }
        else
        {
            if(end)
            {
                system("cls");
                char input;
                
                if(win)
                	congrats();
                else
                	lost();
                	
                printf("\t\t\t  Jogar novamente? (s)/(n): \n");
                input = getch();

                if ((input != 'n') && (input != 'N') && (input != 's') && (input != 'S'))
                    printf("Opção inválida\n");
                else if ((input == 'n') || (input == 'N'))
                {
                    game_over = true;
                    printf("Volte sempre!\n");
                }
                else
                {
                    Restart = true;
                    end = false;
                    win = false;
                    line = 1;
                    colum = 1;
                }
            }

            else
            {
                system("cls");
                Redraw(Lab);
                ChangeColor(6);
                printf("\n\nDigite \'w\' para subir\nDigite \'s\' para descer\nDigite \'d\' para ir a direita\nDigite \'a\' para ir a esquerda\n");
                walk = _getch();

                Maze_walk(Lab,walk);
				Bull_walk(Lab);
            }
        }
    }while(!game_over);

    return 0;
}
void Bull_walk(struct Cell Lab[][SIZE]) // funcao que garante a movimentacao do minotauro
{
	srand((unsigned)time(NULL));
	
	wbull = false;
	
	while(!wbull)
	{
		walk = rand()%4;
		
		//verifica se o jogador colide com o minotauro
		if(Lab[bline - 1][bcolum].display == 'O'){ //baixo
			lost();
			break; 	
		}
		if(Lab[bline + 1][bcolum].display == 'O'){//cima
			lost();
			break; 	
		}
		if(Lab[bline][bcolum - 1].display == 'O'){//direita
			lost();
			break; 	
		}
		if(Lab[bline][bcolum + 1].display == 'O'){//esquerda
			lost();
			break; 
		}
				
		
		//movimentacao do minotauro
		if(walk == 0 && voltar != 0 && Lab[bline - 1][bcolum].display == ' ') // sobe
		{
			
			Lab[bline][bcolum].display = ' ';
			bline--;
			Lab[bline][bcolum].display = 'T';
			wbull = true;
			voltar = 1;	
		}
		
		if(walk == 1 && voltar != 1 && Lab[bline + 1][bcolum].display == ' ') // desce
		{
			Lab[bline][bcolum].display = ' ';
			bline++;
			Lab[bline][bcolum].display = 'T';
			wbull = true;
			voltar = 0;	
		}
		
		if(walk == 2 && voltar != 2 && Lab[bline][bcolum - 1].display == ' ') // esquerda
		{
			Lab[bline][bcolum].display = ' ';
			bcolum--;
			Lab[bline][bcolum].display = 'T';
			wbull = true;
			voltar = 3;	
		}
		
		if(walk == 3 && voltar != 3 && Lab[bline][bcolum + 1].display == ' ') // direita
		{
			Lab[bline][bcolum].display = ' ';
			bcolum++;
			Lab[bline][bcolum].display = 'T';
			wbull = true;
			voltar = 2;	
		}
		
		//verifica se esta em um beco sem saida
		if(Lab[bline - 1][bcolum].display != ' ' && Lab[bline][bcolum - 1].display != ' ' && Lab[bline][bcolum + 1].display != ' ')
			voltar = -1;
			
		if(Lab[bline + 1][bcolum].display != ' ' && Lab[bline][bcolum - 1].display != ' ' && Lab[bline][bcolum + 1].display != ' ')
			voltar = -1;
			
		if(Lab[bline + 1][bcolum].display != ' ' && Lab[bline-1][bcolum].display != ' ' && Lab[bline][bcolum + 1].display != ' ')
			voltar = -1;
		
		if(Lab[bline + 1][bcolum].display != ' ' && Lab[bline-1][bcolum].display != ' ' && Lab[bline][bcolum - 1].display != ' ')
			voltar = -1;	
	}
}
void ChangeColor(int nomeCor) {//muda a cor dos chars na tela

    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE); // Criamos uma variavel para manusear o console
    switch (nomeCor) {
    case 1:
        SetConsoleTextAttribute(console, FOREGROUND_GREEN); // Verde
        break;
    case 2:
        SetConsoleTextAttribute(console, FOREGROUND_BLUE); // Azul
        break;
    case 3:
        SetConsoleTextAttribute(console, FOREGROUND_RED); // Vermelho
        break;
    case 4:
        SetConsoleTextAttribute(console, FOREGROUND_INTENSITY); // PadrÃ£o
        break;
    case 5:
    	SetConsoleTextAttribute(console,FOREGROUND_Yellow); // Amarelo
    	break;
    case 6:
    	SetConsoleTextAttribute(console,FOREGROUND_White); //Branco
        break;
    default:
        break;
    }
}

void congrats()//tela de vitoria
{
	ChangeColor(6);
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t   Parabénsns, você completou o\n\n\n");


    ChangeColor(1);
    
	printf("\t _           _     _      _       _                            \n");
    printf("\t| |         | |   (_)    (_)     | |                           \n");
    printf("\t| |     __ _| |__  _ _ __ _ _ __ | |__  ___  _   _ _ __  ___   \n");  
    printf("\t| |    / _` | |_ \\| | |__| | |_ \\| ___|/ _ `| | | | |__/  _  \\ \n"); 
    printf("\t| |___| (_| | |_) | | |  | | | | | |  | (_| | |_| | |  | (_) | \n");        
    printf("\t|______\\__,_|_.__/|_|_|  |_|_| |_|_|   \\__,_|_____|_|  \\_____/ \n\n");
    

}

void lost()//tela de derrota
{
	ChangeColor(6);
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\t\t\tVocê não conseguiu concluir o\n\n\n");


    ChangeColor(3);
    
	printf("\t _           _     _      _       _                            \n");
    printf("\t| |         | |   (_)    (_)     | |                           \n");
    printf("\t| |     __ _| |__  _ _ __ _ _ __ | |__  ___  _   _ _ __  ___   \n");  
    printf("\t| |    / _` | |_ \\| | |__| | |_ \\| ___|/ _ `| | | | |__/  _  \\ \n"); 
    printf("\t| |___| (_| | |_) | | |  | | | | | |  | (_| | |_| | |  | (_) | \n");        
    printf("\t|______\\__,_|_.__/|_|_|  |_|_| |_|_|   \\__,_|_____|_|  \\_____/ \n\n");
    
    end = true;
}
void screen()//faz com que o cmd seja ajustado para o tamanho do jogo
{
    system("mode con:cols=78 lines=40");   // tamanho do console 
    int x, y;
    HWND cW = GetConsoleWindow();
    x = GetSystemMetrics(SM_CXSCREEN);   // quantidade de pixel por linhas da tela
    y = GetSystemMetrics(SM_CYSCREEN);   // quantidade de pixel por coluna da tela
    SetWindowPos(cW, 0, x / 2, y / 8, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
}

// Inicia o labirinto
void Initialize(struct Cell Lab[][SIZE]) {
    int i=0,j=0;

    for(i=0; i<SIZE; i++) {
        for(j=0; j<SIZE; j++) {
            Lab[i][j].display = '#';
            Lab[i][j].visited = false;
            Lab[i][j].top_wall = true;
            Lab[i][j].bot_wall = true;
            Lab[i][j].left_wall = true;
            Lab[i][j].right_wall = true;
        }
    }
    for(i=1; i<SIZE-1; i++) {
        for(j=1; j<SIZE-1; j++) {
            // CÃ©lulas de fronteira tÃªm menos paredes acessÃ­veis
            Lab[1][j].top_wall = false;
            Lab[SIZE-2][j].bot_wall = false;
            Lab[i][1].left_wall = false;
            Lab[i][SIZE-2].right_wall = false;
        }
    }
}

// printa o labirinto na tela
void Redraw(struct Cell Lab[][SIZE]) 
{
    int i=0,j=0;
    
    ChangeColor(1);
    
	printf("\t _           _     _      _       _                            \n");
    printf("\t| |         | |   (_)    (_)     | |                           \n");
    printf("\t| |     __ _| |__  _ _ __ _ _ __ | |__  ___  _   _ _ __  ___   \n");  
    printf("\t| |    / _` | |_ \\| | |__| | |_ \\| ___|/ _ `| | | | |__/  _  \\ \n"); 
    printf("\t| |___| (_| | |_) | | |  | | | | | |  | (_| | |_| | |  | (_) | \n");        
    printf("\t|______\\__,_|_.__/|_|_|  |_|_| |_|_|   \\__,_|_____|_|  \\_____/ \n");
    
    ChangeColor(3);
    for(i=0; i<SIZE; i++) 
	{
        printf("\n\t\t");
        for(j=0; j< SIZE; j++)
		{
			if(Lab[i][j].display == 'O')
			{
				ChangeColor(6);
				printf(" %c",Lab[i][j].display);
				ChangeColor(3);
			}
			else if(Lab[i][j].display == '*')
			{
				ChangeColor(5);
				printf(" %c",Lab[i][j].display);
				ChangeColor(3);
			}
			else if(Lab[i][j].display == 'X')
			{
				ChangeColor(6);
				printf(" %c",Lab[i][j].display);
				ChangeColor(3);
			}
			else if(Lab[i][j].display == 'T')
			{
				ChangeColor(6);
				printf(" %c",Lab[i][j].display);
				ChangeColor(3);
			}
        	else
            	printf(" %c",Lab[i][j].display);
		}

    }
}

int IsFull(struct Stack* stack)//funcoes da pilha
{
    return stack->top == stack->capacity - 1;
}

// A pilha esta vazia quando o topo eh igual a -1
int IsEmpty(struct Stack* stack)
{
    return stack->top == -1;
}
// Funcao para adicionar um item a pilha. Aumenta em 1
void Push(struct Stack* stack, int item)
{
    if (IsFull(stack))
        return;
    stack->array[++stack->top] = item;
}

// Funcao para remover um item da pilha. Diminui em 1
int Pop(struct Stack* stack)
{
    if (IsEmpty(stack))
        return INT_MIN;
    return stack->array[stack->top--];
}

//Faz a movimentacao do personagem
void Maze_walk(struct Cell Lab[][SIZE],char walk)
{

    if (walk == 'w') //sobe
    {
        if (Lab[line - 1][colum].display == ' ')
        {
            Lab[line][colum].display = ' ';
            line--;
            Lab[line][colum].display = 'O';
        }

        else if(Lab[line - 1][colum].display == '*')//caso seja a runa, basta coletar e manter a movimentacao
        {
            Lab[SIZE - 1][SIZE - 2].display = ' ';

            Lab[line][colum].display = ' ';
            line--;
            Lab[line][colum].display = 'O';
        }
    }

    if (walk == 's')//desce
    {

        if (Lab[line + 1][colum].display == ' ')
        {
            if ((line + 1) == SIZE - 1 && colum == SIZE - 2)
            {
                end = true;
                win = true;
			
			}

            Lab[line][colum].display = ' ';
            line++;
            Lab[line][colum].display = 'O';
        }

        else if(Lab[line + 1][colum].display == '*')//caso seja a runa, basta coletar e manter a movimentacao
        {
            Lab[SIZE - 1][SIZE - 2].display = ' ';

            Lab[line][colum].display = ' ';
            line++;
            Lab[line][colum].display = 'O';

        }
    }

    if (walk == 'd')//direita
    {

        if (Lab[line][colum + 1].display == ' ')
        {
            Lab[line][colum].display = ' ';
            colum++;
            Lab[line][colum].display = 'O';
        }

        else if(Lab[line][colum + 1].display == '*')//caso seja a runa, basta coletar e manter a movimentacao
        {
            Lab[SIZE - 1][SIZE - 2].display = ' ';
            Lab[line][colum].display = ' ';
            colum++;
            Lab[line][colum].display = 'O';
        }

    }

    if (walk == 'a')//esquerda
    {
        if (Lab[line][colum - 1].display == ' ')
        {
            Lab[line][colum].display = ' ';
            colum--;
            Lab[line][colum].display = 'O';
        }

        else if(Lab[line][colum - 1].display == '*')//caso seja a runa, basta coletar e manter a movimentacao
        {
            Lab[SIZE - 1][SIZE - 2].display = ' ';
            Lab[line][colum].display = ' ';
            colum--;
            Lab[line][colum].display = 'O';
        }
    }
}

// GERAR LABIRINTO
void GenerateMaze(struct Cell Lab[][SIZE], int posX, int posY, int goalX, int goalY)
{
    srand((unsigned)time(NULL));                                // Garante que toda vez seja um numero aleatorio
    struct Stack* stack = createStack(200);
    int random = 0;
    int randomX = ((2*rand())+1)%(SIZE-1);                      // Gera um numero impar aleatorio entre 1 e tamanho
    int randomY = ((2*rand())+1)%(SIZE-1);                      // Gera um numero impar aleatorio entre 1 e tamanho
    posX = randomX;                                             // Salvar a posicao X inicial para geracao do labirinto
    posY = randomY;                                             // Salvar a posicao Y inicial para geracao do labirinto
    int visitedCells = 1;
    int totalCells = ((SIZE-1)/2)*((SIZE-1)/2);
    int percent = 0;
	Restart = false;
	
    Lab[randomY][randomX].display = ' ';                      // Define ' ' como a posicao inicial
    Lab[randomY][randomX].visited = true;                     // Defina a posicao inicial como visitada

    while(visitedCells < totalCells)
    {
        if((!Lab[randomY - 2][randomX].visited && (Lab[randomY][randomX].top_wall && Lab[randomY - 2][randomX].bot_wall))    ||
           (!Lab[randomY + 2][randomX].visited && (Lab[randomY][randomX].bot_wall && Lab[randomY + 2][randomX].top_wall))    ||
           (!Lab[randomY][randomX - 2].visited && (Lab[randomY][randomX].left_wall && Lab[randomY][randomX - 2].right_wall)) ||
           (!Lab[randomY][randomX + 2].visited && (Lab[randomY][randomX].right_wall && Lab[randomY][randomX + 2].left_wall)))
        {
            random = (rand() % 4) + 1;      //Escolha uma parede aleatÃ³ria 1-4 para derrubar

            // IR PARA CIMA
            if((random == 1) && (randomY > 1))
            {
                if(!Lab[randomY - 2][randomX].visited)
                {    // Se nÃ£o visitou
                    Lab[randomY-1][randomX].display = ' ';    // Exclui a posicao atual
                    Lab[randomY-1][randomX].visited = true;   // Marcar posicao como visitada
                    Lab[randomY][randomX].top_wall = false;   // Derrubar parede

                    Push(stack,randomX);
                    Push(stack,randomY);

                    randomY -= 2;                             // Mover para a proxima posicao
                    Lab[randomY][randomX].visited = true;     // Marcar posicao movida como visitada
                    Lab[randomY][randomX].display = ' ';      // Exclui a posicao atual
                    Lab[randomY][randomX].bot_wall = false;   // Derrubar parede
                    visitedCells++;                           // Aumentar contador de celulas visitadas
                }
                else
                    continue;
            }

                // DESCER 
            else if((random == 2) && (randomY < SIZE-2))
            {
                if(!Lab[randomY + 2][randomX].visited)
                {    // Se nao visitou
                    Lab[randomY+1][randomX].display = ' ';    // Exclui a posicao atual
                    Lab[randomY+1][randomX].visited = true;   // Marcar posicao como visitada
                    Lab[randomY][randomX].bot_wall = false;   // Derrubar parede

                    Push(stack,randomX);
                    Push(stack,randomY);

                    randomY += 2;                             // Mover para a proxima posicao
                    Lab[randomY][randomX].visited = true;     // Marcar posicao movida como visitada
                    Lab[randomY][randomX].display = ' ';      // Exclui a posicao atual
                    Lab[randomY][randomX].top_wall = false;   // Derrubar parede
                    visitedCells++;                           // Aumentar contador de celulas visitadas
                }
                else
                    continue;
            }

                // PARA A DIREITA
            else if((random == 4) && (randomX < SIZE-2))
            {
                if(!Lab[randomY][randomX + 2].visited)
                {    // Se nao visitou
                    Lab[randomY][randomX+1].display = ' ';    // Exclui a posicao atual
                    Lab[randomY][randomX+1].visited = true;   // Marcar posicao como visitada
                    Lab[randomY][randomX].right_wall = false; // Derrubar parede
                    Push(stack,randomX);
                    Push(stack,randomY);

                    randomX += 2;                             // Mover para a proxima posicao
                    Lab[randomY][randomX].visited = true;     // Marcar posicao movida como visitada
                    Lab[randomY][randomX].display = ' ';      // Exclui a posicao atual
                    Lab[randomY][randomX].left_wall = false;  // Derrubar parede 
                    visitedCells++;                           // Aumentar contador de celulas visitadas
                }
                else
                    continue;
            }

                // PARA ESQUERDA
            else if((random == 3) && (randomX > 1))
            {
                if(!Lab[randomY][randomX - 2].visited)
                {    // Se nÃ£o visitou 
                    Lab[randomY][randomX-1].display = ' ';    // Exclui a posicao atual
                    Lab[randomY][randomX-1].visited = true;   // Marcar posicao como visitada
                    Lab[randomY][randomX].left_wall = false;  // Derrubar parede

                    Push(stack,randomX);
                    Push(stack,randomY);

                    randomX -= 2;                             // Mover para a proxima posicao
                    Lab[randomY][randomX].visited = true;     // Marcar posicao movida como visitada
                    Lab[randomY][randomX].display = ' ';      // Exclui a posicao atual
                    Lab[randomY][randomX].right_wall = false; // Derrubar parede 
                    visitedCells++;                           // Aumentar contador de celulas visitadas
                }
                else
                    continue;
            }


            percent = (visitedCells*100/totalCells*100)/100;        // Progresso em porcentagem
            printf("\n\t\t\t      Gerando o mapa... %d\%\n",percent);
        }
        else
        {
            randomY = Pop(stack);
            randomX = Pop(stack);
        }

        system("cls");
        Redraw(Lab);
    }

    bool XY_da_chave = false;
    int X_chave,Y_chave;


    goalX = randomX;
    goalY = randomY;
    Lab[1][1].display = 'O';               //Coloca o personagem principal no jogo
    Lab[SIZE - 1][SIZE - 2].display = 'X'; // Coloca a parede no jogo
    bline = (SIZE-1)/2;
    bcolum = (SIZE-1)/2;
    Lab[bline][bcolum].display = 'T';      //Coloca o minotauro no jogo
    system("cls");

    while(!XY_da_chave)                   //Faz a geracao da runa
    {
        X_chave = (rand()%SIZE-1);
        Y_chave = (rand()%SIZE-1);

        if(Lab[X_chave][Y_chave].display == ' ')
        {
            Lab[X_chave][Y_chave].display = '*';
            XY_da_chave = true;
        }
    }
    Redraw(Lab);
    printf("\n\a\t\t\t\t  Completo!\n");
}




