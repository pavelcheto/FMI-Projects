/*
 * rle.h
 *
 *  Created on: Jun 2, 2014
 *      Author: pavelcheto
 */

#ifndef RLE_H_
#define RLE_H_

#include <iostream>

struct one
{
	int number;
	char letter;
};

class rle
{
private:
	one *niz;
	int size, rsize;
public:
	rle(char *);
	rle();
	~rle();
	rle(const rle &copy);
	rle &operator=(const rle &other);
	void print_decoded();
	friend std::ostream& operator<< (std::ostream&, const rle&);
	char const& operator[](int);
	rle& operator++();
	rle operator++(int);
	rle& operator--();
	rle operator--(int);
	rle operator+(rle) const;
	rle operator+=(rle);
	rle operator()(int, int);
	rle operator()(int, rle);
	rle delete_f(int, int);
	bool operator==(rle);
	bool operator!=(rle);
	bool operator>(rle);
	bool operator>=(rle);
	bool operator<(rle);
	bool operator<=(rle);
	rle operator*();
	friend bool findLetter(char, rle);
};


#endif /* RLE_H_ */
