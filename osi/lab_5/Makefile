#makefile for lab5
run: build
	.\bin\server.exe
build: 
	cl  /EHsc /Fe".\bin\server" /Fo".\obj\server" src/server.cpp
	cl  /EHsc /Fe".\bin\client" /Fo".\obj\client" src/client.cpp
clean_files:
	del files\*
clean:
	del bin\*.exe obj\*.obj
	
	