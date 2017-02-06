#include <iostream>
#include <stdio.h>
#include <string>
#include <map>
#include <math.h>
using namespace std;

map<int,string> hash_num_rom;
int decimal[30] = {1,2,3,4,5,6,7,8,9,10,20,30,40,50,60,70,80,90,\
					100,200,300,400,500,600,700,800,900,1000,2000,3000};
string roman[30] = {"I","II","III","IV","V","VI","VII","VIII","IX",\
					"X","XX","XXX","XL","L","LX","LXX","LXXX","XC",\
					"C","CC","CCC","CD","D","DC","DCC","DCCC","CM",\
					"M","MM","MMM"};
map<char,int> hash_rom_num;
char roman_literal[7] = {'I','V','X','L','C','D','M'};
int decimal_value[7] = {1,5,10,50,100,500,1000};
void init_hash(void){
	for(int i=0;i<30;i++){
		hash_num_rom[decimal[i]] = roman[i];
	}
}
void init_hash_value(void){
	for(int i=0;i<7;i++){
		hash_rom_num[roman_literal[i]] = decimal_value[i];
	}
}
string convert_to_roman(string input){
	string ret;
	int len = input.length();
	for(int i=0;i<len;i++){
		ret.append(hash_num_rom[pow(10,len-i-1)*(input[i]-'0')]);
	}
	return ret;
}
int convert_to_decimal(string input){
	int running_sum = 0, length = input.length();
	char max_literal = input[length-1];
	running_sum+=hash_rom_num[input[length-1]];
	for(int i=length-2;i>=0;i--){
		if(input[i]<max_literal){
			max_literal = input[i];
			running_sum-=hash_rom_num[input[i]];
		}
		else{
			running_sum+=hash_rom_num[input[i]];
		}
	}
	return running_sum;
}
int main(){
	init_hash();
	init_hash_value();
	string input;
	while(cin >> input){
		//Determine which conversion to apply
		if(input[0] <= '9' && input[0] >= '0'){
			cout << convert_to_roman(input) << endl;
		}
		else{
			cout << convert_to_decimal(input) << endl;
		}
	}
	return 0;
}