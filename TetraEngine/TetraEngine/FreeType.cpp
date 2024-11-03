#include "FreeType.h"

FT_Library FreeType::ft;
FT_Face FreeType::defaultFace;
FT_Face FreeType::currentFace;

unsigned int FreeType::VAO;
unsigned int FreeType::VBO;
std::map<GLchar, FreeType::Character> FreeType::characters;