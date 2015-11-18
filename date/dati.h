#ifndef DATI_H
#define DATI_H
#include <iostream>

class date	
{
private:
	int day, month, year, weekd, posoka;
	bool working, workingResult;

public:
	date();
	date(int, int, int);
	int findWeekday();
	int getDay();
	int getMonth();
	int getYear();
	int getWeekday();
	bool setDay(int);
	bool setMonth(int);
	bool setYear(int);
	friend std::istream& operator>> (std::istream&, date&);
	friend std::ostream& operator<< (std::ostream&, date&);
	bool isLastDay();
	friend date operator+(date, int);
	friend date operator++(date&);
	friend date operator+=(date&, int);
	friend date operator-(date, int);
	friend date operator--(date&);
	friend date operator-=(date&, int);
	friend date operator*(date, int);
	friend date operator*=(date&, int);
	friend date operator/(date, int);
	friend date operator/=(date&, int);
	friend date operator&(date, int);
	friend date operator&=(date&, int);
	friend date operator|(date, int);
	friend date operator|=(date&, int);
	friend date operator^(date, int);
	friend date operator^=(date&, int);
	friend date operator%(date, int);
	friend date operator%=(date&, int);
	friend bool operator==(date, date);
	date isOlder(date);
	friend int operator-(date, date);
	friend int operator/(date, date);
	friend int operator|(date, date);
	friend int operator%(date, date);
	bool isWorking();
	date nearWorkday();
	void setWorking(bool);
	void setWR(bool);
	void setPosoka();
	date(char *, int);

};


#endif DATI_H