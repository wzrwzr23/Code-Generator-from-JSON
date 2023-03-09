#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

void copyOrigFile(string origFile){
    ifstream orig;
    ofstream temp;
    string str;
    orig.open(origFile);
    temp.open("temp.txt");
    while (getline(orig, str))
    {
        temp << str << endl;
    }
    orig.close();
    temp.close();
}

int getMethodNum(string origFile)
{
    ifstream txt;
    string str;
    int count = 0;
    txt.open(origFile);
    while (getline(txt, str))
    {
        if (str.find("######") != string::npos)
        {
            count++;
        }
    }
    txt.close();
    return count / 2;
}

pair<string, string> getClass()
{
    ifstream input;

    string cls;
    string vis;
    string str;
    string iter;
    int count = 0;
    bool read = false;
    input.open("temp.txt");

    if (!input)
    {
        cout << "No such file!";
    }
    else
    {
        for (int i = 0; i < 3; i++)
        {
            getline(input, str);
            if (str == "######" && !read)
            {
                read = true;
                continue;
            }
            if (str == "######" && read)
            {
                read = false;
                continue;
            }
            if (str != "######" && read)
            {
                istringstream iss(str);

                while (iss)
                {
                    iss >> iter;
                    if (iter != "public" && iter != "private" && iter != "protected" && iter != " " && iter != "-" && iter != "–")
                    {
                        cls = iter;
                        continue;
                    }
                    if (iter == "public" || iter == "private" || iter == "protected")
                    {
                        vis = iter;
                        break;
                    }
                }
            }
        }
    }

    input.close();
    return make_pair(cls, vis);
}

void delHead()
{
    string str;
    int count = 0;
    ifstream input;
    ofstream newCopy;
    input.open("temp.txt");
    newCopy.open("tempOut.txt");

    while (getline(input, str))
    {
        count++;
        if (count > 3)
        {
            newCopy << str << endl;
        }
    }
    input.close();
    newCopy.close();
    rename("tempOut.txt", "temp.txt");
}

int getHeaderClassNum(string fileEdit, string classEdit)
{
    int count = 0;
    fstream edit;
    string str;
    string name;

    edit.open(fileEdit);
    while (getline(edit, str))
    {
        if (str.find("class " + classEdit)!=string::npos)
        {
            cout << "class line " << str << " at number "<< count <<endl;
            break;
        }
        else
        {
            count++;
        }
    }
    edit.close();
    return count + 1;
}
int getHeaderClassVisNum(int classNum, string fileEdit, string classVis)
{
    int count = 0;
    fstream edit;
    string str;
    string name;

    edit.open(fileEdit);
    while (getline(edit, str))
    {
        if (str.find(classVis + ":")!=string::npos && count > classNum)
        {
            cout << "class visibility line " << str << " at number "<< count <<endl;
            break;
        }
        else
        {
            count++;
        }
    }
    cout << "end of file, line number: " << count << endl;
    edit.close();
    return count;
}

string getLineToWrite()
{
    ifstream input;
    string name;
    input.open("temp.txt");
    getline(input, name);
    input.close();
    return name;
}

void writeH(int numToWrite, string lineToWrite, string fileToWrite)
{
    ifstream editFile;
    ofstream tempFile;
    int count = 0;
    string str;
    string nextLine;
    editFile.open(fileToWrite);
    tempFile.open("temp.h");

    while (getline(editFile, str))
    {
        if (count < numToWrite)
        {
            count++;
            tempFile << str << endl;
            continue;
        }
        else if (count == numToWrite)
        {
            tempFile << str << endl;
            tempFile << lineToWrite << ";" << endl;
            count++;
            continue;
        }
        else if (count > numToWrite)
        {
            tempFile << str << endl;
            count++;
            continue;
        }
    }
    editFile.close();
    tempFile.close();
    rename("temp.h", fileToWrite.c_str());
}

pair<string, string> getMethod()
{
    ifstream input;
    ifstream methodNameIn;
    ofstream methodNameOut;
    int count = 0;
    string str;
    string type;
    string name;
    string end;
    input.open("temp.txt");
    methodNameOut.open("tempName.txt");
    getline(input, str);

    istringstream iss(str);
    while (iss)
    {
        if (count == 0)
        {
            iss >> type;
            count++;
        }
        else
        {
            iss >> name;
            /*method name end*/
            if(name.find(")") != string::npos){
                methodNameOut << name << endl;
                break;
            }
            /*method continue parsing*/
            else{
                methodNameOut << name << " ";
                continue;
            }
        }
    }
    methodNameOut.close();
    methodNameIn.open("tempName.txt");
    getline(methodNameIn, end);
    input.close();
    methodNameIn.close();
    remove("tempName.txt");
    return make_pair(type, end);
}

int getMainNum(string fileIn)
{
    ifstream input;
    string str;
    int mainNum = 0;
    input.open(fileIn);
    while (getline(input, str))
    {
        if (str.find("int main(int argc, char *argv[])") != string::npos)
        {
            break;
        }
        else
        {
            mainNum++;
        }
    }
    input.close();
    return mainNum;
}

int getMethodStop()
{
    int methodStop = 0;
    ifstream txt;
    string str;
    txt.open("temp.txt");
    while (getline(txt, str))
    {
        if (str != "}")
        {
            methodStop++;
            continue;
        }
        else
        {
            break;
        }
    }
    txt.close();
    return methodStop;
}

void writeCPP(string fileEdit, string methodType, string methodClass, string methodName, int mainNum, int methodStop)
{
    ifstream edit;
    ifstream txt;
    ofstream temp;
    string str;
    string toWrite;
    int count = 0;
    edit.open(fileEdit);
    temp.open("temp.cpp");
    txt.open("temp.txt");
    getline(txt, toWrite);
    while (getline(edit, str))
    {
        if (count < mainNum)
        {
            count++;
            temp << str << endl;
            continue;
        }
        else if (count == mainNum)
        {
            temp << methodType << " " << methodClass << "::" << methodName << endl;
            for (int i = 0; i < methodStop; i++)
            {
                getline(txt, toWrite);
                temp << toWrite << endl;
            }
            temp << str << endl;
            count++;
            continue;
        }
        else if (count > mainNum)
        {
            temp << str << endl;
            count++;
            continue;
        }
    }
    edit.close();
    temp.close();
    txt.close();
    rename("temp.cpp", "student.cpp");
}

void delMethod(int methodStop){
    ifstream txt;
    string str;
    ofstream temp;
    int count = 0;
    txt.open("temp.txt");
    temp.open("tempOut.txt");
    while (getline(txt, str)){
        if (count<= methodStop){
            count++;
            continue;
        }else{
            temp << str << endl;
            continue;
        }
    }
    txt.close();
    temp.close();
    rename("tempOut.txt", "temp.txt");
}

void removeTemp(){
    remove("temp.txt");
}

string getTXT(){
    string txtName;
    cout << "Please put txt file under the same folder, and enter its name:(without '.txt') ";
    cin >> txtName;
    cout << "Got it! Thank you:)"<<endl;
    return txtName;
}

int main()
{
    string name = getTXT();
    string origFile = name +".txt";
    string headerFile = name +".h";
    string cppFile = name + ".cpp";

    int methodNum = getMethodNum(origFile);
    copyOrigFile(origFile);

    for (int i = 0; i < methodNum; i++)
    {
        pair<string, string> x = getClass();
        cout << x.first << "------" << x.second << endl;
        delHead();
        
        int cNum = getHeaderClassNum(headerFile, x.first);
        int vNum = getHeaderClassVisNum(cNum, headerFile, x.second);
        string methodName = getLineToWrite();
        cout << methodName << endl;
        writeH(vNum, methodName, headerFile);
        
        pair<string, string> method = getMethod();
        int mainNum = getMainNum(cppFile);
        int methodStop = getMethodStop();
        writeCPP(cppFile, method.first, x.first, method.second, mainNum, methodStop);
        delMethod(methodStop);
    }

    removeTemp();
}