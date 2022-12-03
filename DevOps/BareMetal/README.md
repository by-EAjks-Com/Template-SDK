# Build

## On Windows

```powershell
git clone https://github.com/Microsoft/vcpkg.git C:\Tools\VCPKG
cd C:\Tools\VCPKG
.\bootstrap-vcpkg.bat
.\vcpkg.exe integrate install
.\vcpkg.exe search <...>
.\vcpkg.exe install boost:x64-windows
.\vcpkg.exe install tbb:x64-windows
.\vcpkg.exe install blosc:x64-windows
.\vcpkg.exe list
```

```powershell
cmake -B [build directory] -S . -DCMAKE_TOOLCHAIN_FILE=[path to vcpkg]/scripts/buildsystems/vcpkg.cmake
cmake --build [build directory]
```
