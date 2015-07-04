///////////////////////////////////////////////////////////////////////////////
// OpenGL Support
///////////////////////////////////////////////////////////////////////////////

#typedef unsigned int GLenum
#typedef unsigned char GLboolean
#typedef unsigned int GLbitfield
#typedef signed char GLbyte
#typedef short GLshort
#typedef int GLint
#typedef int GLsizei
#typedef unsigned char GLubyte
#typedef unsigned short GLushort
#typedef unsigned int GLuint
#typedef float GLfloat
#typedef float GLclampf
#typedef double GLdouble
#typedef double GLclampd
#typedef void GLvoid

%builtin void glAccum (GLenum op, GLfloat value)
%builtin void glAlphaFunc (GLenum func, GLclampf ref)
%builtin GLboolean glAreTexturesResident (GLsizei n, const GLuint *textures, GLboolean *residences)
%builtin void glArrayElement (GLint i)
%builtin void glBegin (GLenum mode)
%builtin void glBindTexture (GLenum target, GLuint texture)
%builtin void glBitmap (GLsizei width, GLsizei height, GLfloat xorig, GLfloat yorig, GLfloat xmove, GLfloat ymove, const GLubyte *bitmap)
%builtin void glBlendFunc (GLenum sfactor, GLenum dfactor)
%builtin void glCallList (GLuint list)
%builtin void glCallLists (GLsizei n, GLenum type, const GLvoid *lists)
%builtin void glClear (GLbitfield mask)
%builtin void glClearAccum (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
%builtin void glClearColor (GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha)
%builtin void glClearDepth (GLclampd depth)
%builtin void glClearIndex (GLfloat c)
%builtin void glClearStencil (GLint s)
//%builtin void glClipPlane (GLenum plane, const GLdouble *equation)
%builtin %alias glColor3 void glColor3f (GLfloat red, GLfloat green, GLfloat blue)
%builtin %alias glColor4 void glColor4f (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
%builtin void glColorMask (GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha)
%builtin void glColorMaterial (GLenum face, GLenum mode)
//%builtin void glColorPointer (GLint size, GLenum type, GLsizei stride, const GLvoid *pointer)
%builtin void glCopyPixels (GLint x, GLint y, GLsizei width, GLsizei height, GLenum type)
%builtin void glCopyTexImage1D (GLenum target, GLint level, GLenum internalFormat, GLint x, GLint y, GLsizei width, GLint border)
%builtin void glCopyTexImage2D (GLenum target, GLint level, GLenum internalFormat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border)
%builtin void glCopyTexSubImage1D (GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width)
%builtin void glCopyTexSubImage2D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height)
%builtin void glCullFace (GLenum mode)
%builtin void glDeleteLists (GLuint list, GLsizei range)
//%builtin void glDeleteTextures (GLsizei n, const GLuint *textures)
%builtin void glDepthFunc (GLenum func)
%builtin void glDepthMask (GLboolean flag)
%builtin void glDepthRange (GLclampd zNear, GLclampd zFar)
%builtin void glDisable (GLenum cap)
%builtin void glDisableClientState (GLenum array)
%builtin void glDrawArrays (GLenum mode, GLint first, GLsizei count)
%builtin void glDrawBuffer (GLenum mode)
//%builtin void glDrawElements (GLenum mode, GLsizei count, GLenum type, const GLvoid *indices)
//%builtin void glDrawPixels (GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *pixels)
%builtin void glEdgeFlag (GLboolean flag)
//%builtin void glEdgeFlagPointer (GLsizei stride, const GLvoid *pointer)
//%builtin void glEdgeFlagv (const GLboolean *flag)
%builtin void glEnable (GLenum cap)
%builtin void glEnableClientState (GLenum array)
%builtin void glEnd ()
%builtin void glEndList ()
%builtin %alias glEvalCoord1 void glEvalCoord1f (GLfloat u)
%builtin %alias glEvalCoord2 void glEvalCoord2f (GLfloat u, GLfloat v)
%builtin void glEvalMesh1 (GLenum mode, GLint i1, GLint i2)
%builtin void glEvalMesh2 (GLenum mode, GLint i1, GLint i2, GLint j1, GLint j2)
%builtin void glEvalPoint1 (GLint i)
%builtin void glEvalPoint2 (GLint i, GLint j)
//%builtin void glFeedbackBuffer (GLsizei size, GLenum type, GLfloat *buffer)
%builtin void glFinish ()
%builtin void glFlush ()
%builtin %alias glFog void glFogf (GLenum pname, GLfloat param)
%builtin void glFrontFace (GLenum mode)
%builtin void glFrustum (GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar)
%builtin GLuint glGenLists (GLsizei range)
//%builtin void glGenTextures (GLsizei n, GLuint *textures)
//%builtin void glGetBooleanv (GLenum pname, GLboolean *params)
//%builtin void glGetClipPlane (GLenum plane, GLdouble *equation)
//%builtin void glGetDoublev (GLenum pname, GLdouble *params)
%builtin GLenum glGetError ()
//%builtin void glGetFloatv (GLenum pname, GLfloat *params)
//%builtin void glGetIntegerv (GLenum pname, GLint *params)
//%builtin void glGetLightfv (GLenum light, GLenum pname, GLfloat *params)
// %builtin void glGetMapfv (GLenum target, GLenum query, GLfloat *v)
//%builtin void glGetMaterialfv (GLenum face, GLenum pname, GLfloat *params)
//%builtin void glGetPixelMapfv (GLenum map, GLfloat *values)
//%builtin void glGetPointerv (GLenum pname, GLvoid* *params)
//%builtin void glGetPolygonStipple (GLubyte *mask)
%builtin const GLubyte *glGetString (GLenum name)
//%builtin void glGetTexEnvfv (GLenum target, GLenum pname, GLfloat *params)
//%builtin void glGetTexGenfv (GLenum coord, GLenum pname, GLfloat *params)
//%builtin void glGetTexImage (GLenum target, GLint level, GLenum format, GLenum type, GLvoid *pixels)
//%builtin void glGetTexLevelParameterfv (GLenum target, GLint level, GLenum pname, GLfloat *params)
//%builtin void glGetTexParameterfv (GLenum target, GLenum pname, GLfloat *params)
%builtin void glHint (GLenum target, GLenum mode)
%builtin void glIndexMask (GLuint mask)
//%builtin void glIndexPointer (GLenum type, GLsizei stride, const GLvoid *pointer)
%builtin %alias glIndex void glIndexf (GLfloat c)
%builtin void glInitNames ()
//%builtin void glInterleavedArrays (GLenum format, GLsizei stride, const GLvoid *pointer)
%builtin GLboolean glIsEnabled (GLenum cap)
%builtin GLboolean glIsList (GLuint list)
%builtin GLboolean glIsTexture (GLuint texture)
%builtin %alias glLightModel void glLightModelf (GLenum pname, GLfloat param)
%builtin %alias glLight void glLightf (GLenum light, GLenum pname, GLfloat param)
%builtin void glLineStipple (GLint factor, GLushort pattern)
%builtin void glLineWidth (GLfloat width)
%builtin void glListBase (GLuint base)
%builtin void glLoadIdentity ()
//%builtin void glLoadMatrixf (const GLfloat *m)
%builtin void glLoadName (GLuint name)
%builtin void glLogicOp (GLenum opcode)
//%builtin void glMap1f (GLenum target, GLfloat u1, GLfloat u2, GLint stride, GLint order, const GLfloat *points)
//%builtin void glMap2f (GLenum target, GLfloat u1, GLfloat u2, GLint ustride, GLint uorder, GLfloat v1, GLfloat v2, GLint vstride, GLint vorder, const GLfloat *points)
%builtin %alias glMapGrid1 void glMapGrid1f (GLint un, GLfloat u1, GLfloat u2)
%builtin %alias glMapGrid2 void glMapGrid2f (GLint un, GLfloat u1, GLfloat u2, GLint vn, GLfloat v1, GLfloat v2)
%builtin %alias glMaterial void glMaterialf (GLenum face, GLenum pname, GLfloat param)
%builtin void glMatrixMode (GLenum mode)
//%builtin void glMultMatrixf (const GLfloat *m)
%builtin void glNewList (GLuint list, GLenum mode)
%builtin void glNormal3f (GLfloat nx, GLfloat ny, GLfloat nz)
//%builtin void glNormalPointer (GLenum type, GLsizei stride, const GLvoid *pointer)
%builtin void glOrtho (GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar)
%builtin void glPassThrough (GLfloat token)
//%builtin void glPixelMapfv (GLenum map, GLsizei mapsize, const GLfloat *values)
%builtin %alias glPixelStore void glPixelStoref (GLenum pname, GLfloat param)
%builtin %alias glPixelTransfer void glPixelTransferf (GLenum pname, GLfloat param)
%builtin void glPixelZoom (GLfloat xfactor, GLfloat yfactor)
%builtin void glPointSize (GLfloat size)
%builtin void glPolygonMode (GLenum face, GLenum mode)
%builtin void glPolygonOffset (GLfloat factor, GLfloat units)
//%builtin void glPolygonStipple (const GLubyte *mask)
%builtin void glPopAttrib ()
%builtin void glPopClientAttrib ()
%builtin void glPopMatrix ()
%builtin void glPopName ()
//%builtin void glPrioritizeTextures (GLsizei n, const GLuint *textures, const GLclampf *priorities)
%builtin void glPushAttrib (GLbitfield mask)
%builtin void glPushClientAttrib (GLbitfield mask)
%builtin void glPushMatrix ()
%builtin void glPushName (GLuint name)
%builtin %alias glRasterPos2 void glRasterPos2f (GLfloat x, GLfloat y)
%builtin %alias glRasterPos3 void glRasterPos3f (GLfloat x, GLfloat y, GLfloat z)
%builtin %alias glRasterPos4 void glRasterPos4f (GLfloat x, GLfloat y, GLfloat z, GLfloat w)
%builtin void glReadBuffer (GLenum mode)
%builtin void glReadPixels (GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid *pixels)
%builtin %alias glRect void glRectf (GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2)
%builtin GLint glRenderMode (GLenum mode)
%builtin %alias glRotate void glRotatef (GLfloat angle, GLfloat x, GLfloat y, GLfloat z)
%builtin %alias glScale void glScalef (GLfloat x, GLfloat y, GLfloat z)
%builtin %alias glScissor void glScissor (GLint x, GLint y, GLsizei width, GLsizei height)
//%builtin void glSelectBuffer (GLsizei size, GLuint *buffer)
%builtin void glShadeModel (GLenum mode)
%builtin void glStencilFunc (GLenum func, GLint ref, GLuint mask)
%builtin void glStencilMask (GLuint mask)
%builtin void glStencilOp (GLenum fail, GLenum zfail, GLenum zpass)
%builtin %alias glTexCoord1 void glTexCoord1f (GLfloat s)
%builtin %alias glTexCoord2 void glTexCoord2f (GLfloat s, GLfloat t)
%builtin %alias glTexCoord3 void glTexCoord3f (GLfloat s, GLfloat t, GLfloat r)
%builtin %alias glTexCoord4 void glTexCoord4f (GLfloat s, GLfloat t, GLfloat r, GLfloat q)
//%builtin void glTexCoordPointer (GLint size, GLenum type, GLsizei stride, const GLvoid *pointer)
%builtin %alias glTexEnv void glTexEnvf (GLenum target, GLenum pname, GLfloat param)
%builtin %alias glTexGen void glTexGenf (GLenum coord, GLenum pname, GLfloat param)
//%builtin void glTexImage1D (GLenum target, GLint level, GLint internalformat, GLsizei width, GLint border, GLenum format, GLenum type, const GLvoid *pixels)
//%builtin void glTexImage2D (GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid *pixels)
%builtin %alias glTexParameter void glTexParameterf (GLenum target, GLenum pname, GLfloat param)
//%builtin void glTexSubImage1D (GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const GLvoid *pixels)
//%builtin void glTexSubImage2D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *pixels)
%builtin %alias glTranslate void glTranslatef (GLfloat x, GLfloat y, GLfloat z)
%builtin %alias glVertex2 void glVertex2f (GLfloat x, GLfloat y)
%builtin %alias glVertex3 void glVertex3f (GLfloat x, GLfloat y, GLfloat z)
%builtin %alias glVertex4 void glVertex4f (GLfloat x, GLfloat y, GLfloat z, GLfloat w)
//%builtin void glVertexPointer (GLint size, GLenum type, GLsizei stride, const GLvoid *pointer)
%builtin void glViewport (GLint x, GLint y, GLsizei width, GLsizei height)

// #defines from GL.H
// Commented out values are duplicates

// Version 
%num GL_VERSION_1_1 

// AccumOp 
%num GL_ACCUM 
%num GL_LOAD 
%num GL_RETURN 
%num GL_MULT 
%num GL_ADD 

// AlphaFunction 
%num GL_NEVER 
%num GL_LESS 
%num GL_EQUAL 
%num GL_LEQUAL 
%num GL_GREATER 
%num GL_NOTEQUAL 
%num GL_GEQUAL 
%num GL_ALWAYS 

// AttribMask 
%num GL_CURRENT_BIT 
%num GL_POINT_BIT 
%num GL_LINE_BIT 
%num GL_POLYGON_BIT 
%num GL_POLYGON_STIPPLE_BIT 
%num GL_PIXEL_MODE_BIT 
%num GL_LIGHTING_BIT 
%num GL_FOG_BIT 
%num GL_DEPTH_BUFFER_BIT 
%num GL_ACCUM_BUFFER_BIT 
%num GL_STENCIL_BUFFER_BIT 
%num GL_VIEWPORT_BIT 
%num GL_TRANSFORM_BIT 
%num GL_ENABLE_BIT 
%num GL_COLOR_BUFFER_BIT 
%num GL_HINT_BIT 
%num GL_EVAL_BIT 
%num GL_LIST_BIT 
%num GL_TEXTURE_BIT 
%num GL_SCISSOR_BIT 
%num GL_ALL_ATTRIB_BITS 

// BeginMode 
%num GL_POINTS 
%num GL_LINES 
%num GL_LINE_LOOP 
%num GL_LINE_STRIP 
%num GL_TRIANGLES 
%num GL_TRIANGLE_STRIP 
%num GL_TRIANGLE_FAN 
%num GL_QUADS 
%num GL_QUAD_STRIP 
%num GL_POLYGON 

// BlendingFactorDest 
%num GL_ZERO 
%num GL_ONE 
%num GL_SRC_COLOR 
%num GL_ONE_MINUS_SRC_COLOR 
%num GL_SRC_ALPHA 
%num GL_ONE_MINUS_SRC_ALPHA 
%num GL_DST_ALPHA 
%num GL_ONE_MINUS_DST_ALPHA 

// BlendingFactorSrc 
//      GL_ZERO 
//      GL_ONE 
%num GL_DST_COLOR 
%num GL_ONE_MINUS_DST_COLOR 
%num GL_SRC_ALPHA_SATURATE 
//      GL_SRC_ALPHA 
//      GL_ONE_MINUS_SRC_ALPHA 
//      GL_DST_ALPHA 
//      GL_ONE_MINUS_DST_ALPHA 

// Boolean 
%num GL_TRUE 
%num GL_FALSE 

// ClearBufferMask 
//      GL_COLOR_BUFFER_BIT 
//      GL_ACCUM_BUFFER_BIT 
//      GL_STENCIL_BUFFER_BIT 
//      GL_DEPTH_BUFFER_BIT 

// ClientArrayType 
//      GL_VERTEX_ARRAY 
//      GL_NORMAL_ARRAY 
//      GL_COLOR_ARRAY 
//      GL_INDEX_ARRAY 
//      GL_TEXTURE_COORD_ARRAY 
//      GL_EDGE_FLAG_ARRAY 

// ClipPlaneName 
%num GL_CLIP_PLANE0 
%num GL_CLIP_PLANE1 
%num GL_CLIP_PLANE2 
%num GL_CLIP_PLANE3 
%num GL_CLIP_PLANE4 
%num GL_CLIP_PLANE5 

// ColorMaterialFace 
//      GL_FRONT 
//      GL_BACK 
//      GL_FRONT_AND_BACK 

// ColorMaterialParameter 
//      GL_AMBIENT 
//      GL_DIFFUSE 
//      GL_SPECULAR 
//      GL_EMISSION 
//      GL_AMBIENT_AND_DIFFUSE 

// ColorPointerType 
//      GL_BYTE 
//      GL_UNSIGNED_BYTE 
//      GL_SHORT 
//      GL_UNSIGNED_SHORT 
//      GL_INT 
//      GL_UNSIGNED_INT 
//      GL_FLOAT 
//      GL_DOUBLE 

// CullFaceMode 
//      GL_FRONT 
//      GL_BACK 
//      GL_FRONT_AND_BACK 

// DataType 
%num GL_BYTE 
%num GL_UNSIGNED_BYTE 
%num GL_SHORT 
%num GL_UNSIGNED_SHORT 
%num GL_INT 
%num GL_UNSIGNED_INT 
%num GL_FLOAT 
%num GL_2_BYTES 
%num GL_3_BYTES 
%num GL_4_BYTES 
%num GL_DOUBLE 

// DepthFunction 
//      GL_NEVER 
//      GL_LESS 
//      GL_EQUAL 
//      GL_LEQUAL 
//      GL_GREATER 
//      GL_NOTEQUAL 
//      GL_GEQUAL 
//      GL_ALWAYS 

// DrawBufferMode 
%num GL_NONE 
%num GL_FRONT_LEFT 
%num GL_FRONT_RIGHT 
%num GL_BACK_LEFT 
%num GL_BACK_RIGHT 
%num GL_FRONT 
%num GL_BACK 
%num GL_LEFT 
%num GL_RIGHT 
%num GL_FRONT_AND_BACK 
%num GL_AUX0 
%num GL_AUX1 
%num GL_AUX2 
%num GL_AUX3 

// Enable 
//      GL_FOG 
//      GL_LIGHTING 
//      GL_TEXTURE_1D 
//      GL_TEXTURE_2D 
//      GL_LINE_STIPPLE 
//      GL_POLYGON_STIPPLE 
//      GL_CULL_FACE 
//      GL_ALPHA_TEST 
//      GL_BLEND 
//      GL_INDEX_LOGIC_OP 
//      GL_COLOR_LOGIC_OP 
//      GL_DITHER 
//      GL_STENCIL_TEST 
//      GL_DEPTH_TEST 
//      GL_CLIP_PLANE0 
//      GL_CLIP_PLANE1 
//      GL_CLIP_PLANE2 
//      GL_CLIP_PLANE3 
//      GL_CLIP_PLANE4 
//      GL_CLIP_PLANE5 
//      GL_LIGHT0 
//      GL_LIGHT1 
//      GL_LIGHT2 
//      GL_LIGHT3 
//      GL_LIGHT4 
//      GL_LIGHT5 
//      GL_LIGHT6 
//      GL_LIGHT7 
//      GL_TEXTURE_GEN_S 
//      GL_TEXTURE_GEN_T 
//      GL_TEXTURE_GEN_R 
//      GL_TEXTURE_GEN_Q 
//      GL_MAP1_VERTEX_3 
//      GL_MAP1_VERTEX_4 
//      GL_MAP1_COLOR_4 
//      GL_MAP1_INDEX 
//      GL_MAP1_NORMAL 
//      GL_MAP1_TEXTURE_COORD_1 
//      GL_MAP1_TEXTURE_COORD_2 
//      GL_MAP1_TEXTURE_COORD_3 
//      GL_MAP1_TEXTURE_COORD_4 
//      GL_MAP2_VERTEX_3 
//      GL_MAP2_VERTEX_4 
//      GL_MAP2_COLOR_4 
//      GL_MAP2_INDEX 
//      GL_MAP2_NORMAL 
//      GL_MAP2_TEXTURE_COORD_1 
//      GL_MAP2_TEXTURE_COORD_2 
//      GL_MAP2_TEXTURE_COORD_3 
//      GL_MAP2_TEXTURE_COORD_4 
//      GL_POINT_SMOOTH 
//      GL_LINE_SMOOTH 
//      GL_POLYGON_SMOOTH 
//      GL_SCISSOR_TEST 
//      GL_COLOR_MATERIAL 
//      GL_NORMALIZE 
//      GL_AUTO_NORMAL 
//      GL_VERTEX_ARRAY 
//      GL_NORMAL_ARRAY 
//      GL_COLOR_ARRAY 
//      GL_INDEX_ARRAY 
//      GL_TEXTURE_COORD_ARRAY 
//      GL_EDGE_FLAG_ARRAY 
//      GL_POLYGON_OFFSET_POINT 
//      GL_POLYGON_OFFSET_LINE 
//      GL_POLYGON_OFFSET_FILL 

// ErrorCode 
%num GL_NO_ERROR 
%num GL_INVALID_ENUM 
%num GL_INVALID_VALUE 
%num GL_INVALID_OPERATION 
%num GL_STACK_OVERFLOW 
%num GL_STACK_UNDERFLOW 
%num GL_OUT_OF_MEMORY 

// FeedBackMode 
%num GL_2D 
%num GL_3D 
%num GL_3D_COLOR 
%num GL_3D_COLOR_TEXTURE 
%num GL_4D_COLOR_TEXTURE 

// FeedBackToken 
%num GL_PASS_THROUGH_TOKEN 
%num GL_POINT_TOKEN 
%num GL_LINE_TOKEN 
%num GL_POLYGON_TOKEN 
%num GL_BITMAP_TOKEN 
%num GL_DRAW_PIXEL_TOKEN 
%num GL_COPY_PIXEL_TOKEN 
%num GL_LINE_RESET_TOKEN 

// FogMode 
//      GL_LINEAR 
%num GL_EXP 
%num GL_EXP2 


// FogParameter 
//      GL_FOG_COLOR 
//      GL_FOG_DENSITY 
//      GL_FOG_END 
//      GL_FOG_INDEX 
//      GL_FOG_MODE 
//      GL_FOG_START 

// FrontFaceDirection 
%num GL_CW 
%num GL_CCW 

// GetMapTarget 
%num GL_COEFF 
%num GL_ORDER 
%num GL_DOMAIN 

// GetPixelMap 
//      GL_PIXEL_MAP_I_TO_I 
//      GL_PIXEL_MAP_S_TO_S 
//      GL_PIXEL_MAP_I_TO_R 
//      GL_PIXEL_MAP_I_TO_G 
//      GL_PIXEL_MAP_I_TO_B 
//      GL_PIXEL_MAP_I_TO_A 
//      GL_PIXEL_MAP_R_TO_R 
//      GL_PIXEL_MAP_G_TO_G 
//      GL_PIXEL_MAP_B_TO_B 
//      GL_PIXEL_MAP_A_TO_A 

// GetPointerTarget 
//      GL_VERTEX_ARRAY_POINTER 
//      GL_NORMAL_ARRAY_POINTER 
//      GL_COLOR_ARRAY_POINTER 
//      GL_INDEX_ARRAY_POINTER 
//      GL_TEXTURE_COORD_ARRAY_POINTER 
//      GL_EDGE_FLAG_ARRAY_POINTER 

// GetTarget 
%num GL_CURRENT_COLOR 
%num GL_CURRENT_INDEX 
%num GL_CURRENT_NORMAL 
%num GL_CURRENT_TEXTURE_COORDS 
%num GL_CURRENT_RASTER_COLOR 
%num GL_CURRENT_RASTER_INDEX 
%num GL_CURRENT_RASTER_TEXTURE_COORDS 
%num GL_CURRENT_RASTER_POSITION 
%num GL_CURRENT_RASTER_POSITION_VALID 
%num GL_CURRENT_RASTER_DISTANCE 
%num GL_POINT_SMOOTH 
%num GL_POINT_SIZE 
%num GL_POINT_SIZE_RANGE 
%num GL_POINT_SIZE_GRANULARITY 
%num GL_LINE_SMOOTH 
%num GL_LINE_WIDTH 
%num GL_LINE_WIDTH_RANGE 
%num GL_LINE_WIDTH_GRANULARITY 
%num GL_LINE_STIPPLE 
%num GL_LINE_STIPPLE_PATTERN 
%num GL_LINE_STIPPLE_REPEAT 
%num GL_LIST_MODE 
%num GL_MAX_LIST_NESTING 
%num GL_LIST_BASE 
%num GL_LIST_INDEX 
%num GL_POLYGON_MODE 
%num GL_POLYGON_SMOOTH 
%num GL_POLYGON_STIPPLE 
%num GL_EDGE_FLAG 
%num GL_CULL_FACE 
%num GL_CULL_FACE_MODE 
%num GL_FRONT_FACE 
%num GL_LIGHTING 
%num GL_LIGHT_MODEL_LOCAL_VIEWER 
%num GL_LIGHT_MODEL_TWO_SIDE 
%num GL_LIGHT_MODEL_AMBIENT 
%num GL_SHADE_MODEL 
%num GL_COLOR_MATERIAL_FACE 
%num GL_COLOR_MATERIAL_PARAMETER 
%num GL_COLOR_MATERIAL 
%num GL_FOG 
%num GL_FOG_INDEX 
%num GL_FOG_DENSITY 
%num GL_FOG_START 
%num GL_FOG_END 
%num GL_FOG_MODE 
%num GL_FOG_COLOR 
%num GL_DEPTH_RANGE 
%num GL_DEPTH_TEST 
%num GL_DEPTH_WRITEMASK 
%num GL_DEPTH_CLEAR_VALUE 
%num GL_DEPTH_FUNC 
%num GL_ACCUM_CLEAR_VALUE 
%num GL_STENCIL_TEST 
%num GL_STENCIL_CLEAR_VALUE 
%num GL_STENCIL_FUNC 
%num GL_STENCIL_VALUE_MASK 
%num GL_STENCIL_FAIL 
%num GL_STENCIL_PASS_DEPTH_FAIL 
%num GL_STENCIL_PASS_DEPTH_PASS 
%num GL_STENCIL_REF 
%num GL_STENCIL_WRITEMASK 
%num GL_MATRIX_MODE 
%num GL_NORMALIZE 
%num GL_VIEWPORT 
%num GL_MODELVIEW_STACK_DEPTH 
%num GL_PROJECTION_STACK_DEPTH 
%num GL_TEXTURE_STACK_DEPTH 
%num GL_MODELVIEW_MATRIX 
%num GL_PROJECTION_MATRIX 
%num GL_TEXTURE_MATRIX 
%num GL_ATTRIB_STACK_DEPTH 
%num GL_CLIENT_ATTRIB_STACK_DEPTH 
%num GL_ALPHA_TEST 
%num GL_ALPHA_TEST_FUNC 
%num GL_ALPHA_TEST_REF 
%num GL_DITHER 
%num GL_BLEND_DST 
%num GL_BLEND_SRC 
%num GL_BLEND 
%num GL_LOGIC_OP_MODE 
%num GL_INDEX_LOGIC_OP 
%num GL_COLOR_LOGIC_OP 
%num GL_AUX_BUFFERS 
%num GL_DRAW_BUFFER 
%num GL_READ_BUFFER 
%num GL_SCISSOR_BOX 
%num GL_SCISSOR_TEST 
%num GL_INDEX_CLEAR_VALUE 
%num GL_INDEX_WRITEMASK 
%num GL_COLOR_CLEAR_VALUE 
%num GL_COLOR_WRITEMASK 
%num GL_INDEX_MODE 
%num GL_RGBA_MODE 
%num GL_DOUBLEBUFFER 
%num GL_STEREO 
%num GL_RENDER_MODE 
%num GL_PERSPECTIVE_CORRECTION_HINT 
%num GL_POINT_SMOOTH_HINT 
%num GL_LINE_SMOOTH_HINT 
%num GL_POLYGON_SMOOTH_HINT 
%num GL_FOG_HINT 
%num GL_TEXTURE_GEN_S 
%num GL_TEXTURE_GEN_T 
%num GL_TEXTURE_GEN_R 
%num GL_TEXTURE_GEN_Q 
%num GL_PIXEL_MAP_I_TO_I 
%num GL_PIXEL_MAP_S_TO_S 
%num GL_PIXEL_MAP_I_TO_R 
%num GL_PIXEL_MAP_I_TO_G 
%num GL_PIXEL_MAP_I_TO_B 
%num GL_PIXEL_MAP_I_TO_A 
%num GL_PIXEL_MAP_R_TO_R 
%num GL_PIXEL_MAP_G_TO_G 
%num GL_PIXEL_MAP_B_TO_B 
%num GL_PIXEL_MAP_A_TO_A 
%num GL_PIXEL_MAP_I_TO_I_SIZE 
%num GL_PIXEL_MAP_S_TO_S_SIZE 
%num GL_PIXEL_MAP_I_TO_R_SIZE 
%num GL_PIXEL_MAP_I_TO_G_SIZE 
%num GL_PIXEL_MAP_I_TO_B_SIZE 
%num GL_PIXEL_MAP_I_TO_A_SIZE 
%num GL_PIXEL_MAP_R_TO_R_SIZE 
%num GL_PIXEL_MAP_G_TO_G_SIZE 
%num GL_PIXEL_MAP_B_TO_B_SIZE 
%num GL_PIXEL_MAP_A_TO_A_SIZE 
%num GL_UNPACK_SWAP_BYTES 
%num GL_UNPACK_LSB_FIRST 
%num GL_UNPACK_ROW_LENGTH 
%num GL_UNPACK_SKIP_ROWS 
%num GL_UNPACK_SKIP_PIXELS 
%num GL_UNPACK_ALIGNMENT 
%num GL_PACK_SWAP_BYTES 
%num GL_PACK_LSB_FIRST 
%num GL_PACK_ROW_LENGTH 
%num GL_PACK_SKIP_ROWS 
%num GL_PACK_SKIP_PIXELS 
%num GL_PACK_ALIGNMENT 
%num GL_MAP_COLOR 
%num GL_MAP_STENCIL 
%num GL_INDEX_SHIFT 
%num GL_INDEX_OFFSET 
%num GL_RED_SCALE 
%num GL_RED_BIAS 
%num GL_ZOOM_X 
%num GL_ZOOM_Y 
%num GL_GREEN_SCALE 
%num GL_GREEN_BIAS 
%num GL_BLUE_SCALE 
%num GL_BLUE_BIAS 
%num GL_ALPHA_SCALE 
%num GL_ALPHA_BIAS 
%num GL_DEPTH_SCALE 
%num GL_DEPTH_BIAS 
%num GL_MAX_EVAL_ORDER 
%num GL_MAX_LIGHTS 
%num GL_MAX_CLIP_PLANES 
%num GL_MAX_TEXTURE_SIZE 
%num GL_MAX_PIXEL_MAP_TABLE 
%num GL_MAX_ATTRIB_STACK_DEPTH 
%num GL_MAX_MODELVIEW_STACK_DEPTH 
%num GL_MAX_NAME_STACK_DEPTH 
%num GL_MAX_PROJECTION_STACK_DEPTH 
%num GL_MAX_TEXTURE_STACK_DEPTH 
%num GL_MAX_VIEWPORT_DIMS 
%num GL_MAX_CLIENT_ATTRIB_STACK_DEPTH 
%num GL_SUBPIXEL_BITS 
%num GL_INDEX_BITS 
%num GL_RED_BITS 
%num GL_GREEN_BITS 
%num GL_BLUE_BITS 
%num GL_ALPHA_BITS 
%num GL_DEPTH_BITS 
%num GL_STENCIL_BITS 
%num GL_ACCUM_RED_BITS 
%num GL_ACCUM_GREEN_BITS 
%num GL_ACCUM_BLUE_BITS 
%num GL_ACCUM_ALPHA_BITS 
%num GL_NAME_STACK_DEPTH 
%num GL_AUTO_NORMAL 
%num GL_MAP1_COLOR_4 
%num GL_MAP1_INDEX 
%num GL_MAP1_NORMAL 
%num GL_MAP1_TEXTURE_COORD_1 
%num GL_MAP1_TEXTURE_COORD_2 
%num GL_MAP1_TEXTURE_COORD_3 
%num GL_MAP1_TEXTURE_COORD_4 
%num GL_MAP1_VERTEX_3 
%num GL_MAP1_VERTEX_4 
%num GL_MAP2_COLOR_4 
%num GL_MAP2_INDEX 
%num GL_MAP2_NORMAL 
%num GL_MAP2_TEXTURE_COORD_1 
%num GL_MAP2_TEXTURE_COORD_2 
%num GL_MAP2_TEXTURE_COORD_3 
%num GL_MAP2_TEXTURE_COORD_4 
%num GL_MAP2_VERTEX_3 
%num GL_MAP2_VERTEX_4 
%num GL_MAP1_GRID_DOMAIN 
%num GL_MAP1_GRID_SEGMENTS 
%num GL_MAP2_GRID_DOMAIN 
%num GL_MAP2_GRID_SEGMENTS 
%num GL_TEXTURE_1D 
%num GL_TEXTURE_2D 
%num GL_FEEDBACK_BUFFER_POINTER 
%num GL_FEEDBACK_BUFFER_SIZE 
%num GL_FEEDBACK_BUFFER_TYPE 
%num GL_SELECTION_BUFFER_POINTER 
%num GL_SELECTION_BUFFER_SIZE 
//      GL_TEXTURE_BINDING_1D 
//      GL_TEXTURE_BINDING_2D 
//      GL_VERTEX_ARRAY 
//      GL_NORMAL_ARRAY 
//      GL_COLOR_ARRAY 
//      GL_INDEX_ARRAY 
//      GL_TEXTURE_COORD_ARRAY 
//      GL_EDGE_FLAG_ARRAY 
//      GL_VERTEX_ARRAY_SIZE 
//      GL_VERTEX_ARRAY_TYPE 
//      GL_VERTEX_ARRAY_STRIDE 
//      GL_NORMAL_ARRAY_TYPE 
//      GL_NORMAL_ARRAY_STRIDE 
//      GL_COLOR_ARRAY_SIZE 
//      GL_COLOR_ARRAY_TYPE 
//      GL_COLOR_ARRAY_STRIDE 
//      GL_INDEX_ARRAY_TYPE 
//      GL_INDEX_ARRAY_STRIDE 
//      GL_TEXTURE_COORD_ARRAY_SIZE 
//      GL_TEXTURE_COORD_ARRAY_TYPE 
//      GL_TEXTURE_COORD_ARRAY_STRIDE 
//      GL_EDGE_FLAG_ARRAY_STRIDE 
//      GL_POLYGON_OFFSET_FACTOR 
//      GL_POLYGON_OFFSET_UNITS 

// GetTextureParameter 
//      GL_TEXTURE_MAG_FILTER 
//      GL_TEXTURE_MIN_FILTER 
//      GL_TEXTURE_WRAP_S 
//      GL_TEXTURE_WRAP_T 
%num GL_TEXTURE_WIDTH 
%num GL_TEXTURE_HEIGHT 
%num GL_TEXTURE_INTERNAL_FORMAT 
%num GL_TEXTURE_BORDER_COLOR 
%num GL_TEXTURE_BORDER 
//      GL_TEXTURE_RED_SIZE 
//      GL_TEXTURE_GREEN_SIZE 
//      GL_TEXTURE_BLUE_SIZE 
//      GL_TEXTURE_ALPHA_SIZE 
//      GL_TEXTURE_LUMINANCE_SIZE 
//      GL_TEXTURE_INTENSITY_SIZE 
//      GL_TEXTURE_PRIORITY 
//      GL_TEXTURE_RESIDENT 

// HintMode 
%num GL_DONT_CARE 
%num GL_FASTEST 
%num GL_NICEST 

// HintTarget 
//      GL_PERSPECTIVE_CORRECTION_HINT 
//      GL_POINT_SMOOTH_HINT 
//      GL_LINE_SMOOTH_HINT 
//      GL_POLYGON_SMOOTH_HINT 
//      GL_FOG_HINT 
//      GL_PHONG_HINT 

// IndexPointerType 
//      GL_SHORT 
//      GL_INT 
//      GL_FLOAT 
//      GL_DOUBLE 

// LightModelParameter 
//      GL_LIGHT_MODEL_AMBIENT 
//      GL_LIGHT_MODEL_LOCAL_VIEWER 
//      GL_LIGHT_MODEL_TWO_SIDE 

// LightName 
%num GL_LIGHT0 
%num GL_LIGHT1 
%num GL_LIGHT2 
%num GL_LIGHT3 
%num GL_LIGHT4 
%num GL_LIGHT5 
%num GL_LIGHT6 
%num GL_LIGHT7 

// LightParameter 
%num GL_AMBIENT 
%num GL_DIFFUSE 
%num GL_SPECULAR 
%num GL_POSITION 
%num GL_SPOT_DIRECTION 
%num GL_SPOT_EXPONENT 
%num GL_SPOT_CUTOFF 
%num GL_CONSTANT_ATTENUATION 
%num GL_LINEAR_ATTENUATION 
%num GL_QUADRATIC_ATTENUATION 

// InterleavedArrays 
//      GL_V2F 
//      GL_V3F 
//      GL_C4UB_V2F 
//      GL_C4UB_V3F 
//      GL_C3F_V3F 
//      GL_N3F_V3F 
//      GL_C4F_N3F_V3F 
//      GL_T2F_V3F 
//      GL_T4F_V4F 
//      GL_T2F_C4UB_V3F 
//      GL_T2F_C3F_V3F 
//      GL_T2F_N3F_V3F 
//      GL_T2F_C4F_N3F_V3F 
//      GL_T4F_C4F_N3F_V4F 

// ListMode 
%num GL_COMPILE 
%num GL_COMPILE_AND_EXECUTE 

// ListNameType 
//      GL_BYTE 
//      GL_UNSIGNED_BYTE 
//      GL_SHORT 
//      GL_UNSIGNED_SHORT 
//      GL_INT 
//      GL_UNSIGNED_INT 
//      GL_FLOAT 
//      GL_2_BYTES 
//      GL_3_BYTES 
//      GL_4_BYTES 

// LogicOp 
%num GL_CLEAR 
%num GL_AND 
%num GL_AND_REVERSE 
%num GL_COPY 
%num GL_AND_INVERTED 
%num GL_NOOP 
%num GL_XOR 
%num GL_OR 
%num GL_NOR 
%num GL_EQUIV 
%num GL_INVERT 
%num GL_OR_REVERSE 
%num GL_COPY_INVERTED 
%num GL_OR_INVERTED 
%num GL_NAND 
%num GL_SET 

// MapTarget 
//      GL_MAP1_COLOR_4 
//      GL_MAP1_INDEX 
//      GL_MAP1_NORMAL 
//      GL_MAP1_TEXTURE_COORD_1 
//      GL_MAP1_TEXTURE_COORD_2 
//      GL_MAP1_TEXTURE_COORD_3 
//      GL_MAP1_TEXTURE_COORD_4 
//      GL_MAP1_VERTEX_3 
//      GL_MAP1_VERTEX_4 
//      GL_MAP2_COLOR_4 
//      GL_MAP2_INDEX 
//      GL_MAP2_NORMAL 
//      GL_MAP2_TEXTURE_COORD_1 
//      GL_MAP2_TEXTURE_COORD_2 
//      GL_MAP2_TEXTURE_COORD_3 
//      GL_MAP2_TEXTURE_COORD_4 
//      GL_MAP2_VERTEX_3 
//      GL_MAP2_VERTEX_4 

// MaterialFace 
//      GL_FRONT 
//      GL_BACK 
//      GL_FRONT_AND_BACK 

// MaterialParameter 
%num GL_EMISSION 
%num GL_SHININESS 
%num GL_AMBIENT_AND_DIFFUSE 
%num GL_COLOR_INDEXES 
//      GL_AMBIENT 
//      GL_DIFFUSE 
//      GL_SPECULAR 

// MatrixMode 
%num GL_MODELVIEW 
%num GL_PROJECTION 
%num GL_TEXTURE 

// MeshMode1 
//      GL_POINT 
//      GL_LINE 

// MeshMode2 
//      GL_POINT 
//      GL_LINE 
//      GL_FILL 

// NormalPointerType 
//      GL_BYTE 
//      GL_SHORT 
//      GL_INT 
//      GL_FLOAT 
//      GL_DOUBLE 

// PixelCopyType 
%num GL_COLOR 
%num GL_DEPTH 
%num GL_STENCIL 

// PixelFormat 
%num GL_COLOR_INDEX 
%num GL_STENCIL_INDEX 
%num GL_DEPTH_COMPONENT 
%num GL_RED 
%num GL_GREEN 
%num GL_BLUE 
%num GL_ALPHA 
%num GL_RGB 
%num GL_RGBA 
%num GL_LUMINANCE 
%num GL_LUMINANCE_ALPHA 

// PixelMap 
//      GL_PIXEL_MAP_I_TO_I 
//      GL_PIXEL_MAP_S_TO_S 
//      GL_PIXEL_MAP_I_TO_R 
//      GL_PIXEL_MAP_I_TO_G 
//      GL_PIXEL_MAP_I_TO_B 
//      GL_PIXEL_MAP_I_TO_A 
//      GL_PIXEL_MAP_R_TO_R 
//      GL_PIXEL_MAP_G_TO_G 
//      GL_PIXEL_MAP_B_TO_B 
//      GL_PIXEL_MAP_A_TO_A 

// PixelStore 
//      GL_UNPACK_SWAP_BYTES 
//      GL_UNPACK_LSB_FIRST 
//      GL_UNPACK_ROW_LENGTH 
//      GL_UNPACK_SKIP_ROWS 
//      GL_UNPACK_SKIP_PIXELS 
//      GL_UNPACK_ALIGNMENT 
//      GL_PACK_SWAP_BYTES 
//      GL_PACK_LSB_FIRST 
//      GL_PACK_ROW_LENGTH 
//      GL_PACK_SKIP_ROWS 
//      GL_PACK_SKIP_PIXELS 
//      GL_PACK_ALIGNMENT 

// PixelTransfer 
//      GL_MAP_COLOR 
//      GL_MAP_STENCIL 
//      GL_INDEX_SHIFT 
//      GL_INDEX_OFFSET 
//      GL_RED_SCALE 
//      GL_RED_BIAS 
//      GL_GREEN_SCALE 
//      GL_GREEN_BIAS 
//      GL_BLUE_SCALE 
//      GL_BLUE_BIAS 
//      GL_ALPHA_SCALE 
//      GL_ALPHA_BIAS 
//      GL_DEPTH_SCALE 
//      GL_DEPTH_BIAS 

// PixelType 
%num GL_BITMAP 
//      GL_BYTE 
//      GL_UNSIGNED_BYTE 
//      GL_SHORT 
//      GL_UNSIGNED_SHORT 
//      GL_INT 
//      GL_UNSIGNED_INT 
//      GL_FLOAT 

// PolygonMode 
%num GL_POINT 
%num GL_LINE 
%num GL_FILL 

// ReadBufferMode 
//      GL_FRONT_LEFT 
//      GL_FRONT_RIGHT 
//      GL_BACK_LEFT 
//      GL_BACK_RIGHT 
//      GL_FRONT 
//      GL_BACK 
//      GL_LEFT 
//      GL_RIGHT 
//      GL_AUX0 
//      GL_AUX1 
//      GL_AUX2 
//      GL_AUX3 

// RenderingMode 
%num GL_RENDER 
%num GL_FEEDBACK 
%num GL_SELECT 

// ShadingModel 
%num GL_FLAT 
%num GL_SMOOTH 


// StencilFunction 
//      GL_NEVER 
//      GL_LESS 
//      GL_EQUAL 
//      GL_LEQUAL 
//      GL_GREATER 
//      GL_NOTEQUAL 
//      GL_GEQUAL 
//      GL_ALWAYS 

// StencilOp 
//      GL_ZERO 
%num GL_KEEP 
%num GL_REPLACE 
%num GL_INCR 
%num GL_DECR 
//      GL_INVERT 

// StringName 
%num GL_VENDOR 
%num GL_RENDERER 
%num GL_VERSION 
%num GL_EXTENSIONS 

// TextureCoordName 
%num GL_S 
%num GL_T 
%num GL_R 
%num GL_Q 

// TexCoordPointerType 
//      GL_SHORT 
//      GL_INT 
//      GL_FLOAT 
//      GL_DOUBLE 

// TextureEnvMode 
%num GL_MODULATE 
%num GL_DECAL 
//      GL_BLEND 
//      GL_REPLACE 

// TextureEnvParameter 
%num GL_TEXTURE_ENV_MODE 
%num GL_TEXTURE_ENV_COLOR 

// TextureEnvTarget 
%num GL_TEXTURE_ENV 

// TextureGenMode 
%num GL_EYE_LINEAR 
%num GL_OBJECT_LINEAR 
%num GL_SPHERE_MAP 

// TextureGenParameter 
%num GL_TEXTURE_GEN_MODE 
%num GL_OBJECT_PLANE 
%num GL_EYE_PLANE 

// TextureMagFilter 
%num GL_NEAREST 
%num GL_LINEAR 

// TextureMinFilter 
//      GL_NEAREST 
//      GL_LINEAR 
%num GL_NEAREST_MIPMAP_NEAREST 
%num GL_LINEAR_MIPMAP_NEAREST 
%num GL_NEAREST_MIPMAP_LINEAR 
%num GL_LINEAR_MIPMAP_LINEAR 

// TextureParameterName 
%num GL_TEXTURE_MAG_FILTER 
%num GL_TEXTURE_MIN_FILTER 
%num GL_TEXTURE_WRAP_S 
%num GL_TEXTURE_WRAP_T 
//      GL_TEXTURE_BORDER_COLOR 
//      GL_TEXTURE_PRIORITY 

// TextureTarget 
//      GL_TEXTURE_1D 
//      GL_TEXTURE_2D 
//      GL_PROXY_TEXTURE_1D 
//      GL_PROXY_TEXTURE_2D 

// TextureWrapMode 
%num GL_CLAMP 
%num GL_REPEAT 

// VertexPointerType 
//      GL_SHORT 
//      GL_INT 
//      GL_FLOAT 
//      GL_DOUBLE 

// ClientAttribMask 
%num GL_CLIENT_PIXEL_STORE_BIT 
%num GL_CLIENT_VERTEX_ARRAY_BIT 
%num GL_CLIENT_ALL_ATTRIB_BITS 

// polygon_offset 
%num GL_POLYGON_OFFSET_FACTOR 
%num GL_POLYGON_OFFSET_UNITS 
%num GL_POLYGON_OFFSET_POINT 
%num GL_POLYGON_OFFSET_LINE 
%num GL_POLYGON_OFFSET_FILL 

// texture 
%num GL_ALPHA4 
%num GL_ALPHA8 
%num GL_ALPHA12 
%num GL_ALPHA16 
%num GL_LUMINANCE4 
%num GL_LUMINANCE8 
%num GL_LUMINANCE12 
%num GL_LUMINANCE16 
%num GL_LUMINANCE4_ALPHA4 
%num GL_LUMINANCE6_ALPHA2 
%num GL_LUMINANCE8_ALPHA8 
%num GL_LUMINANCE12_ALPHA4 
%num GL_LUMINANCE12_ALPHA12 
%num GL_LUMINANCE16_ALPHA16 
%num GL_INTENSITY 
%num GL_INTENSITY4 
%num GL_INTENSITY8 
%num GL_INTENSITY12 
%num GL_INTENSITY16 
%num GL_R3_G3_B2 
%num GL_RGB4 
%num GL_RGB5 
%num GL_RGB8 
%num GL_RGB10 
%num GL_RGB12 
%num GL_RGB16 
%num GL_RGBA2 
%num GL_RGBA4 
%num GL_RGB5_A1 
%num GL_RGBA8 
%num GL_RGB10_A2 
%num GL_RGBA12 
%num GL_RGBA16 
%num GL_TEXTURE_RED_SIZE 
%num GL_TEXTURE_GREEN_SIZE 
%num GL_TEXTURE_BLUE_SIZE 
%num GL_TEXTURE_ALPHA_SIZE 
%num GL_TEXTURE_LUMINANCE_SIZE 
%num GL_TEXTURE_INTENSITY_SIZE 
%num GL_PROXY_TEXTURE_1D 
%num GL_PROXY_TEXTURE_2D 

// texture_object 
%num GL_TEXTURE_PRIORITY 
%num GL_TEXTURE_RESIDENT 
%num GL_TEXTURE_BINDING_1D 
%num GL_TEXTURE_BINDING_2D 

// vertex_array 
%num GL_VERTEX_ARRAY 
%num GL_NORMAL_ARRAY 
%num GL_COLOR_ARRAY 
%num GL_INDEX_ARRAY 
%num GL_TEXTURE_COORD_ARRAY 
%num GL_EDGE_FLAG_ARRAY 
%num GL_VERTEX_ARRAY_SIZE 
%num GL_VERTEX_ARRAY_TYPE 
%num GL_VERTEX_ARRAY_STRIDE 
%num GL_NORMAL_ARRAY_TYPE 
%num GL_NORMAL_ARRAY_STRIDE 
%num GL_COLOR_ARRAY_SIZE 
%num GL_COLOR_ARRAY_TYPE 
%num GL_COLOR_ARRAY_STRIDE 
%num GL_INDEX_ARRAY_TYPE 
%num GL_INDEX_ARRAY_STRIDE 
%num GL_TEXTURE_COORD_ARRAY_SIZE 
%num GL_TEXTURE_COORD_ARRAY_TYPE 
%num GL_TEXTURE_COORD_ARRAY_STRIDE 
%num GL_EDGE_FLAG_ARRAY_STRIDE 
%num GL_VERTEX_ARRAY_POINTER 
%num GL_NORMAL_ARRAY_POINTER 
%num GL_COLOR_ARRAY_POINTER 
%num GL_INDEX_ARRAY_POINTER 
%num GL_TEXTURE_COORD_ARRAY_POINTER 
%num GL_EDGE_FLAG_ARRAY_POINTER 
%num GL_V2F 
%num GL_V3F 
%num GL_C4UB_V2F 
%num GL_C4UB_V3F 
%num GL_C3F_V3F 
%num GL_N3F_V3F 
%num GL_C4F_N3F_V3F 
%num GL_T2F_V3F 
%num GL_T4F_V4F 
%num GL_T2F_C4UB_V3F 
%num GL_T2F_C3F_V3F 
%num GL_T2F_N3F_V3F 
%num GL_T2F_C4F_N3F_V3F 
%num GL_T4F_C4F_N3F_V4F 

// Extensions 
%num GL_EXT_vertex_array 
%num GL_EXT_bgra 
%num GL_EXT_paletted_texture 
%num GL_WIN_swap_hint 
%num GL_WIN_draw_range_elements 
// %num GL_WIN_phong_shading              1
// %num GL_WIN_specular_fog               1

// EXT_vertex_array 
%num GL_VERTEX_ARRAY_EXT 
%num GL_NORMAL_ARRAY_EXT 
%num GL_COLOR_ARRAY_EXT 
%num GL_INDEX_ARRAY_EXT 
%num GL_TEXTURE_COORD_ARRAY_EXT 
%num GL_EDGE_FLAG_ARRAY_EXT 
%num GL_VERTEX_ARRAY_SIZE_EXT 
%num GL_VERTEX_ARRAY_TYPE_EXT 
%num GL_VERTEX_ARRAY_STRIDE_EXT 
%num GL_VERTEX_ARRAY_COUNT_EXT 
%num GL_NORMAL_ARRAY_TYPE_EXT 
%num GL_NORMAL_ARRAY_STRIDE_EXT 
%num GL_NORMAL_ARRAY_COUNT_EXT 
%num GL_COLOR_ARRAY_SIZE_EXT 
%num GL_COLOR_ARRAY_TYPE_EXT 
%num GL_COLOR_ARRAY_STRIDE_EXT 
%num GL_COLOR_ARRAY_COUNT_EXT 
%num GL_INDEX_ARRAY_TYPE_EXT 
%num GL_INDEX_ARRAY_STRIDE_EXT 
%num GL_INDEX_ARRAY_COUNT_EXT 
%num GL_TEXTURE_COORD_ARRAY_SIZE_EXT 
%num GL_TEXTURE_COORD_ARRAY_TYPE_EXT 
%num GL_TEXTURE_COORD_ARRAY_STRIDE_EXT 
%num GL_TEXTURE_COORD_ARRAY_COUNT_EXT 
%num GL_EDGE_FLAG_ARRAY_STRIDE_EXT 
%num GL_EDGE_FLAG_ARRAY_COUNT_EXT 
%num GL_VERTEX_ARRAY_POINTER_EXT 
%num GL_NORMAL_ARRAY_POINTER_EXT 
%num GL_COLOR_ARRAY_POINTER_EXT 
%num GL_INDEX_ARRAY_POINTER_EXT 
%num GL_TEXTURE_COORD_ARRAY_POINTER_EXT 
%num GL_EDGE_FLAG_ARRAY_POINTER_EXT 
%num GL_DOUBLE_EXT 

// EXT_bgra 
%num GL_BGR_EXT 
%num GL_BGRA_EXT 

// EXT_paletted_texture 

// These must match the GL_COLOR_TABLE_*_SGI enumerants 
%num GL_COLOR_TABLE_FORMAT_EXT 
%num GL_COLOR_TABLE_WIDTH_EXT 
%num GL_COLOR_TABLE_RED_SIZE_EXT 
%num GL_COLOR_TABLE_GREEN_SIZE_EXT 
%num GL_COLOR_TABLE_BLUE_SIZE_EXT 
%num GL_COLOR_TABLE_ALPHA_SIZE_EXT 
%num GL_COLOR_TABLE_LUMINANCE_SIZE_EXT 
%num GL_COLOR_TABLE_INTENSITY_SIZE_EXT 

%num GL_COLOR_INDEX1_EXT 
%num GL_COLOR_INDEX2_EXT 
%num GL_COLOR_INDEX4_EXT 
%num GL_COLOR_INDEX8_EXT 
%num GL_COLOR_INDEX12_EXT 
%num GL_COLOR_INDEX16_EXT 

// WIN_draw_range_elements 
%num GL_MAX_ELEMENTS_VERTICES_WIN 
%num GL_MAX_ELEMENTS_INDICES_WIN 

// WIN_phong_shading 
%num GL_PHONG_WIN 
%num GL_PHONG_HINT_WIN 

// WIN_specular_fog 
%num GL_FOG_SPECULAR_TEXTURE_WIN 

// For compatibility with OpenGL v1.0 
%num GL_LOGIC_OP 
%num GL_TEXTURE_COMPONENTS 




///////////////////////////////////////////////////////////////////////////////
// wxGlCanvas

%class wxGLCanvas, wxWindow
%include "wx/glcanvas.h"

wxGLCanvas(wxWindow *parent, wxWindowID id = -1, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0, const wxString& name = "GLCanvas", int *attribList = 0, const wxPalette& palette = wxNullPalette)
void SetCurrent()
%alias SetColor void SetColour(const char* colour)
void SwapBuffers()
