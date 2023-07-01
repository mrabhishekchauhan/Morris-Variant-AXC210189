#include <bits/stdc++.h>
#include "utilFunctions.h"

using namespace std;

int positionsEvaluated=0;
int minMaxEstimate=0;

int staticEstimation(const string& board) {
    positionsEvaluated++;
    int countW = count(board.begin(), board.end(), 'W');
    int countB = count(board.begin(), board.end(), 'B');
    return countW - countB;
}

string maxMin(const string& inputBoardPos, int depth) {
    if (depth == 0)
        return inputBoardPos;
    depth--;

    int v = INT32_MIN;
    vector<string> wMoves = GenerateAdd(inputBoardPos);
    string maxBoard;
    for (const string& wMove : wMoves) {
        string minBoard = minMax(wMove, depth);
        int staticEst = staticEstimation(minBoard);
        if (v < staticEst) {
            v = staticEst;
            minMaxEstimate = v;
            maxBoard = wMove;
        }
    }
    return maxBoard;
}

string minMax(const string& inputBoardPos, int depth) {
    if (depth == 0)
        return inputBoardPos;
    depth--;

    int v = INT32_MAX;
    vector<string> bMoves = GenerateBlackMoves(inputBoardPos);
    string minBoard;
    for (const string& bMove : bMoves) {
        string maxBoard = maxMin(bMove, depth);
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
        if (argc < 4) {
            cout << "Please run using the specified format: ./MiniMaxOpening board1.txt board2.txt 2" << endl;
            return 0;
        }

        ifstream inFile(argv[1]);
        if (!inFile) {
            cout << "Failed to open input file" << argv[1] << endl;
            return 0;
        }
        string board1((istreambuf_iterator<char>(inFile)), istreambuf_iterator<char>());
        inFile.close();

        int depth = stoi(argv[3]);
        if (board1.size() != 22) {
            cout << "Invalid board1.txt length: " << board1.size() << endl;
            return 0;
        }

        string movePlayed = maxMin(board1, depth);

        cout << "Board Position: " << movePlayed << endl;
        cout << "Positions evaluated by static estimation: " << positionsEvaluated << endl;
        cout << "MINIMAX estimate: " << minMaxEstimate << endl;

        ofstream outFile(argv[2]);
        if (!outFile) {
            cout << "Failed to open output file" << argv[2] << endl;
            return 0;
        }
        outFile << movePlayed;
        outFile.close();
    } catch (const exception& e) {
        cout << "An exception occurred: " << e.what() << endl;
    }
    return 0;
}
