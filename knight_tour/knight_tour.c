/****************************************************
* Knight_Tour                                      *
* Assaf Ainhoren                                    *
****************************************************/
/********************************libraries includes****************************/

#include <assert.h> /* assert */
#include <string.h> /* memmove */
#include <time.h> /*time_t */
#include "knight_tour.h"
#include "bit_array.h"

#ifndef NDEBUG
#include <stdio.h> /* printf */
#endif

#define CHESS_BOARD_SIZE 64
#define MAX_POSSIBILITY 8
#define NUM_OF_ROWS 8
#define NUM_OF_COLS 8
#define OUT_OF_BOUNDS -1
#define FULL 64
#define LAST_MOVE 63
#define X 99
#define FULL_BOARD 0xFFFFFFFF

static const time_t g_five_minutes = 300;
static const time_t time_failure = -1;

typedef enum
{
    TOUR_SUCCESS,
    TOUR_FAIL
}ret_stat_ty;

static void InitKnightTourLuts(unsigned char knight_possibilities[]
                               [MAX_POSSIBILITY],
                               unsigned char *possible_move_lut);
#ifndef NDEBUG
void PrintMatrix(unsigned char matrix[][MAX_POSSIBILITY],
                 size_t rows_max); 
#endif
static int GetNextPosition(int curr_position, int direction);
static int AxisToIndex(int x_axis, int y_axis);
static void IndexToAxis(int index, int *x_axis, int *y_axis);
static int IsPositionOutOfBounds(int x_axis, int y_axis);
static bool_ty IsPositionVisited(bit_array_ty chess_board, size_t position);


static void Swap(unsigned char *x, unsigned char *y);
static void SortLutByNumOfPossibilities(unsigned char knight_possibilities[]
                                        [MAX_POSSIBILITY],
                                        unsigned char *possible_move_lut);
void BubbleSort(unsigned char knight_possibilities[]
                [MAX_POSSIBILITY],
                unsigned char *possible_move_lut,
                unsigned char *arr, 
                size_t size);

static void  KnightTourByAlgorithm(size_t curr_pos,
                           size_t position,
                           bit_array_ty chess_board,
                           unsigned char *o_result_tour,
                           time_t timer,
                           unsigned char knight_possibilities[][MAX_POSSIBILITY],
                           unsigned char *possible_move_lut,
                           bool_ty *found_flag);

static bit_array_ty MarkVisitedPositions(bit_array_ty chess_board,
                                         size_t position);


status_ty KnightTour(const size_t start_position,
                     unsigned char *o_result_tour,
                     bool_ty should_use_heuristic)
{
    unsigned char knight_possibilities[CHESS_BOARD_SIZE]
                                      [MAX_POSSIBILITY] = {{0}, {0}};
    unsigned char possible_moves_lut[CHESS_BOARD_SIZE] = {0};
    bit_array_ty chess_board = 0x0;
    bool_ty tour_stat = FALSE;
    bool_ty heuristic_stat = FALSE;
    time_t start_time = 0;

    assert(FULL > start_position);
    assert(NULL != o_result_tour);

    InitKnightTourLuts(knight_possibilities , possible_moves_lut);
    chess_board = MarkVisitedPositions(chess_board,start_position);

    if (TRUE != should_use_heuristic)
    {
        #ifndef NDEBUG
        PrintMatrix(knight_possibilities, CHESS_BOARD_SIZE);
        #endif
        
        if (time_failure != time(&start_time))
        {
            KnightTourByAlgorithm(0, start_position, chess_board,
                          o_result_tour, start_time,
                          knight_possibilities,
                          possible_moves_lut,
                          &tour_stat);

            return (tour_stat == FALSE ? FAIL : SUCCESS); 
        }
    }
    else
    {
        SortLutByNumOfPossibilities(knight_possibilities, possible_moves_lut);
        #ifndef NDEBUG
        PrintMatrix(knight_possibilities, CHESS_BOARD_SIZE);
        #endif

        if (time_failure != time(&start_time))
        {
           KnightTourByAlgorithm(0, start_position, chess_board,
                           o_result_tour, start_time,
                           knight_possibilities,
                           possible_moves_lut,
                           &heuristic_stat);

            return (heuristic_stat == FALSE ? FAIL : SUCCESS);
        }
    }
    return (FAIL); 
}

static void  KnightTourByAlgorithm(size_t curr_pos,
                                   size_t position,
                                   bit_array_ty chess_board,
                                   unsigned char *o_result_tour,
                                   time_t timer,
                                   unsigned char knight_possibilities[]
                                                      [MAX_POSSIBILITY],
                                   unsigned char *possible_move_lut,
                                   bool_ty *found_flag)
{
    
    int direction = 0;
    int num_of_choices = 0;
    int x_axis = 0;
    int y_axis = 0;
    time_t current_time = time(&current_time);
    size_t next_position = 0;
    IndexToAxis(position, &x_axis, &y_axis);
    
    if (difftime(current_time, timer) > g_five_minutes)
    {
        return ;
    }
    /* last knight move */
    if (FULL == BitArrayCountOn(chess_board))
    {
        *found_flag = TRUE;
        return ;
    }

    num_of_choices = possible_move_lut[position];
    
    for (; (!*found_flag) &&
           (direction < num_of_choices);
           ++direction)
    {
        next_position = knight_possibilities[position][direction];
        if (!IsPositionVisited(chess_board,
                            next_position))
        {
            *o_result_tour = next_position;
            KnightTourByAlgorithm(curr_pos+1,next_position, 
                            BitArraySetOn(chess_board, next_position),
                            o_result_tour + 1, current_time,
                            knight_possibilities,
                            possible_move_lut,
                            found_flag);
        }   
    }
    return ;
}

static void InitKnightTourLuts(unsigned char knight_possibilities[][MAX_POSSIBILITY],
                               unsigned char *possible_move_lut)
{
    size_t current_position = 0;
    size_t direction = 0;
    size_t x_index = 0;
    int next_position = 0;
    
    for (current_position = 0;
         current_position < CHESS_BOARD_SIZE;
         ++current_position)
    {
        for (direction = 0; direction < NUM_OF_COLS; ++direction)
        {
            knight_possibilities[current_position][direction] = 99;    
        }
        
    }
    for (current_position = 0;
         current_position < CHESS_BOARD_SIZE;
         ++current_position)
    {
        for (x_index = 0, direction = 0; direction < NUM_OF_COLS ; ++direction)
        {
            next_position = GetNextPosition(current_position, direction);
            if (OUT_OF_BOUNDS != next_position)
            {
                knight_possibilities[current_position][x_index] = next_position;
                ++x_index;
            }
        }
        possible_move_lut[current_position] = x_index;
    }
}
static int GetNextPosition(int curr_position, int direction)
{
    int move_row_lut[NUM_OF_ROWS] = {2, 1, -1, -2, -2, -1, 1, 2};
	int move_col_lut[NUM_OF_COLS] = {1, 2, 2, 1, -1, -2, -2, -1};

	int new_position_x = 0, new_position_y = 0;
	int curr_position_x = 0, curr_position_y = 0;
	
	assert (0 <= direction || direction <= (NUM_OF_COLS - 1));
	
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
	return ((x_axis > NUM_OF_COLS -1) || (y_axis > NUM_OF_ROWS -1) ||
			x_axis < 0 || y_axis < 0);
}
static int AxisToIndex(int x_axis, int y_axis)
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
static bool_ty IsPositionVisited(bit_array_ty chess_board, size_t position)
{    
    return (BitArrayGetValue(chess_board, position));
}

static bit_array_ty MarkVisitedPositions(bit_array_ty chess_board,
                                         size_t position)
{
    
    return (BitArraySetOn(chess_board, position));
}

static void SortLutByNumOfPossibilities(unsigned char knight_possibilities[]
                                                      [MAX_POSSIBILITY],
                                        unsigned char *possible_move_lut) 
{
    size_t i = 0;

	assert(NULL != possible_move_lut);
    assert(NULL != knight_possibilities);

	for ( ; i <  FULL ; ++i)
	{
		BubbleSort(knight_possibilities,
                   possible_move_lut ,
                   knight_possibilities[i],
                   possible_move_lut[i]);
	}

}

void BubbleSort(unsigned char knight_possibilities[]
                                   [MAX_POSSIBILITY],
                    unsigned char *possible_move_lut,
                                   unsigned char *arr, 
                                         size_t size)
{
	size_t i = 0;
	size_t k = 0;
	int is_sorted = 0;
	
    assert(NULL != possible_move_lut);
    assert(NULL != knight_possibilities);
	assert(NULL != arr);
	
	for ( ;i < size && !is_sorted; ++i)
	{
		is_sorted = 1;
		for ( k = 0 ; k < (size - i - 1); ++k)
		{
            if (possible_move_lut[arr[k]] >
                possible_move_lut[arr[k + 1]])
            {
                Swap(&arr[k] , &arr[k + 1]);
                is_sorted = 0;
            }
        }
	}
}


static void Swap(unsigned char *x, unsigned char *y)
{
	*x = *x + *y;
	*y = *x - *y;
	*x = *x - *y;
}
#ifndef NDEBUG
void PrintMatrix(unsigned char matrix[][MAX_POSSIBILITY], size_t rows_max)
{
    size_t rows = 0;
    size_t cols = 0;

    for (; rows < rows_max; ++rows)
    {
        printf("[%ld]", rows);
        for(cols = 0; cols < NUM_OF_COLS; ++cols)
        {
            if (matrix[rows][cols] == 99)
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
#endif
