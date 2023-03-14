#ifndef PT3_H
#define PT3_H

using namespace std;

void copyOrigFile(string origFile);
int getMethodNum(string origFile);
pair<string, string> getClass();
void delHead();
int getHeaderClassNum(string fileEdit, string classEdit);
int getHeaderClassVisNum(int classNum, string fileEdit, string classVis);
string getLineToWrite();
void writeH(int numToWrite, string lineToWrite, string fileToWrite);
pair<string, string> getMethod();
int getMainNum(string fileIn);
int getMethodStop();
void writeCPP(string fileEdit, string methodType, string methodClass, string methodName, int mainNum, int methodStop);
void delMethod(int methodStop);
void removeTemp();
string getTXT();


#endif