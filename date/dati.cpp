#include "dati.h"
#include <iostream>

using namespace std;

int const nod[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

struct holiday
{
	int day, month;
};

const holiday holidays[11] = {{1, 1}, {3, 3}, {1, 5}, {6, 5}, {24, 5}, {6, 9}, {22, 9}, {1, 11}, {24, 12}, {25, 12}, {26, 12}};

date shanoDay(date shano, int pos)
{
	switch (pos)
	{
	case 1:
		while (true)
		{
			if (shano.isWorking())
			{
				return shano;
			}
			else
			{
				shano++;
			}
		}
		break;
	case 2:
		while (true)
		{
			if (shano.isWorking())
			{
				return shano;
			}
			else
			{
				shano--;
			}
		}
		break;
	default:
		date back, forth;
		forth = shanoDay(shano, 1);
		back = shanoDay(shano, 2);
		int edno, dve;
		forth.findWeekday();
		back.findWeekday();
		edno = shano - back;
		dve = shano - forth;
		if (edno >= dve)
		{
			return forth;
		}
		else
		{
			return back;
		}
		break;
	}
}

date::date()
{
	day = 0;
	month = 0;
	year = 0;
	weekd = -1;
	working = false;
	workingResult = false;
	posoka = 0;
}

date::date(int d, int m, int y)
{
	bool vis = false;
	if( y % 4 == 0)
	{
		vis = true;
	}
	if(y == 0)
	{
		cerr << "There is no 0 year.  <_<\nSetting year to 1." << endl;
		y = 1;
	}
	if(m < 1 || m > 12)
	{
		cerr << "Incorrect month. Setting month to 1." << endl;
		m = 1;
	}
	if(d < 1 || d> 31){
		cerr << "Incorrect day. Setting day to 1." << endl;
		d = 1;
	}
	if(m == 4 || m == 6 || m == 9 || m == 11)
	{
		if(d == 31)
		{
			cerr << "This month has only 30 days. Setting day to 30." << endl;
			d = 30;
		}

	}
	if(m == 2)
	{
		if (d > 28)
		{
			if (vis == true)
			{
				if(d > 29){
				cerr << "February has 29 days this year. Setting day to 29."<< endl;
				d = 29;
				}
			}
			else
			{
				cerr << "February has 28 days this year. Setting day to 28." << endl;
				d = 28;
			}
		}
	}
	
	day = d;
	month = m;
	year = y;
    weekd = this -> findWeekday();
	working = false;
	workingResult = false;
	posoka = 0;
}

int date::findWeekday()
{
	int y = year;
	int m = month;
	int d = day;
	int t[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };
	y -= m < 3;
    return (y + y/4 - y/100 + y/400 + t[m-1] + d) % 7;
}

int date::getDay()
{
	return day;
}

int date::getMonth()
{
	return month;
}

int date::getYear()
{
	return year;
}

int date::getWeekday()
{
	return weekd;
}

bool date::setDay(int d)
{
	bool vis = false;
	int y = year;
	int m = month;
	if( y % 4 == 0)
	{
		vis = true;
	}
	if (d < 1 || d > 31)
	{
		cerr << "Incorrect day. Setting day failed." << endl;
		return false;
	}
	if(m == 4 || m == 6 || m == 9 || m == 11)
	{
		if(d == 31)
		{
			cerr << "This month has only 30 days. Setting day failed." << endl;
			return false;
		}

	}
	if(m == 2)
	{
		if (d > 28)
		{
			if (vis == true)
			{
				if(d > 29){
				cerr << "February has 29 days this year. Setting day failed."<< endl;
				return false;
				}
			}
			else
			{
				cerr << "February has 28 days this year. Setting day failed." << endl;
				return false;
			}
		}
	}
	day = d;
	weekd = findWeekday();
	return true;
}

bool date::setMonth(int m)
{
	int d = day;
	int y = year;
	bool vis = false;
	if( y % 4 == 0)
	{
		vis = true;
	}
	if(m < 1 || m > 12)
	{
		cerr << "Incorrect month. Setting month failed." << endl;
		return false;
	}
	if (d == 31)
	{
		if(m == 4 || m == 6 || m == 9 || m == 11)
		{
			cerr << "The current day is 31, please change day first. Setting month failed." << endl;
			return false;
		}
	}
	if (m == 2)
	{
		if(d > 28)
		{
			if (vis == true)
			{
				if(d > 29)
				{
				cerr << "February has 29 days this year. Setting month failed."<< endl;
				return false;
				}
			}
			else
			{
				cerr << "The day is over 28 and it is not a leap year, please change day first. Setting month failed." << endl;
				return false;
			}
		}
	}
	month = m;
	weekd = findWeekday();
	return true;
}

bool date::setYear(int y)
{
	if(y == 0)
	{
		cerr << "There is no 0 year. <_<\nSetting year failed." << endl;
		return false;
	}
	year = y;
	weekd = findWeekday();
	return true;
}

istream& operator>> (istream& in, date& tits)
{
	cout << "Enter day, month and year:" << endl;
	in >> tits.day >>tits.month >> tits.year;
		
	if (tits.day < 1 || tits.day > 31)
	{
		cerr << "Incorrect day. Setting day to 1." << endl;
		tits.day = 1;
	}
	if(tits.month < 1 || tits.month > 12)
	{
		cerr << "Incorrect month. Setting month to 1." << endl;
		tits.month = 1;
	}
	if(tits.year == 0)
	{
		cerr << "There is no 0 year. <_<\nSetting year to 1." << endl;
		tits.year = 1;
	}
	bool vis = false;
	if( tits.year % 4 == 0)
	{
		vis = true;
	}
	if (tits.day == 31)
	{
		if(tits.month == 4 || tits.month == 6 || tits.month == 9 || tits.month == 11)
		{
			cerr << "The current day is 31 but the month you entered has only 30 days. Setting day to 30." << endl;
			tits.day = 30;
		}
	}
	if (tits.month == 2)
	{
		if(tits.day > 28)
		{
			if (vis == true)
			{
				if(tits.day > 29)
				{
				cerr << "February has 29 days this year but you've entered day over 29. Setting day to 29."<< endl;
				tits.day = 29;
				}
			}
			else
			{
				cerr << "February has 28 days this year but you've entered day over 28. Setting day to 28." << endl;
				tits.day = 28;
			}
		}
	}
	tits.weekd = tits.findWeekday();
	tits.working = false;
	return in;
}

ostream& operator<< (ostream& os, date& butt)
{
	cout << "Please choose type of output:\n1. Day.Month.Year\n2. Month.Day.Year\n3. Year/Month/Day\n4. Day Month Year" << endl;
	int choice;
	cin >> choice;
	switch (choice)
	{
	case 1:
		os << butt.day << "." << butt.month << "." << butt.year << endl;
		break;
	case 2:
		os << butt.month << "." << butt.day << "." << butt.year << endl;
		break;
	case 3:
		os << butt.year << "/" << butt.month << "/" << butt.day << endl;
		break;
	case 4:
		os << butt.day << " ";
		switch (butt.month)
		{
		case 1:
			os << "January";
			break;
		case 2:
			os << "February";
			break;
		case 3:
			os << "March";
			break;
		case 4:
			os << "April";
			break;
		case 5:
			os << "May";
			break;
		case 6:
			os << "June";
			break;
		case 7:
			os << "July";
			break;
		case 8:
			os << "August";
			break;
		case 9:
			os << "September";
			break;
		case 10:
			os << "October";
			break;
		case 11:
			os << "November";
			break;
		case 12:
			os << "December";
			break;

		default:
			os << "Ko?";
			break;
		}
		os << " " << butt.year << endl;
		break;
	default:
		os << "Wrong choice." << endl;
		break;
	}
	return os;
}

bool date::isLastDay()
{
	if(month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
	{
		if (day == 31)
		{
			return true;
		}
	}
	if (month == 4 || month == 6 || month == 9 || month == 11)
	{
		if (day == 30)
		{
			return true;
		}
	}
	bool vis = false;
	if (year % 4 == 0)
	{
		vis = true;
	}
	if (month == 2)
	{
		if (vis == true)
		{
			if (day == 29)
			{
				return true;
			}
		}
		else
		{
			if (day == 28)
			{
				return true;
			}
		}
	}
	return false;
}

date operator+ (date other, int dni)
{
	for (int i = dni; i > 0; i--)
	{
		other++;
		if(other.working)
		{
			while (!other.isWorking())
			{
				other++;
			}
		}

	}
	if (other.workingResult)
	{
		if (!other.isWorking())
		{
		other = shanoDay(other, other.posoka);
		}
	}
	return other;
}

date operator++ (date& other)
{
	if (other.isLastDay() == true && other.month == 12)
		{
			other.year++;
			other.day = 1;
			other.month = 1;
		}
		else if (other.isLastDay() == true && other.month != 12)
		{
			other.month++;
			other.day = 1;
		}
		else if (other.isLastDay() == false)
		{
			other.day++;
		}
		int d = other.day;
		int m = other.month;
		int y = other.year;
		other.weekd = other.findWeekday();
		return other;
}

date operator+= (date& other, int dni)
{
	for (int i = dni; i > 0; i--)
	{
		other++;
		if(other.working)
		{
			while (!other.isWorking())
			{
				other++;
			}
		}
	}
	if (other.workingResult)
	{
		if (!other.isWorking())
		{
		other = shanoDay(other, other.posoka);
		}
	}
	return other;
}

date operator-(date other, int dni)
{
	for (int i = dni; i > 0; i--)
	{
		other--;
		if(other.working)
		{
			while (!other.isWorking())
			{
				other--;
			}
		}
	}
	if (other.workingResult)
	{
		if (!other.isWorking())
		{
		other = shanoDay(other, other.posoka);
		}
	}
	return other;
}

date operator--(date& other)
{
	bool vis = false;
	if (other.year % 4 == 0)
	{
		vis = true;
	}
	if (other.day == 1 && other.month == 1)
	{
		other.year--;
		other.day = 31;
		other.month = 12;
	}
	else if (other.day == 1 && other.month != 1)
	{
		if(vis && other.month == 3)
		{
			other.month = 2;
			other.day = 29;
		}
		else
		{
			other.month--;
			other.day = nod[other.month];
		}
	}
	else
	{
		other.day--;
	}
	other.weekd = other.findWeekday();
	return other;
}

date operator-=(date& other, int dni)
{
	for (int i = dni; i > 0;  i--)
	{
		other--;
		if(other.working)
		{
			while (!other.isWorking())
			{
				other--;
			}
		}
	}
	if (other.workingResult)
	{
		if (!other.isWorking())
		{
		other = shanoDay(other, other.posoka);
		}
	}
	return other;
}

date operator*(date other, int mes)
{
	for (int i = 0; i < mes; i++)
	{
		if (other.month == 12)
		{
			other.year++;
			other.month = 1;
		}
		else
		{
			other.month++;
		}
	}
	if (other.day > nod[other.month])
	{
		if (other.month == 2 && other.year % 4 == 0)
		{
			other.day = 29;
		}
		else
		{
			other.day = nod[other.month];
		}
	}
	if (other.workingResult)
	{
		if (!other.isWorking())
		{
		other = shanoDay(other, other.posoka);
		}
	}
	return other;
}

date operator*=(date& other, int mes)
{
	other = other * mes;
	if (other.workingResult)
	{
		if (!other.isWorking())
		{
		other = shanoDay(other, other.posoka);
		}
	}
	return other;
}

date operator/(date other, int mes)
{
	for (int i = 0; i < mes; i++)
	{
		if (other.month == 1)
		{
			other.year--;
			other.month = 12;
		}
		else
		{
			other.month--;
		}
	}
	if (other.day > nod[other.month])
	{
		if (other.month == 2 && other.year % 4 == 0)
		{
			other.day = 29;
		}
		else
		{
			other.day = nod[other.month];
		}
	}
	if (other.workingResult)
	{
		if (!other.isWorking())
		{
		other = shanoDay(other, other.posoka);
		}
	}
	other.weekd = other.findWeekday();
	return other;
}

date operator/=(date& other, int mes)
{
	other = other / mes;
	if (other.workingResult)
	{
		if (!other.isWorking())
		{
		other = shanoDay(other, other.posoka);
		}
	}
	return other;
}

date operator&(date other, int god)
{
	other.year += god;
	if (other.year % 4 != 0 && other.month == 2 && other.day == 29)
	{
		other.day = 28;
	}
	if (other.workingResult)
	{
		if (!other.isWorking())
		{
		other = shanoDay(other, other.posoka);
		}
	}
	other.weekd = other.findWeekday();

	return other;
}

date operator&=(date& other, int god)
{
	other = other & god;
	if (other.workingResult)
	{
		if (!other.isWorking())
		{
		other = shanoDay(other, other.posoka);
		}
	}
	return other;
}

date operator|(date other, int god)
{
	other.year -= god;
	if (other.year % 4 != 0 && other.month == 2 && other.day == 29)
	{
		other.day = 28;
	}
	if (other.workingResult)
	{
		if (!other.isWorking())
		{
		other = shanoDay(other, other.posoka);
		}
	}
	other.weekd = other.findWeekday();
	return other;
}

date operator|=(date& other, int god)
{
	other = other | god;
	if (other.workingResult)
	{
		if (!other.isWorking())
		{
		other = shanoDay(other, other.posoka);
		}
	}
	return other;
}

date operator^(date other, int sed)
{
	other += 7 * sed;
	other.weekd = other.findWeekday();
	if (other.workingResult)
	{
		if (!other.isWorking())
		{
		other = shanoDay(other, other.posoka);
		}
	}
	return other;
}

date operator^=(date& other, int sed)
{
	other = other ^ sed;
	if (other.workingResult)
	{
		if (!other.isWorking())
		{
		other = shanoDay(other, other.posoka);
		}
	}
	return other;
}

date operator%(date other, int sed)
{
	other -= 7 * sed;
	if (other.workingResult)
	{
		if (!other.isWorking())
		{
		other = shanoDay(other, other.posoka);
		}
	}
	other.weekd = other.findWeekday();
	return other;
}

date operator%=(date& other, int sed)
{
	other = other % sed;
	if (other.workingResult)
	{
		if (!other.isWorking())
		{
		other = shanoDay(other, other.posoka);
		}
	}
	return other;
}

date date::isOlder(date other)
{
	if(year > other.year)
	{
		return *this;
	}
	else if (year < other.year)
	{
		return other;
	}
	else
	{
		if (month > other.month)
		{
			return *this;
		}
		else if (month < other.month)
		{
			return other;
		}
		else
		{
			if (day > other.day)
			{
				return *this;
			}
			else
			{
				return other;
			}

		}
	}
}

bool operator==(date one, date two)
{
	if (one.year == two.year && one.month == two.month && one.day == two.day)
	{
		return true;
	}
	return false;
}

int operator-(date one, date two)
{
	if (one == two)
	{
		cout << "Comparing the same date." << endl;
		return  0;
	}
	date *p1, *p2;
	if(one.isOlder(two) == one)
	{
		p1 = &one;
		p2 = &two;
	}
	else
	{
		p1 = &two;
		p2 = &one;
	}
	int dif = 0;
	for (int i = 0; 1; i++)
	{
		(*p2)++;
		dif++;
		if (*p2 == *p1)
		{
			break;
		}
	}


	return dif;
}

int operator/(date one, date two)
{
	date *p1, *p2;
	int dif = 0;
	if (one == two)
	{
		cout << "Comparing the same date." << endl;
		return  0;
	}
	if (one.year == two.year && one.month == two.month)
	{
		return 0;
	}
	if (one.isOlder(two) == one)
	{
		p1 = &one;
		p2 = &two;
	}
	else
	{
		p1 = &two;
		p2 = &one;
	}
	for (int i = 0; 1; i++)
	{
		(*p2)*= 1;
		dif++;
		if (p2 -> year == p1 -> year && p2 -> month == p1 -> month)
		{
			break;
		}
	}

	return dif;
}

int operator|(date one, date two)
{
	date *p1, *p2;
	int dif = 0;
	if (one == two)
	{
		cout << "Comparing the same date." << endl;
		return  0;
	}
	if (one.year == two.year)
	{
		return 0;
	}
	if (one.isOlder(two) == one)
	{
		p1 = &one;
		p2 = &two;
	}
	else
	{
		p1 = &two;
		p2 = &one;
	}
	while (p2 -> year != p1 -> year)
	{
		(*p2) &= 1;
		dif++;
	}
	return dif;
}

int operator%(date one, date two)
{
	return (one - two) / 7;
}

date easter(int y)
{
	int a, b, c, d, e, day, month;
	a = y % 4;
	b = y % 7;
	c = y % 19;
	d = (19 * c + 15) % 30;
	e = (2*a + 4*b - d + 34) % 7;
	month = (d + e + 114) / 31;
	day =  ((d + e + 114) % 31) + 1;
	date easter(day, month, y);
	easter += 13;
	return easter;

}

bool date::isWorking()
{
	for (int i = 0; i < 11; i++)
	{
		if (month == holidays[i].month && day == holidays[i].day)
		{
			return false;
		}
	}
	if (findWeekday() == 0 || findWeekday() == 6)
	{
		return false;
	}
	if (easter(year) - 2 == *this || easter(year) + 1 == *this)
	{
		return false;
	}
	return true;
}

date date::nearWorkday()
{
	int dir = 0;
	cout << "Please choose direction:\n0. Closest\n1. Forward\n2. Backward\n";
	cin >> dir;
	if (dir > 2 || dir < 0)
	{
		cout << "Incorrect choice. Setting direction to Closest." << endl;
		dir = 0;
	}
	switch (dir)
	{
	case 1:
		return shanoDay(*this, 1);
		break;
	case 2:
		return shanoDay(*this, 2);
		break;
	default:
		return shanoDay(*this, 0);
		break;
	}
}

void date::setWorking(bool other)
{
	working = other;
}

void date::setWR(bool other)
{
	workingResult = other;
}

void date::setPosoka()
{
	cout << "Please choose direction:\n0. Closest\n1. Forward\n2. Backward\n";
	cin >> posoka;
	if (posoka > 2 || posoka < 0)
	{
		cout << "Incorrect choice. Setting direction to Closest." << endl;
		posoka = 0;
	}
}

date::date(char * input, int y)
{
	year = y;
	working = false;
	workingResult = false;
	posoka = 0;
	int number = 0, _month = 0, weekday = 0;
	char numberm_first[] = {"first"}, numberm_second[] = {"second"}, numberm_third[] = {"third"}, numberm_fourth[] = {"fourth"}, numberm_last[] = {"last"};
	char numberg_first[] = {"First"}, numberg_second[] = {"Second"}, numberg_third[] = {"Third"}, numberg_fourth[] = {"Fourth"}, numberg_last[] = {"Last"};
	char daym_first[] = {"monday"}, daym_second[] = {"tuesday"}, daym_third[] = {"wednesday"}, daym_fourth[] = {"thursday"}, daym_fifth[] = {"friday"}, daym_sixth[] = {"saturday"}, daym_seventh[] = {"sunday"};
	char dayg_first[] = {"Monday"}, dayg_second[] = {"Tuesday"}, dayg_third[] = {"Wednesday"}, dayg_fourth[] = {"Thursday"}, dayg_fifth[] = {"Friday"}, dayg_sixth[] = {"Saturday"}, dayg_seventh[] = {"Sunday"};
	char monthm1[] = "january", monthm2[] = "february", monthm3[] = "march", monthm4[] = "april", monthm5[] = "may", monthm6[] = "june", monthm7[] = "july", monthm8[] = "august", monthm9[] = "september", monthm10[] = "october", monthm11[] = "november", monthm12[] = "december";
	char monthg1[] = "January", monthg2[] = "February", monthg3[] = "March", monthg4[] = "April", monthg5[] = "May", monthg6[] = "June", monthg7[] = "July", monthg8[] = "August", monthg9[] = "September", monthg10[] = "October", monthg11[] = "November", monthg12[] = "December";

	while (number == 0)
	{
		if (strstr(input, numberm_first) != NULL || strstr(input, numberg_first) != NULL)
		{
			number = 1;
			break;
		}
		if (strstr(input, numberm_second) != NULL || strstr(input, numberg_second) != NULL)
		{
			number = 2;
			break;
		}
		if (strstr(input, numberm_third) != NULL || strstr(input, numberg_third) != NULL)
		{
			number = 3;
			break;
		}
		if (strstr(input, numberm_fourth) != NULL || strstr(input, numberg_fourth) != NULL)
		{
			number = 4;
			break;
		}
		if (strstr(input, numberm_last) != NULL || strstr(input, numberg_last) != NULL)
		{
			number = 5;
			break;
		}
		else
		{
			cout << "No valid day." << endl;
			break;
		}
	}
	while (weekday == 0)
	{
		if (strstr(input, daym_first) != NULL || strstr(input, dayg_first) != NULL)
		{
			weekday = 1;
			break;
		}
		if (strstr(input, daym_second) != NULL || strstr(input, dayg_second) != NULL)
		{
			weekday = 2;
			break;
		}
		if (strstr(input, daym_third) != NULL || strstr(input, dayg_third) != NULL)
		{
			weekday = 3;
			break;
		}
		if (strstr(input, daym_fourth) != NULL || strstr(input, dayg_fourth) != NULL)
		{
			weekday = 4;
			break;
		}
		if (strstr(input, daym_fifth) != NULL || strstr(input, dayg_fifth) != NULL)
		{
			weekday = 5;
			break;
		}
		if (strstr(input, daym_sixth) != NULL || strstr(input, dayg_sixth) != NULL)
		{
			weekday = 6;
			break;
		}
		if (strstr(input, daym_seventh) != NULL || strstr(input, dayg_seventh) != NULL)
		{
			weekday = 7;
			break;
		}
		else
		{
			cout << "No valid weekday." << endl;
			break;
		}
	}
	while (_month == 0)
	{
		if (strstr(input, monthm1) != NULL || strstr(input, monthg1) != NULL)
		{
			_month = 1;
			break;
		}
		if (strstr(input, monthm2) != NULL || strstr(input, monthg2) != NULL)
		{
			_month = 2;
			break;
		}
		if (strstr(input, monthm3) != NULL || strstr(input, monthg3) != NULL)
		{
			_month = 3;
			break;
		}
		if (strstr(input, monthm4) != NULL || strstr(input, monthg4) != NULL)
		{
			_month = 4;
			break;
		}
		if (strstr(input, monthm5) != NULL || strstr(input, monthg5) != NULL)
		{
			_month = 5;
			break;
		}
		if (strstr(input, monthm6) != NULL || strstr(input, monthg6) != NULL)
		{
			_month = 6;
			break;
		}
		if (strstr(input, monthm7) != NULL || strstr(input, monthg7) != NULL)
		{
			_month = 7;
			break;
		}
		if (strstr(input, monthm8) != NULL || strstr(input, monthg8) != NULL)
		{
			_month = 8;
			break;
		}
		if (strstr(input, monthm9) != NULL || strstr(input, monthg9) != NULL)
		{
			_month = 9;
			break;
		}
		if (strstr(input, monthm10) != NULL || strstr(input, monthg10) != NULL)
		{
			_month = 10;
			break;
		}
		if (strstr(input, monthm11) != NULL || strstr(input, monthg11) != NULL)
		{
			_month = 11;
			break;
		}
		if (strstr(input, monthm12) != NULL || strstr(input, monthg12) != NULL)
		{
			_month = 12;
			break;
		}
		else
		{
			cout << "No valid month." << endl;
			break;
		}
	}
	if (_month < 1 || _month > 12)
	{
		cout << "Setting month to 1." << endl;
		_month = 1;
	}
	if (weekday < 1 || weekday > 7)
	{
		cout << "Setting weekday to 1." << endl;
		weekday = 1;
	}
	if (number < 1 || number > 5)
	{
		cout << "Setting day to 1." << endl;
		number = 1;
	}
	if (weekday == 7)
	{
		weekday = 0;
	}
	month = _month;
	date temp(1, month, year);
	while (temp.weekd != weekday)
	{
		temp++;
	}
	number--;
	if (number == 4)
	{
		temp ^= 5;
	}
	else
	{
		temp ^= number;
	}
	if (temp.month > _month)
	{
		while (temp.month != _month)
		{
			temp %= 1;
		}
	}
	if (temp.year > y)
	{
		while (temp.year != y)
		{
			temp %= 1;
		}
	}
	day = temp.day;
	month = temp.month;
	weekd = findWeekday();
}
