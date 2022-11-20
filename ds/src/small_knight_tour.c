/****************************************************
* Knight_Tour                                      *
* Assaf Ainhoren                                    *
* Reviewer: Ester Shpoker                           *
* date: 18.07.2022                                  *
****************************************************/
/********************************libraries includes****************************/
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h> /* memmove */
#include <time.h> /*time_t */
#include "knight_tour.h"
#include "bit_array.h"

#define CHESS_BOARD_SIZE 16
#define MAX_POSSIBILITY 4
#define NUM_OF_ROWS 4
#define NUM_OF_COLS 4
#define OUT_OF_BOUNDS -1

static const time_t g_five_minutes = 30;
static unsigned char possible_moves_lut[CHESS_BOARD_SIZE] = {0};


static size_t GetNextPosition(int curr_position, int direction);
static size_t AxisToIndex(int x_axis, int y_axis);
static void IndexToAxis(int index, int *x_axis, int *y_axis);
static int IsPositionOutOfBounds(int x_axis, int y_axis);
int PositionCompare(const void *data1, const void *data2);
void PrintMatrix(unsigned char matrix[][NUM_OF_COLS], size_t rows_max); 
static bool_ty IsPositionVisited(bit_array_ty chess_board, size_t position);

static void InitKnightTourLuts(unsigned char knight_possibilities[][MAX_POSSIBILITY],
                               unsigned char *possible_move_lut);

static status_ty RecursiveTour(size_t position,
                         bit_array_ty chess_board,
                         unsigned char *o_result_tour,
                         time_t timer,
                         unsigned char knight_possibilities[][MAX_POSSIBILITY],
                         unsigned char *possible_move_lut);
static bit_array_ty MarkVisitedPositions(bit_array_ty chess_board,
                                         size_t position);

status_ty KnightTour(const size_t start_position,
                     unsigned char *o_result_tour,
                     bool_ty should_use_heuristic)
{
    unsigned char knight_possibilities[CHESS_BOARD_SIZE][MAX_POSSIBILITY] = {{0}, {0}};
    bit_array_ty chess_board = 0x0;
    time_t start_time = 0;
    bool_ty status = SUCCESS;
    InitKnightTourLuts(knight_possibilities, possible_moves_lut);
    PrintMatrix(knight_possibilities, CHESS_BOARD_SIZE);
    if (-1 != time(&start_time))
    {
        return(RecursiveTour(start_position, chess_board,
                             o_result_tour, start_time,
                             knight_possibilities,
                             possible_moves_lut));
    }
    return (FAIL);
    /* *o_result_tour = chess_board;
        printf("%d\n", knight_possibilities[0][0]);
        printf("%d\n", knight_possibilities[0][1]);
        printf("%d\n", knight_possibilities[1][0]);
        printf("%d\n", knight_possibilities[1][1]);
        printf("%d\n", knight_possibilities[1][2]);
        printf("%d\n", possible_moves_lut[9]);*/
    
    
}
static status_ty RecursiveTour(size_t position,
                               bit_array_ty chess_board,
                               unsigned char *o_result_tour,
                               time_t timer,
                               unsigned char knight_possibilities[][MAX_POSSIBILITY],
                               unsigned char *possible_move_lut)
{
    int direction = 0;
    int x_axis = 0;
    int y_axis = 0;
    time_t current_time = time(&current_time);
    IndexToAxis(position, &x_axis, &y_axis);

    if (difftime(current_time, timer) >= g_five_minutes)
    {
        return (FAIL);
    } 
    if (64 == BitArrayCountOn(chess_board))
    {
        return (SUCCESS);
    }

    if (IsPositionOutOfBounds(x_axis, y_axis) ||
        IsPositionVisited(chess_board, position))
    {
        return (FAIL);    
    }
    chess_board = MarkVisitedPositions(chess_board, position);
    for (direction = 0; direction < MAX_POSSIBILITY; ++direction)
    {
        if (!RecursiveTour(GetNextPosition(position, direction), 
                                chess_board, ++o_result_tour, current_time,
                                knight_possibilities,
                                possible_move_lut))
        {
            *o_result_tour = position;
            return (SUCCESS);   
        }
    }
    return (FAIL);
}
static void InitKnightTourLuts(unsigned char knight_possibilities[][MAX_POSSIBILITY],
                               unsigned char *possible_move_lut)
{
    size_t current_position = 0;
    size_t direction = 0;
    int next_position = 0;

    for (current_position = 0;
         current_position < CHESS_BOARD_SIZE;
         ++current_position)
    {
        for (direction = 0; direction < MAX_POSSIBILITY; ++direction)
        {
            next_position = GetNextPosition(current_position, direction);

            if (OUT_OF_BOUNDS != next_position)
            {
                knight_possibilities[current_position][direction] = next_position;
                ++possible_move_lut[current_position];
            }
            else
            {
                knight_possibilities[current_position][direction] = 99;
            }
        }
    }
    /*TODO: to quick sort aftert that */
   /* for ( current_position = 0; current_position < MAX_POSSIBILITY;
        ++current_position )
    {
        qsort(knight_possibilities + current_position, MAX_POSSIBILITY,
              sizeof(char), PositionCompare);
    }*/
}
static size_t GetNextPosition(int curr_position, int direction)
{
	/* LUTs which indicate on the change that made by each direction	*/
	static const int move_row_lut[8] = {1, 2, 2, 1, -1, -2, -2, -1};
	static const int move_col_lut[8] = {2, 1, -1, -2, -2, -1, 1, 2};
	
	int new_position_x = 0, new_position_y = 0;
	int curr_position_x = 0, curr_position_y = 0;
	
	assert (0 <= direction && direction <= 7);
	
	IndexToAxis(curr_position, &curr_position_x, &curr_position_y);
	
	/*	update position as the rule of the direction says */
	new_position_x = curr_position_x + move_col_lut[direction];
	new_position_y = curr_position_y + move_row_lut[direction];
	
	/*	check if the new position is out of bounds and if not, return it */
	return (IsPositionOutOfBounds(new_position_x, new_position_y) ?
            (OUT_OF_BOUNDS) :
			AxisToIndex(new_position_x, new_position_y));
}

static int IsPositionOutOfBounds(int x_axis, int y_axis)
{							
	return (x_axis >= NUM_OF_COLS || y_axis >= NUM_OF_ROWS ||
			x_axis < 0 || y_axis < 0);
}
static size_t AxisToIndex(int x_axis, int y_axis)
{
	assert(x_axis >= 0); 
    assert(y_axis >= 0);
	assert(y_axis < NUM_OF_ROWS);
    assert(x_axis < NUM_OF_COLS);
	
	return ((y_axis * NUM_OF_ROWS) + x_axis);
}

static void IndexToAxis(int index, int *x_axis, int *y_axis)
{
	assert(0 != x_axis);
    assert(0 != y_axis);
	
	*x_axis = index % NUM_OF_COLS;
	*y_axis = index / NUM_OF_ROWS;
}
int PositionCompare(const void *data1, const void *data2)
{
    return (possible_moves_lut[*(unsigned char *)data2] - 
            possible_moves_lut[*(unsigned char *)data1]);
}

static bool_ty IsPositionVisited(bit_array_ty chess_board, size_t position)
{    
    return (BitArrayGetValue(chess_board, position));
}

static bit_array_ty MarkVisitedPositions(bit_array_ty chess_board,
                                         size_t position)
{
    
    return (BitArraySetBit(chess_board, position, 1));
}
void PrintMatrix(unsigned char matrix[][NUM_OF_COLS], size_t rows_max)
{
    size_t rows = 0;
    size_t cols = 0;

    for (; rows < rows_max; ++rows)
    {

        for(cols = 0; cols < NUM_OF_COLS; ++cols)
        {
            if (matrix[rows][cols] == 'X')
            {
                printf("X  ");
            }
            else
            {
                printf("%d  ", matrix[rows][cols]);

            }
            printf("| ");
        }
        printf("\n");
    }
    printf("\n\n");
}

