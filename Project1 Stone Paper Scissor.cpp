// Project1 Stone Paper Scissor

#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

enum enGameChoice { Stone = 1, Paper = 2, Scissors = 3 };

enum enWinner { Player1 = 1, Computer = 2, Draw = 3 };

struct stRoundInfo
{
    short RoundNumber = 0;
    enGameChoice PlayerChoice;
    enGameChoice ComputerChoice;
    enWinner Winner;
    string WinnerName;
};

struct stGameResults
{
    short GameRounds = 0;
    short Player1WinTimes = 0;
    short Computer2WinTimes = 0;
    short DrawTimes = 0;
    enWinner GameWinner;
    string WinnerName = "";
};

enGameChoice ReadPlayer1Choice()
{
    short Choice = 1;

    do
    {
        cout << "Your Choice [1]:Stone , [2]:Paper, [3]:Scissors ?";
        cin >> Choice;

    } while (Choice < 1 || Choice>3);

    return (enGameChoice)Choice;
}

int RandomNumber(int From, int To)
{
    int RandNum = rand() % (To - From + 1) + From;
    return RandNum;
}

enGameChoice GetComputer2Choice()
{
    return (enGameChoice)RandomNumber(1, 3);
}

enWinner WhoWonTheRound(stRoundInfo RoundInfo)
{
    if (RoundInfo.PlayerChoice == RoundInfo.ComputerChoice)
    {

        return enWinner::Draw;
    }
    switch (RoundInfo.PlayerChoice)
    {
    case enGameChoice::Stone:

        if (RoundInfo.ComputerChoice == enGameChoice::Paper)
        {
            return enWinner::Computer;
        }
        break;

    case enGameChoice::Paper:
        if (RoundInfo.ComputerChoice == enGameChoice::Scissors)
        {
            return enWinner::Computer;
        }
        break;

    case enGameChoice::Scissors:
        if (RoundInfo.ComputerChoice == enGameChoice::Stone)
        {
            return enWinner::Computer;
        }
        break;
    }
    return enWinner::Player1;
}

string WennerName(enWinner Winner)
{
    string ArrWinnerName[3] = { "Player1","Computer","No Winner" };
    return ArrWinnerName[Winner - 1];
}

string ChoiceName(enGameChoice Choice)
    { 
        string ArrChoiceName[3] = { "Stone","Paper","Scissors" };

        return ArrChoiceName[Choice - 1];
    }

void PrintRoundResult(stRoundInfo RoundInfo)
{
    cout << "\n-----------Round[" << RoundInfo.RoundNumber << "]-----------\n\n";
    cout << "Player Choice :" << ChoiceName(RoundInfo.PlayerChoice) << endl;
    cout << "Computer Choice :" << ChoiceName(RoundInfo.ComputerChoice) << endl;
    cout << "Round Winner :[" << RoundInfo.WinnerName << "]\n";
    cout << "---------------------------------\n" << endl;
}

enWinner WhoWonTheGame(short Player1WonTimes,short Computer2WonTimes)
    {
        if (Player1WonTimes > Computer2WonTimes)
            return enWinner::Player1;
        else if (Computer2WonTimes > Player1WonTimes)
            return enWinner::Computer;
        else
            return enWinner::Draw;
    }

stGameResults FillGameResult(int GameRounds, short Player1WinTimes, short Computer2WinTimes, short DrawTimes)
{
    stGameResults GameResult;
    GameResult.GameRounds = GameRounds;
    GameResult.Player1WinTimes = Player1WinTimes;
    GameResult.Computer2WinTimes = Computer2WinTimes;
    GameResult.DrawTimes = DrawTimes;
    GameResult.GameWinner = WhoWonTheGame(Player1WinTimes, Computer2WinTimes);
    GameResult.WinnerName = WennerName(GameResult.GameWinner);

    return GameResult;
}

stGameResults PlayGame(short HowManyRounds)
{
    stRoundInfo RoundInfo;
    short Player1WinTimes = 0, Computer2WinTimes = 0, DrawTimes = 0;
    for (short GameRound = 1;GameRound <= HowManyRounds;GameRound++)
    {
        cout << "\nRound [" << GameRound << "] Begins\n";
        RoundInfo.RoundNumber = GameRound;
        RoundInfo.PlayerChoice = ReadPlayer1Choice();
        RoundInfo.ComputerChoice = GetComputer2Choice();
        RoundInfo.Winner = WhoWonTheRound(RoundInfo);
        RoundInfo.WinnerName = WennerName(RoundInfo.Winner);

        if (RoundInfo.Winner == enWinner::Player1)
            Player1WinTimes++;
        else if (RoundInfo.Winner == enWinner::Computer)
            Computer2WinTimes++;
        else
            DrawTimes++;

        PrintRoundResult(RoundInfo);
    }
    return FillGameResult(HowManyRounds, Player1WinTimes, Computer2WinTimes, DrawTimes);
}

short ReadHowManyRounds()
{
    short GameRounds = 1;

    do
    {
        cout << "How Many Rounds ?\n";
        cin >> GameRounds;

    } while (GameRounds < 1 || GameRounds>10);

    return GameRounds;
}

void SetWinnerScreenColor(enWinner Winner)
{
    switch (Winner)
    {
    case enWinner::Player1:
        system("color 2F");//Turn Screen To Green
        break;
    case enWinner::Computer:
        system("color 4F");//Turn Screen To Red
        break;
    default:
        system("color 6F");//Turn Screen To Yellow
    }
}

string Tabs(short NumberOfTabs)
{
    string t = "";
    for (int i = 1;i < NumberOfTabs;i++)
    {
        t = t + "\t";
    }
    return t;
}

void ShowGameOverScreen()
{
    cout << Tabs(2) << "-----------------------------------------------------\n\n";
    cout << Tabs(2) << "                 +++ G a m e O v e r +++\n";
    cout << Tabs(2) << "-----------------------------------------------------\n\n";
}

void ShowFinalGameResult(stGameResults GameResults)
{
    cout << Tabs(2) << "__________________[Game Results]_________________\n\n";
    cout << Tabs(2) << "Game Rounds              :" << GameResults.GameRounds << endl;
    cout << Tabs(2) << "Player1 Won Times        :" << GameResults.Player1WinTimes << endl;
    cout << Tabs(2) << "Computer2 Won Times       :" << GameResults.Computer2WinTimes << endl;
    cout << Tabs(2) << "Draw Times               :" << GameResults.DrawTimes << endl;
    cout << Tabs(2) << "Final Winner             :" << GameResults.WinnerName << endl;
    cout << Tabs(2) << "______________________________________________________";

    SetWinnerScreenColor(GameResults.GameWinner);
}

void ReSetScreen()
{ 
    system("cls");
}

void StartGame()
{
    char PlayAgain = 'Y';

    do
    {
        ReSetScreen();
        stGameResults GameResult = PlayGame (ReadHowManyRounds());
        ShowGameOverScreen();
        ShowFinalGameResult(GameResult);

        cout << "Do You Want To Play Again?";
        cin >> PlayAgain;

    } while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main()
{
    srand((unsigned)time(NULL));

    StartGame();

    return 0;
}

