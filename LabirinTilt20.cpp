#include <iostream>
#include <ctime>
#include <windows.h>
#include <conio.h>
#include <stack>
#include <fstream>
#include <locale.h>
#include <time.h>

//#define _WIN32_WINNT  0x0500
//#include "stdafx.h" //http://sourceforge.net/p/wpbdc/website/ci/master/tree/Judge/StdAfx.h

using namespace std;
bool pode = false, acabou = false;
int linha = 0, coluna = 1;
char labirinto[35][35];

/********************************
* USED FOR THE SIZE OF THE MAZE *
*   Must be an odd number for   *
*    maze traversal reasons     *
********************************/
#define SIZE 25

// CELL STRUCTURE
struct Cell
{
    bool visited;
    bool top_wall;
    bool bot_wall;
    bool left_wall;
    bool right_wall;
    char display;
};

// FUNCTION DECLARATIONS
void Initialize(Cell Level[][SIZE]);
void ClearScreen();
void Redraw(Cell Level[][SIZE]);
void GenerateMaze(Cell Level[][SIZE], int& posX, int& posY, int& goalX, int& goalY);
void telafinal();

void andar(char walk)
{

    if (walk == 'w')
    {

        if (labirinto[linha - 1][coluna] == ' ')
        {
            labirinto[linha][coluna] = ' ';
            linha--;
            labirinto[linha][coluna] = 'O';
        }
    }
                        
    if (walk == 's')
    {
        if (labirinto[linha + 1][coluna] == ' ')
        {
            if ((linha + 1) == SIZE - 1 && coluna == SIZE - 2)
                acabou = true;
            
            labirinto[linha][coluna] = ' ';
            linha++;
            labirinto[linha][coluna] = 'O';
            
        }
    }

    if (walk == 'd')
    {
        if (labirinto[linha][coluna + 1] == ' ')
        {
            labirinto[linha][coluna] = ' ';
            coluna++;
            labirinto[linha][coluna] = 'O';
        }
    }

    if (walk == 'a')
    {
        if (labirinto[linha][coluna - 1] == ' ')
        {
            labirinto[linha][coluna] = ' ';
            coluna--;
            labirinto[linha][coluna] = 'O';
        }
    }
    else
    {

    }
}

void mudaCor(int nomeCor) {

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
        SetConsoleTextAttribute(console, FOREGROUND_INTENSITY); // Padr�o
    case 5:
        printf("\u001b[37m");//branco
    case 6:
        printf("\u001b[36m");//ciano
    default:
        break;
    }
}

void tela()
{
    system("mode con:cols=70 lines=40");   // tamanho do console 
    int x, y;
    HWND cW = GetConsoleWindow();
    x = GetSystemMetrics(SM_CXSCREEN);   // quantidade de pixel por linhas da tela
    y = GetSystemMetrics(SM_CYSCREEN);   // quantidade de pixel por coluna da tela
    SetWindowPos(cW, 0, x / 2, y / 8, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
}

void mostrar()
{
    mudaCor(1);
    printf("\t  _           _     _      _       _   _ _    _ \n");
    printf("\t | |         | |   (_)    (_)     | | (_) |  | | \n");
    printf("\t | |     __ _| |__  _ _ __ _ _ __ | |_ _| |  | |_\n");
    printf("\t | |    / _` | |_ \\| | |__| | |_ \\| __| | |  | __|\n");
    printf("\t | |___| (_| | |_) | | |  | | | | | | | | |__| |\n");
    printf("\t |______\\__,_|_.__/|_|_|  |_|_| |_|_| |_|____|_|\n\n\n\n");

       mudaCor(6);


    for (int i = 0; i < SIZE; i++) 
    {
        cout << "\t";
        for (int j = 0; j < SIZE; j++)
        {
            if (labirinto[i][j] == 'O')
            {
                cout << "\u001b[37m " << labirinto[i][j];
                mudaCor(6);
            }
            else
            cout << " " << labirinto[i][j];
        }
          

        cout << endl;
    }
}

                                                                                                                                           // MAIN
int main() {

    setlocale(LC_ALL, "Portuguese");

    Cell Level[SIZE][SIZE];
    int posX = 0;
    int posY = 0;
    int goalX = 0;
    int goalY = 0;
    bool game_over = false;

    char walk;

    while (!game_over) {
        
        if (!pode)
        {
            system("cls");
            tela();
            Initialize(Level);
            Redraw(Level);
            GenerateMaze(Level, posX, posY, goalX, goalY); //Mapa gerado
            mostrar();
        }
            
        else
        {   

            printf(" Digite \'w\' para subir\n Digite \'s\' para descer\n Digite \'d\' para ir a direita\n Digite \'a\' para ir a esquerda\n");
            walk = _getch();

            andar(walk);
            system("cls");
            mostrar();

            if (acabou)
            {
                system("cls");
                telafinal();
                char input;
                cout << "\t\t\u001b[37m  Jogar novamente? (s)/(n): ";
                cin >> input;

                if ((input != 'n') && (input != 'N') && (input != 's') && (input != 'S'))
                    cout << "Op��o inv�lida" << endl;
                else if ((input == 'n') || (input == 'N')) {
                    game_over = true;
                    cout << "Volte sempre!" << endl;
                }
                else
                {
                    acabou = false;
                    pode = false;
                    linha = 0;
                    coluna = 1;
                }

            }
        }
    }
    return 0;
}

// INITIALIZE MAZE
void Initialize(Cell Level[][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            Level[i][j].display = '*';
            Level[i][j].visited = false;
            Level[i][j].top_wall = true;
            Level[i][j].bot_wall = true;
            Level[i][j].left_wall = true;
            Level[i][j].right_wall = true;
        }
    }
    for (int i = 1; i < SIZE - 1; i++) {
        for (int j = 1; j < SIZE - 1; j++) {
            // Border Cells have fewer accessible walls
            Level[1][j].top_wall = false;
            Level[SIZE - 2][j].bot_wall = false;
            Level[i][1].left_wall = false;
            Level[i][SIZE - 2].right_wall = false;
        }
    }
}

// CLEAR SCREEN
void ClearScreen()
{
    HANDLE hOut;
    COORD Position;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    Position.X = 0;
    Position.Y = 0;
    SetConsoleCursorPosition(hOut, Position);
}

// REDRAW MAZE
void Redraw(Cell Level[][SIZE]) {

    mudaCor(1);
    printf("\t  _           _     _      _       _   _ _    _ \n");
    printf("\t | |         | |   (_)    (_)     | | (_) |  | | \n");
    printf("\t | |     __ _| |__  _ _ __ _ _ __ | |_ _| |  | |_\n");
    printf("\t | |    / _` | |_ \\| | |__| | |_ \\| __| | |  | __|\n");
    printf("\t | |___| (_| | |_) | | |  | | | | | | | | |__| |\n");
    printf("\t |______\\__,_|_.__/|_|_|  |_|_| |_|_| |_|____|_|\n\n\n\n");

        mudaCor(4);

    for (int i = 0; i < SIZE; i++) {
        cout << "\t";
        for (int j = 0; j < SIZE; j++)
            cout << " " << Level[i][j].display;

        cout << endl;
    }
}

// GENERATE MAZE
void GenerateMaze(Cell Level[][SIZE], int& posX, int& posY, int& goalX, int& goalY) {
    srand((unsigned)time(NULL));                                            // Pick random start cell
    int random = 0;
    int randomX = ((2 * rand()) + 1) % (SIZE - 1);                      // Generate a random odd number between 1 and SIZE
    int randomY = ((2 * rand()) + 1) % (SIZE - 1);                      // Generate a random odd number between 1 and SIZE
    posX = randomX;                                             // Save player's initial X position
    posY = randomY;                                             // Save player's initial Y position
    int visitedCells = 1;
    int totalCells = ((SIZE - 1) / 2) * ((SIZE - 1) / 2);
    int percent = 0;
    stack<int> back_trackX, back_trackY;                        // Stack is used to trace the reverse path

    Level[randomY][randomX].display = ' ';                      // Set S as the start cell
    Level[randomY][randomX].visited = true;                     // Set start cell as visited;

    while (visitedCells < totalCells)
    {
        if (((Level[randomY - 2][randomX].visited == false) && (Level[randomY][randomX].top_wall == true && Level[randomY - 2][randomX].bot_wall == true)) ||
            ((Level[randomY + 2][randomX].visited == false) && (Level[randomY][randomX].bot_wall == true && Level[randomY + 2][randomX].top_wall == true)) ||
            ((Level[randomY][randomX - 2].visited == false) && (Level[randomY][randomX].left_wall == true && Level[randomY][randomX - 2].right_wall == true)) ||
            ((Level[randomY][randomX + 2].visited == false) && (Level[randomY][randomX].right_wall == true && Level[randomY][randomX + 2].left_wall == true)))
        {
            random = (rand() % 4) + 1;      // Pick a random wall 1-4 to knock down

             // GO UP
            if ((random == 1) && (randomY > 1)) {
                if (Level[randomY - 2][randomX].visited == false) {    // If not visited
                    Level[randomY - 1][randomX].display = ' ';    // Delete display
                    Level[randomY - 1][randomX].visited = true;   // Mark cell as visited
                    Level[randomY][randomX].top_wall = false;   // Knock down wall

                    back_trackX.push(randomX);          // Push X for back track
                    back_trackY.push(randomY);          // Push Y for back track

                    randomY -= 2;                   // Move to next cell
                    Level[randomY][randomX].visited = true;     // Mark cell moved to as visited
                    Level[randomY][randomX].display = ' ';      // Update path
                    Level[randomY][randomX].bot_wall = false;   // Knock down wall
                    visitedCells++;                 // Increase visitedCells counter
                }
                else
                    continue;
            }

            // GO DOWN
            else if ((random == 2) && (randomY < SIZE - 2)) {
                if (Level[randomY + 2][randomX].visited == false) {    // If not visited
                    Level[randomY + 1][randomX].display = ' ';    // Delete display
                    Level[randomY + 1][randomX].visited = true;   // Mark cell as visited
                    Level[randomY][randomX].bot_wall = false;   // Knock down wall

                    back_trackX.push(randomX);          // Push X for back track
                    back_trackY.push(randomY);          // Push Y for back track

                    randomY += 2;                   // Move to next cell
                    Level[randomY][randomX].visited = true;     // Mark cell moved to as visited
                    Level[randomY][randomX].display = ' ';      // Update path
                    Level[randomY][randomX].top_wall = false;   // Knock down wall
                    visitedCells++;                 // Increase visitedCells counter
                }
                else
                    continue;
            }

            // GO LEFT
            else if ((random == 3) && (randomX > 1)) {
                if (Level[randomY][randomX - 2].visited == false) {    // If not visited
                    Level[randomY][randomX - 1].display = ' ';    // Delete display
                    Level[randomY][randomX - 1].visited = true;   // Mark cell as visited
                    Level[randomY][randomX].left_wall = false;  // Knock down wall

                    back_trackX.push(randomX);          // Push X for back track
                    back_trackY.push(randomY);          // Push Y for back track

                    randomX -= 2;                   // Move to next cell
                    Level[randomY][randomX].visited = true;     // Mark cell moved to as visited
                    Level[randomY][randomX].display = ' ';      // Update path
                    Level[randomY][randomX].right_wall = false; // Knock down wall
                    visitedCells++;                 // Increase visitedCells counter
                }
                else
                    continue;
            }

            // GO RIGHT
            else if ((random == 4) && (randomX < SIZE - 2)) {
                if (Level[randomY][randomX + 2].visited == false) {    // If not visited
                    Level[randomY][randomX + 1].display = ' ';    // Delete display
                    Level[randomY][randomX + 1].visited = true;   // Mark cell as visited
                    Level[randomY][randomX].right_wall = false; // Knock down wall

                    back_trackX.push(randomX);          // Push X for back track
                    back_trackY.push(randomY);          // Push Y for back track

                    randomX += 2;                   // Move to next cell
                    Level[randomY][randomX].visited = true;     // Mark cell moved to as visited
                    Level[randomY][randomX].display = ' ';      // Update path
                    Level[randomY][randomX].left_wall = false;  // Knock down wall
                    visitedCells++;                 // Increase visitedCells counter
                }
                else
                    continue;
            }

            percent = (visitedCells * 100 / totalCells * 100) / 100;        // Progress in percentage
            cout << endl << "\t\t\u001b[37m       Gerando o mapa... " << percent << "%" << endl;
            if (percent == 100)
                pode = true;

        }
        else {
            randomX = back_trackX.top();
            back_trackX.pop();

            randomY = back_trackY.top();
            back_trackY.pop();
        }

        ClearScreen();
        Redraw(Level);
    }

    goalX = randomX;
    goalY = randomY;
    //Level[goalY][goalX].display = 'E';
    system("cls");
    ClearScreen();
    Redraw(Level);
    cout << endl << "\a\t   Completo!" << endl;

    if(pode)
    {
        

        for (int i = 0; i < SIZE; i++)
            for (int j = 0; j < SIZE; j++)
                labirinto[i][j] = Level[i][j].display;

        labirinto[0][1] = 'O';
        labirinto[SIZE - 1][SIZE - 2] = ' ';

        system("cls");
    }
      
}

void telafinal()
{
    mudaCor(6);
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\t\t   Parab�ns, voc� completou o\n\n\n";


    mudaCor(1);
    printf("\t  _           _     _      _       _   _ _    _ \n");
    printf("\t | |         | |   (_)    (_)     | | (_) |  | | \n");
    printf("\t | |     __ _| |__  _ _ __ _ _ __ | |_ _| |  | |_\n");
    printf("\t | |    / _` | |_ \\| | |__| | |_ \\| __| | |  | __|\n");
    printf("\t | |___| (_| | |_) | | |  | | | | | | | | |__| |\n");
    printf("\t |______\\__,_|_.__/|_|_|  |_|_| |_|_| |_|____|_|\n\n\n\n");



}


