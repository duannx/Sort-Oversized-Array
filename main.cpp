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
vector <int> get_data(string file_name, int start_position, int size){
	int pos = 0;			// indices of vector
    int c;					// store char 
    string str ="";			// store each number
    vector <int> arr; 		// store numbers
	FILE *file = fopen(file_name.c_str(), "r"); //Open file
	 if(file) {
      do {  
          c = fgetc(file);			//Read a char
          if(c != EOF) {
          	if(c == 32 && str!=""){ //End a number (if char = ' ')
          		if(pos >= start_position)
         			arr.push_back(atoi( str.c_str() )); //Convert to int and add to vector
				str = "";			//Set str empty to start new number
				pos++;				//increase indice
			}
			if(c != 32){			// if char != ' '
			  	str.push_back((char) c); //Add char to str
			}
		  }  
		  
          if(pos > size + start_position - 1 || c == EOF) { //If vector have enoungh element. Sort vector. Write to part file and coninue while loop
            break;
          }           
      } while(c != EOF); 
      fclose(file);   
	        
    }
    return arr;
     
}

void merge_file(string first_file, string second_file, string out_file, int size_of_part, int num_of_part){
	vector <int> arr1, arr2;					// store data from two file
	int num1 =1, num2 = 1;						//number of part
	
	//Get data
	arr1 = get_data(first_file,0,size_of_part);	
	arr2 = get_data(second_file,0,size_of_part);
	
	//Write file
	ofstream outfile;
	outfile.open (out_file.c_str(),ios::out | ios::app | ios::binary); 
		
	while(arr1.size() > 0 && arr2.size() > 0){
		//Choose the smaller element and write to file
		if(arr1[0] <= arr2[0]){
			outfile << arr1[0] << " ";
			arr1.erase(arr1.begin());
		}else{
			outfile << arr2[0] << " ";
			arr2.erase(arr2.begin());
		}	
		
		if(arr1.size() == 0){
			if(num1 == num_of_part){ // all element of first_file were used
				while(arr2.size() > 0 && num2 <= num_of_part){
					outfile << arr2[0] << " ";
					arr2.erase(arr2.begin());
					if(arr2.size() == 0 && num2 < num_of_part){
						arr2 = get_data(second_file,(num2 - 1)*size_of_part,size_of_part);
						num2++;
					}
				}
				break;
			}
			else{
				num1++;
				arr1 = get_data(first_file,(num1 - 1)*size_of_part,size_of_part);
				
			}			
		}
		if(arr2.size() == 0){
			if(num2 == num_of_part){ // all element of first_file were used
				while(arr1.size() > 0 && num1 <= num_of_part){
					outfile << arr1[0] << " ";
					arr1.erase(arr1.begin());
					if(arr1.size() == 0 && num1 < num_of_part){
						arr1 = get_data(first_file,(num1 - 1)*size_of_part,size_of_part);
						num1++;
					}
				}
				break;
			}
			else{
				num2++;
				arr2 = get_data(second_file,(num2 - 1)*size_of_part,size_of_part);
				
			}			
		}
	}
	outfile.close();
}

int main(){
	
	const int size = TOTAL_NUMBER / 2; 	//size of an vector
	vector <int> arr; 		// store numbers
	int i = 1;
	
	//Divide input file to 4 sorted file
	for(i=1; i<=2; i++){
		arr.clear();
		//Get data
		arr = get_data("input.txt",(i-1)*size,size);
		sort(arr.begin(),arr.end());
		//Create file name
        string file_name;
		ostringstream oss;
		oss << "part" << i << ".txt";
		file_name = oss.str();
		
		//Write file
		ofstream outfile;
		outfile.open (file_name.c_str(),ios::out | ios::app | ios::binary);
		int j = 0;
		for(j=0;j<arr.size();j++){
		   	outfile << arr[j] << " ";
		} 
		outfile.close();	
	}
    arr.clear(); 
    
    merge_file("part1.txt","part2.txt","result.txt",TOTAL_NUMBER / 4,2); 
	return 0;
}



