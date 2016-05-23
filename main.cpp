#include <iostream>
#include <algorithm>

using namespace std;

const int SIZE = 8;

int main(){
   int intArray[SIZE] = {5, 3, 32, -1, 1, 104, 53,54};

    //call sort function
    sort(intArray, intArray + SIZE);

	//show sorted array
    cout << "Sorted Array: " << endl;
    for (size_t i = 0; i != SIZE; ++i)
        cout << intArray[i] << " ";

   return 0;
}



