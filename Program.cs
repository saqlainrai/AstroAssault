using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Runtime.InteropServices.ComTypes;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Input;
using EZInput;
using MyGameProject.BL;

namespace MyGameProject
{
    internal class Program
    {
        // Global Variables
        static int JetX = 20, JetY = 25;
        static int Enemy1X = 1, Enemy1Y = 85;
        static int Enemy2X = 3, Enemy2Y = 3;
        static int Enemy3X = 5, Enemy3Y = 50;
        static int score = 0;
        static int health = 3;
        static int level = 1;
        static int deathCounter = 0;
        static string Enemy1Direction = "Right";
        static string Enemy2Direction = "Left";
        static string Enemy3Direction = "Right";
        static char previous = ' ';

        static string name = "Unknown";

        //static char character1 = Convert.ToChar(219); // rectangular bar    // both cases achieve the same result
        static char character1 = '█';                   // rectangular bar    // both cases achieve the same result
        static char character2 = (char)25;              // down arrow ↓
        static char character3 = (char)31;              // down arrow ▼
        static char character4 = (char)3;               // heart symbol
        static char character5 = (char)18;              // midlle arrow ↕

        /*    ^
         O   |||   O
         ||  |█|  ||
         ||  |█|  ||
         |/==|█|==\|
        /____|_|____\
           @ | | @
        */

        static char[,] maze = new char[30, 100];

        static char[,] newJet = new char[7, 13] {
            {' ', ' ', ' ', ' ', ' ', ' ', '^', ' ', ' ', ' ', ' ', ' ', ' '},
            {' ', '0', ' ', ' ', ' ', '|', '|', '|', ' ', ' ', ' ', '0', ' '},
            {' ', '|', '|', ' ', ' ', '|', character1, '|', ' ', ' ', '|', '|', ' '},
            {' ', '|', '|', ' ', '/', ' ', character1, ' ', '\\', ' ', '|', '|', ' '},
            { ' ', '|', '/', '=', '=', '|', character1, '|', '=', '=', '\\', '|', ' '},
            { '/', '_', '_', '_', '_', '|', '_', '|', '_', '_', '_', '_', '\\'},
            { ' ', ' ', ' ', '@', ' ', '|', ' ', '|', ' ', '@', ' ', ' ', ' '}};

        static char[,] Enemy3 = new char[4, 7]{
            { '#', ' ', ' ', character3, ' ', ' ', '#'},
            { character1, '=', '=', character1, '=', '=', character1},
            { '|', ' ', ' ', character1, ' ', ' ', '|'},
            { ' ', ' ', ' ', '|', ' ', ' ', ' '}};

        static void Main(string[] args)
        {
            // Arrays Declaration
            int[] bulletX = new int[100];
            int[] bulletY = new int[100];
            int[] enemyBullet1X = new int[100];
            int[] enemyBullet1Y = new int[100];
            int[] enemyBullet2X = new int[100];
            int[] enemyBullet2Y = new int[100];
            int[] enemyBullet3X = new int[100];
            int[] enemyBullet3Y = new int[100];

            List<JetBullets> allJetBullets = new List<JetBullets>();
            List<Enemy1Bullets> allEnemy1Bullets = new List<Enemy1Bullets>();
            List<Enemy2Bullets> allEnemy2Bullets = new List<Enemy2Bullets>();
            List<Enemy3Bullets> allEnemy3Bullets = new List<Enemy3Bullets>();

            // Count Variable
            int bulletCount = 0;
            int enemyBullet1Count = 0;
            int enemyBullet2Count = 0;
            int enemyBullet3Count = 0;
            int timeCounter = 0;

            for (int i = 0; i < 30; i++)
            {
                for (int j = 0; j < 100; j++)
                {
                    if (i == 0 || j == 0 || i == 29 || j == 99)
                    {
                        maze[i, j] = '%';
                    }
                    else
                    {
                        maze[i, j] = ' ';
                    }
                }
            }
            Console.Clear();
            establishColor();

            string option = "1";

            Console.Clear();

            int consoleX = 30;
            doColor("by");
            mainCharacterPrecise();
            Console.SetCursorPosition(40, 29);
            Console.WriteLine("Loading....");
            while (consoleX < 55)
            {
                Console.SetCursorPosition(consoleX, 28);
                Console.WriteLine("█");
                Thread.Sleep(100);
                consoleX++;
            }
            establishColor();
            bool mainMenuPlaying = true;
            while (mainMenuPlaying)
            {
                Console.Clear();
                doColor("ry");
                printHeader();
                option = mainMenu();

                // Play a new Game
                if (option == "1")
                {
                    doColor("by");
                    int i;
                    for (i = 0; i < bulletCount; i++)
                    {
                        eraseJetBullet(bulletX[i], bulletY[i]);
                    }
                    for (i = 0; i < enemyBullet1Count; i++)
                    {
                        eraseJetBullet(enemyBullet1X[i], enemyBullet1Y[i]);
                    }
                    for (i = 0; i < enemyBullet2Count; i++)
                    {
                        eraseJetBullet(enemyBullet2X[i], enemyBullet2Y[i]);
                    }
                    for (i = 0; i < enemyBullet3Count; i++)
                    {
                        eraseJetBullet(enemyBullet3X[i], enemyBullet3Y[i]);
                    }
                    score = 0;
                    health = 3;
                    bulletCount = 0;
                    enemyBullet1Count = 0;
                    enemyBullet2Count = 0;
                    enemyBullet3Count = 0;
                    Console.Clear();
                    printScoreMaze();
                    printJet();

                    bool gamePlaying = true;
                    while (gamePlaying)
                    {
                        printMaze();
                        doColor("bw");
                        // to use IsKeyDown import   using System.Windows.Input;
                        // and it will detect key only if that key is pressed at same instance
                        if (Keyboard.IsKeyPressed(Key.LeftArrow))
                        {
                            moveJetLeft();
                        }
                        if (Keyboard.IsKeyPressed(Key.RightArrow))
                        {
                            moveJetRight();
                        }
                        if (Keyboard.IsKeyPressed(Key.UpArrow))
                        {
                            moveJetUp();
                        }
                        if (Keyboard.IsKeyPressed(Key.DownArrow))
                        {
                            moveJetDown();
                        }

                        if (Keyboard.IsKeyPressed(Key.Space))
                        {
                            createJetBullet(ref bulletCount, bulletX, bulletY);
                            score++;
                        }
                        if (Keyboard.IsKeyPressed(Key.End))
                        {
                            gamePlaying = false;
                        }
                        if (Keyboard.IsKeyPressed(Key.Escape))
                        {
                            gamePlaying = false;
                            storegameData();
                        }

                        // loops to generate random objects and bullet fires on the console
                        if (timeCounter % 10 == 0)
                        {
                            createEnemy3Bullet(ref enemyBullet3Count, enemyBullet3X, enemyBullet3Y); // the lowermost will fire first
                        }
                        if (timeCounter % 14 == 0)
                        {
                            createEnemy2Bullet(ref enemyBullet2Count, enemyBullet2X, enemyBullet2Y);
                        }
                        if (timeCounter % 16 == 0)
                        {
                            createEnemy1Bullet(enemyBullet1X, enemyBullet1Y, ref enemyBullet1Count);
                        }
                        moveEnemy1Bullet(ref enemyBullet1Count, enemyBullet1X, enemyBullet1Y);
                        moveEnemy2Bullet(ref enemyBullet2Count, enemyBullet2X, enemyBullet2Y);
                        moveEnemy3Bullet(ref enemyBullet3Count, enemyBullet3X, enemyBullet3Y);
                        moveJetBullet(bulletX, bulletY, ref bulletCount);
                        moveEnemy1Horizontal();
                        moveEnemy2Horizontal();
                        moveEnemy3Horizontal();
                        //bulletCollisionwithEnemy(ref bulletCount, bulletX, bulletY);
                        //bulletCollisionwithJet(enemyBullet1Count, enemyBullet2Count, enemyBullet3Count, enemyBullet1X, enemyBullet2X, enemyBullet3X, enemyBullet1Y, enemyBullet2Y, enemyBullet3Y);
                        printScore();
                        timeCounter++;

                        if (health == 0)
                        {
                            break;
                        }
                        if (score == 50)
                        {
                            level = 1;
                        }
                        else if (score == 100)
                        {
                            level = 2;
                        }
                        else if (score >= 100)
                        {
                            gamePlaying = false;
                            Console.Clear();
                            Console.WriteLine("You Win");
                        }
                    }
                }

                // Load a new Game
                else if (option == "2")
                {
                    doColor("by");
                    loadgameData();
                    if (score != -1)
                    {
                        Console.Clear();
                        printMaze();
                        printScoreMaze();
                        printJet();

                        bool gamePlaying = true;
                        while (gamePlaying)
                        {
                            printMaze();
                            doColor("bw");
                            // to use IsKeyDown import   using System.Windows.Input;
                            // and it will detect key only if that key is pressed at same instance
                            if (Keyboard.IsKeyPressed(Key.LeftArrow))
                            {
                                moveJetLeft();
                            }
                            if (Keyboard.IsKeyPressed(Key.RightArrow))
                            {
                                moveJetRight();
                            }
                            if (Keyboard.IsKeyPressed(Key.UpArrow))
                            {
                                moveJetUp();
                            }
                            if (Keyboard.IsKeyPressed(Key.DownArrow))
                            {
                                moveJetDown();
                            }

                            if (Keyboard.IsKeyPressed(Key.Space))
                            {
                                createJetBullet(ref bulletCount, bulletX, bulletY);
                            }
                            if (Keyboard.IsKeyPressed(Key.End))
                            {
                                gamePlaying = false;
                            }
                            if (Keyboard.IsKeyPressed(Key.Escape))
                            {
                                gamePlaying = false;
                                storegameData();
                            }

                            // loops to generate random objects and bullet fires on the console
                            if (timeCounter % 10 == 0)
                            {
                                createEnemy3Bullet(ref enemyBullet3Count, enemyBullet3X, enemyBullet3Y); // the lowermost will fire first
                            }
                            else if (timeCounter % 14 == 0)
                            {
                                createEnemy2Bullet(ref enemyBullet2Count, enemyBullet2X, enemyBullet2Y);
                            }
                            else if (timeCounter % 16 == 0)
                            {
                                createEnemy1Bullet(enemyBullet1X, enemyBullet1Y, ref enemyBullet1Count);
                            }
                            moveEnemy1Bullet(ref enemyBullet1Count, enemyBullet1X, enemyBullet1Y);
                            moveEnemy2Bullet(ref enemyBullet2Count, enemyBullet2X, enemyBullet2Y);
                            moveEnemy3Bullet(ref enemyBullet3Count, enemyBullet3X, enemyBullet3Y);
                            moveJetBullet(bulletX, bulletY, ref bulletCount);
                            moveEnemy1Horizontal();
                            moveEnemy2Horizontal();
                            moveEnemy3Horizontal();
                            //bulletCollisionwithEnemy(ref bulletCount, bulletX, bulletY);
                            //bulletCollisionwithJet(enemyBullet1Count, enemyBullet2Count, enemyBullet3Count, enemyBullet1X, enemyBullet2X, enemyBullet3X, enemyBullet1Y, enemyBullet2Y, enemyBullet3Y);
                            printScore();
                            timeCounter++;

                            if (health == 0)
                            {
                                break;
                            }
                            if (score == 50)
                            {
                                level = 1;
                            }
                            else if (score == 100)
                            {
                                level = 2;
                            }
                            else if (score >= 100)
                            {
                                gamePlaying = false;
                                Console.Clear();
                                Console.WriteLine("You Win");
                            }
                        }
                    }
                    else
                    {
                        Console.WriteLine("                      No! Game is Stored");
                        Console.ReadKey();
                    }
                }

                // Keys
                else if (option == "3")
                {
                    Console.Clear();
                    printHeader();
                    Console.WriteLine(" K E Y S    T O    P L A Y");
                    Console.WriteLine();
                    Console.WriteLine("Sr No.\tKeys\t Functions");
                    Console.WriteLine();
                    Console.WriteLine("1.\tArrows\t Move the Jet");
                    Console.WriteLine("2.\tZ\t Shoot Jumbo Bullets");
                    Console.WriteLine("3.\tS\t Hide Jet");
                    Console.WriteLine("4.\tESCAPE\t Store and Exit Game");
                    Console.WriteLine("5.\tEND\t Exit Game");
                    Console.WriteLine();
                    Console.WriteLine("Press any key to continue.....");
                    Console.ReadKey();
                }

                // Instructions
                else if (option == "4")
                {
                    Console.Clear();
                    printHeader();
                    Console.WriteLine("I N S T R U C T I O N S    M E N U");
                    Console.WriteLine();
                    Console.WriteLine("1.  Use arrows keys to move the character");
                    Console.WriteLine("2.  Press Z to use jumbo fires");
                    Console.WriteLine("3.  Press S to Hide the character");
                    Console.WriteLine("4.  Authors own all Copyrights");
                    Console.WriteLine();
                    Console.WriteLine("Press any key to continue.....");
                    Console.ReadKey();
                }

                // define the name
                else if (option == "5")
                {
                    Console.Clear();
                    printHeader();
                    Console.Write("Enter your Name: ");
                    name = Console.ReadLine();
                    Console.ReadKey();
                }

                // Exit Game
                else if (option == "6")
                {
                    mainMenuPlaying = false;
                }

                // Else Case
                else
                {
                    Console.WriteLine("Invalid Value");
                    Console.ReadKey();
                }
            }


        }

        // Main Functions
        static string mainMenu()
        {
            doColor("gy");
            string result;

            Console.WriteLine("M A I N    M E N U");
            Console.WriteLine();
            Console.WriteLine("1. Play New Game");
            Console.WriteLine("2. Load Game");
            Console.WriteLine("3. View the Keys to Play");
            Console.WriteLine("4. View Instructions");
            Console.WriteLine("5. Define your Name");
            Console.WriteLine("6. End Game");
            Console.WriteLine();
            Console.Write("Your Option...");
            result = Console.ReadLine();
            establishColor();
            return result;
        }
        static void mainCharacterPrecise()
        {
            doColor("bw");
            Console.WriteLine("              @##===                                                                                 ");
            Console.WriteLine("          .=+# =*=   ...                               _                                              ");
            Console.WriteLine("         .=+##+ .=+=    %.                          =**=           .=+*=+%                          ");
            Console.WriteLine("         ****###+ . +=+++*+                       =**++=*+        .=**===+**.                        ");
            Console.WriteLine("         ##***####+ . ++++++*+ .                 =**. +%+       =*+===++#*                           ");
            Console.WriteLine("         +##***#####+   +++++++*+=.              %#** .+***+ =*+==++++#+.                            ");
            Console.WriteLine("         +*##***######+   ++++++++**=             ##**+. +++***+++**##.                              ");
            Console.WriteLine("          +###***#######+   +*+++++++**=           ##*** =####**#####+                               ");
            Console.WriteLine("           #*##***########+  ........... ++   .  +*##******#######***##+                             ");
            Console.WriteLine("            +*##***#########******######**#####************###****######%=                           ");
            Console.WriteLine("             +###***###*++++========  =************************########***##+                        ");
            Console.WriteLine("              *###***##*+=         =+*+= =+*****************#######*=   ==+++***=                    ");
            Console.WriteLine("               ==##***+    =++=+++      =+***************##########*****+=     ==+***+= +            ");
            Console.WriteLine("                *###***==++   =+*++==++*****#*********#####################****+==   +*+=            ");
            Console.WriteLine("                **###**#+        +**=****#*********#########**###+      ==++**#####+=                ");
            Console.WriteLine("                 #####+            +**#*********########*+==*+ +=.                                   ");
            Console.WriteLine("                 #%#*             =+*********#######*+== =*###  =*+                                  ");
            Console.WriteLine("                *#*            ++*********######**+=   =+#####*..+++*+                               ");
            Console.WriteLine("               **           ++********#######*+=      +*#######=  +++++*=                            ");
            Console.WriteLine("             =#+.         =+******#######*+=      ===+########## .++++++++*=.                        ");
            Console.WriteLine("            **+ .     =+******########*+==     =+***++##########*. =++++++++**=.                     ");
            Console.WriteLine("          .*****+==+*****############*******++****###############+ .   =+++++++*+ .                  ");
            Console.WriteLine("         .***********###############*#########*************#########*= ... =++++== ..                ");
            Console.WriteLine("       . ********###########*++***             ########************#####*+  .. ======= . +*+         ");
            Console.WriteLine("         #***########*+===                               #######***********#*+= .. *+++==  .         ");
            Console.WriteLine("         +++==#####````                                          ##########*******##%%+              ");
            Console.WriteLine("                                                                          #####%%+                   ");
            Console.WriteLine("                                                                                                     ");
            Console.WriteLine("                                                                                                     ");
            Console.WriteLine("                                                                                                     ");
        }
        static void printHeader()
        {
            doColor("bw");
            Console.WriteLine("    ___         __                ___                          ____   ");
            Console.WriteLine("   /   |  _____/ /__________     /   |  ______________ ___  __/ / /_  ");
            Console.WriteLine("  / /| | / ___/ __/ ___/ __ \\   / /| | / ___/ ___/ __ `/ / / / / __/  ");
            Console.WriteLine(" / ___ |(__  ) /_/ /  / /_/ /  / ___ |(__  |__  ) /_/ / /_/ / / /_    ");
            Console.WriteLine("/_/  |_/____/\\__/_/   \\____/  /_/  |_/____/____/\\__,_/\\__,_/_/\\__/    ");
            Console.WriteLine();
            doColor("bw");
            for (int i = 0; i < 68; i++)
            {
                Console.Write("_");
                Thread.Sleep(10);
            }
            Console.WriteLine();
        }
        static void loadgameData()
        {
            string path = "C:\\Users\\HP\\Desktop\\Programs\\MyGameProject\\gameData.txt";
            StreamReader file = new StreamReader(path);
            score = int.Parse(file.ReadLine());
            if (score != -1)
            {
                health = int.Parse(file.ReadLine());
                name = file.ReadLine();
            }
            file.Close();
            StreamWriter myFile = new StreamWriter(path);
            myFile.WriteLine("-1");
            myFile.Close();
        }
        static void storegameData()
        {
            string path = "C:\\Users\\HP\\Desktop\\Programs\\MyGameProject\\gameData.txt";
            StreamWriter file = new StreamWriter(path);
            file.WriteLine(score);
            file.WriteLine(health);
            file.WriteLine(name);
            file.Close();
        }
        static void doColor(string index)
        {
            // list of colors available in c#
            //Black
            //DarkBlue
            //DarkGreen
            //DarkCyan
            //DarkRed
            //DarkMagenta
            //DarkYellow
            //Gray
            //DarkGray
            //Blue
            //Green
            //Cyan
            //Red
            //Magenta
            //Yellow
            //White

            if (index == "ry")
            {
                Console.ForegroundColor = ConsoleColor.Red;
                Console.BackgroundColor = ConsoleColor.Yellow;
            }
            else if (index == "by")
            {
                Console.ForegroundColor = ConsoleColor.Black;
                Console.BackgroundColor = ConsoleColor.Yellow;
            }
            else if (index == "gy")
            {
                Console.ForegroundColor = ConsoleColor.DarkGreen;
                Console.BackgroundColor = ConsoleColor.Yellow;
            }
            else if (index == "by")
            {
                Console.ForegroundColor = ConsoleColor.Blue;
                Console.BackgroundColor = ConsoleColor.Yellow;
            }
            //Console.ResetColor();                    // resets the color to the default
        }
        static void establishColor()
        {
            Console.ForegroundColor = ConsoleColor.Black;
            Console.BackgroundColor = ConsoleColor.Yellow;
        }

        // Jet Functions
        static void eraseJet()
        {
            for (int x = 0; x < 7; x++)
            {
                for (int y = 0; y < 13; y++)
                {
                    maze[JetX + x, JetY + y] = ' ';
                }
            }
        }
        static void printJet()
        {
            doColor("bw");
            for (int x = 0; x < 7; x++)
            {
                for (int y = 0; y < 13; y++)
                {
                    maze[JetX + x, JetY + y] = newJet[x, y];
                }
            }
        }
        static void moveJetLeft()
        {
            char next = maze[JetX, JetY - 1];
            if (next == ' ')
            {
                eraseJet();
                JetY--;
                printJet();
            }
        }
        static void moveJetRight()
        {
            char next = maze[JetX, JetY + 13];
            if (next == ' ')
            {
                eraseJet();
                JetY++;
                printJet();
            }
        }
        static void moveJetUp()
        {
            char next = maze[JetX - 1, JetY];
            if (next == ' ')
            {
                eraseJet();
                JetX--;
                printJet();
            }
        }
        static void moveJetDown()
        {
            char next = maze[JetX + 7, JetY];
            if (next == ' ')
            {
                eraseJet();
                JetX++;
                printJet();
            }
        }
        static void printJetBullet(int x, int y)
        {
            // called in move jet bullet function
            maze[x, y] = '.';
        }
        static void eraseJetBullet(int x, int y)
        {
            // called in move jet bullet function
            maze[x, y] = ' ';
        }
        static void moveJetBullet(int[] bulletX, int[] bulletY, ref int bulletCount)
        {
            for (int x = 0; x < bulletCount; x++)
            {
                //char next = maze[bulletX[x], bulletY[x] - 1];
                char next = maze[bulletX[x] - 1, bulletY[x]];
                if (next == ' ')
                {
                    eraseJetBullet(bulletX[x], bulletY[x]);
                    bulletX[x] = bulletX[x] - 1;
                    printJetBullet(bulletX[x], bulletY[x]);
                }
                else
                {
                    eraseJetBullet(bulletX[x], bulletY[x]);
                    deleteJetBulletfromArray(ref x, ref bulletCount, bulletX, bulletY);
                }
            }
        }
        static void deleteJetBulletfromArray(ref int index, ref int bulletCount, int[] bulletX, int[] bulletY)
        {
            for (int x = index; x < bulletCount; x++)
            {
                bulletX[x] = bulletX[x + 1];
                bulletY[x] = bulletY[x + 1];
            }
            bulletCount--;
        }
        static void createJetBullet(ref int bulletCount, int[] bulletX, int[] bulletY)
        {
            maze[JetX - 1, JetY + 6] = '.';
            bulletX[bulletCount] = JetX - 1;
            bulletY[bulletCount] = JetY + 6;
            bulletCount++;
        }
        static void createJumboJetBullet(ref int bulletCount, int[] bulletX, int[] bulletY)
        {
            Console.SetCursorPosition(JetX + 1, JetY);
            Console.WriteLine(".");
            bulletX[bulletCount] = JetX + 1;
            bulletY[bulletCount] = JetY;
            bulletCount++;
            Console.SetCursorPosition(JetX + 11, JetY);
            Console.WriteLine(".");
            bulletX[bulletCount] = JetX + 11;
            bulletY[bulletCount] = JetY;
            bulletCount++;
        }

        // Enemy 1 Functions (Upper-Most)
        static void moveEnemy1Bullet(ref int enemyBullet1Count, int[] enemyBullet1X, int[] enemyBullet1Y)
        {
            for (int x = 0; x < enemyBullet1Count; x++)
            {
                char next = maze[enemyBullet1X[x] + 1, enemyBullet1Y[x]];
                if (next == ' ')
                {
                    eraseEnemy1Bullet(enemyBullet1X[x], enemyBullet1Y[x]);
                    enemyBullet1X[x] = enemyBullet1X[x] + 1;
                    printEnemy1Bullet(enemyBullet1X[x], enemyBullet1Y[x]);
                }
                else
                {
                    eraseEnemy1Bullet(enemyBullet1X[x], enemyBullet1Y[x]);
                    deleteEnemyBullet1fromArray(ref x, ref enemyBullet1Count, enemyBullet1X, enemyBullet1Y);
                }
            }
            Thread.Sleep(20);
        }
        static void createEnemy1Bullet(int[] enemyBullet1X, int[] enemyBullet1Y, ref int enemyBullet1Count)
        {
            maze[Enemy1X + 1, Enemy1Y + 2] = 'V';
            enemyBullet1X[enemyBullet1Count] = Enemy1X + 1;
            enemyBullet1Y[enemyBullet1Count] = Enemy1Y + 2;
            enemyBullet1Count++;
        }
        static void printEnemy1Bullet(int x, int y)
        {
            maze[x, y] = 'V';
        }
        static void eraseEnemy1Bullet(int x, int y)
        {
            maze[x, y] = ' ';
        }
        static void deleteEnemyBullet1fromArray(ref int index, ref int enemyBullet1Count, int[] enemyBullet1X, int[] enemyBullet1Y)
        {
            for (int x = index; x < enemyBullet1Count; x++)
            {
                enemyBullet1X[x] = enemyBullet1X[x + 1];
                enemyBullet1Y[x] = enemyBullet1Y[x + 1];
            }
            enemyBullet1Count--;
        }
        static void printEnemy1()
        {
            maze[Enemy1X, Enemy1Y] = character3;
            maze[Enemy1X, Enemy1Y + 1] = character3;
            maze[Enemy1X, Enemy1Y + 2] = character2;
            maze[Enemy1X, Enemy1Y + 3] = character3;
            maze[Enemy1X, Enemy1Y + 4] = character3;
            //{ character3, character3, character2, character3, character3 }

        }
        static void moveEnemy1Horizontal()
        {
            if (Enemy1Direction == "Right")
            {
                char next = maze[Enemy1X, Enemy1Y + 5];
                if (next == ' ' || next == '.')
                {
                    maze[Enemy1X, Enemy1Y] = ' ';
                    maze[Enemy1X, Enemy1Y + 1] = ' ';
                    maze[Enemy1X, Enemy1Y + 2] = ' ';
                    maze[Enemy1X, Enemy1Y + 3] = ' ';
                    maze[Enemy1X, Enemy1Y + 4] = ' ';
                    Enemy1Y++;
                    printEnemy1();
                }
                if (next == '%')
                {
                    Enemy1Direction = "Left";
                }
            }
            if (Enemy1Direction == "Left")
            {
                char next = maze[Enemy1X, Enemy1Y - 1];
                if (next == ' ' || next == '.')
                {
                    maze[Enemy1X, Enemy1Y] = ' ';
                    maze[Enemy1X, Enemy1Y + 1] = ' ';
                    maze[Enemy1X, Enemy1Y + 2] = ' ';
                    maze[Enemy1X, Enemy1Y + 3] = ' ';
                    maze[Enemy1X, Enemy1Y + 4] = ' ';
                    Enemy1Y--;
                    printEnemy1();
                }
                if (next == '%')
                {
                    Enemy1Direction = "Right";
                }
            }
        }

        // Enemy 2 Functions
        static void deleteEnemyBullet2fromArray(ref int index, ref int enemyBullet2Count, int[] enemyBullet2X, int[] enemyBullet2Y)
        {
            for (int x = index; x < enemyBullet2Count; x++)
            {
                enemyBullet2X[x] = enemyBullet2X[x + 1];
                enemyBullet2Y[x] = enemyBullet2Y[x + 1];
            }
            enemyBullet2Count--;
        }
        static void moveEnemy2Bullet(ref int enemyBullet2Count, int[] enemyBullet2X, int[] enemyBullet2Y)
        {
            for (int x = 0; x < enemyBullet2Count; x++)
            {
                char next = maze[enemyBullet2X[x] + 1, enemyBullet2Y[x]];
                if (next == ' ')
                {
                    eraseEnemy2Bullet(enemyBullet2X[x], enemyBullet2Y[x]);
                    enemyBullet2X[x] = enemyBullet2X[x] + 1;
                    printEnemy2Bullet(enemyBullet2X[x], enemyBullet2Y[x]);
                }
                else
                {
                    eraseEnemy2Bullet(enemyBullet2X[x], enemyBullet2Y[x]);
                    deleteEnemyBullet2fromArray(ref x, ref enemyBullet2Count, enemyBullet2X, enemyBullet2Y);
                }
            }
            Thread.Sleep(20);
        }
        static void moveEnemy2Horizontal()
        {
            if (Enemy2Direction == "Right")
            {
                char next = maze[Enemy2X, Enemy2Y + 5];
                if (next == ' ' || next == '.')
                {
                    maze[Enemy2X, Enemy2Y] = ' ';
                    maze[Enemy2X, Enemy2Y + 1] = ' ';
                    maze[Enemy2X, Enemy2Y + 2] = ' ';
                    maze[Enemy2X, Enemy2Y + 3] = ' ';
                    maze[Enemy2X, Enemy2Y + 4] = ' ';
                    Enemy2Y++;
                    printEnemy2();
                }
                if (next == '%')
                {
                    Enemy2Direction = "Left";
                }
            }
            if (Enemy2Direction == "Left")
            {
                char next = maze[Enemy2X, Enemy2Y - 1];
                if (next == ' ' || next == '.')
                {
                    maze[Enemy2X, Enemy2Y] = ' ';
                    maze[Enemy2X, Enemy2Y + 1] = ' ';
                    maze[Enemy2X, Enemy2Y + 2] = ' ';
                    maze[Enemy2X, Enemy2Y + 3] = ' ';
                    maze[Enemy2X, Enemy2Y + 4] = ' ';
                    Enemy2Y--;
                    printEnemy2();
                }
                if (next == '%')
                {
                    Enemy2Direction = "Right";
                }
            }
        }
        static void printEnemy2()
        {
            maze[Enemy2X, Enemy2Y] = '=';
            maze[Enemy2X, Enemy2Y + 1] = '=';
            maze[Enemy2X, Enemy2Y + 2] = character5;
            maze[Enemy2X, Enemy2Y + 3] = '=';
            maze[Enemy2X, Enemy2Y + 4] = '=';
        }
        static void createEnemy2Bullet(ref int enemyBullet2Count, int[] enemyBullet2X, int[] enemyBullet2Y)
        {
            maze[Enemy2X + 1, Enemy2Y + 2] = 'o';
            enemyBullet2X[enemyBullet2Count] = Enemy2X + 1;
            enemyBullet2Y[enemyBullet2Count] = Enemy2Y + 2;
            enemyBullet2Count++;
        }
        static void printEnemy2Bullet(int x, int y)
        {
            maze[x, y] = 'o';
        }
        static void eraseEnemy2Bullet(int x, int y)
        {
            maze[x, y] = ' ';
        }

        // Enemy 3 Functions
        static void moveEnemy3Bullet(ref int enemyBullet3Count, int[] enemyBullet3X, int[] enemyBullet3Y)
        {
            for (int x = 0; x < enemyBullet3Count; x++)
            {
                char next = maze[enemyBullet3X[x]+1, enemyBullet3Y[x]];
                if (next == ' ')
                {
                    eraseEnemy3Bullet(enemyBullet3X[x], enemyBullet3Y[x]);
                    enemyBullet3X[x] = enemyBullet3X[x] + 1;
                    printEnemy3Bullet(enemyBullet3X[x], enemyBullet3Y[x]);
                }
                else
                {
                    eraseEnemy3Bullet(enemyBullet3X[x], enemyBullet3Y[x]);
                    deleteEnemyBullet3fromArray(ref x, ref enemyBullet3Count, enemyBullet3X, enemyBullet3Y);
                }
            }
            Thread.Sleep(20);
        }
        static void createEnemy3Bullet(ref int enemyBullet3Count, int[] enemyBullet3X, int[] enemyBullet3Y)
        {
            maze[Enemy3X + 4, Enemy3Y + 3] = '▼';
            enemyBullet3X[enemyBullet3Count] = Enemy3X + 4;
            enemyBullet3Y[enemyBullet3Count] = Enemy3Y + 3;
            enemyBullet3Count++;
        }
        static void printEnemy3Bullet(int x, int y)
        {
            maze[x, y] = '▼';
        }
        static void eraseEnemy3Bullet(int x, int y)
        {
            maze[x, y] = ' ';
        }
        static void deleteEnemyBullet3fromArray(ref int index, ref int enemyBullet3Count, int[] enemyBullet3X, int[] enemyBullet3Y)
        {
            for (int x = index; x < enemyBullet3Count; x++)
            {
                enemyBullet3X[x] = enemyBullet3X[x + 1];
                enemyBullet3Y[x] = enemyBullet3Y[x + 1];
            }
            enemyBullet3Count--;
        }
        static void printEnemy3()
        {
            doColor("bw");
            for (int x = 0; x < 4; x++)
            {
                for (int y = 0; y < 7; y++)
                {
                    maze[Enemy3X + x, Enemy3Y + y] = Enemy3[x, y];
                }
            }
        }
        static void eraseEnemy3()
        {
            for (int x = 0; x < 4; x++)
            {
                for (int y = 0; y < 7; y++)
                {
                    maze[Enemy3X + x, Enemy3Y + y] = ' ';
                }
            }
        }
        static void moveEnemy3Horizontal()
        {
            if (Enemy3Direction == "Right")
            {
                char next = maze[Enemy3X, Enemy3Y + 7];
                if (next == ' ' || next == '.')
                {
                    eraseEnemy3();
                    Enemy3Y++;
                    printEnemy3();
                }
                if (next == '%')
                {
                    Enemy3Direction = "Left";
                }
            }
            if (Enemy3Direction == "Left")
            {
                char next = maze[Enemy3X, Enemy3Y - 1];
                if (next == ' ' || next == '.')
                {
                    eraseEnemy3();
                    Enemy3Y--;
                    printEnemy3();
                }
                if (next == '%')
                {
                    Enemy3Direction = "Right";
                }
            }
        }
        static void printMaze()
        {
            Console.SetCursorPosition(0, 0);
            for (int i = 0; i < 30; i++)
            {
                for (int j = 0; j < 100; j++)
                {
                    Console.Write(maze[i, j]);
                }
                Console.WriteLine();
            }
        }
        static void printScoreMaze()
        {
            doColor("bw");
            Console.SetCursorPosition(101, 7);
            Console.Write("*******************************");
            Console.SetCursorPosition(101, 8);
            Console.Write("*                             *");
            Console.SetCursorPosition(101, 9);
            Console.Write("*******************************");
            Console.SetCursorPosition(101, 10);
            Console.Write("*                             *");
            Console.SetCursorPosition(101, 11);
            Console.Write("*******************************");
            Console.SetCursorPosition(101, 12);
            Console.Write("*                             *");
            Console.SetCursorPosition(101, 13);
            Console.Write("*******************************");
            Console.SetCursorPosition(101, 14);
            Console.Write("*                             *");
            Console.SetCursorPosition(101, 15);
            Console.Write("*******************************");
        }
        static void printScore()
        {
            doColor("bw");
            Console.SetCursorPosition(103, 8);
            Console.Write("Level: " + level);
            Console.SetCursorPosition(103, 10);
            Console.Write("Player: " + name);
            Console.SetCursorPosition(103, 12);
            Console.Write("Score: " + score);
            Console.SetCursorPosition(103, 14);
            Console.Write("Health: ");
            for (int x = 0; x < health; x++)
            {
                Console.Write(character4);
            }
            Console.Write("     ");
        }
    }
}
