#include <iostream>
#include <algorithm>  	
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <fstream>
#include <string> 
#include <sstream>

using namespace std;

#define TOTAL_NUMBER 1000000

int main(){
	const int size = TOTAL_NUMBER / 2; 	//size of array	
	int pos = 0;			// index of array
	int c;					// store int  
	int arr[size]; 			// store numbers

	//Read file and write first half to "firsthalf.txt", store second half to array
	FILE *file = fopen("input.txt", "r"); //Open file
	if (file) {
		//write first half to "firsthalf.txt"
		//store first half to array
		while (!feof(file) && pos < size)
		{
			fscanf(file, "%d", &c);		//Read an int  
			arr[pos++] = c; 				//push to array 	  
		}
		//sort array
		sort(arr, arr + size);
		//write array to file
		ofstream outfile;
		outfile.open("firsthalf.txt", ios::out | ios::app | ios::binary);
		int i = 0;
		for (; i < size; i++){
			outfile << arr[i] << " ";
		}
		outfile.close();

		//store second half to array
		pos = 0;
		while (!feof(file) && pos < size)
		{
			fscanf(file, "%d", &c);		//Read an int  
			arr[pos++] = c; 				//push to array 	  
		}
		//sort array
		sort(arr, arr + size);

		fclose(file);
	}

	//merge two half and write to result file
	FILE *first_half = fopen("firsthalf.txt", "r"); //Open file
	if (first_half){
		int i = 0;						//index of arr
		ofstream outfile;
		outfile.open("result.txt", ios::out | ios::app | ios::binary);
		while (!feof(first_half))
		{
			fscanf(first_half, "%d", &c);		//Read an int
			while (i < size && arr[i] <= c){
				outfile << arr[i++] << " ";		//put element of array to file until c < arr[i]
			}
			outfile << c << " ";
		}

		outfile.close();
	}

	cout << "Success! See result in result.txt";

	return 0;
}



