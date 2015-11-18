#include "rle.h"
#include <iostream>
#include <cstring>

using namespace std;

rle::rle(char * input)
{
	int sm;
	sm = strlen(input);
	niz = new one[sm];
	rsize = sm;
	size = 0;
	for(int i = 0; input[i] != '\0'; i++)
	{
		int broi = 0;
		for(int j = i; input[j] == input[i]; j++)
		{
			broi++;
		}
		niz[size].number = broi;
		niz[size].letter = input[i];
		size++;
		i += broi - 1;
		broi = 0;
	}
	one *temp;
	temp = new one[size];
	for(int i = 0; i < size; i++)
	{
		temp[i] = niz[i];
	}
	delete[] niz;
	niz = new one[size];
	for(int i = 0; i < size; i++)
	{
		niz[i] = temp[i];
	}
	delete[] temp;
}

rle::rle(){
	niz = new one[1];
	size = 0;
	rsize = 0;
}

rle::~rle()
{
	delete[] niz;
}

rle::rle(const rle &copy)
{
	size = copy.size;
	rsize = copy.rsize;
	niz = new one[size];
	for(int i = 0; i < size; i++)
			{
				niz[i] = copy.niz[i];
			}
}

rle &rle::operator=(const rle &other)
{
	if(this != &other)
	{
		size = other.size;
		rsize = other.rsize;
		delete[] niz;
		niz = new one[size];
		for(int i = 0; i < size; i++)
		{
			niz[i] = other.niz[i];
			
		}
	}

	return *this;
}

void rle::print_decoded()
{
	for(int i = 0; i < size; i++)
	{
		for(int j = 0; j < niz[i].number; j++)
		{
			cout << niz[i].letter;
		}
	}
	cout << endl;
}

ostream& operator<< (ostream& out, const rle& other)
{

	for(int i = 0; i < other.size; i++)
	{
		out << '(' << other.niz[i].number << ',' << other.niz[i].letter << ')';
	}
	out << endl;
	return out;
}

char const &rle::operator[](int number)
{
	if (number < 1 || number > rsize)
	{
		cout << "Bad input";
		return '.';
	}
	number--;
	int a = 0, b = 0, c = 0;
	for(int i = 0; i < size; i++)
	{
		for(int j = 0; j < niz[i].number; j++)
		{
			if (a == number)
			{
				b = i;
				c++;
				break;
			}
			else
			{
				a++;
			}
		}
		if (c != 0)
		{
			break;
		}
	}
	return niz[b].letter;
}

rle& rle::operator++()
{
	niz[size-1].number += 1;
	rsize++;
	return *this;
}

rle rle::operator++(int)
{
	rle ans = *this;
	++(*this);
	return ans;
}

rle& rle::operator--()
{
	if(niz[size-1].number == 1)
	{
		one *temp;
		temp = new one[size-1];
		for(int i = 0; i < size - 1; i++)
		{
			temp[i] = niz[i];
		}
		delete[] niz;
		niz = new one[size - 1];
		for(int i = 0; i < size - 1; i++)
		{
			niz[i] = temp[i];
		}
		delete[] temp;
		size--;
		rsize--;
	}
	else
	{
		niz[size-1].number--;
		rsize--;
	}
	return *this;
}

rle rle::operator--(int)
{
	rle ans = *this;
	--(*this);
	return ans;
}

rle rle::operator+(rle other) const
{
	rle ans = *this;
	rle bns = *this;
	delete[] ans.niz;
	ans.size = bns.size + other.size;
	ans.rsize = bns.rsize + other.size;
	ans.niz = new one[ans.size];
	for(int i = 0; i < bns.size; i++)
	{
		ans.niz[i] = bns.niz[i];
	}
	for(int i = bns.size, j = 0; i < ans.size; i++, j++)
	{
		ans.niz[i] = other.niz[j];
	}
	for (int i = 0; i < ans.size - 1; i++)
	{
		if (ans.niz[i].letter == ans.niz[i + 1].letter)
		{
			bns.niz[i].number += ans.niz[i + 1].number;
			delete[] ans.niz;
			ans.size--;
			ans.niz = new one[ans.size];
			for(int i = 0; i < size; i++)
			{
				ans.niz[i] = bns.niz[i];
			}
			for(int i = size, j = 1; i < ans.size; i++, j++)
			{
				ans.niz[i] = other.niz[j];
			}
		}
	}
	return ans;
}

rle rle::operator+=(rle other)
{
	*this = *this + other;
	return *this;
}

rle rle::operator()(int start, int lenght)
{
	if(start < 0 || start > rsize - 1)
	{
		cout << "Incorrect start. Setting start to 1" << endl;
		start = 0;
	}
	if (lenght > rsize - start)
	{
		cout << "Incorrect length. Setting length to 1." << endl;
		lenght = 1;
	}
	rle ans;
	int a = 0, b = 0, c = 0, d = 0, yes = lenght;
	for(int i = 0; i < size; i++)
	{
		for(int j = 0; j < niz[i].number; j++)
		{
			if (a == start)
			{
				b = i;
				c++;
				break;
			}
			else
			{
				a++;
			}
		}
		if (c != 0)
		{
			break;
		}
	}
	c = 0;
	for(int i = 0; i < b; i++)
	{
		c += niz[i].number;
	}
	int e = 1, f = 0;
	d = start - c;
	f = niz[b].number - d;
	int finally = f;
	int fuck = lenght - f;
	for(int i = b + 1; fuck > 0; i++)
		{
			finally += niz[i].number;
			fuck -= niz[i].number;
		}
	delete[] ans.niz;
	ans.niz = new one[finally];
	ans.niz[0].number = f;
	ans.niz[0].letter = niz[b].letter;
	ans.rsize = yes;
	ans.size = 1;
	lenght -= f;
	if(lenght > 0)
	{
		for(int i = b + 1; lenght > 0; i++)
		{
			ans.niz[e] = niz[i];
			e++;
			lenght -= niz[i].number;
		}
	}
	ans.size = e;
	while(finally != yes)
	{
		--ans;
		finally--;
	}
	
	return ans;
}

rle rle::operator()(int start, rle other)
{
	rle second = (*this)(start, rsize - start);
	for (int i = 0; i < rsize - start; i++)
	{
		(*this)--;
	}
	*this += other;
	*this += second;
	return *this;
}

rle rle::delete_f(int start, int length)
{
	rle f;
	cout << rsize << ' ';
	f = (*this)(start + length, rsize - start - length);
	for (int i = 0; i < rsize - start; i++)
	{
		(*this)--;
	}
	*this += f;
	return *this;
}

bool rle::operator==(rle other)
{
	int a = 0, b = 0;
	if (size > other.size)
	{
		b = size;
	}
	else
	{
		b = other.size;
	}
	for (int i = 0; i < b; i++)
	{
		if (niz[i].number == other.niz[i].number && niz[i].letter == other.niz[i].letter)
		{
			a++;
		}
	}
	if (a == b)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool rle::operator!=(rle other)
{
	return !((*this) == other);
}

bool rle::operator>(rle other)
{
	if (rsize == other.rsize)
	{
		return false;
	}
	else
	{
		rle cmp;
		for (int i = 0; i < rsize - other.rsize; i++)
		{
			cmp = (*this)(i, other.rsize);
			cout << cmp;
			if (cmp == other)
			{
				return true;
			}
		}
	}
	return false;
}

bool rle::operator>=(rle other)
{
	if (*this == other)
	{
		return true;
	}
	rle cmp;
	for (int i = 0; i < rsize - other.rsize; i++)
	{
		cmp = (*this)(i, other.rsize);
		if (cmp == other)
		{
			return true;
		}
	}
	return false;
}

bool rle::operator<(rle other)
{
	if (rsize == other.rsize)
	{
		return false;
	}
	else
	{
		rle cmp;
		for (int i = 0; i < other.rsize - rsize; i++)
		{
			cmp = other(i, rsize);
			if (cmp == (*this))
			{
				return true;
			}
		}
	}
	return false;
}

bool rle::operator<=(rle other)
{
	if (*this == other)
	{
		return true;
	}
	else
	{
		rle cmp;
		for (int i = 0; i < other.rsize - rsize; i++)
		{
			cmp = other(i, rsize);
			if (cmp == (*this))
			{
				return true;
			}
		}
	}
	return false;
}

bool findLetter(char input, rle obj)
{
	for (int i = 0; i < obj.size; ++i)
	{
		if (obj.niz[i].letter == input)
		{
			return true;
		}
	}
	return false;
}
rle rle::operator*()
{
	rle ans;
	delete[] ans.niz;
	ans.niz = new one[size];
	ans.size = size;
	ans.rsize = rsize;
	for (int i = 0; i < size; ++i)
	{
		ans.niz[i].number = 0;
		ans.niz[i].letter = '.';
	}
	int e = 0;
	for (int i = 0; i < size; ++i)
	{
		if (findLetter(niz[i].letter, ans))
		{
			for (int j = 0; j < size; ++j)
			{
				if(ans.niz[j].letter == niz[i].letter)
				{
					ans.niz[j].number += niz[i].number;
				}
			}
		}
		else
		{
			ans.niz[e].letter = niz[i].letter;
			ans.niz[e].number = niz[i].number;
			e++;
		}
	}
	rle ans2;
	ans2.rsize = rsize;
	int c = 0;
	for (int i = 0; i < size; ++i)
	{
		if (ans.niz[i].number != 0)
		{
			c++;
		}
	}
	ans2.size = c;
	delete[] ans2.niz;
	ans2.niz = new one[ans2.size];
	for (int i = 0; i < ans2.size; ++i)
	{
		ans2.niz[i] = ans.niz[i];
	}
	return ans2;
}










