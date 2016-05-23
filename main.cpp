#include <iostream>
#include <algorithm>  	
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <fstream>
#include <string> 
#include <sstream>

using namespace std; 

int main(){
	const int size = 2500; 	//size of an vector
	int pos = 1;			// indices of vector
    int c;					// store char
	int i=0;				// use for for loop
	int index = 1;			// number of vector
    string str ="";			// store each number
    vector <int> arr; 		// store numbers
	
	// Read file input and write sorted array to other file
    FILE *file = fopen("input.txt", "r"); //Open file
    if(file) {
      do {  
          c = fgetc(file);			//Read a char
          if(c != EOF) {
          	if(c == 32 && str!=""){ //End a number (if char = ' ')
         		arr.push_back(atoi( str.c_str() )); //Convert to int and add to vector
				str = "";			//Set str empty to start new number
				pos++;				//increase indice
			}
			if(c != 32){			// if char != ' '
			  	str.push_back((char) c); //Add char to str
			}
		  }  
		  
          if(pos > size || c == EOF) { //If vector have enoungh element. Sort vector. Write to part file and coninue while loop
            sort(arr.begin(),arr.end()); // Sort vector
            
            //Create file name
            string file_name;
		    ostringstream oss;
			oss << "part" << index << ".txt";
			file_name = oss.str();  
			
			//Write file
			ofstream outfile;
			outfile.open (file_name.c_str(),ios::out | ios::app | ios::binary);
			for(i=0;i<arr.size();i++){
		    	outfile << arr[i] << " ";
			}
			outfile << "\n";
			outfile.close();
			
			index ++;
			arr.clear();
			str =  "";
			pos = 0;  
          }           
      } while(c != EOF); 
      fclose(file);           
    }
     
    
 	 
    return 0;
}



