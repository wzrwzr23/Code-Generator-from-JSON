#include <fstream>
#include <iostream>
#include <string>
#include <list>
#include <algorithm>
#include <map>
using namespace std;

typedef struct {
    string field;
    string type;
} ClassStruct;

string defType(string str){
    int index = str.find_first_of(":") + 2;
    if (index < str.length()){
        if (str[index] == '"'){
            return "string";
        }
        else if (str.find_first_of(".") < str.length()){
            return "float";
        }
        else{
            return "int";
        }
    }
    return NULL;
}

string extract(string str){
    int index = str.find_first_of(":");
    str.erase(str.begin(), str.begin()+index+2);
    if (str.length() >= 3){
        if (str[0] == '"'){
            str.erase(0, 1); /* delete " */
        }
        str.erase(str.length()-1, 1); /* delete \n */
        if (str[str.length()-1] == ','){
            str.erase(str.length()-1, 1); /* delete , */
        }
        if (str[str.length()-1] == '"'){
            str.erase(str.length()-1, 1); /* delete " */
        }
    }    

    return str;
}

vector<ClassStruct> unionVector(vector<ClassStruct> a, vector<ClassStruct> b){
    if (a.size() == 0){
        return b;
    }
    if(b.size() == 0){
        return a;
    }
    bool add = true;
    int bSize = b.size();
    for (int i = 0; i < bSize; i++) {
        add = true;
        for (int j = 0; j < a.size(); j++){
            if (a[i].field == b[j].field){
                add = false;
                break;
            }
        }
        if(add){a.push_back(b[i]);}
    }
    return a;	
}

vector<vector<ClassStruct>> enumerationHelper(vector<ClassStruct> v){
    vector<vector<ClassStruct>> csVecVec;
    csVecVec.push_back(v);

    for (int i=0; i<v.size(); i++){ /* go through the rest */ 
        int j = i + 1;
        for (j; j<v.size(); j++){
            csVecVec.push_back({v[i], v[j]});
        }
    }
    return csVecVec;
}

vector<vector<ClassStruct>> enumeration(vector<ClassStruct> v){
    vector<vector<ClassStruct>> csVecVec;
    csVecVec.push_back(v);
    bool push;
    bool dup = false;
    int dupNum = 0;

    int dupIdx;
    int vSize = v.size();
    if (vSize <= 1){
        return csVecVec;
    }
    cout<<"----2\n";
    /* add single member, prevent dupication*/ 
    csVecVec.push_back({v[0]}); /* push the first element*/ 
    for (int i=1; i<vSize; i++){ /* go through the rest */ 
        push = true;
        for (int k=1; k<csVecVec.size(); k++){
            if (csVecVec[k][0].type == v[i].type){ /*duplicate*/
                push = false;
                dup = true;
                dupNum ++;
                break;
            }
        }
        if (push){
            csVecVec.push_back({v[i]});
        }
    }
    if (vSize == 2){
        return csVecVec;
    }
    if (!dup){
        for (int i=0; i<vSize-1; i++){ /* go through the rest */ 
            int j = i +1;
            for (j; j<vSize; j++){
                csVecVec.push_back({v[i], v[j]});
            }
        }
    }
    if (vSize == 3 && !dup){
        return csVecVec;
    }
    if (vSize == 3 && dup){ 
        if (dupNum == 2){ /* all members with the same types*/
            csVecVec.push_back({v[0],v[1]});
        }
        if (dupNum == 1){ /* 2 members with the same types*/
            for (int i=0; i<vSize-1; i++){ /* go through the rest */ 
                int j = i + 1;
                for (j; j<vSize; j++){
                    if (v[i].type == v[j].type){ /*duplicate*/
                        dupIdx = i;
                        break;
                    }
                }    
            }
            // csVecVec.push_back({v[dupIdx],v[dupIdx]});
            for (int i=0; i<vSize; i++){
                if (i != dupIdx){
                    csVecVec.push_back({v[dupIdx],v[i]});
                }
            }
        }
        return csVecVec;
    }

    cout<<"----3\n";
    if (vSize == 4 && !dup){
        csVecVec.push_back({v[1], v[2], v[3]});
        csVecVec.push_back({v[1], v[2], v[0]});
        csVecVec.push_back({v[1], v[0], v[3]});
        csVecVec.push_back({v[0], v[2], v[3]});
        return csVecVec;
    }else{
        if (dupNum == 3){
            csVecVec.push_back({v[0], v[1], v[2]});
            csVecVec.push_back({v[0], v[1]});
        }
        else if (dupNum == 1){
            int dupIdx1;
            for (int i=0; i<vSize-1; i++){ /* go through the rest */ 
                int j = i + 1;
                for (j; j<vSize; j++){
                    if (v[i].type == v[j].type){ /*duplicate*/
                        dupIdx = i;
                        dupIdx1 = j;
                        break;
                    }
                }    
            }
            csVecVec.push_back({v[dupIdx],v[dupIdx1]});
            vector<vector<ClassStruct>> tem;
            switch (dupIdx)
            {
                case 0:
                    tem = enumerationHelper({v[1],v[2],v[3]});
                    csVecVec.insert(csVecVec.end(), tem.begin(),tem.end());
                    break;
                case 1:
                    tem = enumerationHelper({v[0],v[2],v[3]});
                    csVecVec.insert(csVecVec.end(), tem.begin(),tem.end());
                    break;
                case 2:
                    tem = enumerationHelper({v[1],v[0],v[3]});
                    csVecVec.insert(csVecVec.end(), tem.begin(),tem.end());
                    break;
                case 3:
                    tem = enumerationHelper({v[1],v[2],v[0]});
                    csVecVec.insert(csVecVec.end(), tem.begin(),tem.end());
                    break;
            }
            for (int i=0; i<vSize; i++){
                if (i != dupIdx && i != dupIdx1){
                    csVecVec.push_back({v[dupIdx], v[dupIdx1], v[i]});
                }
            }
        }else{
            dupNum = 0;
            bool twoDup = true;
            int anoIdx = 4;
            for (int i=0; i<vSize-1; i++){ /* go through the rest */ 
                int j = i + 1;
                dupNum = 0;
                for (j; j<vSize; j++){
                    if (v[i].type == v[j].type){ /*duplicate*/
                        dupIdx = i;
                        dupNum ++;
                    }else{
                        anoIdx = j;
                    }
                } 
                if (dupNum == 2 && anoIdx != 4){
                    twoDup = false;
                    break;
                }
            }
            
            for (int i=0; i<vSize; i++){
                if (twoDup){
                    if (i != dupIdx && i != anoIdx){
                        csVecVec.push_back({v[dupIdx], v[anoIdx], v[i]}); 
                        if (v[i].type == v[dupIdx].type){
                            csVecVec.push_back({v[dupIdx], v[i]}); /* a1, a2 */
                        }else{
                            csVecVec.push_back({v[anoIdx], v[i]}); /* b1, b2 */
                        }
                    }
                }else{
                    if (i != dupIdx && i != anoIdx){
                        csVecVec.push_back({v[dupIdx], v[i]});
                        csVecVec.push_back({v[dupIdx], v[anoIdx], v[i]});
                    }
                }
            }
            if (twoDup){
                csVecVec.push_back({v[dupIdx], v[anoIdx]});
            }else{
                switch (anoIdx){
                    case 0:
                        csVecVec.push_back({v[1], v[2], v[3]});
                        break;
                    case 1:
                        csVecVec.push_back({v[0], v[2], v[3]});
                        break;
                    case 2:
                        csVecVec.push_back({v[1], v[0], v[3]});
                        break;
                    case 3:
                        csVecVec.push_back({v[1], v[2], v[0]});
                        break;
                    
                }
            }
            
        }
        return csVecVec;
    }
    cout<<"----4\n";
    return csVecVec;
}

void writeh(string className, vector<vector<ClassStruct>> csVecVec){
    /*-------.h file-------*/
    string hFileName = className + ".h";
    string upperClassName = className;
    for(int i = 0;i < upperClassName.length();++i){
        upperClassName[i] = toupper(upperClassName[i]);
    }
    upperClassName += "_H";
    ofstream outFile(hFileName);
    outFile << "#ifndef " << upperClassName << "\n#define " << upperClassName 
        << "\nusing namespace std;" <<endl;
    outFile << "class " << className << "{\n    protected:\n    private:" <<endl;

    vector<ClassStruct> v = csVecVec[0]; /*v with all member variables*/
    /* add class members */
    for (int i=0; i<v.size(); i++){ 
        outFile << "        " << v[i].type << " " << v[i].field << ";" << endl;
    }
    outFile << "    public:" << endl; 
    
    /* -------add constructors------ */
    int enu = csVecVec.size();
    int memNum;
    /* Go through every combination of member variables. Each combination has one construtor */
    for (int i=0; i<enu; i++){ 
        outFile << "        " << className << "(";
        v = csVecVec[i];
        memNum = v.size();
        for (int j=0; j<memNum-1; j++){ /* go through every member variable */
            outFile << v[j].type << " a" << j+1 << ", ";
        }
        outFile << v[memNum-1].type << " a" << memNum << ");" << endl;
    }
    outFile << "};\n#endif" << endl;
    outFile.close();
}


void writecpp(string className, vector<vector<ClassStruct>> csVecVec){
    int enu = csVecVec.size();
    vector<ClassStruct> v;
    int memNum;
    string content = "#include <iostream>\n#include \"" + className + ".h\"\nusing namespace std;\n";

    for (int i=0; i<enu; i++){ 
        content = content + className + "::" + className + "(";
        v = csVecVec[i];
        memNum = v.size();
        for (int j=0; j<memNum-1; j++){ /* go through every member variable for arguments */
            content = content + v[j].type + " a" + to_string(j+1) + ", ";
        }
        content = content + v[memNum-1].type + " a" + to_string(memNum) + "){\n";

        for (int j=0; j<memNum; j++){ /* go through every member variable for assignment */
            content = content + "    " +v[j].field + " = a" + to_string(j+1) + ";\n";
        }
        content += "}\n";
    }

    content += "int main (int argc, char *argv[]){\n";
    string ccpFileName = className + ".cpp";
    string origin;
    string buf;
    ifstream is(ccpFileName);
	if (!is.is_open())
	{
		cerr << ccpFileName << " open failed" << endl;
		return;
	}
    while (getline(is,buf)){
        origin = origin + buf + "\n";
    }
    is.close();
	ofstream os(ccpFileName, ios::trunc);
	os << content << origin << "    return 0;\n}" << endl;
	os.close();
}

int main() {
    ifstream ifs;
    ifs.open("student.json",ios::in) ;
    if (!ifs.is_open()) {
        cout << "open failed" << endl;
        return 0;
    }

    string buf;
    string ccpFileName;

    map<string, vector<ClassStruct>> classMemMap;
    map<string, bool> classExist;
    vector<ClassStruct> csVec;

    ClassStruct cs1;
    ClassStruct cs2;
    ClassStruct cs3;
    ClassStruct cs4;
    string className;
    string instanceName;
    string field1;
    string value1;
    string type1;
    string field2;
    string value2;
    string type2;
    string field3;
    string value3;
    string type3;
    string field4;
    string value4;
    string type4;
    int index = 0;
    bool end = false;

    while (getline(ifs,buf)){
        if (buf.find("Class") < buf.length()){ /* this line contains the class name*/
            className = extract(buf);
            index = 1;
            continue;
        }
        
        if (index == 1){ /* this line contains the instance name*/
            end = true;
            instanceName = extract(buf);
            index = 2;
            continue;
        }

        if (buf.find("Field") < buf.length() || buf.find("Value") < buf.length()){
            end = true;
            switch (index){
                case 2:
                    field1 = extract(buf);
                    index = 3;
                    cs1.field = extract(buf);
                    break;
                case 3:
                    value1 = extract(buf);
                    type1 = defType(buf);
                    if (type1 == "float"){value1 += "f";}
                    if (type1 == "string"){value1 = "\"" + value1 + "\"";} 
                    index = 4;
                    cs1.type = defType(buf);
                    break;
                case 4:
                    field2 = extract(buf);
                    index = 5;
                    cs2.field = extract(buf);
                    break;
                case 5:
                    value2 = extract(buf);
                    type2 = defType(buf);
                    if (type2 == "float"){value2 += "f";}
                    if (type2 == "string"){value2 = "\"" + value2 + "\"";} 
                    index = 6;
                    cs2.type = defType(buf);
                    break;
                case 6:
                    field3 = extract(buf);
                    index = 7;
                    cs3.field = extract(buf);
                    break;
                case 7:
                    value3 = extract(buf);
                    type3 = defType(buf);
                    if (type3 == "float"){value3 += "f";}
                    if (type3 == "string"){value3 = "\"" + value3 + "\"";} 
                    index = 8;
                    cs3.type = defType(buf);
                    break;
                case 8:
                    field4 = extract(buf);
                    index = 9;
                    cs4.field = extract(buf);
                    break;
                case 9:
                    value4 = extract(buf);
                    type4 = defType(buf);
                    if (type4 == "float"){value4 += "f";}
                    if (type4 == "string"){value4 = "\"" + value4 + "\"";} 
                    index = 10;
                    cs4.type = defType(buf);
                    break;
            }
            continue;
        }

        if (end){
            if (index >= 4){csVec.push_back(cs1);}
            if (index >= 6){csVec.push_back(cs2);}
            if (index >= 8){csVec.push_back(cs3);}
            if (index >= 10){csVec.push_back(cs4);}
            classMemMap[className] = unionVector(classMemMap[className], csVec);
            
            ccpFileName = className + ".cpp";
            if (!classExist[className]){ /* clear the cpp file content */
                ofstream os(ccpFileName, ios::trunc);
                os.close();
            }
            classExist[className] = true;
            ofstream outFile(ccpFileName, ios::app);
            
            /*instantiation*/
            outFile << "    " << className << " " << instanceName << " = " << className << "(";
            if (index >= 4){outFile << value1;}
            if (index >= 6){outFile << ", " << value2;}
            if (index >= 8){outFile << ", " << value3;}
            if (index >= 10){outFile << ", " << value4;}
            outFile << ");" << endl;
            outFile.close();
        }
        end = false;
        csVec.clear();
        index = 0;
    }
    ifs.close();
    for (auto it : classMemMap) {
        className = it.first;
        vector<vector<ClassStruct>> classStructEnu = enumeration(it.second);
        // for (int i=0;i<classStructEnu.size();i++){
        //     for (int j=0;j<classStructEnu[i].size();j++){
        //         cout<<classStructEnu[i][j].field<<", ";   
        //     }
        //     cout << "\n";
        // }
        writecpp(className, classStructEnu);
        writeh(className, classStructEnu);
    }
    return 0;
}
