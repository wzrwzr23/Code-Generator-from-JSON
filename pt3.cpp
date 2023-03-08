#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

void copyOrigFile(string origFile, string tempFile){
    ifstream orig;
    ofstream temp;
    string str;
    orig.open(origFile);
    temp.open(tempFile);
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
        if (str == "######")
        {
            count++;
        }
    }
    txt.close();
    return count / 2;
}

pair<string, string> getClass(string fileName)
{
    ifstream input;

    string cls;
    string vis;
    string str;
    string iter;
    int count = 0;
    bool read = false;
    input.open(fileName);

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

void delHead(string fileIn)
{
    string str;
    int count = 0;
    ifstream input;
    ofstream newCopy;
    input.open(fileIn);
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
    rename("tempOut.txt", fileIn.c_str());
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
        if (str == "class " + classEdit)
        {
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
        if (str == classVis + ":" && count > classNum)
        {
            break;
        }
        else
        {
            count++;
        }
    }
    edit.close();
    return count;
}

string getLineToWrite(string fileToWrite)
{
    ifstream input;
    string name;
    input.open(fileToWrite);
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

pair<string, string> getMethod(string fileIn)
{
    ifstream input;
    ifstream methodNameIn;
    ofstream methodNameOut;
    int count = 0;
    string str;
    string type;
    string name;
    string end;
    input.open(fileIn);
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
                methodNameOut << " " << name << endl;
                break;
            }
            /*method continue parsing*/
            else{
                methodNameOut << name;
                continue;
            }
        }
    }
    methodNameOut.close();
    methodNameIn.open("tempName.txt");
    getline(methodNameIn, end);
    input.close();
    methodNameIn.close();
    cout << type << " " << end << endl;
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

int getMethodStop(string txtFile)
{
    int methodStop = 0;
    ifstream txt;
    string str;
    txt.open(txtFile);
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

void writeCPP(string txtFile, string fileEdit, string methodType, string methodClass, string methodName, int mainNum, int methodStop)
{
    ifstream edit;
    ifstream txt;
    ofstream temp;
    string str;
    string toWrite;
    int count = 0;
    edit.open(fileEdit);
    temp.open("temp.cpp");
    txt.open(txtFile);
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

void delMethod(string txtFile, int methodStop){
    ifstream txt;
    string str;
    ofstream temp;
    int count = 0;
    txt.open(txtFile);
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
    rename("tempOut.txt", txtFile.c_str());
}

int main()
{
    string origFile = "student.txt";
    string headerFile = "student.h";
    string cppFile = "student.cpp";
    string tempFile = "temp.txt";
    copyOrigFile(origFile, tempFile);
    int methodNum = getMethodNum(origFile);

    for (int i = 0; i < methodNum; i++)
    {
        pair<string, string> x = getClass(tempFile);
        delHead(tempFile);
        int cNum = getHeaderClassNum(headerFile, x.first);
        int vNum = getHeaderClassVisNum(cNum, headerFile, x.second);
        string methodName = getLineToWrite(tempFile);
        writeH(vNum, methodName, headerFile);
        pair<string, string> method = getMethod(tempFile);
        int mainNum = getMainNum(cppFile);
        int methodStop = getMethodStop(tempFile);
        writeCPP(tempFile, cppFile, method.first, x.first, method.second, mainNum, methodStop);
        delMethod(tempFile, methodStop);
    }
    remove("temp.txt");
}