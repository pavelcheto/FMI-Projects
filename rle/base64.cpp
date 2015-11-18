/*
 * base64.cpp
 *
 *  Created on: Jun 5, 2014
 *      Author: pavelcheto
 */
#include "base64.h"
#include <iostream>
#include <cstring>

using namespace std;

const char base64::table[65] = {"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"};

base64::base64()
{
	isEncoded = false;
	size = 1;
	rsize = 0;
	niz = new char[size];
}

base64::base64(char * input)
{
	isEncoded = false;
	size = 1;
	rsize = 0;
	niz = new char[size];
	for (unsigned int i = 0; i < strlen(input); ++i)
	{
		addLetter(input[i]);
	}
}

void base64::addLetter(char input)
{
	if(rsize == size)
	{
		char* temp;
		temp = new char[size];

		for(int i = 0; i < rsize; i++)
		{
			temp[i]=niz[i];
		}
		delete[] niz;
		size += 10;
		niz = new char[size];
		niz[size-1]='\0';

		for(int i = 0; i < rsize; i++)
		{
			niz[i] = temp[i];
		}

		delete[] temp;
	}
	niz[rsize] = input;
	rsize++;
}

base64::base64(const base64 &input)
{
	size = input.size;
	rsize = input.rsize;
	isEncoded = input.isEncoded;
	niz = new char[size];
	for (int i = 0; i < rsize; ++i)
	{
		niz[i] = input.niz[i];
	}
}

base64 &base64::operator=(const base64 &input)
{
	if (this != &input)
	{
		size = input.size;
		rsize = input.rsize;
		isEncoded = input.isEncoded;
		delete[] niz;
		niz = new char[size];
		for (int i = 0; i < rsize; ++i)
		{
			niz[i] = input.niz[i];
		}
	}
	return *this;
}

base64::~base64()
{
	delete[] niz;
}

void base64::encode()
{
	if (isEncoded)
	{
		return;
	}
	char * temp;
	temp = new char[size];
	int temp_size = rsize;
	for (int i = 0; i < size; ++i)
	{
		temp[i] = niz[i];
	}
	delete[] niz;
	rsize = 0;
	size = 1;
	niz = new char[size];
	int i = 0;
	char encoded[4];
	for( ; i < temp_size - temp_size % 3; i += 3)
	{
		encoded[0] = table[(temp[i] >> 2)];
		encoded[1] = table[((temp[i] & 3) << 4) + (temp[i + 1] >> 4)];
		encoded[2] = table[((temp[i + 1] & 15) << 2) + (temp[i + 2] >> 6)];
		encoded[3] = table[(temp[i + 2] & 63)];
		addLetter(encoded[0]);
		addLetter(encoded[1]);
		addLetter(encoded[2]);
		addLetter(encoded[3]);
	}
	if(temp_size % 3 == 1)
	{
		encoded[0]=table[(temp[i] >> 2)];
		encoded[1] = table[((temp[i] & 3) << 4)];
		encoded[2] = '=';
		encoded[3] = '=';
		addLetter(encoded[0]);
		addLetter(encoded[1]);
		addLetter(encoded[2]);
		addLetter(encoded[3]);
	}

	if(temp_size % 3 == 2)
	{
		encoded[0] = table[(temp[i] >> 2)];
		encoded[1] = table[((temp[i] & 3) << 4) + (temp[i + 1] >> 4)];
		encoded[2] = table[((temp[i + 1] & 15) << 2)];
		encoded[3] = '=';
		addLetter(encoded[0]);
		addLetter(encoded[1]);
		addLetter(encoded[2]);
		addLetter(encoded[3]);
	}

	delete[] temp;
	isEncoded = true;

}

int base64::findPos(char a)
{
	for(int i = 0; i < 64; i++)
	{
		if(a == table[i])
		{
			return i;
		}
	}
	return 0;

}

void base64::decode()
{
	if(!isEncoded)
	{
		return;
	}

	base64 temp;
	char encoded[3];
	int i = 0;
	int temp_size = rsize;
	if(niz[rsize - 1] == '=')
	{
		temp_size--;
	}
	if(niz[rsize - 2] == '=')
	{
		temp_size--;
	}
	for( ; i < temp_size - temp_size % 4; i += 4)
	{
		encoded[0] = (findPos(niz[i]) << 2) + (findPos(niz[i +1 ]) >> 4);
		encoded[1] = (((findPos(niz[i + 1]) & 15) << 4) + (findPos(niz[i + 2]) >> 2));
		encoded[2] = (((findPos(niz[i + 2]) & 3) << 6) + findPos(niz[i + 3]));
		temp.addLetter(encoded[0]);
		temp.addLetter(encoded[1]);
		temp.addLetter(encoded[2]);
		}
		if(temp_size % 4 == 2){
		encoded[0] = (findPos(niz[i]) << 2) + (findPos(niz[i + 1]) >> 4);
		temp.addLetter(encoded[0]);
		}
		if(temp_size % 4 == 3){
		encoded[0] = (findPos(niz[i]) << 2) + (findPos(niz[i + 1]) >> 4);
		encoded[1]=(((findPos(niz[i + 1]) & 15) << 4) + (findPos(niz[i + 2]) >> 2));
		temp.addLetter(encoded[0]);
		temp.addLetter(encoded[1]);
		}

		*this = temp;
		isEncoded = false;

}

char base64::operator[](int input)
{
	input--;
	bool wasEncoded = isEncoded;
	if(isEncoded)
	{
		decode();
	}
	char c = niz[input];
	if(wasEncoded)
	{
		encode();
	}
	return c;
}

ostream& operator<< (ostream& out, const base64& other)
{
	base64 print = other;
	print.decode();
	for(int i = 0; i < print.rsize; ++i)
	{
		out << print.niz[i];
	}
	out << endl;

	return out;
}

const base64 base64::operator+(base64 other)
{
	base64 ans = *this;
	bool thisEncoded = ans.isEncoded;
	if(ans.isEncoded)
	{
		ans.decode();
	}
	other.decode();
	for(int i = 0; i < other.rsize; i++)
	{
		ans.addLetter(other.niz[i]);
	}
	if(thisEncoded)
	{
		ans.encode();
	}
	return ans;
}

base64 base64::operator+=(base64 other)
{
	*this = *this + other;
	return *this;
}

base64 base64::operator()(int start, int length)
{
	base64 ans, toz;
	toz = *this;
	toz.decode();
	if(start > toz.rsize - 1 || start < 0)
	{
		cout << "Incorrect start. Setting start to 0." << endl;
		start = 0;
	}
	if (length > toz.rsize - start)
	{
		cout << "Incorrect length. Setting length to 1." << endl;
		length = 1;
	}
	for(int i = start; i < start + length; i++)
	{
		ans.addLetter(toz.niz[i]);
	}
	ans.encode();
	return ans;
}

base64 base64::operator()(int start, base64 other)
{
	bool wasEncoded = isEncoded;
	decode();
	other.decode();
	base64 temp1 = (*this)(0, start), temp2 = (*this)(start, rsize - start);
	temp1 += other;
	temp1 += temp2;
	*this = temp1;
	if(wasEncoded)
	{
		encode();
	}
	return *this;
}

base64 base64::delete_f(int start, int length)
{
	bool wasEncoded = isEncoded;
	decode();
	base64 temp1 = (*this)(0, start), temp2 = (*this)(start + length, rsize - length - start);
	temp1 += temp2;
	*this = temp1;
	if(wasEncoded)
	{
		encode();
	}
	return *this;
}

base64 base64::cmp(int start, int length)
{
	base64 toz, ans;
	toz = *this;

	if(start > toz.rsize - 1 || start < 0)
	{
		cout << "Incorrect start. Setting start to 0." << endl;
		start = 0;
	}
	if (length > toz.rsize - start)
	{
		cout << "Incorrect length. Setting length to 1." << endl;
		length = 1;
	}
	for(int i = start; i < start + length; i++)
	{
		ans.addLetter(toz.niz[i]);
	}
	return ans;
}

bool base64::operator<(base64 other)
{
	if(!isEncoded || !other.isEncoded)
	{
		cout << "Comparing non-encoded strings." << endl;
		return false;
	}
	if(rsize >= other.rsize)
	{
		return false;
	}
	base64 cmp;
	char *temp1, *temp2;
	temp1 = new char[rsize + 1];
	temp2 = new char[rsize + 1];
	strcpy(temp1, niz);
	temp1[rsize] = '\0';
	temp2[rsize] = '\0';
	for (int i = 0; i < other.rsize - rsize; ++i)
	{
		cmp = other.cmp(i, rsize);
		for (int k = 0; k < rsize; ++k)
		{
			temp2[k] = cmp.niz[k];
		}
		if(strcmp(temp1, temp2) == 0)
		{
			return true;
		}
	}
	
	return false;
}

bool base64::operator<=(base64 other)
{
	if(!isEncoded || !other.isEncoded)
	{
		cout << "Comparing non-encoded strings." << endl;
		return false;
	}
	if(rsize > other.rsize)
	{
		return false;
	}
	if(*this < other)
	{
		return true;
	}
	if(strcmp(niz, other.niz) == 0)
	{
		return true;
	}


	return false;
}

bool base64::operator>(base64 other)
{
	if(!isEncoded || !other.isEncoded)
	{
		cout << "Comparing non-encoded strings." << endl;
		return false;
	}
	if(other.rsize >= rsize)
	{
		return false;
	}
	base64 comp;
	char *temp1, *temp2;
	temp1 = new char[rsize + 1];
	temp2 = new char[rsize + 1];
	strcpy(temp1, other.niz);
	temp1[other.rsize] = '\0';
	temp2[other.rsize] = '\0';
	for (int i = 0; i < rsize - other.rsize; ++i)
	{
		comp = cmp(i, other.rsize);
		for (int k = 0; k < other.rsize; ++k)
		{
			temp2[k] = comp.niz[k];
		}
		if(strcmp(temp1, temp2) == 0)
		{
			return true;
		}
	}
	return false;
}

bool base64::operator>=(base64 other)
{
	if(!isEncoded || !other.isEncoded)
	{
		cout << "Comparing non-encoded strings." << endl;
		return false;
	}
	if(other.rsize > rsize)
	{
		return false;
	}
	if(*this > other)
	{
		return true;
	}
	if(strcmp(niz, other.niz) == 0)
	{
		return true;
	}


	return false;
}





