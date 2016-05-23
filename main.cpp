#include <iostream>
#include <algorithm>  	
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <fstream>
#include <string> 
#include <sstream>

using namespace std; 
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
int main(){
	
	const int size = 2500; 	//size of an vector
	vector <int> arr; 		// store numbers
	int i = 1;
	
	//Divide input file to 4 sorted file
	for(i=1; i<=4; i++){
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
		outfile << "\n";
		outfile.close();	
	}
    return 0;
}



