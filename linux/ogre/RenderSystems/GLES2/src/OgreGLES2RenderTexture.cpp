/*
-----------------------------------------------------------------------------
This source file is part of OGRE
    (Object-oriented Graphics Rendering Engine)
For the latest info, see http://www.ogre3d.org

Copyright (c) 2000-2014 Torus Knot Software Ltd

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
-----------------------------------------------------------------------------
*/

#include "OgreGLES2RenderTexture.h"
#include "OgreGLES2HardwarePixelBuffer.h"

namespace Ogre {
    GLES2CopyingRenderTexture::GLES2CopyingRenderTexture(GLES2CopyingRTTManager *manager,
                                                       const String &name,
                                                       const GLES2SurfaceDesc &target,
                                                       bool writeGamma, uint fsaa)
        : GLES2RenderTexture(name, target, writeGamma, fsaa)
    {
    }

    void GLES2CopyingRenderTexture::getCustomAttribute(const String& name, void* pData)
    {
        if (name==GLRenderTexture::CustomAttributeString_TARGET)
        {
            GLES2SurfaceDesc &target = *static_cast<GLES2SurfaceDesc*>(pData);
            target.buffer = static_cast<GLES2HardwarePixelBuffer*>(mBuffer);
            target.zoffset = mZOffset;
        }
    }

    void GLES2CopyingRTTManager::unbind(RenderTarget *target)
    {
        // Copy on unbind
        GLES2SurfaceDesc surface;
        surface.buffer = 0;
        target->getCustomAttribute(GLRenderTexture::CustomAttributeString_TARGET, &surface);
        if (surface.buffer)
        {
            static_cast<GLES2TextureBuffer*>(surface.buffer)->copyFromFramebuffer(surface.zoffset);
        }
    }
}
