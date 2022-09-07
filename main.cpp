// =================================================================
//
// File: main.cpp
// Author: Gamaliel Marines Olvera A01708746
// Date: 03/09/2022
//
// =================================================================
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include "header.h"
#include "search.h"
#include "bubble.h"
#include "selection.h"
#include "insertion.h"

using namespace std;

int main(int argc, char* argv[])
{
	//variables, vectors and files needed for the execution of the program
	int num_of_data;
	int num_of_searches;
	int num_of_comparisons_bubble;
	int num_of_comparisons_selection;
	int num_of_comparisons_insertion;
	
	vector<int> data_vec, search_data_vec;
	
	string data;
	string searched_data;
	
	//reads file
	ifstream input_file(argv[1], ios::in);
	//writes file
	ofstream output_file(argv[2], ios::out);

	//error management and validation
	if (argc != 3)
	{
		//if the number of data is larger than needed
		cout<<"Cannot be executed, number of arguments exceeds the need."<<argv[0]<<"\nFormat: <exe> <input.txt> <output.txt>";
		return -1;
	}
	
	else if (input_file.fail())
	{
		//if the file coudnt be opened
		cout<<"Cannot open input file\n";
		return -1;
	}
	
	else if (output_file.fail())
	{
		//if canoot be written in file
		cout<<"Cannot create output file\n";
		return -1;
	}

	input_file>>num_of_data;

	//reading the vector of data
	for (size_t i{}; i < num_of_data; ++i)
	{
		getline(input_file, data, ' ');
		
		data_vec.push_back(stoi(data));
	}

	//copies of the vector of data
	vector<int> data_vec_copy = data_vec;
	vector<int> data_vec_copy_2 = data_vec;

	//sorting the vector of data
	num_of_comparisons_bubble = bubbleSort(data_vec);
	num_of_comparisons_selection = selectionSort(data_vec_copy);
	num_of_comparisons_insertion = insertionSort(data_vec_copy_2);

	//number of comparisons
	output_file<<num_of_comparisons_bubble<<" "<<num_of_comparisons_selection<<" "<<num_of_comparisons_insertion<<endl<<endl;

	//filtering the vector of data
	input_file>>num_of_searches;

	pair<int, int> results{};

	for (size_t i{}; i < num_of_searches; ++i)
	{
		getline(input_file, searched_data, ' ');
		search_data_vec.push_back(stoi(searched_data));

		results = sequentialSearch(data_vec, search_data_vec[i]);
		output_file<<results.first<<" "<<results.second<<" ";

		results = binarySearch(data_vec, search_data_vec[i]);
		output_file<<results.second<<"\n";
	}

	input_file.close();
	output_file.close();
}
