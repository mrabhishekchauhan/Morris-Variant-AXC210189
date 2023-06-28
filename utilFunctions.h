#include <bits/stdc++.h>
using namespace std;

string Swap(const string board) {
    string swappedBoard = board;
    unordered_map<char, char> swappedDict = {{'W', 'B'}, {'B', 'W'}};
    for (char& c : swappedBoard) {
        c = swappedDict[c];
    }
    return swappedBoard;
}

vector<string> GenerateHopping(const string board) {
    vector<string> nextHopMoveList;
    for (int i = 0; i < board.size(); ++i) {
        if (board[i] == 'W') {
            for (int j = 0; j < board.size(); ++j) {
                if (board[j] == 'x') {
                    string boardCopy = board;
                    boardCopy[i] = 'x';
                    boardCopy[j] = 'W';
                    if (CloseMill(j, boardCopy)) {
                        GenerateRemove(boardCopy, nextHopMoveList);
                    }
                    else {
                        nextHopMoveList.emplace_back(boardCopy);
                    }
                }
            }
        }
    }
    return nextHopMoveList;
}



vector<string> GenerateRemove(const string board, const vector<string>& addPieceList) {
    vector<string> moves = addPieceList;
    bool isPositionChanged = false;
    for (int i = 0; i < board.size(); ++i) {
        if (board[i] == 'B') {
            if (!CloseMill(i, board)) {
                string boardCopy = board;
                boardCopy[i] = 'x';
                isPositionChanged = true;
                moves.emplace_back(boardCopy);
            }
        }
    }
    if (!isPositionChanged) {
        string boardCopy = board;
        moves.emplace_back(boardCopy);
    }
    return moves;
}

vector<string> GenerateMove(const string board) {
    vector<string> nextMoveList;
    for (int i = 0; i < board.size(); ++i) {
        if (board[i] == 'W') {
            vector<int> neighboursList = Neighbours(i);
            for (int j : neighboursList) {
                if (board[j] == 'x') {
                    string boardCopy = board;
                    boardCopy[i] = 'x';
                    boardCopy[j] = 'W';
                    if (CloseMill(j, boardCopy)) {
                        nextMoveList = GenerateRemove(boardCopy, nextMoveList);
                    }
                    else {
                        nextMoveList.emplace_back(boardCopy);
                    }
                }
            }
        }
    }
    return nextMoveList;
}

vector<string> GenerateMovesMidgameEndgame(const string board) {
    if (count(board.begin(), board.end(), 'W') == 3) {
        return GenerateHopping(board);
    }
    else {
        return GenerateMove(board);
    }
}

vector<string> GenerateAdd(const string board) {
    vector<string> addPieceList;
    for (int i = 0; i < board.size(); ++i) {
        if (board[i] == 'x') {
            string boardCopy = board;
            boardCopy[i] = 'W';
            if (CloseMill(i, boardCopy)) {
                addPieceList = GenerateRemove(boardCopy, addPieceList);
            }
            else {
                addPieceList.emplace_back(boardCopy);
            }
        }
    }
    return addPieceList;
}

vector<string> GenerateMovesOpening(const string board){
    return GenerateAdd(board);
}


//Getting list of moves for Black Player
vector<string> GenerateBlackMoves(const string board) {
    vector<string> blackMoveList, nextBlackMoveList;
    string blackSwappedBoard = Swap(board);
    blackMoveList = GenerateMovesMidgameEndgame(blackSwappedBoard);
    for (const string& move : blackMoveList) {
        string processedMove = Swap(move);
        nextBlackMoveList.emplace_back(processedMove);
    }
    return nextBlackMoveList;
}



//Finding the neighbour of a current position in the board
vector<int> Neighbours(int pos) {
    switch(pos) {
        case 0:
            return {1, 6};
        case 1:
            return {0, 11};
        case 2:
            return {3, 7};
        case 3:
            return {2, 10};
        case 4:
            return {5, 8};
        case 5:
            return {4, 9};
        case 6:
            return {0, 7, 18};
        case 7:
            return {2, 6, 8, 15};
        case 8:
            return {4, 7, 12};
        case 9:
            return {5, 10, 14};
        case 10:
            return {3, 9, 11, 17};
        case 11:
            return {1, 10, 20};
        case 12:
            return {8, 13};
        case 13:
            return {12, 14, 16};
        case 14:
            return {9, 13};
        case 15:
            return {7, 16};
        case 16:
            return {13, 15, 17, 19};
        case 17:
            return {10, 16};
        case 18:
            return {6, 19};
        case 19:
            return {16, 18, 20};
        case 20:
            return {11, 19};
        default:
            cout << "Invalid Neighbour position" << endl;
            return {};
    }
}

//Checking if a position canc lose a mill in the board
bool CloseMill(int loc, const string board) {
    char piece = board[loc];
    if(piece == 'W' || piece == 'B'){
        switch (loc) {
            case 0:
                return ((board[6] == piece && board[18] == piece));
            case 1:
                return (board[11] == piece && board[20] == piece);
            case 2:
                return ((board[7] == piece && board[15] == piece));
            case 3:
                return ((board[10] == piece && board[17] == piece));
            case 4:
                return (board[8] == piece && board[12] == piece);
            case 5:
                return ((board[9] == piece && board[14] == piece));
            case 6:
                return ((board[0] == piece && board[18] == piece) || (board[7] == piece && board[8] == piece));
            case 7:
                return ((board[6] == piece && board[8] == piece) || (board[2] == piece && board[15] == piece));
            case 8:
                return ((board[6] == piece && board[7] == piece) || (board[4] == piece && board[12] == piece));
            case 9:
                return ((board[5] == piece && board[14] == piece) || (board[10] == piece && board[11] == piece));
            case 10:
                return ((board[9] == piece && board[11] == piece) || (board[3] == piece && board[17] == piece));
            case 11:
                return ((board[9] == piece && board[10] == piece) || (board[1] == piece && board[20] == piece));
            case 12:
                return ((board[4] == piece && board[8] == piece) || (board[13] == piece && board[14] == piece));
            case 13:
                return ((board[12] == piece && board[14] == piece) || (board[16] == piece && board[19] == piece));
            case 14:
                return ((board[5] == piece && board[9] == piece) || (board[12] == piece && board[13] == piece));
            case 15:
                return ((board[2] == piece && board[7] == piece) || (board[16] == piece && board[17] == piece));
            case 16:
                return ((board[13] == piece && board[19] == piece) || (board[15] == piece && board[17] == piece));
            case 17:
                return ((board[15] == piece && board[16] == piece) || (board[3] == piece && board[10] == piece));
            case 18:
                return ((board[0] == piece && board[6] == piece) || (board[19] == piece && board[20] == piece));
            case 19:
                return ((board[18] == piece && board[20] == piece) || (board[13] == piece && board[16] == piece));
            case 20:
                return ((board[18] == piece && board[19] == piece) || (board[1] == piece && board[11] == piece));
            default:
                return false;
        }
    }
    return false;    
}
