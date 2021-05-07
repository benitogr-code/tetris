# Tetris

An implementation of the classic game **Tetris** using _SDL_ and _OpenGL_.

See it in action in this ![video](https://user-images.githubusercontent.com/53510560/117455455-7d9e5780-af47-11eb-9583-2873258b8944.mp4).

---

The project is organized in two distintic parts.

### System

Abstracts platform details (window, input, logging), providing a basic framework with lifecycle hooks for the client application. Additionally, some wrapper classes for OpenGL resources are provided like Shaders, GPU Buffers or Textures.

### Game

The Tetris game application implemented used the system utilities. For rendering, batching and instancing are used to reduce the number of draw calls.
