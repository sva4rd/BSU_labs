#makefile for lab4
run: build
	.\bin\main.exe
build: 
	cl  /EHsc /Fe".\bin\main" /Fo".\obj\main" src/Receiver.cpp
	cl  /EHsc /Fe".\bin\Sender" /Fo".\obj\Sender" src/Sender.cpp
clean_files:
	del files\*
clean:
	del bin\*.exe obj\*.obj
	
	