/*
 * main.cpp
 *
 *  Created on: Jun 2, 2014
 *      Author: pavelcheto
 */

#include <iostream>
#include "rle.h"
#include "base64.h"

using namespace std;



int main(void)
{
	rle edno("aaaabbbbcccaabbbb");
	edno.print_decoded();
	cout << edno;
	cout << edno[2] << endl;
	rle dve("cccb");
	cout << edno + dve;
	cout << ++dve;
	dve--;
	cout << edno(7, 5);
	rle tri = edno;
	cout << tri(6, dve);
	//cout << edno.delete_f(6, 8);
	rle chetiri("bbc");
	if(chetiri <= edno)
	{
		cout << "Da." << endl;
	}
	else
	{
		cout << "No." << endl;
	}
	cout << *edno << endl << endl << endl << endl;

	base64 one("abcdefghi");
	one.encode();
	cout << one;
	cout << one[2] << endl;
	base64 two("xyz");
	cout << one + two;
	cout << one(3, 2);
	cout << one(3, two);
	cout << one.delete_f(3, 3);
	base64 three("def");
	three.encode();
	if (one > three)
	{
		cout << "Da." << endl;
	}
	else
	{
		cout << "Ne." << endl;
	}
	return 0;
}


