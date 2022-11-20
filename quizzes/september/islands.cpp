#include <iostream> // std::cout
#include <cstring> // memset
#define COLS 5
#define ROWS 5
void IslandDFS(bool (&mat)[ROWS][COLS], long c_row, long c_col,
                long row, long col);
size_t Island(bool (&mat)[ROWS][COLS]);

int main(void)
{
    bool mat[ROWS][COLS] = {{1, 1, 0, 0, 0},
                            {0, 1, 0, 0, 1},
                            {1, 0, 1, 1, 1},
                            {0, 0, 1, 0, 0},
                            {1, 0, 1, 0, 1}};

    std::cout << "Testing Island and num of islands is :" <<
    Island(mat) << std::endl;

    bool mat1[ROWS][COLS] = {{1, 1, 1, 0, 0},
                            {0, 1, 0, 0, 1},
                            {1, 0, 1, 1, 1},
                            {1, 0, 1, 0, 0},
                            {1, 0, 1, 0, 1}};
    std::cout << "Testing Island and num of islands is :" <<
    Island(mat1) << std::endl;
    bool mat2[ROWS][COLS];
    memset(mat2, 0, sizeof(mat2));
    std::cout << "Testing Island and num of islands is :" <<
    Island(mat2) << std::endl;
}

size_t Island(bool (&mat)[ROWS][COLS])
{
    size_t count = 0;
    for (long i = 0; i < ROWS; ++i)
    {
        for (long j = 0; j < COLS; ++j)
        {
            if (mat[i][j] == 1)
            {
                ++count;
                IslandDFS(mat, i, j, ROWS, COLS);
            }
        }
    }
    return count;
}
void IslandDFS(bool (&mat)[ROWS][COLS], long c_row, long c_col,
                long row, long col)
{
    if (0 > c_row || 0 > c_col || row - 1 < c_row || col - 1 < c_col||
       mat[c_row][c_col] != 1 )
    {
        return ; 
    }

    if (mat[c_row][c_col] == 1)
    {
        mat[c_row][c_col] = 0;
        IslandDFS(mat, c_row-1, c_col, row, col);
        IslandDFS(mat, c_row+1, c_col, row, col);        
        IslandDFS(mat, c_row, c_col + 1, row, col);        
        IslandDFS(mat, c_row, c_col - 1, row, col);        
        IslandDFS(mat, c_row + 1, c_col + 1, row, col);        
        IslandDFS(mat, c_row - 1, c_col - 1, row, col);                
        IslandDFS(mat, c_row + 1, c_col - 1, row, col);        
        IslandDFS(mat, c_row - 1, c_col + 1, row, col);        
        
    }

}
