import os

def BuildUnitTest():
    print("Building Unit Test...")
    current_path = os.getcwd()
    os.chdir(os.path.join(os.getcwd(),os.pardir,"UnitTest"))
    os.system("make -f makefile.mak clean")
    os.system("make -f makefile.mak")
    os.system("make -f makefile.mak install")
    print(os.listdir())
    os.chdir(os.path.join(os.getcwd(),os.pardir))
    print(os.listdir())
    if (os.path.isdir("bin")):
        os.chdir(os.path.join(os.getcwd(),"bin"))
        print(os.listdir())
    if (not os.path.isfile(os.path.join(current_path,"tests","bin","UnitTest"))):
        print("Build Failed")
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
