//------------------------------------------------------------------------------
//  ArrayClass.cpp ver 4
//  Definitionsfil till klassen IntArray
//  David Hegardt  2015-02-14
//------------------------------------------------------------------------------
#include "arrayheader.h"
#include "Timer.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <sstream> 
#include <random>
#include <ctime>
using namespace std;

//---------------------------------------------------------------------------
// Förvald konstruktor
//---------------------------------------------------------------------------
IntArray::IntArray() : maxSize(0), size(0)
{
	arr = nullptr;
}
int sum(IntArray const &a);
//---------------------------------------------------------------------------
// Initieringskonstruktor
// Initierar datamedlemmen num med initieringslista och allokerar plats
// för IntArrayen(arr)vilken initieras i funktionskroppen
//---------------------------------------------------------------------------
IntArray::IntArray(int pMaxSize) : maxSize(pMaxSize), size(0)
{
	arr = new int[maxSize];
}

//---------------------------------------------------------------------------
// Kopieringskonstruktor
//---------------------------------------------------------------------------
IntArray::IntArray(const IntArray &a) : maxSize(a.maxSize), size(a.size)
{
	arr = new int[a.maxSize];
	for (int i = 0; i<a.size; i++)
		arr[i] = a.arr[i];
}

//---------------------------------------------------------------------------
// Destruktor
//---------------------------------------------------------------------------
IntArray:: ~IntArray()
{
	delete[] arr;
	arr = NULL;
	cout << endl << "Running destructor for IntArray with maxSize= " << maxSize << endl;
}
void IntArray::deleteArray()
{
	delete[] arr;
}
//---------------------------------------------------------------------------
// Hämta värde från element med index idx
//---------------------------------------------------------------------------
int IntArray::getValue(int idx) const
{
	return arr[idx];
}

//---------------------------------------------------------------------------
// Lägg in ett heltal på första lediga plats i arrayen
// Testa så att det finns plats innan värdet läggs till i arrayen!
//---------------------------------------------------------------------------
bool IntArray::addValue(int value)
{
	bool valueAdded = false;
	if (size < maxSize)
	{
		arr[size] = value;
		size++;
		valueAdded = true;
	}
	return valueAdded;
}

//---------------------------------------------------------------------------
// Överlagring av tilldelningsoperatorn
//---------------------------------------------------------------------------
const IntArray &IntArray::operator=(const IntArray &a)
{
	if (this != &a)
	{
		delete[]arr;
		arr = new int[a.maxSize];
		maxSize = a.maxSize;
		size = a.size;
		for (int i = 0; i < a.size; i++)
			arr[i] = a.arr[i];
	}
	return *this;
}

// Överlagring av index operatorn
// ---------------------------------------------------------------------------
int& IntArray::operator[] (int idx)
{
	return arr[idx];
}

int IntArray::operator[] (int idx) const
{
	return arr[idx];
}

// RandomFill - fyller array med maxSize - 1 antal tal
// ----------------------------------------------------------------------------
void IntArray::randomFill(default_random_engine pGenerator)
{
	size = 0; // nollställer size innan varje körning
	uniform_int_distribution<int> random(0, maxSize - 1);
	while (addValue(random(pGenerator)));

}



// PrintArray - skriver ut arrayen
// ---------------------------------------------------------------------------
void IntArray::printArray(IntArray &a1)
{
	for (int i = 0; i < maxSize; i++)
	{
		cout << " " << a1.getValue(i);
	}
	cout << endl;
}

// Sorteringsfunktioner
// -----------------------------------------------------------------------------

// Swap - för att byta ett tal till ett annat
// -----------------------------------------------------------------------------
void swap(int &a, int &b)
{
	int tmp = a;
	a = b;
	b = tmp;
}


//------------------------------------------------------------------------------
// Bubblesort 2
//------------------------------------------------------------------------------
void IntArray::bubbleSort2(IntArray &a1, int n)
{
	bool sorted = false;
	for (int pass = 0; pass < n - 1 && !sorted; pass++)
	{
		sorted = true;
		for (int i = 0; i < n - 1; i++)
		{
			if (a1[i] > a1[i + 1])           // Jämför elementen i och i+1
			{
				swap(a1[i], a1[i + 1]);        // Byt plats om element i > element i+1
				sorted = false;
			}
		}
	}
}

//-----------------------------------------------------------------------------
// insertSort
//-----------------------------------------------------------------------------
void IntArray::insertSort(IntArray &a1, int n)
{
	if (n > 1)
	{
		int save, j;
		for (int k = n - 1; k >= 0; k--)
		{
			j = k + 1;
			save = a1[k];
			while (j < n && save > a1[j])
			{
				a1[j - 1] = a1[j];
				j++;
			}
			a1[j - 1] = save;
		}
	}
}

//-----------------------------------------------------------------------------
// quick1
// QuickSort - sorterar snabbt
//-----------------------------------------------------------------------------
void IntArray::quick1(IntArray &a1, int first, int last)
{
	if (first < last)
	{
		int low = first;
		int high = last;
		if (a1[first] > a1[last])     // Place a sentinel in the position a[last ] !
			swap(a1[first], a1[last]);

		do
		{
			// Gå från från början och sök första värdet som är större än a[first]
			do { low++; } while (a1[low] < a1[first]);

			// Gå från slutet och sök första värdet som är mindre än a[first]
			do { high--; } while (a1[high] > a1[first]);

			// Byt plats på a[low] och a[high] om low < high
			if (low < high)
				swap(a1[low], a1[high]);
		} while (low <= high);            // Fortsätt tills low > high 

		swap(a1[first], a1[high]);        // Placera a[first] i sorterad position

		quick1(a1, first, high - 1);                // Sortera vänster dellista 
		quick1(a1, high + 1, last);                 // Sortera höger dellista
	}
}

//-----------------------------------------------------------------------------
// q1
// a1 är Array objektet som ska sorteras
// n är antal element i arrayen
//-----------------------------------------------------------------------------
void IntArray::q1(IntArray &a1, int n)
{
	quick1(a1, 0, n - 1);
}

//-----------------------------------------------------------------------------
// selectSort
//-----------------------------------------------------------------------------
void IntArray::selectSort(IntArray &a1, int n)
{
	for (int i = 0; i < n - 1; i++)
	{
		int smallIdx = i;             //Index för det minsta elementet till höger om pos i
		for (int j = i + 1; j < n; j++)  // Leta rätt på det minsta "osorterade" elementet
			if (a1[j] < a1[smallIdx])
				smallIdx = j;             // Spara index för det minsta elementet 
		if (smallIdx != i)             // Byt plats om det fanns något mindre än a[i]
			swap(a1[i], a1[smallIdx]);
	}
}

// speedRun - tar emot 4 vektorer för att spara tider
// skapar en ny array för att lagra och sortera med olika storlekar
// ---------------------------------------------------------------------------------------------------

void speedRun(vector<double> &tmpVecBubble, vector<double> &tmpVecInsert, vector<double> &tmpVecQuick, vector<double> &tmpVecSelect, const size_t MAX_SIZE1, int i, vector<double> &v1, vector<double> &v2, vector<double> &v3, vector<double> &v4)
{


	// Medelvärde för Bubblesort
	double bubbleSum = 0;
	for (double n : tmpVecBubble)
	{
		bubbleSum += n;
	}
	double mBubble;
	mBubble = bubbleSum / (10);
	v1.push_back(mBubble);

	// Medelvärde för Insertsort
	double insertSum = 0;
	for (double n : tmpVecInsert)
	{
		insertSum += n;
	}
	double mInsert;
	mInsert = insertSum / (10);
	v2.push_back(mInsert);

	// Medelvärde för QuickSort
	double quickSum = 0;
	for (double n : tmpVecQuick)
	{
		quickSum += n;
	}
	double mQuick;
	mQuick = quickSum / (10);
	v3.push_back(mQuick);

	//Medelvärde för SelectSort
	double selectSum = 0;
	for (double n : tmpVecSelect)
	{
		selectSum += n;
	}
	double mSelect;
	mSelect = selectSum / (10);
	v4.push_back(mSelect);


	if (i == 8) {
		writeToFile(v1, v2, v3, v4);
	}
}

// writeToFile
// Tar emot 4 vektorer och skriver ut tidsvärden för respektive
// sorteringsalgoritm
// -----------------------------------------------------------
void writeToFile(vector<double> &v1, vector<double> &v2, vector<double> &v3, vector<double> &v4)
{
	const size_t antal = 5000;
	int it = 1;
	string filename = "sort.txt";
	fstream outFile(filename, ios::out);
	for (auto idx : v1)
	{
		outFile << "bubblesort" << char(9) << (antal*it) << char(9) << idx << endl;
		it++;
	}
	it = 1;
	for (auto idx : v2)
	{
		outFile << "insertsort" << char(9) << (antal*it) << char(9) << idx << endl;
		it++;
	}
	it = 1;
	for (auto idx : v3)
	{
		outFile << "quicksort" << char(9) << (antal*it) << char(9) << idx << endl;
		it++;
	}
	it = 1;
	for (auto idx : v4)
	{
		outFile << "selectsort" << char(9) << (antal*it) << char(9) << idx << endl;
		it++;
	}
	//	outFile.close();
}

//---------------------------------------------------------------------------
// sum
// Beräkna summa av elementen i arrayen a
//---------------------------------------------------------------------------
int sum(IntArray const &a)
{
	int s = 0;
	for (size_t i = 0; i < a.getSize(); i++)
		s += a.getValue(i);
	return s;
}



