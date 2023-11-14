#include "../nl_gl.h"

PFNGLATTACHSHADERPROC glAttachShader;
PFNGLBINDBUFFERPROC glBindBuffer;
PFNGLBINDVERTEXARRAYPROC glBindVertexArray;
PFNGLBUFFERDATAPROC glBufferData;
PFNGLCOMPILESHADERPROC glCompileShader;
PFNGLCREATEPROGRAMPROC glCreateProgram;
PFNGLCREATESHADERPROC glCreateShader;
PFNGLDELETEBUFFERSPROC glDeleteBuffers;
PFNGLDELETEPROGRAMPROC glDeleteProgram;
PFNGLDELETESHADERPROC glDeleteShader;
PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArrays;
PFNGLDETACHSHADERPROC glDetachShader;
PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;
PFNGLGENBUFFERSPROC glGenBuffers;
PFNGLGENVERTEXARRAYSPROC glGenVertexArrays;
PFNGLGETATTRIBLOCATIONPROC glGetAttribLocation;
PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog;
PFNGLGETPROGRAMIVPROC glGetProgramiv;
PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;
PFNGLGETSHADERIVPROC glGetShaderiv;
PFNGLLINKPROGRAMPROC glLinkProgram;
PFNGLSHADERSOURCEPROC glShaderSource;
PFNGLUSEPROGRAMPROC glUseProgram;
PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;
PFNGLBINDATTRIBLOCATIONPROC glBindAttribLocation;
PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation;
PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv;
PFNGLACTIVETEXTUREPROC glActiveTexture;
PFNGLUNIFORM1IPROC glUniform1i;
PFNGLUNIFORM1FPROC glUniform1f;
PFNGLGENERATEMIPMAPPROC glGenerateMipmap;
PFNGLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArray;
PFNGLUNIFORM2FVPROC glUniform2fv;
PFNGLUNIFORM3FVPROC glUniform3fv;
PFNGLUNIFORM4FVPROC glUniform4fv;
PFNGLBUFFERSUBDATAPROC glBufferSubData;

int initialize_gl()
{
#define LOAD_GL_EXTENSION(type, fn) fn = (type)wglGetProcAddress(#fn); if (fn == 0){return 0;} 
    {
        LOAD_GL_EXTENSION(PFNGLATTACHSHADERPROC, glAttachShader);
        LOAD_GL_EXTENSION(PFNGLBINDBUFFERPROC, glBindBuffer);
        LOAD_GL_EXTENSION(PFNGLBINDVERTEXARRAYPROC, glBindVertexArray);
        LOAD_GL_EXTENSION(PFNGLBUFFERDATAPROC, glBufferData);
        LOAD_GL_EXTENSION(PFNGLCOMPILESHADERPROC, glCompileShader);
        LOAD_GL_EXTENSION(PFNGLCREATEPROGRAMPROC, glCreateProgram);
        LOAD_GL_EXTENSION(PFNGLCREATESHADERPROC, glCreateShader);
        LOAD_GL_EXTENSION(PFNGLDELETEBUFFERSPROC, glDeleteBuffers);
        LOAD_GL_EXTENSION(PFNGLDELETEPROGRAMPROC, glDeleteProgram);
        LOAD_GL_EXTENSION(PFNGLDELETESHADERPROC, glDeleteShader);
        LOAD_GL_EXTENSION(PFNGLDELETEVERTEXARRAYSPROC, glDeleteVertexArrays);
        LOAD_GL_EXTENSION(PFNGLDETACHSHADERPROC, glDetachShader);
        LOAD_GL_EXTENSION(PFNGLENABLEVERTEXATTRIBARRAYPROC, glEnableVertexAttribArray);
        LOAD_GL_EXTENSION(PFNGLGENBUFFERSPROC, glGenBuffers);
        LOAD_GL_EXTENSION(PFNGLGENVERTEXARRAYSPROC, glGenVertexArrays);
        LOAD_GL_EXTENSION(PFNGLGETATTRIBLOCATIONPROC, glGetAttribLocation);
        LOAD_GL_EXTENSION(PFNGLGETPROGRAMINFOLOGPROC, glGetProgramInfoLog);
        LOAD_GL_EXTENSION(PFNGLGETPROGRAMIVPROC, glGetProgramiv);
        LOAD_GL_EXTENSION(PFNGLGETSHADERINFOLOGPROC, glGetShaderInfoLog);
        LOAD_GL_EXTENSION(PFNGLGETSHADERIVPROC, glGetShaderiv);
        LOAD_GL_EXTENSION(PFNGLLINKPROGRAMPROC, glLinkProgram);
        LOAD_GL_EXTENSION(PFNGLSHADERSOURCEPROC, glShaderSource);
        LOAD_GL_EXTENSION(PFNGLUSEPROGRAMPROC, glUseProgram);
        LOAD_GL_EXTENSION(PFNGLVERTEXATTRIBPOINTERPROC, glVertexAttribPointer);
        LOAD_GL_EXTENSION(PFNGLBINDATTRIBLOCATIONPROC, glBindAttribLocation);
        LOAD_GL_EXTENSION(PFNGLGETUNIFORMLOCATIONPROC, glGetUniformLocation);
        LOAD_GL_EXTENSION(PFNGLUNIFORMMATRIX4FVPROC, glUniformMatrix4fv);
        LOAD_GL_EXTENSION(PFNGLACTIVETEXTUREPROC, glActiveTexture);
        LOAD_GL_EXTENSION(PFNGLUNIFORM1IPROC, glUniform1i);
        LOAD_GL_EXTENSION(PFNGLUNIFORM1FPROC, glUniform1f);
        LOAD_GL_EXTENSION(PFNGLGENERATEMIPMAPPROC, glGenerateMipmap);
        LOAD_GL_EXTENSION(PFNGLDISABLEVERTEXATTRIBARRAYPROC, glDisableVertexAttribArray);
        LOAD_GL_EXTENSION(PFNGLUNIFORM2FVPROC, glUniform2fv);
        LOAD_GL_EXTENSION(PFNGLUNIFORM3FVPROC, glUniform3fv);
        LOAD_GL_EXTENSION(PFNGLUNIFORM4FVPROC, glUniform4fv);
        LOAD_GL_EXTENSION(PFNGLBUFFERSUBDATAPROC, glBufferSubData);
    }
#undef LOAD_GL_EXTENSION

    return 1;
}