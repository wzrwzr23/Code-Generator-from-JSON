#ifndef ASGM2P2_H
#define ASGM2P2_H
using namespace std;

typedef struct ClassStruct ClassStruct;
struct ClassStruct
{
    string field;
    string type;
};

string defType(string str);
string extract(string str);
string getJsonPath();
vector<ClassStruct> unionVector(vector<ClassStruct> a, vector<ClassStruct> b);
vector<vector<ClassStruct>> enumerationHelper(vector<ClassStruct> v);
vector<vector<ClassStruct>> enumeration(vector<ClassStruct> v);
void writeh(string className, vector<vector<ClassStruct>> csVecVec);
void writecpp(string className, vector<vector<ClassStruct>> csVecVec);

#endif
