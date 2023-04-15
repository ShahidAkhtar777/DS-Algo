// https://leetcode.com/problems/n-queens/description/

class Solution
{
public:
    bool isPossible(vector<vector<int>> board, int n, int row, int col)
    {

        // row
        for (int j = 0; j < n; j++)
        {
            if (board[row][j] == 1)
                return false;
        }

        // col
        for (int i = 0; i < n; i++)
        {
            if (board[i][col] == 1)
                return false;
        }

        // diagonal
        int i = row, j = col;
        while (i >= 0 && j >= 0)
        {
            if (board[i][j] == 1)
                return false;
            i--;
            j--;
        }

        i = row, j = col;
        while (i >= 0 && j < n)
        {
            if (board[i][j] == 1)
                return false;
            i--;
            j++;
        }

        return true;
    }

    void traverse(vector<vector<string>> &res, vector<vector<int>> &board, int n, int row)
    {
        // Base Case
        if (row == n)
        {
            // print board
            vector<string> ans;
            for (auto i : board)
            {
                string temp = "";
                for (auto j : i)
                {
                    if (j == 1)
                        temp += 'Q';
                    else
                        temp += '.';
                }
                ans.push_back(temp);
            }
            res.push_back(ans);
            return;
        }

        // Rec Case
        for (int col = 0; col < n; col++)
        {
            if (isPossible(board, n, row, col))
            {
                board[row][col] = 1;
                traverse(res, board, n, row + 1);
                board[row][col] = 0;
            }
        }
    }

    vector<vector<string>> solveNQueens(int n)
    {
        vector<vector<string>> res;

        vector<vector<int>> board(n, vector<int>(n, 0));

        traverse(res, board, n, 0);
        return res;
    }
};