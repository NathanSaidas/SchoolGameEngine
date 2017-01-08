Feel free to review all of the source code however the Shadow Mapping code is found within these files mainly.


If the computer this project is running on does not support OpenGL version 4.4 please adjust the "#version #"
found inside the shader files to match the OpenGL version or else these shaders will not run.

C++ Files
Common/EntityComponent/ TestComponent.h/.cpp - Creates the objects
Common/Graphics/RenderTexture.h/.cpp - Creates the render texture which is what the depth renders to, to be sampled later.
Common/Graphics/Graphics.h/.cpp - Main class responsible for handling rendering operations.


Shader Files
Resources/Shaders/Built-In/DefaultShader.glsl - The shader which utilizes the shadow map for rendering shadowed fragments onto geometry.
Resources/Shaders/Built-In/DepthShader.glsl - Renders depth into the 


If for some reason the program doesn't run on the machine, please send me an email with the Graphics Card vendor name. 
There has been issues with rendering before NVIDIA cards because of the unsupported OpenGL versions / invalid window context creation.

For additional commit logs or more up to date project this can be found at my github https://github.com/NathanSaidas/SchoolGameEngine 