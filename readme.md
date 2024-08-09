# Shut the Box

Simply shut the box and you win. But it isn't that simple.
Roll the dice and select the men, whose numbers add up to the dice total.
You can only select a man one time per game. If you roll a total that you can 
not make with the remaining men, you lose. If you don't get stuck and are able 
to select all the men, you win and have successfully shut the box.

This game uses the Horstmann Graphics library that was created for the C++ text
book Big C++. The source code can be compiled in Microsoft Visual Studio. The 
original source files of the Horstmann Graphics needed to be updated to compile
without errors. 

ccc_msw.cpp -> changed sprintf() to sprintf_s()
ccc_shap.cpp -> changed sprintf() to sprintf_s()

to use sprintf_s() the second parameter was entered as sizeof(first parameter).

To get this code to compile in visual studio (2017 is the latest verified
version) follow these steps after cloning the repo:

1. Create new project >> visual C++ >> empty project. Set name and save folder
to what you want.
2. In solution explorer right click on the solution name, click 'add', click
'Existing Item...'
3. Navigate to the repo. Add all the .cpp and .h files in the repo main folder.
4. Repeat steps 2 and 3 for all the .cpp and .h files in the HorstmannGraphics
folder.
5. In solution explorer right click on the solution name and click properties.
6. On the left, navigate to 'Configuration Properties' >> C/C++ >> General.
7. On the right, select 'Additional Include Directories', click the dropdown 
arrow, then click <Edit...>.
8. In the 'Additional Include Directories' window, select the 'New Line' icon,
click on the "..." that appears, then navigate to the HorstmannGraphics folder
in the repo, then click 'Select Folder', click OK, returning you to the property
pages.
9. On the left, navigate to 'Configuration Properties' >> Linker >> System.
10. On the right, select 'SubSystem', click the dropdown arrow and select 
'Windows (/SUBSYSTEM:WINDOWS)'.
11. Click Apply, click OK.

You should now be able to compile and run the game.
