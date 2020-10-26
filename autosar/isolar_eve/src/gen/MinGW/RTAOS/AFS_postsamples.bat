@echo off
copy Samples\includes\Std_Types.h /Y "C:\Users\consi\Desktop\AFS\src\gen\MinGW\RTAOS\" >nul
copy Samples\includes\Platform_Types.h /Y "C:\Users\consi\Desktop\AFS\src\gen\MinGW\RTAOS\" >nul
copy Samples\includes\Compiler.h /Y "C:\Users\consi\Desktop\AFS\src\gen\MinGW\RTAOS\" >nul
copy Samples\includes\Os_Compiler_Cfg.h /Y "C:\Users\consi\Desktop\AFS\src\gen\MinGW\RTAOS\" >nul
copy Samples\includes\Compiler_Cfg.h /Y "C:\Users\consi\Desktop\AFS\src\gen\MinGW\RTAOS\" >nul
if exist Samples\includes\Os_MemMap.h copy Samples\includes\Os_MemMap.h /Y "C:\Users\consi\Desktop\AFS\src\gen\MinGW\RTAOS\" >nul
