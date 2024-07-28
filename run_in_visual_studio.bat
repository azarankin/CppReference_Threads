@echo off

REM Find the path to the latest installed Visual Studio
setlocal
set "vswhere=%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe"
if not exist "%vswhere%" (
    echo Error: vswhere.exe not found.
    exit /b 1
)

for /f "tokens=* usebackq" %%i in (`"%vswhere%" -latest -requires Microsoft.Component.MSBuild -property installationPath`) do set "VSPath=%%i"

if not defined VSPath (
    echo Error: Visual Studio installation not found.
    exit /b 1
)

REM Create a temporary code-workspace file
set "workspaceFile=%cd%\temp.code-workspace"
echo {> "%workspaceFile%"
echo     "folders": [>> "%workspaceFile%"
echo         {>> "%workspaceFile%"
echo             "path": "." >> "%workspaceFile%"
echo         }>> "%workspaceFile%"
echo     ]>> "%workspaceFile%"
echo }>> "%workspaceFile%"

REM Open Visual Studio with the workspace file
start "" "%VSPath%\Common7\IDE\devenv.exe" "%workspaceFile%"

REM Clean up the temporary workspace file
ping 127.0.0.1 -n 5 > nul
del "%workspaceFile%"

endlocal

