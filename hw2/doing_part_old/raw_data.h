#ifndef RAW_DATA
#define RAW_DATA

typedef unsigned long long int uint_64;
typedef unsigned int uint_16;

//data type loaded from file
class data
{
public:
	uint_16 click;
	uint_16 impression;
	char displayURL[27];
	uint_64 adID;
	uint_16 advertiseID;
	uint_16 depth;
	uint_16 position;
	uint_16 queryID;
	uint_16 keywordID;
	uint_16 titleID;
	uint_16 descriptionID;
	uint_64 userID;
	bool operator ==(const data &);
};

//print function
void printf_data(data* ptr);

#endif