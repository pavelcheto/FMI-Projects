#include <iostream>
#include <fstream>
#include <string>
#include <list>

using namespace std;

struct Letter
{
	int x, y;
	Letter()
	{
		x = y = 0;
	}
	Letter(int _x, int _y)
	{
		x = _x;
		y = _y;
	}
};

list<Letter> working;
Letter temp;
list<list<Letter>> final;

string listToString(char matrix[8][8], list<Letter> otnovo)
{
	list<Letter>::iterator it = otnovo.begin();
	char c[64];
	int counter;
	for (int i = 0; it != otnovo.end(); i++)
	{
		Letter b = *it;
		c[i] = matrix[b.x][b.y];
		it++;
		counter = i;
	}
	string pisnaMiDaMislqImena(c, counter + 1);
	return pisnaMiDaMislqImena;
}

void printResult(char matrix[8][8])
{
	ofstream output("output.txt", ios::out);
	list<list<Letter>>::iterator it = final.begin();
	list<Letter> it2;
	while (it != final.end())
	{
		it2 = *it;
		output << listToString(matrix, it2) << ' ';
		list<Letter>::iterator it3 = it2.begin();
		while (it3 != it2.end())
		{
			Letter b = *it3;
			output << '(' << b.x << "," << b.y << ") ";
			it3++;
		}
		output << endl;
		it++;
	}
}

void findNeighbour(char matrix[8][8], int msize, int i, int j, bool path[8][8], string word, int current)
{
	//cout << "Pushing: " << i << ' ' << j << endl;
	if (current > word.size() - 1)
	{
		final.push_back(working);
		//cout << ">>>>>>>>>>>>>>>>>Found" << endl;
		//working.pop_back();
		return;
	}
	if (i - 1 >= 0 && i - 1 < msize && j >= 0 && j < msize && word[current] == matrix[i - 1][j] && !path[i - 1][j])
	{
		temp.x = i - 1;
		temp.y = j;
		working.push_back(temp);
		path[i - 1][j] = true;
		//cout << "Entered: " << i - 1 << ' ' << j << endl;
		findNeighbour(matrix, msize, i - 1, j, path, word, current + 1);
		path[i - 1][j] = false;
		working.pop_back();
	}
	if (i - 1 >= 0 && i - 1 < msize && j - 1 >= 0 && j - 1 < msize && word[current] == matrix[i - 1][j - 1] && !path[i - 1][j - 1])
	{
		temp.x = i - 1;
		temp.y = j - 1;
		working.push_back(temp);
		path[i - 1][j - 1] = true;
		//cout << "Entered: " << i - 1 << ' ' << j - 1 << endl;
		findNeighbour(matrix, msize, i - 1, j - 1, path, word, current + 1);
		path[i - 1][j - 1] = false;
		working.pop_back();
	}
	if (i - 1 >= 0 && i - 1 < msize && j + 1 >= 0 && j + 1 < msize && word[current] == matrix[i - 1][j + 1] && !path[i - 1][j + 1])
	{
		temp.x = i - 1;
		temp.y = j + 1;
		working.push_back(temp);
		path[i - 1][j + 1] = true;
		//cout << "Entered: " << i - 1 << ' ' << j + 1 << endl;
		findNeighbour(matrix, msize, i - 1, j + 1, path, word, current + 1);
		path[i - 1][j + 1] = false;
		working.pop_back();
	}
	if (i >= 0 && i < msize && j - 1 >= 0 && j - 1 < msize && word[current] == matrix[i][j - 1] && !path[i][j - 1])
	{
		temp.x = i;
		temp.y = j - 1;
		working.push_back(temp);
		path[i][j - 1] = true;
		//cout << "Entered: " << i << ' ' << j - 1 << endl;
		findNeighbour(matrix, msize, i, j - 1, path, word, current + 1);
		path[i][j - 1] = false;
		working.pop_back();
	}
	if (i >= 0 && i < msize && j + 1 >= 0 && j + 1 < msize && word[current] == matrix[i][j + 1] && !path[i][j + 1])
	{
		temp.x = i;
		temp.y = j + 1;
		working.push_back(temp);
		path[i][j + 1] = true;
		//cout << "Entered: " << i << ' ' << j + 1 << endl;
		findNeighbour(matrix, msize, i, j + 1, path, word, current + 1);
		path[i][j + 1] = false;
		working.pop_back();
	}
	if (i + 1 >= 0 && i + 1 < msize && j >= 0 && j < msize && word[current] == matrix[i + 1][j] && !path[i + 1][j])
	{
		temp.x = i + 1;
		temp.y = j;
		working.push_back(temp);
		path[i + 1][j] = true;
		//cout << "Entered: " << i + 1 << ' ' << j << endl;
		findNeighbour(matrix, msize, i + 1, j, path, word, current + 1);
		path[i + 1][j] = false;
		working.pop_back();
	}
	if (i + 1 >= 0 && i + 1 < msize && j - 1 >= 0 && j - 1 < msize && word[current] == matrix[i + 1][j - 1] && !path[i + 1][j - 1])
	{
		temp.x = i + 1;
		temp.y = j - 1;
		working.push_back(temp);
		path[i + 1][j - 1] = true;
		//cout << "Entered: " << i + 1 << ' ' << j - 1 << endl;
		findNeighbour(matrix, msize, i + 1, j - 1, path, word, current + 1);
		path[i + 1][j - 1] = false;
		working.pop_back();
	}
	if (i + 1 >= 0 && i + 1 < msize && j + 1 >= 0 && j + 1 < msize && word[current] == matrix[i + 1][j + 1] && !path[i + 1][j + 1])
	{
		temp.x = i + 1;
		temp.y = j + 1;
		working.push_back(temp);
		path[i + 1][j + 1] = true;
		//cout << "Entered: " << i + 1 << ' ' << j + 1 << endl;
		findNeighbour(matrix, msize, i + 1, j + 1, path, word, current + 1);
		path[i + 1][j + 1] = false;
		working.pop_back();
	}
	//cout << "return false " << i << ' ' << j << endl;
	return;
}

void nullPath(bool path[8][8])
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			path[i][j] = false;
		}
	}
}

void checkWord(char matrix[8][8], int msize, string word)
{
	bool path[8][8];
	nullPath(path);

	for (int i = 0; i < msize; i++)
	{
		for (int j = 0; j < msize; j++)
		{
			if (matrix[i][j] == word[0])
			{
				path[i][j] = true;
				temp.x = i;
				temp.y = j;
				working.push_back(temp);
				findNeighbour(matrix, msize, i, j, path, word, 1);
				nullPath(path);
				working.pop_back();
			}
		}
	}
}

void check(char matrix[8][8], int msize, list<string> dict)
{
	list<string>::iterator it = dict.begin();
	for (int i = 0; i < dict.size(); i++)
	{
		checkWord(matrix, msize, *it);
		it++;
	}
}


int main()
{
	ifstream input("input.txt", ios::in);
	char asd[64];
	list<string> tempmatrix;
	int msize = 0;
	input.getline(asd, 19, '\n');
	string test(asd);
	tempmatrix.push_back(test);
	msize = test.size() / 2 + 1;
	for (int i = 0; i < msize - 1; i++)
	{
		input.getline(asd, 19, '\n');
		string temp(asd);
		tempmatrix.push_back(temp);
	}
	

	char matrix[8][8];
	for (int i = 0; i < msize; i++)
	{
		for (int j = 0, k = 0; j < msize; j++, k += 2)
		{
			matrix[i][j] = tempmatrix.front()[k];
		}
		tempmatrix.pop_front();
	}

	list<string> dict;

	while(input)
	{
		input.getline(asd, 64, '\n');
		string temp(asd);
		dict.push_back(temp);
	}
	dict.pop_back();

	check(matrix, msize, dict);
	printResult(matrix);

	return 0;
}