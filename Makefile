#MakeFile
#EMRCHI001
#August 2020

CC=g++
CFLAGS=--std=c++11 -fpermissive -w
LIB=./lib
SRC=./src
DIR=./bin
TARGET=interpolation_main

compile:
	@cd $(DIR); cmake ../$(SRC); make
	@mv $(DIR)/$(TARGET) .

run $(args):
	@mkdir -p ./out
	./$(TARGET) $(args)

clean:
	@rm -r $(DIR)/*
	@rm $(TARGET)
