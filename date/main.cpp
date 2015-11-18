#include "dati.h"
#include <iostream> 

using namespace std;



int main()
{
	date asd(31, 1, 2012);
	cout << "Weekday: " << asd.getWeekday() << endl;
	date bsd;
	cin >> bsd;
	cout << bsd << endl;
	date csd("last monday of may", 2014);
	cout << "String date: " << endl << csd << endl;
	asd *= 1;
	cout << "Added month: " << endl << asd << endl;
	cout << "Differnce in days: " << asd - csd << endl << endl;
	date dsd(31, 5, 2014);
	cout << "Nearest workday: "<< endl;
	cout << dsd.nearWorkday() << endl;
	date esd(15, 4, 2014);
	esd.setWorking(true);
	esd += 4;
	cout << "Calculated with working dates only: " << endl << esd << endl;
	date fsd(15,4, 2014);
	fsd.setWR(true);
	fsd.setPosoka();
	cout << "Calculated with last working day: " << endl;
	cout << fsd + 4 << endl;

	return 0;
}
