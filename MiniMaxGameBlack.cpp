#include <bits/stdc++.h>
#include "utilFunctions.h"

using namespace std;

string MaxMin(const string& brdPos, int depth);
string MinMax(const string& brdPos, int depth);

int positionsEvaluated = 0;
int miniMaxEstimate = 0;

int StaticEstimation(const string& brd)
{
    positionsEvaluated++;
    int whites = count(brd.begin(), brd.end(), 'W');
    int blacks = count(brd.begin(), brd.end(), 'B');
    int numBlackMoves = GenerateBlackMoves(brd).size();

    if (blacks <= 2)
        return 10000;
    else if (whites <= 2)
        return -10000;
    else if (numBlackMoves == 0)
        return 10000;
    else
        return (1000 * (whites - blacks)) - numBlackMoves;
}

string MaxMin(const string& brdPos, int depth)
{
    if (depth == 0)
        return brdPos;
    depth--;

    string mxBrd;
    int v = numeric_limits<int>::min();
    vector<string> wMoves = GenerateMovesMidgameEndgame(brdPos);

    for (const string& move : wMoves)
    {
        string mnBrd = MinMax(move, depth);
        int staticEs = StaticEstimation(mnBrd);

        if (v < staticEs)
        {
            v = staticEs;
            mxBrd = move;
            miniMaxEstimate = v;
        }
    }

    return mxBrd;
}

string MinMax(const string& brdPos, int depth)
{
    if (depth == 0)
        return brdPos;
    depth--;

    string mnBrd;
    int v = numeric_limits<int>::max();
    vector<string> bMoves = GenerateBlackMoves(brdPos);

    for (const string& move : bMoves)
    {
        string mxBrd = MaxMin(move, depth);
        int staticEs = StaticEstimation(mxBrd);

        if (v > staticEs)
        {
            v = staticEs;
            mnBrd = move;
        }
    }

    return mnBrd;
}

int main(int argc, char* argv[])
{
    if (argc != 4)
    {
        cout << "Please specify in format: ./MiniMaxGameBlack board1.txt board2.txt 2" << endl;
        return 0;
    }

    string boardFile = argv[1];
    string outputFile = argv[2];
    int depth = stoi(argv[3]);

    ifstream inFile(boardFile);
    if (!inFile)
    {
        cout << "Failed to open " << boardFile << endl;
        return 0;
    }

    string brd1;
    getline(inFile, brd1);
    inFile.close();

    if (brd1.size() != 21)
    {
        cout << "Invalid board1.txt length: " << brd1.size() << endl;
        return 0;
    }

    string swappedBoard=Swap(brd1);
    cout<<"------------------Input Board------------------"<<endl;
    cout<<"\n\n";
    drawBoard(swappedBoard);
    string move=MaxMin(swappedBoard, depth);
    string blackMove = Swap(move);
    StaticEstimation(blackMove);
    
    ofstream outFile(outputFile);
    if (!outFile)
    {
        cout << "Failed to open " << outputFile << endl;
        return 0;
    }

    cout<<"\n------------------Output Board------------------"<<endl;
    cout<<"\n\n";
    drawBoard(blackMove);

    cout << "Board Position: " << blackMove << endl;
    cout << "Positions evaluated by static estimation: " << positionsEvaluated << endl;
    cout << "MINIMAX estimate: " << miniMaxEstimate << endl;
    outFile << blackMove;
    outFile.close();

    return 0;
}
