/****************************************************
* knight_tour                                       *
* Assaf Ainhoren                                    *
* Reviewer: Ester Shpoker                           *
* date: 13.08.2022                                  *
****************************************************/
#ifndef __ILRD_OL127_128_KNIGHT_TOUR_H__
#define __ILRD_OL127_128_KNIGHT_TOUR_H__

#include <stddef.h> /*size_t*/
#include "utils.h" /* bool_ty, status_ty */

/* A Implementation of the mathemtical famous knight's Tour puzzle  * 
 * knight's tour is a sequence of moves of a knight on a chessboard *
 * such that the knight visits every square exactly once.           *
 *  If the knight ends on a square that is one knight's             *
 *  move from the beginning square or he past 5 minutes -           *
 *                             THE GAME IS OVER                     * 
 * PARAMS:	const size_t start_position - start cell for  tour.     *
 * 			unsigned char *o_result_tour - buffer of char that will *
 * 							contain cells of result tour indexes.   *
 *							the buffer should be size of 64 chars.  *
 * 	        bool_ty should_use_heuristic - should be heuristic      *
 *                                         (Warnsdorff) or not.     *
 *                                                                  *
 * RETURN:	status_ty - SUCCESS or FAIL.                            *
 * 			If the tour takes more than 5 minutes,                  *
 *          a failure will be returned.                             *
 *                                                                  *
 * COMPLEXITY:	time: O(8^(n^2))	|	space: O(1)                 *
********************************************************************/

status_ty KnightTour(const size_t start_position,
                    unsigned char *o_result_tour,
					bool_ty should_use_heuristic);

#endif /* __ILRD_OL127_128_KNIGHT_TOUR_H__ */