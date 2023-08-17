echo off
for /F "delims=" %%i in ('where glslc') DO (set GLSLC=%%i)
set FILE_SUFFIX=.spv

for /R %%i in (*.vert) do (
   %GLSLC% "%%i" -o "%%i%FILE_SUFFIX%"
)
for /R %%i in (*.frag) do (
   %GLSLC% "%%i" -o "%%i%FILE_SUFFIX%"
)