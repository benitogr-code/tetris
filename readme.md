# Tetris

An implementation of the classic game Tetris using _SDL_ and _OpenGL_.

This project is organized in two distintic parts.

### System

Abstracts platform details (window, input, logging), providing a basic framework with lifecycle hooks for the client application. Additionally, some wrapper classes for OpenGL resources are provided like Shaders, GPU Buffers or Textures.

### Game

The Tetris game application implemented used the system utilities. For rendering, batching and instancing are used to reduce the number of draw calls.

Check it out in action in this [video](/assets/media/demo.mp4).
