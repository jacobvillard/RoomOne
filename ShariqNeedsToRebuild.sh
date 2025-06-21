#!/bin/bash
echo "running in bash"
# Shariq's Unreal Engine Build Script because they are too lazy to do it manually and Linux SUXX11!!!11!!

ENGINE_PATH="/home/shariq/opt/Linux_Unreal_Engine_5.5.4/Engine"
PROJECT_PATH="/home/shariq/Documents/GitHub/RoomOne/RoomOne.uproject"

echo "The files are being reborn"
"$ENGINE_PATH/Build/BatchFiles/Linux/GenerateProjectFiles.sh" -project="$PROJECT_PATH" -game

echo "Rebuilding the project"
"$ENGINE_PATH/Build/BatchFiles/Linux/Build.sh" RoomOneEditor Linux Development "$PROJECT_PATH"

echo "Launching Unreal (in theory)"
"$ENGINE_PATH/Binaries/Linux/UnrealEditor" "$PROJECT_PATH"