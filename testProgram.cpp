// Testprogram för Arrayclassen
// David Hegardt 2016-02-10
// --------------------------------------------------------------------------------
#include "arrayheader.h"
#include "Timer.h"
#include <iostream>
#include <algorithm>
#include <random>
#include <ctime>
#include <vector>
#include <array>
using namespace std;

int main()
{
	default_random_engine generator(static_cast<unsigned>(time(0))); // Skickar in time som seed
	// Deklarera och initiera vektor och objekt
	
	vector<double> bubbleVec;
	vector<double> insertVec;
	vector<double> quickVec;
	vector<double> selectVec;
	//IntArray a1;
	
	const size_t MAX_SIZE1 = 5000;
	size_t antal = 1;
	int i = 0;
	antal = MAX_SIZE1;
	cout << "Number of values:" << MAX_SIZE1 << endl;

	Timer bubbleTimer;
	Timer insertTimer;
	Timer quickTimer;
	Timer selectTimer;
	vector<double> tmpVecBubble;
	vector<double> tmpVecInsert;
	vector<double> tmpVecQuick;
	vector<double> tmpVecSelect;
	vector<double> v1;
	vector<double> v2;
	vector<double> v3;
	vector<double> v4;
	IntArray a1(MAX_SIZE1*i);
	
	
	
	for (i = 1; i < 9; i++) {			// loopa 8 gånger för varje arraystorlek
		IntArray zero(MAX_SIZE1*i);
		IntArray a1(MAX_SIZE1*i);
		
		for (int j = 1; j < 11; j++) {		// loopa 10 gånger för varje mätning
											// Slumpa tal
			
			a1.randomFill(generator);
			cout << " **************** Test Number :" << j << " ********************** " << endl;
			cout << "Osorterad:";
			cout << endl;
			IntArray aRandom;
			aRandom = a1;				// Spara slumpade tal i arrayen aRandom

										//a1.printArray(a1); //< --- kommentera bort för att se arrayen utskriven
		
			// Använd bubbleSort2
			bubbleTimer.start();		// Starta timer
			a1.bubbleSort2(a1,MAX_SIZE1*i);		// anropa sorteringsfunktion
			cout << "Sorterad med BubbleSort2:" << endl;
			cout << "SorteringsTid = " << bubbleTimer.stop() / 1000000 << " [s]" << endl;
			tmpVecBubble.push_back(bubbleTimer.stop() / 1000000);		// Lägg in timad tid i vektor
			cout << "ArrayStorlek = " << antal*i << endl;
		

			a1 = aRandom;			// Lägg tillbaka slumpade värden i arrayen
			cout << endl;
			
			// Använd insertSort
			insertTimer.start();		// Starta timer
			a1.insertSort(a1, MAX_SIZE1*i);			// anropa sorteringsfunktion
			cout << "Sorterad med InsertSort:" << endl;
			cout << "SorteringsTid = " << insertTimer.stop() / 1000000 << " [s]" << endl;
			tmpVecInsert.push_back(insertTimer.stop() / 1000000);		// Lägg in timad tid i vektor
			cout << "ArrayStorlek = " << antal*i << endl;
			
			a1 = aRandom;			// Lägg tillbaka slumpade värden i arrayen
			cout << endl;
			
			// Använd QuickSort
			quickTimer.start();			// Starta timer
			a1.q1(a1, MAX_SIZE1*i);			// anropa sorteringsfunktion
			cout << "Sorterad med QuickSort:" << endl;
			cout << "SorteringsTid = " << quickTimer.stop() / 1000000 << " [s]" << endl;
			tmpVecQuick.push_back(quickTimer.stop() / 1000000);			// Lägg in timad tid i vektor
			cout << "ArrayStorlek = " << antal*i << endl;
			//a1.printArray(a1, MAX_SIZE*i);

			a1 = aRandom;			// Lägg tillbaka slumpade värden i arrayen
			cout << endl;
			
			// Använd selectSort
			selectTimer.start();		// Starta timer
			a1.selectSort(a1, MAX_SIZE1*i);			// Select sort (Urvalssortering)
			cout << "Sorterad med SelectSort:" << endl;
			cout << "SorteringsTid = " << selectTimer.stop() / 1000000 << " [s]" << endl;
			tmpVecSelect.push_back(selectTimer.stop() / 1000000);		// Lägg in timad tid i vektor
			cout << "ArrayStorlek = " << antal*i << endl;


			a1 = zero;		// Nollställ array
			

		}
		speedRun(tmpVecBubble, tmpVecInsert, tmpVecQuick, tmpVecSelect, MAX_SIZE1,i,v1,v2,v3,v4);

	}

	system("pause");
	return 0;
}