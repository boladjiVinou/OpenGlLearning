#include <iostream>
#include <glad/glad.h>
#include "stb_image.h"

using namespace std;
class TextureLoader
{
public:
	unsigned int loadTexture(const char* path);
};