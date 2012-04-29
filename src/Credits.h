#pragma once

#include <string>
#include "TextureManager.h"
#include "Graphics.h"
#include "Writer.h"

class CCredits{

    public:

        CCredits();
        ~CCredits();
        void init();
        void draw();

    private:

        CTextureManager*    texman;
        CWriter*			escriptor;

        int image_credits, marvin, vader;
};
