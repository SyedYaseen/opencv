# OpenCV Notes

# OpenCV C++ Installation Windows Visual Studio
- Download latest version from https://opencv.org/releases/
- Check the install location. Mine is C:\Program Files\OpenCV
- Set environment variable ```setx OpenCV_DIR C:\Program Files\OpenCV\build\x64\vc16```
- Set ```C:\Program Files\OpenCV\build\x64\vc16\bin``` in PATH variable
- In Visual studio: 
	- Project -> Properties -> VC++ Directories
	- Include Dirs: C:\Program Files\OpenCV\build\include
	- Lib dirs: C:\Program Files\OpenCV\build\x64\vc16\lib
	- Linker -> Input -> Additional Dependencies -> opencv_world4100d.lib. Check correct file name from C:\Program Files\OpenCV\build\x64\vc16\lib

pyimagesearch banner: document.querySelector('div.pyi-top-bar').hidden = true
document.querySelector('is-stuck is-at-top').hidden = true
