/*
 * base64.h
 *
 *  Created on: Jun 5, 2014
 *      Author: pavelcheto
 */

#ifndef BASE64_H_
#define BASE64_H_

#include <iostream>

class base64
{
private:
	char * niz;
	static const char table[65];
	int size, rsize;
	bool isEncoded;

public:
	base64();
	base64(char *);
	void addLetter(char);
	base64(const base64 &);
	base64 &operator=(const base64 &);
	~base64();
	void encode();
	void decode();
	int findPos(char);
	char operator[](int);
	friend std::ostream& operator<<(std::ostream&, const base64&);
	const base64 operator+(base64);
	base64 operator+=(base64);
	base64 operator()(int, int);
	base64 operator()(int, base64);
	base64 delete_f(int, int);
	base64 cmp(int, int);
	bool operator<(base64);
	bool operator<=(base64);
	bool operator>(base64);
	bool operator>=(base64);
};


#endif /* BASE64_H_ */
