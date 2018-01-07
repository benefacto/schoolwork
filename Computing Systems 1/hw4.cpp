#include <exception>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <functional>
#include <list>
#include <math.h>
#include <queue>
#include <sstream>
#include <string>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

// holds cache configuration
struct cacheProperties
{
  int dataPortionSize;
  int blockSize;
  int associativity;
  /*
	0 for direct mapped
	1 for fully associative
	2 for 2-way
	4 for 4-way
  */
  int replacementPolicy;
  // 1 for LRU, 0 for no LRU

  // further properties to be computed by ProcessCache()
  int cacheSize;
  int tagLength;
  int indexLength;
  int offsetLength;
  // default constructor
  cacheProperties():dataPortionSize(0),
					blockSize(0),
					associativity(0),
					replacementPolicy(0),
					cacheSize(0),
					tagLength(0),
					indexLength(0),
					offsetLength(0)
  {}
};

// memory reference holds hex form as string
// and binary form as string
struct memoryReference
{
  string hexForm;
  string binaryForm;
};

// converts to binary
const char* hexCharToBin(char c)
{
  switch(toupper(c))
	{
	case '0': return "0000";
	case '1': return "0001";
	case '2': return "0010";
	case '3': return "0010";
	case '4': return "0100";
	case '5': return "0101";
	case '6': return "0110";
	case '7': return "0111";
	case '8': return "1000";
	case '9': return "1001";
	case 'A': return "1010";
	case 'B': return "1011";
	case 'C': return "1100";
	case 'D': return "1101";
	case 'E': return "1110";
	case 'F': return "1111";
	default:
	  cout << "Error: hexCharToBin default\n";
	  return "ZZZZ";
	}
}

// helper function for converting hex to binary
string hexCharToBinString(const string& hex)
{
  string bin;
  // start at 2 to eliminate "0x" portion of hex
  for(unsigned i = 2; i != hex.length(); i++)
	{
	  bin += hexCharToBin(hex[i]);
	}
  return bin;
}

// converts a string of binary to an integer
int binStringToInt(const string& bin)
{
  int number = 0;
  int powerNumber = bin.length()-1;

  if(powerNumber < 1)
	{
	  cout << "Error: powerNumber < 1\n";
	  return -1;
	}
  else
	{
	  for(unsigned i = 0; i < bin.length(); i++)
		{
		  number += int(bin[i])*int(pow(2,double(powerNumber)));
		  powerNumber--;
		}
	}

  return number;
}

// converts a single character hex string to an integer
int hexCharToInt(char c)
{
  switch(toupper(c))
	{
	case '0': return 0;
	case '1': return 1;
	case '2': return 2;
	case '3': return 3;
	case '4': return 4;
	case '5': return 5;
	case '6': return 6;
	case '7': return 7;
	case '8': return 8;
	case '9': return 9;
	case 'A': return 10;
	case 'B': return 11;
	case 'C': return 12;
	case 'D': return 13;
	case 'E': return 14;
	case 'F': return 15;
	default:
	  cout << "Error: hexStringToInt default\n";
	  return 99;
	}
}

int hexStringToInt(const string& hex)
{
  int number;
  // start at 2 to eliminate "0x" portion of hex
  for(unsigned i = 2; i != hex.length(); i++)
	{
	  number += hexCharToInt(hex[i]);
	}
  return number;
}


// returns tag from binary string
string getTag(string binary, int tagLength)
{
  string tag = "";
  for (int i = 0; i < tagLength; i++)
	{
	  tag += binary[i];
	}
  return tag;
}

// reads cache config file to determine parameters
void ReadConfigFile(char *fileAddress, cacheProperties *current)
{
  ifstream file;
  string line;
  int index = 0;
  file.exceptions(ifstream::badbit);
  file.open(fileAddress);

  while(getline(file,line))
	{
	  istringstream iss(line);

	  if (index == 0)
		{
		  iss >> current->dataPortionSize;
		}
	  else if (index == 1)
		{
		  iss >> current->blockSize;
		}
	  else if (index == 2)
		{
		  iss >> current->associativity;
		}
	  else
		{
		  iss >> current->replacementPolicy;
		}
	  index++;
	}
  file.close();
}

// read trace file to create queue of memeoryReference
void ReadTraceFile(char *fileAddress, queue<memoryReference> *references)
{
  ifstream file;
  memoryReference current;
  string line;
  file.exceptions(ifstream::badbit);
  file.open(fileAddress);

  while(getline(file,line))
	{
	  current.hexForm = line;
	  current.binaryForm = hexCharToBinString(line);
	}
  file.close();
}

// print output
void Output(string hex, bool hitMiss)
{
  string hitMissStr;

  if(hitMiss == true)
	{
	  hitMissStr = "hit";
	}
  else
	{
	  hitMissStr = "miss";
	}

  cout << hex << "\t" << hitMissStr;
}

// process trace file in direct-mapped cache
void DirectMappedCache(cacheProperties *properties, queue<memoryReference> *references)
{
  deque<string> *cache = new deque<string>();
  deque<string>::iterator nth;
  memoryReference current;
  int setIndex = 0;
  string setIndexBin = "";
  bool hitMiss = false;

  // initialize cache to empty
  for (int i = 0; i < properties->cacheSize; i++)
	{
	  cache->push_back("empty");
	}

  while(references->empty() != true)
	{
	  current = references->front();
	  references->pop();
	  // get setIndex
	  for (int i = properties->tagLength-1; i < properties->indexLength; i++)
		{
		  setIndexBin += current.binaryForm;
		}
	  setIndex = binStringToInt(setIndexBin);
	  nth = cache->begin() + setIndex;

	  // add to cache and output
	  if (cache->at(setIndex) == "empty")
		{
		  cache->insert(nth,getTag(current.binaryForm,properties->tagLength));
		  hitMiss = false;
		  Output(current.hexForm,hitMiss);
		}
	  else
		{
		  cache->insert(nth,getTag(current.binaryForm,properties->tagLength));
		  hitMiss = true;
		  Output(current.hexForm,hitMiss);
		}
	}
	 
  delete cache;
}


// process trace file in fully associative cache
void FullyAssociativeCache(cacheProperties *properties, queue<memoryReference> *references)
{

}

// process trace file in two-way cache
void TwoWayCache(cacheProperties *properties, queue<memoryReference> *references)
{

}

// process trace file in four-way cache
void FourWayCache(cacheProperties *properties, queue<memoryReference> *references)
{

}


// construct cache parameters and trigger correct cache function
void ProcessCache(cacheProperties *properties, queue<memoryReference> *references)
{
  if(properties->blockSize <= 0)
	{
	  cerr << "Error: properties->blockSize = "
		   << properties->blockSize << "\n" ;
	  return;
	}
  
  properties->cacheSize = (properties->dataPortionSize)/(properties->blockSize);

  if (properties->cacheSize <= 0)
	{
	  cerr << "Error: cacheSize = "
		   << properties->cacheSize << "\n";
	  return;
	}
  
  // determine offset - assuming always 4 bytes per word
  //properties->offsetLength = int(log2(double(4)));

  // determine indexLength
  if (properties->associativity == 1)
	{
	  // no index for fully associative
	  properties->indexLength = 0;
	}
  else if(properties->associativity == 0)
	{
	  properties->indexLength = int(log2(double(properties->cacheSize)));
	}
  else
	{
	  properties->indexLength = int(log2(double(properties->cacheSize * properties->associativity)));
	}

  // determine tagLength, assuming address always 32-bit length
  properties->tagLength = 32 - properties->indexLength - properties->offsetLength;

  // call cache function
  switch(properties->associativity)
	{
	case 0: DirectMappedCache(properties,references);
	  break;
	case 1: FullyAssociativeCache(properties,references);
	  break;
	case 2: TwoWayCache(properties,references);
	  break;
	case 4: FourWayCache(properties,references);
	  break;
	default:
	  cout <<"Error: properties->associativity isn't valid\n";
	}
}

// main function, entry point
int main(int argc, char *argv[])
{
  cacheProperties *cache = new cacheProperties();
  queue<memoryReference> *references = new queue<memoryReference>();

  // checks if 2 arguments: config file & trace file
  if (argc != 3)
	{
	  cerr << "Invalid number of command line arguments: " << argc << "\n"
		   << "First argument should be config file, second argument"
		   << " should be trace file."
		   << "\n";
	  return 0;
	}
  // calls read file and handles exception in opening/reading
  else
	{
	    try
		  {
			ReadConfigFile(argv[2],cache);
			ReadTraceFile(argv[3],references);
		  }
		catch(ifstream::failure e)
		  {
			cerr << "Exception opening/reading file"
			     << "\n";
			return 0;
		  }
	}
  // begin processing cache
  ProcessCache(cache,references);
  delete cache;
  delete references;
}
