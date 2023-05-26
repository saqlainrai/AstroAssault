#include <iostream>
#include <conio.h>
#include <windows.h>
#include <ctime>
#include <iomanip>
#include <time.h>
#include <fstream>
using namespace std;

// Function Prototypes

// Main Functions
void mainCharacterPrecise();
void printHeader();
void printMaze();
string mainMenu();

// Jet Functions
void printJet();
void eraseJet();
void moveJetLeft();
void moveJetRight();
void moveJetUp();
void moveJetDown();
void moveJetBullet();
void createJetBullet();
void createJumboJetBullet();
void printJetBullet(int x, int y);
void eraseJetBullet(int x, int y);
void deleteJetBulletfromArray(int index);

// Enemy 1 Functions
void printEnemy1();
void eraseEnemy1();
void moveEnemy1Horizontal();
void createEnemy1Bullet();
void moveEnemy1Bullet();
void printEnemy1Bullet(int x, int y);
void eraseEnemy1Bullet(int x, int y);
void deleteEnemyBullet1fromArray(int index);

// Enemy 2 Functions
void printEnemy2();
void eraseEnemy2();
void moveEnemy2Horizontal();
void createEnemy2Bullet();
void moveEnemy2Bullet();
void printEnemy2Bullet(int x, int y);
void eraseEnemy2Bullet(int x, int y);
void deleteEnemyBullet2fromArray(int index);

// Enemy 3 Functions
void printEnemy3();
void eraseEnemy3();
void moveEnemy3Horizontal();
void createEnemy3Bullet();
void moveEnemy3Bullet();
void printEnemy3Bullet(int x, int y);
void eraseEnemy3Bullet(int x, int y);
void deleteEnemyBullet3fromArray(int index);

void gotoxy(int x, int y);
char getCharAtxy(short int x, short int y);
void doColor(int index);

void printScore(); // shows the score on the console
void printTime();
void printScoreMaze();

void printGameOver();

void bulletCollisionwithEnemy();
void bulletCollisionwithBullet();
void bulletCollisionwithJet();

void loadgameData();
void storegameData();

// Global Variables
int JetX = 10, JetY = 20;
int Enemy1X = 20, Enemy1Y = 1;
int Enemy2X = 45, Enemy2Y = 3;
int Enemy3X = 5, Enemy3Y = 5;
int score = 0;
int health = 1;
int deathCounter = 0;
string Enemy1Direction = "Right";
string Enemy2Direction = "Left";
string Enemy3Direction = "Right";
char previous = ' ';

// Global array
int bulletX[100];
int bulletY[100];
int enemyBullet1X[100];
int enemyBullet1Y[100];
int enemyBullet2X[100];
int enemyBullet2Y[100];
int enemyBullet3X[100];
int enemyBullet3Y[100];

// global Count
int bulletCount = 0;
int enemyBullet1Count = 0;
int enemyBullet2Count = 0;
int enemyBullet3Count = 0;
int timeCounter = 0;
string name = "Unknown";

char character1 = 219; // rectangular bar
char character2 = 25;  // down arrow ↓
char character3 = 31;  // down arrow ▼
char character4 = 3;   // heart symbol
char character5 = 18;  // midlle arrow ↕

/*    ^
 O   |||   O
 ||  |█|  ||
 ||  |█|  ||
 |/==|█|==\|
/____|_|____\
   @ | | @
*/

char newJet[7][13] = {
    {' ', ' ', ' ', ' ', ' ', ' ', '^', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', '0', ' ', ' ', ' ', '|', '|', '|', ' ', ' ', ' ', '0', ' '},
    {' ', '|', '|', ' ', ' ', '|', character1, '|', ' ', ' ', '|', '|', ' '},
    {' ', '|', '|', ' ', '/', ' ', character1, ' ', '\\', ' ', '|', '|', ' '},
    {' ', '|', '/', '=', '=', '|', character1, '|', '=', '=', '\\', '|', ' '},
    {'/', '_', '_', '_', '_', '|', '_', '|', '_', '_', '_', '_', '\\'},
    {' ', ' ', ' ', '@', ' ', '|', ' ', '|', ' ', '@', ' ', ' ', ' '}};

char Jet1[4][7] = {{' ', ' ', ' ', '^', ' ', ' ', ' '},
                   {'`', '`', '`', '`', '`', '`', '`'},
                   {' ', '\\', ' ', '~', ' ', '/', ' '},
                   {'`', '`', '`', '`', '`', '`', '`'}};

char Enemy3[4][7] = {
    {'#', ' ', ' ', character3, ' ', ' ', '#'},
    {character1, '=', '=', character1, '=', '=', character1},
    {'|', ' ', ' ', character1, ' ', ' ', '|'},
    {' ', ' ', ' ', '|', ' ', ' ', ' '}};

char Enemy1[5] = {character3, character3, character2, character3, character3};
char Enemy2[5] = {'=', '=', character5, '=', '='};

int main()
{
    doColor(142);

    string option = "1";

    system("cls");
    mainCharacterPrecise();
    int x = 0;
    int consoleX = 30;
    gotoxy(40, 29);
    cout << "Loading....";
    while (x < 25)
    {
        gotoxy(consoleX, 28);
        cout << character1;
        Sleep(100);
        x++;
        consoleX++;
    }

    bool mainMenuPlaying = true;
    while (mainMenuPlaying)
    {
        enemyBullet1Count = 0;
        enemyBullet2Count = 0;
        enemyBullet3Count = 0;
        doColor(142);
        system("cls");
        printHeader();
        option = mainMenu();

        // Play a new Game
        if (option == "1")
        {
            score = 0;
            health = 3;
            bulletCount = 0;
            system("cls");
            printMaze();
            printScoreMaze();
            printJet();

            bool gamePlaying = 1;
            while (gamePlaying)
            {
                doColor(142);
                if (GetAsyncKeyState(VK_LEFT))
                {
                    moveJetLeft();
                }
                if (GetAsyncKeyState(VK_RIGHT))
                {
                    moveJetRight();
                }
                if (GetAsyncKeyState(VK_UP))
                {
                    moveJetUp();
                }
                if (GetAsyncKeyState(VK_DOWN))
                {
                    moveJetDown();
                }
                if (GetAsyncKeyState(VK_SPACE))
                {
                    createJetBullet();
                }
                if (GetAsyncKeyState(VK_END))
                {
                    gamePlaying = 0;
                }
                if (GetAsyncKeyState(0X5A))
                {
                    createJumboJetBullet();
                }
                if (GetAsyncKeyState(VK_ESCAPE))
                {
                    gamePlaying = 0;
                    storegameData();
                }
                if (GetAsyncKeyState(0x53))
                {
                    eraseJet();
                }

                // loops to generate random objects and bullet fires on the console
                if (timeCounter % 10 == 0)
                {
                    createEnemy3Bullet(); // the lowermost will fire first
                }
                else if (timeCounter % 14 == 0)
                {
                    createEnemy2Bullet();
                }
                else if (timeCounter % 16 == 0)
                {
                    createEnemy1Bullet();
                }
                moveEnemy1Bullet();
                moveEnemy2Bullet();
                moveEnemy3Bullet();
                moveEnemy1Horizontal();
                moveEnemy2Horizontal();
                moveEnemy3Horizontal();
                moveJetBullet();
                bulletCollisionwithEnemy();
                bulletCollisionwithJet();
                bulletCollisionwithBullet();
                printScore();
                timeCounter++;

                if (health == 0)
                {
                    system("cls");
                    printHeader();
                    printGameOver();
                    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
                    fflush(stdin);
                    getch();
                    break;
                }
            }
        }

        // Load a new Game
        else if (option == "2")
        {
            loadgameData();
            if (score != -1)
            {
                system("cls");
                printMaze();
                // printEnemy3();
                printScoreMaze();
                printJet();

                bool gamePlaying = 1;
                int i = 1;
                while (gamePlaying)
                {
                    doColor(142);
                    if (GetAsyncKeyState(VK_LEFT))
                    {
                        moveJetLeft();
                    }
                    if (GetAsyncKeyState(VK_RIGHT))
                    {
                        moveJetRight();
                    }
                    if (GetAsyncKeyState(VK_UP))
                    {
                        moveJetUp();
                    }
                    if (GetAsyncKeyState(VK_DOWN))
                    {
                        moveJetDown();
                    }
                    if (GetAsyncKeyState(VK_SPACE))
                    {
                        createJetBullet();
                    }
                    if (GetAsyncKeyState(VK_END))
                    {
                        gamePlaying = 0;
                    }
                    if (GetAsyncKeyState(0X5A))
                    {
                        createJumboJetBullet();
                    }
                    if (GetAsyncKeyState(VK_ESCAPE))
                    {
                        gamePlaying = 0;
                        storegameData();
                    }
                    if (GetAsyncKeyState(0x53))
                    {
                        eraseJet();
                    }

                    // loops to generate random objects and bullet fires on the console
                    if (timeCounter % 10 == 0)
                    {
                        createEnemy3Bullet(); // the lowermost will fire first
                    }
                    else if (timeCounter % 14 == 0)
                    {
                        createEnemy2Bullet();
                    }
                    else if (timeCounter % 16 == 0)
                    {
                        createEnemy1Bullet();
                    }
                    moveEnemy1Bullet();
                    moveEnemy2Bullet();
                    moveEnemy3Bullet();
                    moveEnemy1Horizontal();
                    moveEnemy2Horizontal();
                    moveEnemy3Horizontal();
                    moveJetBullet();
                    bulletCollisionwithEnemy();
                    bulletCollisionwithJet();
                    bulletCollisionwithBullet();
                    printScore();
                    timeCounter++;

                    if (health == 0)
                    {
                        // system("cls");
                        // printHeader();
                        // printGameOver();
                        // getch();
                        // cout << "Loop terminated";
                        // getch();
                        gamePlaying = 0;
                    }
                }
            }
            else
            {
                cout << "                      No! Game is Stored" << endl;
                getch();
            }
        }

        // Keys
        else if (option == "3")
        {
            system("cls");
            printHeader();
            cout << " K E Y S    T O    P L A Y" << endl;
            cout << endl;
            cout << "Sr No.\tKeys\t Functions" << endl;
            cout << endl;
            cout << "1.\tArrows\t Move the Jet" << endl;
            cout << "2.\tZ\t Shoot Jumbo Bullets" << endl;
            cout << "3.\tS\t Hide Jet" << endl;
            cout << "4.\tESCAPE\t Store and Exit Game" << endl;
            cout << "5.\tEND\t Exit Game" << endl;
            cout << endl;
            cout << "Press any key to continue.....";
            getch();
        }

        // Instructions
        else if (option == "4")
        {
            system("cls");
            printHeader();
            cout << "I N S T R U C T I O N S    M E N U" << endl;
            cout << "1.  Use arrows keys to move the character" << endl;
            cout << "2.  Press END to use jumbo fires" << endl;
            cout << "Press any key to continue.....";
            getch();
        }

        // define the name
        else if (option == "5")
        {
            system("cls");
            printHeader();
            cout << "Enter your Name: ";
            cin >> name;
            getch();
        }

        // Exit Game
        else if (option == "6")
        {
            mainMenuPlaying = false;
        }
        else
        {
            cout << "Invalid Value";
            getch();
        }
    }
}

// Main Functions
string mainMenu()
{
    string result;

    cout << "M A I N    M E N U" << endl;
    cout << "1. Play New Game" << endl;
    cout << "2. Load Game" << endl;
    cout << "3. View the Keys to Play" << endl;
    cout << "4. View Instructions" << endl;
    cout << "5. Define your Name" << endl;
    cout << "6. End Game" << endl;
    cout << "Your Option...";
    cin >> result;

    return result;
}
void mainCharacterPrecise()
{
    cout << "              @##===                                                                                 " << endl;
    cout << "          .=+# =*=   ...                               _                                              " << endl;
    cout << "         .=+##+ .=+=    %.                          =**=           .=+*=+%                          " << endl;
    cout << "         ****###+ . +=+++*+                       =**++=*+        .=**===+**.                        " << endl;
    cout << "         ##***####+ . ++++++*+ .                 =**. +%+       =*+===++#*                           " << endl;
    cout << "         +##***#####+   +++++++*+=.              %#** .+***+ =*+==++++#+.                            " << endl;
    cout << "         +*##***######+   ++++++++**=             ##**+. +++***+++**##.                              " << endl;
    cout << "          +###***#######+   +*+++++++**=           ##*** =####**#####+                               " << endl;
    cout << "           #*##***########+  ........... ++   .  +*##******#######***##+                             " << endl;
    cout << "            +*##***#########******######**#####************###****######%=                           " << endl;
    cout << "             +###***###*++++========  =************************########***##+                        " << endl;
    cout << "              *###***##*+=         =+*+= =+*****************#######*=   ==+++***=                    " << endl;
    cout << "               ==##***+    =++=+++      =+***************##########*****+=     ==+***+= +            " << endl;
    cout << "                *###***==++   =+*++==++*****#*********#####################****+==   +*+=            " << endl;
    cout << "                **###**#+        +**=****#*********#########**###+      ==++**#####+=                " << endl;
    cout << "                 #####+            +**#*********########*+==*+ +=.                                   " << endl;
    cout << "                 #%#*             =+*********#######*+== =*###  =*+                                  " << endl;
    cout << "                *#*            ++*********######**+=   =+#####*..+++*+                               " << endl;
    cout << "               **           ++********#######*+=      +*#######=  +++++*=                            " << endl;
    cout << "             =#+.         =+******#######*+=      ===+########## .++++++++*=.                        " << endl;
    cout << "            **+ .     =+******########*+==     =+***++##########*. =++++++++**=.                     " << endl;
    cout << "          .*****+==+*****############*******++****###############+ .   =+++++++*+ .                  " << endl;
    cout << "         .***********###############*#########*************#########*= ... =++++== ..                " << endl;
    cout << "       . ********###########*++***             ########************#####*+  .. ======= . +*+         " << endl;
    cout << "         #***########*+===                               #######***********#*+= .. *+++==  .         " << endl;
    cout << "         +++==#####````                                          ##########*******##%%+              " << endl;
    cout << "                                                                          #####%%+                   " << endl;
    cout << "                                                                                                     " << endl;
    cout << "                                                                                                     " << endl;
    cout << "                                                                                                     " << endl;
}
void printHeader()
{
    doColor(129);
    cout << "    ___         __                ___                          ____   " << endl;
    cout << "   /   |  _____/ /__________     /   |  ______________ ___  __/ / /_  " << endl;
    cout << "  / /| | / ___/ __/ ___/ __ \\   / /| | / ___/ ___/ __ `/ / / / / __/  " << endl;
    cout << " / ___ |(__  ) /_/ /  / /_/ /  / ___ |(__  |__  ) /_/ / /_/ / / /_    " << endl;
    cout << "/_/  |_/____/\\__/_/   \\____/  /_/  |_/____/____/\\__,_/\\__,_/_/\\__/    " << endl;
    cout << endl;
    doColor(132);
    for (int i = 0; i < 72; i++)
    {
        cout << "_";
        Sleep(10);
    }
    cout << endl;
}
void loadgameData()
{
    fstream file;
    file.open("gameData.txt", ios::in);
    file >> score;
    file >> health;
    file >> name;
    file.close();
    file.open("gameData.txt", ios::out);
    file << "-1";
    file.close();
}
void storegameData()
{
    fstream file;
    file.open("gameData.txt", ios::out);
    file << score << endl;
    file << health << endl;
    file << name;
    file.close();
}
void doColor(int index)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, index);
}

// Jet Functions
void eraseJet()
{
    for (int x = 0; x < 7; x++)
    {
        for (int y = 0; y < 13; y++)
        {
            gotoxy(JetX + y, JetY + x);
            cout << " ";
        }
        cout << endl;
    }
}
void printJet()
{
    doColor(142);
    for (int x = 0; x < 7; x++)
    {
        for (int y = 0; y < 13; y++)
        {
            gotoxy(JetX + y, JetY + x);
            cout << newJet[x][y];
        }
        cout << endl;
    }
}
void moveJetLeft()
{
    char next = getCharAtxy(JetX - 1, JetY);
    if (next == ' ')
    {
        eraseJet();
        JetX--;
        printJet();
    }
}
void moveJetRight()
{
    char next = getCharAtxy(JetX + 13, JetY);
    if (next == ' ')
    {
        eraseJet();
        JetX++;
        printJet();
    }
}
void moveJetUp()
{
    char next = getCharAtxy(JetX, JetY - 1);
    if (next == ' ')
    {
        eraseJet();
        JetY--;
        printJet();
    }
}
void moveJetDown()
{
    char next = getCharAtxy(JetX, JetY + 7);
    if (next == ' ')
    {
        eraseJet();
        JetY++;
        printJet();
    }
}
void printJetBullet(int x, int y)
{
    // called in move jet bullet function
    gotoxy(x, y);
    cout << ".";
}
void eraseJetBullet(int x, int y)
{
    // called in move jet bullet function
    gotoxy(x, y);
    cout << " ";
}
void moveJetBullet()
{
    for (int x = 0; x < bulletCount; x++)
    {
        char next = getCharAtxy(bulletX[x], bulletY[x] - 1);
        if (next == ' ')
        {
            eraseJetBullet(bulletX[x], bulletY[x]);
            bulletY[x] = bulletY[x] - 1;
            printJetBullet(bulletX[x], bulletY[x]);
        }
        else
        {
            eraseJetBullet(bulletX[x], bulletY[x]);
            deleteJetBulletfromArray(x);
        }
    }
}
void deleteJetBulletfromArray(int index)
{
    for (int x = index; x < bulletCount; x++)
    {
        bulletX[x] = bulletX[x + 1];
        bulletY[x] = bulletY[x + 1];
    }
    bulletCount--;
}
void createJetBullet()
{
    gotoxy(JetX + 6, JetY - 1);
    cout << ".";
    bulletX[bulletCount] = JetX + 6;
    bulletY[bulletCount] = JetY - 1;
    bulletCount++;
}
void createJumboJetBullet()
{
    gotoxy(JetX + 1, JetY);
    cout << ".";
    bulletX[bulletCount] = JetX + 1;
    bulletY[bulletCount] = JetY;
    bulletCount++;
    gotoxy(JetX + 11, JetY);
    cout << ".";
    bulletX[bulletCount] = JetX + 11;
    bulletY[bulletCount] = JetY;
    bulletCount++;
}

// Enemy 1 Functions (Upper-Most)
void moveEnemy1Bullet()
{
    for (int x = 0; x < enemyBullet1Count; x++)
    {
        char next = getCharAtxy(enemyBullet1X[x], enemyBullet1Y[x] + 1);
        if (next == ' ')
        {
            eraseEnemy1Bullet(enemyBullet1X[x], enemyBullet1Y[x]);
            enemyBullet1Y[x] = enemyBullet1Y[x] + 1;
            printEnemy1Bullet(enemyBullet1X[x], enemyBullet1Y[x]);
        }
        else
        {
            eraseEnemy1Bullet(enemyBullet1X[x], enemyBullet1Y[x]);
            deleteEnemyBullet1fromArray(x);
        }
    }
    Sleep(50);
}
void createEnemy1Bullet()
{
    gotoxy(Enemy1X + 2, Enemy1Y + 1);
    cout << "V";
    enemyBullet1X[enemyBullet1Count] = Enemy1X + 2;
    enemyBullet1Y[enemyBullet1Count] = Enemy1Y + 1;
    enemyBullet1Count++;
}
void printEnemy1Bullet(int x, int y)
{
    gotoxy(x, y);
    cout << "V";
}
void eraseEnemy1Bullet(int x, int y)
{
    gotoxy(x, y);
    cout << " ";
}
void deleteEnemyBullet1fromArray(int index)
{
    for (int x = index; x < enemyBullet1Count; x++)
    {
        enemyBullet1X[x] = enemyBullet1X[x + 1];
        enemyBullet1Y[x] = enemyBullet1Y[x + 1];
    }
    enemyBullet1Count--;
}
void printEnemy1()
{
    gotoxy(Enemy1X, Enemy1Y);
    for (int x = 0; x < 5; x++)
    {
        cout << Enemy1[x];
    }
}
void moveEnemy1Horizontal()
{
    if (Enemy1Direction == "Right")
    {
        char next = getCharAtxy(Enemy1X + 5, Enemy1Y);
        if (next == ' ' || next == '.')
        {
            gotoxy(Enemy1X, Enemy1Y);
            cout << "    ";
            Enemy1X++;
            printEnemy1();
        }
        if (next == '%')
        {
            Enemy1Direction = "Left";
        }
    }
    if (Enemy1Direction == "Left")
    {
        char next = getCharAtxy(Enemy1X - 1, Enemy1Y);
        if (next == ' ' || next == '.')
        {
            gotoxy(Enemy1X, Enemy1Y);
            cout << "     ";
            Enemy1X--;
            printEnemy1();
        }
        if (next == '%')
        {
            Enemy1Direction = "Right";
        }
    }
}

// Enemy 2 Functions
void deleteEnemyBullet2fromArray(int index)
{
    for (int x = index; x < enemyBullet2Count; x++)
    {
        enemyBullet2X[x] = enemyBullet2X[x + 1];
        enemyBullet2Y[x] = enemyBullet2Y[x + 1];
    }
    enemyBullet2Count--;
}
void moveEnemy2Bullet()
{
    for (int x = 0; x < enemyBullet2Count; x++)
    {
        char next = getCharAtxy(enemyBullet2X[x], enemyBullet2Y[x] + 1);
        if (next == ' ')
        {
            eraseEnemy2Bullet(enemyBullet2X[x], enemyBullet2Y[x]);
            enemyBullet2Y[x] = enemyBullet2Y[x] + 1;
            printEnemy2Bullet(enemyBullet2X[x], enemyBullet2Y[x]);
        }
        else
        {
            eraseEnemy2Bullet(enemyBullet2X[x], enemyBullet2Y[x]);
            deleteEnemyBullet2fromArray(x);
        }
    }
    Sleep(50);
}
void moveEnemy2Horizontal()
{
    if (Enemy2Direction == "Right")
    {
        char next = getCharAtxy(Enemy2X + 5, Enemy2Y);
        if (next == ' ' || next == '.')
        {
            gotoxy(Enemy2X, Enemy2Y);
            cout << "    ";
            Enemy2X++;
            printEnemy2();
        }
        if (next == '%')
        {
            Enemy2Direction = "Left";
        }
    }
    if (Enemy2Direction == "Left")
    {
        char next = getCharAtxy(Enemy2X - 1, Enemy2Y);
        if (next == ' ' || next == '.')
        {
            gotoxy(Enemy2X, Enemy2Y);
            cout << "     ";
            Enemy2X--;
            printEnemy2();
        }
        if (next == '%')
        {
            Enemy2Direction = "Right";
        }
    }
    // gotoxy(EnemyX + 2, EnemyY + 1);
    // cout << "o";
}
void printEnemy2()
{
    gotoxy(Enemy2X, Enemy2Y);
    for (int x = 0; x < 5; x++)
    {
        cout << Enemy2[x];
    }
}
void createEnemy2Bullet()
{
    gotoxy(Enemy2X + 2, Enemy2Y + 1);
    cout << "o";
    enemyBullet2X[enemyBullet2Count] = Enemy2X + 2;
    enemyBullet2Y[enemyBullet2Count] = Enemy2Y + 1;
    enemyBullet2Count++;
}
void printEnemy2Bullet(int x, int y)
{
    gotoxy(x, y);
    cout << "o";
}
void eraseEnemy2Bullet(int x, int y)
{
    gotoxy(x, y);
    cout << " ";
}

// Enemy 3 Functions
void moveEnemy3Bullet()
{
    for (int x = 0; x < enemyBullet3Count; x++)
    {
        char next = getCharAtxy(enemyBullet3X[x], enemyBullet3Y[x] + 1);
        if (next == ' ')
        {
            eraseEnemy3Bullet(enemyBullet3X[x], enemyBullet3Y[x]);
            enemyBullet3Y[x] = enemyBullet3Y[x] + 1;
            printEnemy3Bullet(enemyBullet3X[x], enemyBullet3Y[x]);
        }
        else
        {
            eraseEnemy3Bullet(enemyBullet3X[x], enemyBullet3Y[x]);
            deleteEnemyBullet3fromArray(x);
        }
    }
    Sleep(20);
}
void createEnemy3Bullet()
{
    gotoxy(Enemy3X + 3, Enemy3Y + 4);
    cout << character3;
    enemyBullet3X[enemyBullet3Count] = Enemy3X + 3;
    enemyBullet3Y[enemyBullet3Count] = Enemy3Y + 4;
    enemyBullet3Count++;
}
void printEnemy3Bullet(int x, int y)
{
    gotoxy(x, y);
    cout << character3;
}
void eraseEnemy3Bullet(int x, int y)
{
    gotoxy(x, y);
    cout << " ";
}
void deleteEnemyBullet3fromArray(int index)
{
    for (int x = index; x < enemyBullet3Count; x++)
    {
        enemyBullet3X[x] = enemyBullet3X[x + 1];
        enemyBullet3Y[x] = enemyBullet3Y[x + 1];
    }
    enemyBullet3Count--;
}
void printEnemy3()
{
    doColor(129);
    for (int x = 0; x < 4; x++)
    {
        for (int y = 0; y < 7; y++)
        {
            gotoxy(Enemy3X + y, Enemy3Y + x);
            cout << Enemy3[x][y];
        }
    }
}
void eraseEnemy3()
{
    for (int x = 0; x < 4; x++)
    {
        for (int y = 0; y < 7; y++)
        {
            gotoxy(Enemy3X + y, Enemy3Y + x);
            cout << " ";
        }
    }
}
void moveEnemy3Horizontal()
{
    if (Enemy3Direction == "Right")
    {
        char next = getCharAtxy(Enemy3X + 7, Enemy3Y);
        if (next == ' ' || next == '.')
        {
            eraseEnemy3();
            // gotoxy(Enemy3X, Enemy3Y);
            // cout << "    ";
            Enemy3X++;
            printEnemy3();
            // gotoxy(Enemy3X, Enemy3Y);
            // for (int x = 0; x < 5; x++)
            // {
            //     cout << Enemy[x];
            // }
        }
        if (next == '%')
        {
            Enemy3Direction = "Left";
        }
    }
    if (Enemy3Direction == "Left")
    {
        char next = getCharAtxy(Enemy3X - 1, Enemy3Y);
        if (next == ' ' || next == '.')
        {
            eraseEnemy3();
            // gotoxy(Enemy3X, Enemy3Y);
            // cout << "     ";
            Enemy3X--;
            printEnemy3();
            // gotoxy(Enemy3X, Enemy3Y);
            // for (int x = 0; x < 5; x++)
            // {
            //     cout << Enemy[x];
            // }
        }
        if (next == '%')
        {
            Enemy3Direction = "Right";
        }
    }
}

void printMaze()
{
    doColor(142);
    cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
    cout << "%                                                                                                %" << endl;
    cout << "%                                                                                                %" << endl;
    cout << "%                                                                                                %" << endl;
    cout << "%                                                                                                %" << endl;
    cout << "%                                                                                                %" << endl;
    cout << "%                                                                                                %" << endl;
    cout << "%                                                                                                %" << endl;
    cout << "%                                                                                                %" << endl;
    cout << "%                                                                                                %" << endl;
    cout << "%                                                                                                %" << endl;
    cout << "%                                                                                                %" << endl;
    cout << "%                                                                                                %" << endl;
    cout << "%                                                                                                %" << endl;
    cout << "%                                                                                                %" << endl;
    cout << "%                                                                                                %" << endl;
    cout << "%                                                                                                %" << endl;
    cout << "%                                                                                                %" << endl;
    cout << "%                                                                                                %" << endl;
    cout << "%                                                                                                %" << endl;
    cout << "%                                                                                                %" << endl;
    cout << "%                                                                                                %" << endl;
    cout << "%                                                                                                %" << endl;
    cout << "%                                                                                                %" << endl;
    cout << "%                                                                                                %" << endl;
    cout << "%                                                                                                %" << endl;
    cout << "%                                                                                                %" << endl;
    cout << "%                                                                                                %" << endl;
    cout << "%                                                                                                %" << endl;
    cout << "%                                                                                                %" << endl;
    cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
    doColor(142);
}

void printScore()
{
    doColor(132);
    gotoxy(103, 10);
    cout << "Player: " << name;
    gotoxy(103, 12);
    cout << "Score: " << score;
    gotoxy(103, 14);
    cout << "Health: ";
    for (int x = 0; x < health; x++)
    {
        cout << character4;
    }
    cout << "     ";
    gotoxy(103, 16);
    printTime();
}
void printScoreMaze()
{
    doColor(142);
    gotoxy(100, 9);
    cout << "*******************************";
    gotoxy(100, 10);
    cout << "*                             *";
    gotoxy(100, 11);
    cout << "*******************************";
    gotoxy(100, 12);
    cout << "*                             *";
    gotoxy(100, 13);
    cout << "*******************************";
    gotoxy(100, 14);
    cout << "*                             *";
    gotoxy(100, 15);
    cout << "*******************************";
    gotoxy(100, 16);
    cout << "*                             *";
    gotoxy(100, 17);
    cout << "*******************************";
}
void gotoxy(int x, int y)
{
    COORD coordinates;
    coordinates.X = x;
    coordinates.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
}
char getCharAtxy(short int x, short int y)
{
    CHAR_INFO ci;
    COORD xy = {0, 0};
    SMALL_RECT rect = {x, y, x, y};
    COORD coordBufSize;
    coordBufSize.X = 1;
    coordBufSize.Y = 1;
    return ReadConsoleOutput(GetStdHandle(STD_OUTPUT_HANDLE), &ci, coordBufSize, xy, &rect) ? ci.Char.AsciiChar : ' ';
}

void printTime()
{
    doColor(132);
    time_t now = time(0);
    string output = ctime(&now);
    cout << output;
    doColor(240);
}

void bulletCollisionwithEnemy()
{
    for (int x = 0; x < bulletCount; x++)
    {
        if ((Enemy1X == bulletX[x] || Enemy1X + 1 == bulletX[x] || Enemy1X + 2 == bulletX[x] || Enemy1X + 3 == bulletX[x] || Enemy1X + 4 == bulletX[x]) && Enemy1Y == bulletY[x])
        {
            score++;
        }
        if ((Enemy2X == bulletX[x] || Enemy2X + 1 == bulletX[x] || Enemy2X + 2 == bulletX[x] || Enemy2X + 3 == bulletX[x] || Enemy2X + 4 == bulletX[x]) && Enemy2Y == bulletY[x])
        {
            score++;
        }
    }
}
void bulletCollisionwithBullet()
{
    for (int x = 0; x < bulletCount; x++)
    {
        for (int y = 0; y < enemyBullet1Count; y++)
        {
            if ((bulletX[x] == enemyBullet1X[y]) && (bulletY[x + 1] == enemyBullet1Y[y]))
            {
                score = score + 5;
            }
        }
    }
}
void bulletCollisionwithJet()
{
    for (int x = 0; x < enemyBullet1Count; x++)
    {
        if ((JetX + 1 == enemyBullet1X[x] || JetX + 2 == enemyBullet1X[x] || JetX + 3 == enemyBullet1X[x] || JetX + 4 == enemyBullet1X[x] || JetX + 5 == enemyBullet1X[x] || JetX + 6 == enemyBullet1X[x]) && JetY == enemyBullet1Y[x])
        {
            deathCounter++;
        }
        if ((JetX + 7 == enemyBullet1X[x] || JetX + 8 == enemyBullet1X[x] || JetX + 9 == enemyBullet1X[x] || JetX + 10 == enemyBullet1X[x] || JetX + 11 == enemyBullet1X[x]) && JetY == enemyBullet1Y[x])
        {
            deathCounter++;
        }
    }
    for (int x = 0; x < enemyBullet2Count; x++)
    {
        if ((JetX + 1 == enemyBullet2X[x] || JetX + 2 == enemyBullet2X[x] || JetX + 3 == enemyBullet2X[x] || JetX + 4 == enemyBullet2X[x] || JetX + 5 == enemyBullet2X[x] || JetX + 6 == enemyBullet2X[x]) && JetY == enemyBullet2Y[x])
        {
            deathCounter++;
        }
        if ((JetX + 7 == enemyBullet2X[x] || JetX + 8 == enemyBullet2X[x] || JetX + 9 == enemyBullet2X[x] || JetX + 10 == enemyBullet2X[x] || JetX + 11 == enemyBullet2X[x]) && JetY == enemyBullet2Y[x])
        {
            deathCounter++;
        }
    }
    for (int x = 0; x < enemyBullet3Count; x++)
    {
        if ((JetX + 1 == enemyBullet2X[x] || JetX + 2 == enemyBullet2X[x] || JetX + 3 == enemyBullet2X[x] || JetX + 4 == enemyBullet2X[x] || JetX + 5 == enemyBullet2X[x] || JetX + 6 == enemyBullet2X[x]) && JetY == enemyBullet3Y[x])
        {
            deathCounter++;
        }
        if ((JetX + 7 == enemyBullet3X[x] || JetX + 8 == enemyBullet3X[x] || JetX + 9 == enemyBullet3X[x] || JetX + 10 == enemyBullet3X[x] || JetX + 11 == enemyBullet3X[x]) && JetY == enemyBullet3Y[x])
        {
            deathCounter++;
        }
    }
    if (deathCounter == 1)
    {
        health--;
        deathCounter = 0;
    }
}

void printGameOver()
{
    doColor(142);
    gotoxy(0, 8);
    cout << "                =++++++++++      =+++++-     .++++      .++++ .***************:           " << endl;
    cout << "              ++@@#++++++++    ==@@#+%@@++   -@@@@*+. :=*@@@@.:@@@@+==========.           " << endl;
    cout << "            -+@@#*:          -+@@#*. -+#@@== -@@@@@@*-#@@@@@@.:@@@@:                      " << endl;
    cout << "           :@@@@:    :::::: :@@@@:     -@@@@:-@@@@@@@@@@@@@@@.:@@@@+------                " << endl;
    cout << "           :@@@@:   -%@@@@@.:@@@@=.....=@@@@:-@@@@%%@@@%@@@@@.:@@@@%#####*                " << endl;
    cout << "           :@@@@-.    :@@@@.:@@@@@@@@@@@@@@@:-@@@@: *@= -@@@@.:@@@@:                      " << endl;
    cout << "              @@@@-   -@@@@.:@@@@:     -@@@@:-@@@@:     -@@@@.:@@@@:                      " << endl;
    cout << "                %@@@@@@@@@@.:@@@@:     -@@@@.-@@@@:     -@@@@.:@@@@@@@@@@@@@@@-           " << endl;
    cout << "                 ..........  ....       ....                    ..                        " << endl;
    cout << "                                                                                          " << endl;
    cout << "             .@@@@@@@@@@@   :@@@@.     :@@@@.:@@@@@@@@@@@@@@@--@@@@@@@@@@@@%              " << endl;
    cout << "           :%%@@=.:::.=@@@% :@@@@.     -@@@@::@@@@-           -@@@@-:::::+@@%%.           " << endl;
    cout << "           :@@@@:     :@@@@.:@@@@.     -@@@@::@@@@-           -@@@@.     =@@@@.           " << endl;
    cout << "           :@@@@:     :@@@@.:@@@@##: -*#@@@@::@@@@%%%%%%#     -@@@@.   -#%@@@@.           " << endl;
    cout << "           :@@@@:     :@@@@..++@@@@#+%@@@@+= :@@@@+------     -@@@@*+++%@%====            " << endl;
    cout << "           :@@@@:     :@@@@.   +*@@@@@@@++   :@@@@:           -@@@@**@@@@%+=              " << endl;
    cout << "           .##@@+-----+@@#*      *#@@%*+     :@@@@+==========.-@@@@. +#@@@@@--            " << endl;
    cout << "              ###########.         =#=       .***************::####.   -######.           " << endl;
    getch();
}
/*
1. how we will print while moving the array
2. the game started flickering while a little large character
3. IN PRINT THE KEYSTROCKS USED IN the game playing for different functions
*/