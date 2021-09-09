CHFilter2

Using C++ or Rust, make a program that uses a file system filter driver ( https://docs.microsoft.com/en-gb/windows-hardware/drivers/ifs/ ) to display a message every time a file with a name containing the string "cyberhive" is opened for reading.

Part 1:
Created a file system filter driver based on the code provided by the Visual Studio 2019 wizard
Registers for callbacks on IRP_MJ_READ
When a file is read the filename is checked and a debug message is logged.

The CHFilter2.inf file was updated to match the latest requirements from Microsoft

To test the driver convert windows to test mode
SECURE BOOT OFF
bcdedit /set TESTSIGNING ON

right click CHFilter2.inf -> Install

net start CHFilter2 to start the filter driver
net stop CHFilter2 to stop the filter driver

Output can be observed in DebugView with kernal mode output switched on.


