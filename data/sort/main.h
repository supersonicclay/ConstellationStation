

#ifndef MAIN_H
#define MAIN_H


struct entry_t
{
	float mag;
	char line[600];
	bool operator< (entry_t& other)
	{ return mag < other.mag; }
};


#endif