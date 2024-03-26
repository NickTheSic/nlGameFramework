#ifndef __NL_GL_WIN32_H__
#define __NL_GL_WIN32_H__


#include "nl_win32_include.h"
#include "gl/GL.h"


#define GL_ARRAY_BUFFER          0x8892		
#define GL_STREAM_DRAW           0x88E0
#define GL_STATIC_DRAW           0x88E4		  
#define GL_DYNAMIC_DRAW          0x88E8		  
#define GL_FRAGMENT_SHADER       0x8B30	  
#define GL_VERTEX_SHADER         0x8B31		  
#define GL_COMPILE_STATUS        0x8B81		  
#define GL_LINK_STATUS           0x8B82		  
#define GL_INFO_LOG_LENGTH       0x8B84	  
#define GL_TEXTURE0              0x84C0			  
#define GL_ELEMENT_ARRAY_BUFFER  0x8893 		  
#define GL_CLAMP_TO_EDGE         0x812F
#define GL_CLAMP_TO_BORDER       0x812D
#define GL_FRAMEBUFFER           0x8D40


typedef void   (APIENTRY* PFNGLATTACHSHADERPROC) (GLuint program, GLuint shader);
extern  PFNGLATTACHSHADERPROC glAttachShader;

typedef void   (APIENTRY* PFNGLBINDBUFFERPROC) (GLenum target, GLuint buffer);
extern  PFNGLBINDBUFFERPROC glBindBuffer;

typedef void   (APIENTRY* PFNGLBINDVERTEXARRAYPROC) (GLuint array);
extern  PFNGLBINDVERTEXARRAYPROC glBindVertexArray;

typedef void   (APIENTRY* PFNGLBUFFERDATAPROC) (GLenum target, ptrdiff_t size, const GLvoid* data, GLenum usage);
extern  PFNGLBUFFERDATAPROC glBufferData;

typedef void   (APIENTRY* PFNGLCOMPILESHADERPROC) (GLuint shader);
extern  PFNGLCOMPILESHADERPROC glCompileShader;

typedef GLuint(APIENTRY* PFNGLCREATEPROGRAMPROC) (void);
extern  PFNGLCREATEPROGRAMPROC glCreateProgram;

typedef GLuint(APIENTRY* PFNGLCREATESHADERPROC) (GLenum type);
extern  PFNGLCREATESHADERPROC glCreateShader;

typedef void   (APIENTRY* PFNGLDELETEBUFFERSPROC) (GLsizei n, const GLuint* buffers);
extern  PFNGLDELETEBUFFERSPROC glDeleteBuffers;

typedef void   (APIENTRY* PFNGLDELETEPROGRAMPROC) (GLuint program);
extern  PFNGLDELETEPROGRAMPROC glDeleteProgram;

typedef void   (APIENTRY* PFNGLDELETESHADERPROC) (GLuint shader);
extern  PFNGLDELETESHADERPROC glDeleteShader;

typedef void   (APIENTRY* PFNGLDELETEVERTEXARRAYSPROC) (GLsizei n, const GLuint* arrays);
extern  PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArrays;

typedef void   (APIENTRY* PFNGLDETACHSHADERPROC) (GLuint program, GLuint shader);
extern  PFNGLDETACHSHADERPROC glDetachShader;

typedef void   (APIENTRY* PFNGLENABLEVERTEXATTRIBARRAYPROC) (GLuint index);
extern  PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;

typedef void   (APIENTRY* PFNGLGENBUFFERSPROC) (GLsizei n, GLuint* buffers);
extern  PFNGLGENBUFFERSPROC glGenBuffers;

typedef void   (APIENTRY* PFNGLGENVERTEXARRAYSPROC) (GLsizei n, GLuint* arrays);
extern  PFNGLGENVERTEXARRAYSPROC glGenVertexArrays;

typedef GLint(APIENTRY* PFNGLGETATTRIBLOCATIONPROC) (GLuint program, const char* name);
extern  PFNGLGETATTRIBLOCATIONPROC glGetAttribLocation;

typedef void   (APIENTRY* PFNGLGETPROGRAMINFOLOGPROC) (GLuint program, GLsizei bufSize, GLsizei* length, char* infoLog);
extern  PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog;

typedef void   (APIENTRY* PFNGLGETPROGRAMIVPROC) (GLuint program, GLenum pname, GLint* params);
extern  PFNGLGETPROGRAMIVPROC glGetProgramiv;

typedef void   (APIENTRY* PFNGLGETSHADERINFOLOGPROC) (GLuint shader, GLsizei bufSize, GLsizei* length, char* infoLog);
extern  PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;

typedef void   (APIENTRY* PFNGLGETSHADERIVPROC) (GLuint shader, GLenum pname, GLint* params);
extern  PFNGLGETSHADERIVPROC glGetShaderiv;

typedef void   (APIENTRY* PFNGLLINKPROGRAMPROC) (GLuint program);
extern  PFNGLLINKPROGRAMPROC glLinkProgram;

typedef void   (APIENTRY* PFNGLSHADERSOURCEPROC) (GLuint shader, GLsizei count, const char** string, const GLint* length);
extern  PFNGLSHADERSOURCEPROC glShaderSource;

typedef void   (APIENTRY* PFNGLUSEPROGRAMPROC) (GLuint program);
extern  PFNGLUSEPROGRAMPROC glUseProgram;

typedef void   (APIENTRY* PFNGLVERTEXATTRIBPOINTERPROC) (GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* pointer);
extern  PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;

typedef void   (APIENTRY* PFNGLBINDATTRIBLOCATIONPROC) (GLuint program, GLuint index, const char* name);
extern  PFNGLBINDATTRIBLOCATIONPROC glBindAttribLocation;

typedef GLint(APIENTRY* PFNGLGETUNIFORMLOCATIONPROC) (GLuint program, const char* name);
extern  PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation;

typedef void   (APIENTRY* PFNGLUNIFORMMATRIX4FVPROC) (GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
extern  PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv;

typedef void   (APIENTRY* PFNGLACTIVETEXTUREPROC) (GLenum texture);
extern  PFNGLACTIVETEXTUREPROC glActiveTexture;

typedef void   (APIENTRY* PFNGLUNIFORM1IPROC) (GLint location, GLint v0);
extern  PFNGLUNIFORM1IPROC glUniform1i;

typedef void   (APIENTRY* PFNGLUNIFORM1FPROC) (GLint location, GLfloat v0);
extern  PFNGLUNIFORM1FPROC glUniform1f;

typedef void   (APIENTRY* PFNGLGENERATEMIPMAPPROC) (GLenum target);
extern  PFNGLGENERATEMIPMAPPROC glGenerateMipmap;

typedef void   (APIENTRY* PFNGLDISABLEVERTEXATTRIBARRAYPROC) (GLuint index);
extern  PFNGLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArray;

typedef void   (APIENTRY* PFNGLUNIFORM2FVPROC) (GLint location, GLsizei count, const GLfloat* value);
extern  PFNGLUNIFORM2FVPROC glUniform2fv;

typedef void   (APIENTRY* PFNGLUNIFORM3FVPROC) (GLint location, GLsizei count, const GLfloat* value);
extern  PFNGLUNIFORM3FVPROC glUniform3fv;

typedef void   (APIENTRY* PFNGLUNIFORM4FVPROC) (GLint location, GLsizei count, const GLfloat* value);
extern  PFNGLUNIFORM4FVPROC glUniform4fv;

typedef void   (APIENTRY* PFNGLBUFFERSUBDATAPROC)  (GLenum target, ptrdiff_t offset, ptrdiff_t size, const void* data);
extern  PFNGLBUFFERSUBDATAPROC glBufferSubData;

typedef void   (APIENTRY* PFNGLGENFRAMEBUFFERPROC) (GLsizei n, const GLuint* buffers);
extern PFNGLGENFRAMEBUFFERPROC glGenFramebuffers;

typedef void   (APIENTRY* PFNGLBINDFRAMEBUFFERPROC) (GLenum target, GLuint buffer);
extern PFNGLBINDFRAMEBUFFERPROC glBindFramebuffer;

// TODO:  These are the incorrect types to be using
typedef void   (APIENTRY* PFNGLGETBUFFERSUBDATA) (GLenum target, ptrdiff_t offset, ptrdiff_t size, void* data);
extern PFNGLGETBUFFERSUBDATA glGetBufferSubData;

typedef void   (APIENTRY* PFNGLDELETEFRAMEBUFFERS) (GLsizei n, const GLuint* buffer);
extern PFNGLDELETEFRAMEBUFFERS glDeleteFramebuffers;

typedef void   (APIENTRY* PFNGLGENTEXTURE) (GLsizei n, const GLuint* buffer);
extern PFNGLGENTEXTURE glGenTexture;


#endif //__NL_GL_WIN32_H__