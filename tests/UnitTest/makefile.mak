INCLUDE := ../../include
SRC_FILES := UnitTest.cpp \
	TestHVector.cpp
OUT_DIR := ../bin         
CPPFLAGS := -I$(INCLUDE) -I.

all: UnitTest

UnitTest:
	$(CXX) $(SRC_FILES) -o $@

$(OUT_DIR):
	mkdir -p $(OUT_DIR)

install: $(OUT_DIR)
	cp UnitTest $(OUT_DIR)

clean:
	-rm -f $(OUT_DIR)/UnitTest
