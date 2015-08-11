import subprocess
import os
import sys
def recevie() :
    #test
    code_ = """#include<iostream>
   using namespace std;
   int main() {
    int n;
    cin>>n;
    for(int i=0; i<n; i++) {
    int a, b;
    cin>>a>>b;
    cout<<a+b<<endl;
    }
    return 0;
    }
    """
    f = open("plus.cpp", 'w')
    f.write(code_)
    f.close()
    
if __name__ == "__main__" :
    recevie()
    r = open("test", 'r')
    caseNum = r.readline()
    Input = r.readline()
    cmd = "cat test | ./Main > result"
    os.system("g++ -o Main plus.cpp")
    os.system(cmd)
    
    f = open("result", 'r')
    print "*************"
#    for i in caseNum :
#        result = f.readline()
#        print (result)
    
    f.close()

    os.system("rm plus.cpp Main")
