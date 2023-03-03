//
// Created by Daron Adams on 2/21/23.
//
#include "defs.h"

#ifndef CHESS_ENGINE_BITOPS_H
#define CHESS_ENGINE_BITOPS_H

/*
 * Takes in two bitboards and returns True if the 1st is a subset of the 2nd
 * This operation can help by combining piece attacks with opponent pieces,
 * allowing you to see which pieces are currently under attack
 */
bool isSubsetOfB(U64 a, U64 b) {return (a & b) == a;}

/*
 * Takes two bitboards and returns a superset of them together
 * A superset would consist of "adding" the two sets together
 * This would be useful to get all occupied squares by getting a super set
 * of all white pieces and black pieces
 */
U64 createSuperSet(U64 a, U64 b) {return (a | b);}
#endif //CHESS_ENGINE_BITOPS_H
