#include <map>
#include <vector>
#ifndef FUNC
#define FUNC
#include "raw_data.h"

typedef std::vector<data> ve_container;
typedef std::map<uint_16, std::vector<data> > sMap;
typedef std::map<uint_64, std::map<uint_16, std::vector<data> > > mMap;
typedef std::map<uint_64, std::map<uint_64, std::map<uint_16, std::vector<data> > > > bMap;


//typedef std::map<uint_64, std::map<uint_64, data>  > dataInMap;


void get(bMap & , const uint_64 &, const uint_64 &, const uint_16 &, const uint_16 &, const uint_16 &);
void clicked(bMap & p, const uint_64 &);
void impressed(bMap & , const uint_64 &, const uint_64 &);
void profit(bMap &, const uint_16 &, const double &);
void quit();
#endif
