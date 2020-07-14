import os

def BuildUnitTest():
    print("Building Unit Test...")
    os.chdir(os.path.join(os.getcwd(),os.pardir,"UnitTest"))
    os.system("make -f makefile.mak clean")
    os.system("make -f makefile.mak")
    os.system("make -f makefile.mak install")
    if (!os.path.isfile(os.path.join(os.getcwd(),os.pardir,os.pardir,"bin","UnitTest"))):
        print("Build Failed")
    else:
        print("Build Successful")
        
def RunUnitTest():
    print("Running Unit Test...")
    os.chdir(os.path.join(os.getcwd(),os.pardir,os.pardir,"UnitTest"))
    os.system("./UnitTest")
    
def main():
    BuildUnitTest()
   
if __name__ == '__main__':
    main()
