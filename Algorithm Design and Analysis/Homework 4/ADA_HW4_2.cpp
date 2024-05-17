//discuss with b06303131 ¨H®aºÍ
//reference: https://github.com/KeithGalli/Connect4-Python/blob/master/connect4_with_ai.py?fbclid=IwAR1lZbBoWsbVU-GhsWCqjW7YlSukyNk8tsXHT8_CXacWBeyPSHMtWxgkNFw

#include "ADA_HW4_2.h"
#include <bits/stdc++.h>

using namespace std;

#define ROW 6
#define COL 7
#define LEN 4

#define EMPTY 0
#define PLAYER_PIECE 1
#define YP_PIECE 2

#define POS_INF LONG_LONG_MAX
#define NEG_INF LONG_LONG_MIN

vector<vector<int>> board(ROW, vector<int>(COL, 0));

void drop_piece(vector<vector<int>> &board, int row, int col, int piece){
    board[row][col] = piece;
}

bool is_valid(vector<vector<int>> &board, int col){
    if (board[ROW - 1][col] == 0)
        return true;
    else
        return false;
}

vector<int> get_valid_col(vector<vector<int>> &board){
    vector<int> valid_col;
    for (int i = 0; i < COL; i++){
        if (is_valid(board, i))
            valid_col.push_back(i);
    }
    return valid_col;
}

bool winning_move(vector<vector<int>> &board, int piece){
    int i, j;
    for (i = 0; i < ROW; i++){
        for (j = 0; j < (COL - 3); j++){
            if (board[i][j] == piece && board[i][j + 1] == piece && board[i][j + 2] == piece && board[i][j + 3] == piece)
                return true;
        }
    }
    for (i = 0; i < (ROW - 3); i++){
        for (j = 0; j < COL; j++){
            if (board[i][j] == piece && board[i + 1][j] == piece && board[i + 2][j] == piece && board[i + 3][j] == piece)
                return true;
        }
    }
    for (i = 0; i < (ROW - 3); i++){
        for (j = 0; j < (COL - 3); j++){
            if (board[i][j] == piece && board[i + 1][j + 1] == piece && board[i + 2][j + 2] == piece && board[i + 3][j + 3] == piece)
                return true;
        }
    }
    for (i = 3; i < ROW; i++){
        for (j = 0; j < (COL - 3); j++){
            if (board[i][j] == piece && board[i - 1][j + 1] == piece && board[i - 2][j + 2] == piece && board[i - 3][j + 3] == piece)
                return true;
        }
    }
    return false;
}

bool is_terminal_node(vector<vector<int>> &board){
    if (winning_move(board, PLAYER_PIECE) || winning_move(board, YP_PIECE) || (int) (get_valid_col(board).size() == 0))
        return true;
    else
        return false;
}

int get_next_row(vector<vector<int>> &board, int col){
    for (int i = 0; i < ROW; i++){
        if (board[i][col] == 0)
            return i;
    }
}

long long evaluate_window(vector<int> &window, int piece){
    int opp_piece;
    if (piece == PLAYER_PIECE)
        opp_piece = YP_PIECE;
    else
        opp_piece = PLAYER_PIECE;
    int a = count(window.begin(), window.end(), piece);
    int b = count(window.begin(), window.end(), EMPTY);
    int c = count(window.begin(), window.end(), opp_piece);
    if (a == 4)
        return 500;
    else if (a == 3 && b == 1)
        return 100;
    else if (a == 3 && c == 1)
        return 0;
    else if (a == 2 && b == 2)
        return 50;
    else if (a == 2 && b == 1 && c == 1)
        return 0;
    else if (a == 2 && c == 2)
        return -10;
    else if (a == 1 && b == 3)
        return 5;
    else if (a == 1 && b == 2 && c == 1)
        return 0;
    else if (a == 1 && b == 1 && c == 2)
        return -15;
    else if (a == 1 && c == 3)
        return -40;
    else if (b == 4)
        return 0;
    else if (b == 3 && c == 1)
        return -5;
    else if (b == 2 && c == 2)
        return -30;
    else if (b == 1 && c == 3)
        return -50;
    else if (c == 4)
        return -100;
}

long long score_position(vector<vector<int>> &board, int piece){
    long long score = 0;
    int i, j, k;
    for (i = 0; i < ROW; i++){
        if (board[i][COL / 2] == piece)
            score += 3;
    }
    vector<int> window;
    for (i = 0; i < ROW; i++){
        for (j = 0; j < (COL - 3); j++){
            window.clear();
            for (k = 0; k < LEN; k++)
                window.push_back(board[i][j + k]);
            score += evaluate_window(window, piece);
        }
    }
    for (i = 0; i < COL; i++){
        for (j = 0; j < (ROW - 3); j++){
            window.clear();
            for (k = 0; k < LEN; k++)
                window.push_back(board[j + k][i]);
            score += evaluate_window(window, piece);
        }
    }
    for (i = 0; i < (ROW - 3); i++){
        for (j = 0; j < (COL - 3); j++){
            window.clear();
            for (k = 0; k < LEN; k++)
                window.push_back(board[i + k][j + k]);
            score += evaluate_window(window, piece);
        }
    }
    for (i = 0; i < (ROW - 3); i++){
        for (j = 0; j < (COL - 3); j++){
            window.clear();
            for (k = 0; k < LEN; k++)
                window.push_back(board[i + 3 - k][j + k]);
            score += evaluate_window(window, piece);
        }
    }
    return score;
}

vector<vector<int>> copyBoard(vector<vector<int>> &board){
	vector<vector<int>> board_new(ROW, vector<int>(COL));
	for(int i = 0; i < ROW; i++){
		for (int j = 0; j < COL; j++) {
			board_new[i][j] = board[i][j];
		}
	}
	return board_new;
}

int random_choice(vector<int> &array){
	int n = array.size();
	return array[rand() % n];
}

pair<int, long long> minimax(vector<vector<int>> &board, int depth, long long alpha, long long beta, bool maximizingPlayer){
    vector<int> valid_col = get_valid_col(board);
    bool is_terminal = is_terminal_node(board);
    if (depth == 0 || is_terminal){
        if (is_terminal){
            if (winning_move(board, PLAYER_PIECE))
                return make_pair(-1, POS_INF);
            else if (winning_move(board, YP_PIECE))
                return make_pair(-1, NEG_INF);
            else
                return make_pair(-1, 0);
        }
        else
            return make_pair(-1, score_position(board, PLAYER_PIECE));
    }
    int i;
    if (maximizingPlayer){
        long long value = NEG_INF;
        int column = random_choice(valid_col);
        for (i = 0; i < (int) valid_col.size(); i++){
            int col = valid_col[i];
            int row = get_next_row(board, col);
            vector<vector<int>> board_new = copyBoard(board);
            drop_piece(board_new, row, col, PLAYER_PIECE);
            long long new_score = minimax(board_new, depth - 1, alpha, beta, false).second;
            if (new_score > value){
                value = new_score;
                column = col;
            }
            alpha = max(alpha, value);
            if (alpha >= beta)
                break;
        }
        return make_pair(column, value);
    }
    else{
        long long value = POS_INF;
        int column = random_choice(valid_col);
        for (i = 0; i < (int) valid_col.size(); i++){
            int col = valid_col[i];
            int row = get_next_row(board, col);
            vector<vector<int>> board_new = copyBoard(board);
            drop_piece(board_new, row, col, YP_PIECE);
            long long new_score = minimax(board_new, depth - 1, alpha, beta, true).second;
            if (new_score < value){
                value = new_score;
                column = col;
            }
            beta = min(beta, value);
            if (alpha >= beta)
                break;
        }
        return make_pair(column, value);
    }
}

int decide(int yp_move){
    int ans;
    if (yp_move == -1){
        srand(time(NULL));
        board.clear();
		board.resize(ROW);
		for(int i = 0; i < ROW; i++)
            board[i].resize(COL, 0);
        ans = 3;
        int row = get_next_row(board, ans);
        drop_piece(board, row, ans, PLAYER_PIECE);
    }
    else{
        int row = get_next_row(board, yp_move);
        drop_piece(board, row, yp_move, YP_PIECE);
        ans = minimax(board, 6, NEG_INF, POS_INF, true).first;
        if (is_valid(board, ans)){
            row = get_next_row(board, ans);
            drop_piece(board, row, ans, PLAYER_PIECE);
        }
    }
    return ans;
}

