# Building, Testing, and Deploying the Template-SDK Package

```powershell
cd /Path/To/Template-SDK/DevOps/BareMetal
```

## On Windows

```powershell
git clone https://github.com/Microsoft/vcpkg.git C:\Tools\VCPKG
```

```powershell
cd C:\Tools\VCPKG
```

```powershell
.\bootstrap-vcpkg.bat
.\vcpkg.exe integrate install
.\vcpkg.exe search <...>
.\vcpkg.exe install cli11:x64-windows
.\vcpkg.exe install pybind11:x64-windows
.\vcpkg.exe install spdlog:x64-windows
.\vcpkg.exe list
```
