# OpenCV Notes

# OpenCV C++ Installation Windows Visual Studio
- Download latest version from https://opencv.org/releases/
- Check the install location. Mine is C:\Program Files\OpenCV
- Set environment variable ```setx OpenCV_DIR C:\Program Files\OpenCV\build\x64\vc16```
- In Visual studio: 
	- Project -> Properties -> VC++ Directories
	- Include Dirs: C:\Program Files\OpenCV\build\include
	- Lib dirs: C:\Program Files\OpenCV\build\x64\vc16\lib
	- Linker -> Input -> Additional Dependencies -> opencv_world4100d.lib. Check correct file name from C:\Program Files\OpenCV\build\x64\vc16\lib
	