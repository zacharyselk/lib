// Bubble sort is one of the simplest sorting methods there is, it is very
// intuitive, but also ineffeciant. Bubble sort will compair each of the n-1
// ajacent pairs, swapping them if the left element is greater than the right
// element. Repeating this process n times to ensure that the list is fully
// sorted.
//
// Bubble sort will allways perform (n-1)*n equality checks and between 0 and
// (n-1)*n swap operations, making this a O(n^2) algorithm

#ifndef LIB_BUBBLE_SORT_H
#define LIB_BUBBLE_SORT_H

#include<iostream>

template<typename T>
void bubbleSort(T &arrayBegining, T &arrayEnd, bool verbose=false)
{
  int dataSize = 1;
  unsigned int arrayLength = &arrayEnd - &arrayBegining + dataSize;

  if(verbose)
    {
      std::cout << "The current array:\n";
      for(int i = 0; i < arrayLength; ++i)
	std::cout << *(&arrayBegining+i*dataSize) << ' ';
      std::cout << "\n\n";
    }
  
  // If the array is empty, then it is already sorted
  if(arrayLength == 0)
      return;

  for(int counter = 0; counter < arrayLength; ++counter)
    for(int iterator = 1; iterator < arrayLength; ++iterator)
      if(*(&arrayBegining+iterator*dataSize) <
	 *(&arrayBegining+(iterator-1)*dataSize))
	{
	  if(verbose)
	    {
	      std::cout << "Swapping the elements at indexes " << iterator-1
			<< " and " << iterator << ":\n"
			<< *(&arrayBegining+(iterator-1)*dataSize) << " > "
			<< *(&arrayBegining+iterator*dataSize) << "\n\n";
	    }
	  
	  // Swap the elements using bitwise "exclusive or"
	  *(&arrayBegining+iterator*dataSize) =
	    *(&arrayBegining+iterator*dataSize) ^
	    *(&arrayBegining+(iterator-1)*dataSize);
	  
	  *(&arrayBegining+(iterator-1)*dataSize) =
	    *(&arrayBegining+iterator*dataSize) ^
	    *(&arrayBegining+(iterator-1)*dataSize);
	  
	  *(&arrayBegining+iterator*dataSize) =
	    *(&arrayBegining+iterator*dataSize) ^
	    *(&arrayBegining+(iterator-1)*dataSize);
	}

  if(verbose)
    {
      std::cout << "The final array:\n";
      for(int i = 0; i < arrayLength; ++i)
	std::cout << *(&arrayBegining+i*dataSize) << ' ';
      std::cout << "\n\n";
    }
}

#endif
