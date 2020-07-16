import os
import sys
def BuildUnitTest():
    print("Building Unit Test...")
    base_path = os.path.join(os.getcwd(),os.pardir,os.pardir)
    os.chdir(os.path.join(base_path,"tests","UnitTest"))
    os.system("make -f makefile.mak clean")
    res = os.system("make -f makefile.mak")
    os.system("make -f makefile.mak install")
    if (res != 0 or not os.path.isfile(os.path.join(base_path,"tests","bin","UnitTest"))):
        print("Build Failed")
        sys.exit(res)
    else:
        print("Build Successful")
        
def RunUnitTest():
    print("Running Unit Test...")
    os.chdir(os.path.join(os.getcwd(),os.pardir,"bin"))
    os.system("./UnitTest")
    
def main():
    BuildUnitTest()
    RunUnitTest()
   
if __name__ == '__main__':
    main()
