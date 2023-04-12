#makefile for lab1
run: build
	.\bin\main.exe
build: 
	cl  /EHsc /Fe".\bin\main" /Fo".\obj\main" src/main.cpp
	cl  /EHsc /Fe".\bin\reporter" /Fo".\obj\reporter" src/reporter.cpp
	cl  /EHsc /Fe".\bin\creator" /Fo".\obj\creator" src/creator.cpp
clean_files:
	del files\*
clean:
	del bin\*.exe obj\*.obj
	
	