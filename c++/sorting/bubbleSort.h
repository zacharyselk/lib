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

#include <iostream>

// A simple implementation of bubble sort, it will only accept intager arrays
// and it will sort the entire array in assending order
void bubbleSort_simple(int array[], int length)
{
  // A temporary storage for when we need to swap elements of the array
  int temp;

  // If the length is 0 or 1, then the "array" is already sorted
  if(length <= 1)
    return;
  
  // Uses the loop with count to repeat n times, the nested loop will iterate
  // through the n-1 pairs swapping when the left element is greater than the
  // right element
  for(int count = 0; count < length; ++count)
    for(int index = 1; index < length; ++index)
      if(array[index-1] > array[index])
	{
	  // Using the temporary varable for storage, swaps
	  // array[index] & array[index-1]
	  temp = array[index-1];
	  array[index-1] = array[index];
	  array[index] = temp;
	}
}



// This is a more complicated and generalized implementation of bubble sort
template<typename T>
void bubbleSort(T &arrayBegining, T &arrayEnd, bool verbose=false)
{
  int dataSize = 1;
  unsigned int arrayLength = &arrayEnd - &arrayBegining + dataSize;

  // Debugging information, show the array given as it sees it
  if(verbose)
    {
      std::cout << "Running Bubble sort\nThe given array:\n";
      for(int i = 0; i < arrayLength; ++i)
	std::cout << *(&arrayBegining+i*dataSize) << ' ';
      std::cout << "\n\n";
    }
  
  // If the array is empty or has one element, then it is already sorted
  if(arrayLength <= 1)
      return;

  for(int counter = 0; counter < arrayLength; ++counter)
    for(int iterator = 1; iterator < arrayLength; ++iterator)
      if(*(&arrayBegining+iterator*dataSize) <
	 *(&arrayBegining+(iterator-1)*dataSize))
	{
	  // More info than needed for verbose
	  /*
	  // Debugging information, prints each swap that is made
	  if(verbose)
	    {
	      std::cout << "Swapping the elements at indexes " << iterator-1
			<< " and " << iterator << ":\n"
			<< *(&arrayBegining+(iterator-1)*dataSize) << " > "
			<< *(&arrayBegining+iterator*dataSize) << "\n\n";
	    }
	  */

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

  // Debuggin information, displays the final (sorted) array
  if(verbose)
    {
      std::cout << "The final array:\n";
      for(int i = 0; i < arrayLength; ++i)
	std::cout << *(&arrayBegining+i*dataSize) << ' ';
      std::cout << "\n\nPress enter to continue";

      std::string empty;
      getline(std::cin, empty);
      std::cout << "\n\n";
    }
}

#endif
