/*
ID: kashthe1
LANG: C++
TASK: clocks
*/
/*******************************************************************************
 *	Author 		: Kashyap R Puranik ( kashthealien at gmail dot com )
 *	fileName	: clocks.cpp
 *	description : solves the problem in usaco by the name clocks
 *
 *	date 		: 06/09/2009 12:25:56 
 ******************************************************************************/

#include <iostream>
#include <stdlib.h>
#include <stack>
#include <string>
using namespace std;
// A queue consisting of list of moves
// "","0","1","2","3","4","5","6","7","8","9","00","01","02","03","04" ...
// The moves will be added
stack< string > open;
// The possible moves
	
int moves[9][9] = {
  	  // A, B, C, D, E, F, G, H, I
		{1, 1, 0, 1, 1, 0, 0, 0, 0},
		{1, 1, 1, 0, 0, 0, 0, 0, 0},
		{0, 1, 1, 0, 1, 1, 0, 0, 0},
		{1, 0, 0, 1, 0, 0, 1, 0, 0},
		{0, 1, 0, 1, 1, 1, 0, 1, 0},
		{0, 0, 1, 0, 0, 1, 0, 0, 1},
		{0, 0, 0, 1, 0, 0, 1, 1, 1},
		{0, 0, 0, 0, 0, 0, 1, 1, 1},
		{0, 0, 0, 0, 1, 1, 0, 1, 1}
	};

int start[9];				// stating position
FILE* fp2 = fopen("clocks.out", "w");

// This implements breadth first search
int search( int max )
{
	int startCopy[9];						// A copy of the stating state
	string movesList;
	int flag = 1;							// indicates search is complete		
	int i, j;								// for loop counter

	for ( i = 0 ; i < 9 ; i ++ ) startCopy[i] = start[i];
	
	movesList = open.top();					// List of moves
	// See if the current list of moves satisfies
	for ( i = 0 ; i < movesList.size() ; i ++ ) {
		for ( j = 0 ; j < 9 ; j ++ ) {
			startCopy[j] = (startCopy[j] + 3 * moves[movesList[i]-'0'][j] ) % 12;
		}
	}

	// See if the clocks are all 12'o clock
	for ( i = 0 ; i < 9 ; i ++ ){if (startCopy[i] != 0){ flag = 0; break;}}
	// If we have reached the required state
	if (flag) {					// print the list of moves to the output
		for ( i = 0 ; i < movesList.size() ; i ++ ) {
			if( !i ) fprintf(fp2, "%c", movesList[i] + 1);
			else fprintf(fp2, " %c", movesList[i] + 1);
		}
		fprintf(fp2, "\n");
		flag = 0;
		return 1;
	}
	// If the current list of moves was not the required solution
	// generate children moves-lists of the current moves-list and add to stack
	for ( i = movesList[movesList.size()-1] - '0'; i < 9 ; i ++ )
	{
		string newList = open.top();
		newList += char(i+'0');
		if ( newList.size() >= max) break;
		open.push(newList);
		if ( search( max ))
			return 1;
	}	
	open.pop();
	return 0;
}
int main()
{
	// Open input and output files
	FILE *fp =fopen("clocks.in", "r");

	
	int i, j;					// for loop counter
	// Get the input
	for ( i = 0 ; i < 9 ; i ++ ) fscanf(fp, "%d", & start[i]);
	// search for the solution

	for ( i = 1 ; i <= 10 ; i ++ ) {
		string t;
		open.push(t);			// insert an empty list of moves
		if(	search(i))				// Start the breadth first search
			break;
	}
	// Close input and output files
	fclose(fp);

}
