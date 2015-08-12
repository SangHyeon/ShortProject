import subprocess
import os
import sys

problem_num = -1

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
    global problem_num
    problem_num = 1001
    cmd = "%s"%problem_num + "/%s.cpp"%problem_num
    f = open(cmd, 'w')
    f.write(code_)
    f.close()
    
if __name__ == "__main__" :
    recevie()
    if problem_num == -1 :
        print "ERROR"
    else :
        cmd = "g++ -o Main %s"%problem_num + "/%s.cpp"%problem_num
        cmd2 = "cat test | ./Main > result"
        cmd3 = "cp %s"%problem_num + "/answer answer"
        os.system(cmd)
        os.system(cmd2)
        os.system(cmd3)
   
    
#    f = open("result", 'r')
    print "*************"
#    for i in caseNum :
#        result = f.readline()
#        print (result)
    
#    f.close()
    remov = "rm %s/"%problem_num + "%s.cpp "%problem_num + "Main"
    os.system(remov)
