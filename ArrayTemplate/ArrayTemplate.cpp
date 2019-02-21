// ArrayTemplate.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <vector>
#include <string>

template <typename T, int N> class Array {
private:
	T ar[N];
public:
	int GetSize() {
		return N;
	}
	T & operator[](int i) { // if I return by value here and not by reference
							// then !! t[0] is just  value - in particular r-value!!!
							// so assignment t[0]=4; will complain about that!
		return ar[i];
	}
};


int compare(std::string s1, std::string s2) {
	if (s1.length() != s2.length()) {
		return 0;
	}
	unsigned int common = 0;
	while ((s1[common] == s2[common]) && common < s1.length()) {
		++common;
	}
	if (common != s1.length()) {
		common = 0;
	}
	return common;

}

void KMP(std::string str, std::string substring) {
	int n1 = str.length();
	int n2 = substring.length();
	if (n2 > n1) {
		return;
	}
	// find largest valid sufix and prefix table ilp
	int * ilp = new int[n2];
	ilp[0] = 0;


	

	for (int i = 1; i < n2; ++i)
	{
		std::vector<std::string> prefix;
		std::vector<std::string> suffix;
		int common = 0;

		std::string tmp_pre = "";
		std::string tmp_suff = "";
		
		for (int j = 0; j <= i - 1; ++j) {
			tmp_pre = tmp_pre + substring[j];
			prefix.push_back(tmp_pre);
			tmp_suff = substring[i - j] + tmp_suff;
			suffix.push_back(tmp_suff);
		}

		std::cout << i << "---------------------" << std::endl;
		std::cout << prefix.size() << std::endl;
		std::cout << suffix.size() << std::endl;
		//std::cout << prefix[0] << std::endl;
		for (std::string s : prefix) { std::cout << s << std::endl; }
		for (std::string s : suffix) { std::cout << s << std::endl; }
		common = 0;
		for (std::string s1 : prefix) 
		{
				for (std::string s2 : suffix) 
				{
					int comp = compare(s1, s2);
					if (comp > common) 
					{
						common = comp;
					}
					
				}
		}
		ilp[i] = common;
	}

	std::cout << "-------------ILP-------------- " << std::endl;
	for (int i = 0; i < n2; ++i) { std::cout << i<< " " << ilp[i] << std::endl; }
	std::cout << "--------------------------- " << std::endl;
	
	// now we can start KMP algorithm

	int start_compare_string = 0;
	int start_compare_substring = 0;
	int nmatches = 0;
	while (start_compare_string + n2 <= n1) {
		
		while ((str[start_compare_string] == substring[start_compare_substring]) && (start_compare_substring < n2)) {
			++nmatches;
			++start_compare_string;
			++start_compare_substring;
			std::cout << nmatches << " A "<<std::endl;
			std::cout << start_compare_string <<  " B " << std::endl;
			std::cout << start_compare_substring << " C " << std::endl;
		}
		if (nmatches == n2) {
			std::cout << "Found a match AT " << start_compare_string-n2 << std::endl;
		}
		if (nmatches != 0) {
			nmatches = ilp[nmatches - 1];
			start_compare_substring = nmatches;
		}
		else {
			nmatches = 0;
			start_compare_substring = nmatches;
			++start_compare_string;
		}
		std::cout << nmatches << " D " << std::endl;
		std::cout << start_compare_substring << " E " << std::endl;
		std::cout << start_compare_string << " F " << std::endl;

		//else {
		//	nmatches = ilp[nmatches];
			//start_compare_substring = nmatches;
		//}
	}

	delete ilp;


}

int main()
{
	Array<int, 5> t;
	t[0] = 5;
	t[1] = 4;
	std::cout << t[0] << " " << t[1] << std::endl;
    std::cout << "Hello World!\n"; 
	std::string s1 = "ababxxababababxxaab";
	std::string s2 = "abab";
	std::cout << (s1[0] == s2[0]) << std::endl;
	std::cout << s1.length() << std::endl;
	KMP(s1, s2);
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
