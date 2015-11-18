#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <sstream> 
#include <stack>

using namespace std;

ofstream output;

bool whitespace(char c)
{
	if (c == ' ') return true;
	if (c == '\n') return true;
	if (c == '\t') return true;
	if (c == '\r') return true;
	return false;
}

void trimText(string c)
{
	int max = c.length();
	string result;
	for (int i = 0; i < max; i++)
	{
		if(c[i] == '\n')
		{
			while(c[i] == '\n')
			{
				i++;
			}
		}
		if (whitespace(c[i]))
		{
			result.push_back(c[i]);
			i++;
			while (whitespace(c[i]))
			{
				i++;
			}
		}
		result.push_back(c[i]);
	}
	output << result;
}

void toUpper(string c)
{
	string result;
	int max = c.length();
	for (int i = 0; i < max; i++)
	{
		if(c[i] == '\n')
		{
			while(c[i] == '\n')
			{
				i++;
			}
		}
		if (c[i] <= 'z' && c[i] >= 'a')
		{
			result.push_back(c[i] - 32);
		}
		else
		{
			result.push_back(c[i]);
		}
	}
	output << result;
}

void toLower(string c)
{
	string result;
	int max = c.length();
	for (int i = 0; i < max; i++)
	{
		if(c[i] == '\n')
		{
			while(c[i] == '\n')
			{
				i++;
			}
		}
		if (c[i] <= 'Z' && c[i] >= 'A')
		{
			result.push_back(c[i] + 32);
		}
		else
		{
			result.push_back(c[i]);
		}
	}
	output << result;
}

void toHex(string c)
{
	if (c.size() == 0)
	{
		return;
	}
	int result = atoi(c.c_str());
	output << hex << result;
}

void toOct(string c)
{
	if (c.size() == 0)
	{
		return;
	}
	int result = atoi(c.c_str());
	output << oct << result;
}

void toPre(string c)
{
	if (c.size() == 0)
	{
		return;
	}
	double result;
	istringstream iss;
    iss.str(c);
    iss >> result;
	output << setprecision(2) << fixed << result;
}

void toNl()
{
	output << '\n';
}

void toTb()
{
	output << "     ";
}

void toNothing(string c)
{
	string result;
	int max = c.length();
	for (int i = 0; i < max; i++)
	{
		if(c[i] == '\n')
		{
			while(c[i] == '\n')
			{
				i++;
			}
		}
		result.push_back(c[i]);
	}
	output << result;
}

void choose(string c, int n)
{
	switch (n)
	{
	case 0:
		toNothing(c);
		break;
	case 1:
		trimText(c);
		break;
	case 2:
		toUpper(c);
		break;
	case 3:
		toLower(c);
		break;
	case 4:
		toHex(c);
		break;
	case 5:
		toOct(c);
		break;
	case 6:
		toPre(c);
		break;
	case 7:
		toNl();
		break;
	case 8:
		toTb();
		break;
	default:
		toNothing(c);
		break;
	}
}

int tagRecognizer(string c)
{
	if (c.compare("trim") == 0)
	{
		return 1;
	}
	else if (c.compare("toupper") == 0)
	{
		return 2;
	}
	else if (c.compare("tolower") == 0)
	{
		return 3;
	}
	else if (c.compare("hex") == 0)
	{
		return 4;
	}
	else if (c.compare("oct") == 0)
	{
		return 5;
	}
	else if (c.compare("pre") == 0)
	{
		return 6;
	}
	else if (c.compare("nl") == 0)
	{
		return 7;
	}
	else if (c.compare("tb") == 0)
	{
		return 8;
	}
	
	return -1;
}

void parse(string c)
{
	stack<int> tags;
	tags.push(0);
	int counter = 0;
	int max = c.length();
	while (counter < max)
	{
		string temp;
		while (c[counter] != '<' && counter < max)
		{
			temp.push_back(c[counter]);
			counter++;
		}
		choose(temp, tags.top());
		if (c[counter] == '<')
		{
			string tag;
			counter++;
			if (c[counter] == '/')
			{
				counter++;
				while (c[counter] != '>' && counter < max)
				{
					tag.push_back(c[counter]);
					counter++;
				}
				int tagr = tagRecognizer(tag);
				if (tagr == -1)
				{
					cout << "Error, unknown tag!" << endl;
				}
				else
				{
					if (tagr == tags.top())
					{
						tags.pop();
					}
					else
					{
						cout << "Error, wrong closing tag!" << endl;
					}
				}
			}
			else
			{
				while (c[counter] != '>' && counter < max)
				{
					tag.push_back(c[counter]);
					counter++;
				}
				int tagr = tagRecognizer(tag);
				if (tagr == -1)
				{
					cout << "Error, unknown tag!" << endl;
				}
				else if(tagr == 7)
				{
					toNl();
				}
				else if(tagr == 8)
				{
					toTb();
				}
				else
				{
					tags.push(tagr);
				}
			}
			counter++;
		}
	}
}

int main()
{
	string ifname, ofname;
	ifstream input;
	cout << "Please enter file name for input: ";
	cin >> ifname;
	input.open(ifname, ios::in);
	while(!input.is_open())
	{
		cout << "Nope! Wrong name! Please enter file name for input: ";
		cin >> ifname;
		input.open(ifname, ios::in);
	}
	string temp, s;
	while(getline(input, temp))
	{
      s += temp;
	}
	input.close();
	cout << "Please enter file name for output: ";
	cin >> ofname;
	output.open(ofname, ios::out);
	parse(s);
	output.close();
	return 0;
}