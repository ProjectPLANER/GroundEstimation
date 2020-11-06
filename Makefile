#MakeFile
#EMRCHI001
#August 2020

CC=g++
CFLAGS=--std=c++11 -fpermissive -w
# INCLUDES=-Iinclude/GsTL-1.2.1 #-Iinclude/tiff/libtiff -Iinclude/tiff/port -Iinclude/tiff/libtiff/.libs -Iinclude/opencv/lib -Iinclude/opencv/bin -Iinclude/opencv/build/include/opencv2
LIB=./lib
SRC=./src
DIR=./bin
TARGET=interpolation_main
# TIFF=`pkg-config --cflags --libs libtiff-4`#-ltiff #./include/tiff/libtiff/* ./include/tiff/libtiff/.libs/* ./include/tiff/port/*
# CV2=`pkg-config --cflags --libs opencv`#./include/opencv/lib/*.so #-lcv2

compile:
# 	$(CC) $(INCLUDES) -g -c -o $(DIR)/tiffHandler.o $(SRC)/tiffHandler.cpp  $(TIFF) $(CFLAGS)
# 	$(CC) $(INCLUDES) -g -c -o $(DIR)/krigeHandler.o $(SRC)/krigeHandler.cpp $(CFLAGS)
# 	$(CC) $(INCLUDES) -g -c -o $(DIR)/interpolateMain.o $(SRC)/interpolateMain.cpp $(CV2) $(CFLAGS)
# 	$(CC) -g -o $(TARGET) $(CV2) $(TIFF) $(DIR)/*.o
	@cd $(DIR); cmake ../$(SRC); make
	@mv $(DIR)/$(TARGET) .

run $(args):
	@mkdir -p ./out
	./$(TARGET) $(args) #2> /dev/null

clean:
# 	@rm $(DIR)/*.o
	@rm -r $(DIR)/*
	@rm $(TARGET)
