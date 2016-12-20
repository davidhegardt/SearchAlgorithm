//------------------------------------------------------------------------------
//  arrayheader.h
//  Headerfil till klassen IntArray
//  David Hegardt 2015-02-15
//------------------------------------------------------------------------------
#ifndef arrayheaderH
#define arrayheaderH
#include <vector>
#include <string>
#include <random>
using namespace std;
class IntArray
{
private:
	int *arr;       // Pekare till arrayen
	size_t maxSize;    // Arrayens maximala storlek
	size_t size;       // IntArrayens aktuella storlek 

public:
	// Konstruktorer och destruktor
	IntArray();
	IntArray(int pNum);
	IntArray(const IntArray &a);
	~IntArray();
	// Get- och set-funktioner
	size_t getMaxSize() const { return maxSize; }
	size_t getSize() const { return size; }
	int getValue(int idx) const;
	
	bool addValue(int value);
	void randomFill(default_random_engine pGenerator);
	void deleteArray();
	//Sorteringsfunktioner
	void bubbleSort2(IntArray &a1,int n);
	void insertSort(IntArray &a1,int n);
	void q1(IntArray &a1, int n);
	void quick1(IntArray &a1, int first, int last);
	void selectSort(IntArray &a1, int n);
	void printArray(IntArray &a1);
	
	// Överlagringsfunktioner
	const IntArray &operator=(const IntArray &a);
	int &operator[](int i);
	int operator[](int i) const;
};
// Hanterar skrivning till fil
void writeToFile(vector<double> &v1, vector<double> &v2, vector<double> &v3, vector<double> &v4);


// Sparar tider
void speedRun(vector<double> &tmpVecBubble, vector<double> &tmpVecInsert, vector<double> &tmpVecQuick,
	vector<double> &tmpVecSelect, const size_t MAX_SIZE1, int i, vector<double> &v1,
	vector<double> &v2, vector<double> &v3, vector<double> &v4);

#endif
