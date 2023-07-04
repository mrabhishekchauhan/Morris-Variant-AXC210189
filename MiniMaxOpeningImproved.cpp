#include <bits/stdc++.h>
#include "utilFunctions.h"

using namespace std;

string MaxMin(const string& brdPos, int depth);
string MinMax(const string& brdPos, int depth);

int positionsEvaluated=0;
int miniMaxEstimate=0;

//Static Estimation function for MiniMax Opening
int staticEstimation(const string& board) {
    positionsEvaluated++;
    int countW = count(board.begin(), board.end(), 'W');
    int countB = count(board.begin(), board.end(), 'B');
    int numMills = CountMills(board);
    return countW - countB + numMills;
}

//MaxMin function for estimating miniMax value
string MaxMin(const string& inputBoardPos, int depth) {
    if (depth == 0)
        return inputBoardPos;
    depth--;

    int v = INT32_MIN;
    vector<string> wMoves = GenerateAdd(inputBoardPos);
    string maxBoard;
    for (const string& wMove : wMoves) {
        string minBoard = MinMax(wMove, depth);
        int staticEst = staticEstimation(minBoard);
        if (v < staticEst) {
            v = staticEst;
            miniMaxEstimate = v;
            maxBoard = wMove;
        }
    }
    return maxBoard;
}

//MinMax function for estimating miniMax value
string MinMax(const string& inputBoardPos, int depth) {
    if (depth == 0)
        return inputBoardPos;
    depth--;

    int v = INT32_MAX;
    vector<string> bMoves = GenerateBlackMoves(inputBoardPos);
    string minBoard;
    for (const string& bMove : bMoves) {
        string maxBoard = MaxMin(bMove, depth);
        int staticEst = staticEstimation(maxBoard);
        if (v > staticEst) {
            v = staticEst;
            minBoard = bMove;
        }
    }
    return minBoard;
}

int main(int argc, char* argv[]) {
    try {
        //Checking for correct number of arguments
        if (argc < 4) {
            cout << "Please run using the specified format: ./MiniMaxOpening board1.txt board2.txt 2" << endl;
            return 0;
        }

        //Reading input from command line and opening input file
        ifstream inFile(argv[1]);
        if (!inFile) {
            cout << "Failed to open input file" << argv[1] << endl;
            return 0;
        }
        string board1((istreambuf_iterator<char>(inFile)), istreambuf_iterator<char>());
        inFile.close();

        int depth = stoi(argv[3]);
        if (board1.size() != 21) {
            cout << "Invalid board1.txt length: " << board1.size() << endl;
            return 0;
        }

        //Printing input board and calling MaxMin function
        cout<<"------------------Input Board------------------"<<endl;
        cout<<"\n\n";
        DrawBoard(board1);
        string movePlayed = MaxMin(board1, depth);

        //Writing output to file and printing output board with static estimation
        ofstream outFile(argv[2]);
        if (!outFile) {
            cout << "Failed to open output file" << argv[2] << endl;
            return 0;
        }

        cout<<"\n------------------Output Board------------------"<<endl;
        cout<<"\n\n";
        DrawBoard(movePlayed);

        cout << "\nOutput Board Position: " << movePlayed << endl;
        cout << "Positions evaluated by static estimation: " << positionsEvaluated << endl;
        cout << "MINIMAX estimate: " << miniMaxEstimate << endl;
        outFile << movePlayed;
        outFile.close();
    } catch (const exception& e) {
        cout << "An exception occurred: " << e.what() << endl;
    }
    return 0;
}
