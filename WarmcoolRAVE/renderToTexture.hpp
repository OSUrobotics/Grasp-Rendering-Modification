#ifndef RENDER_TO_TEXTURE_HPP
#define RENDER_TO_TEXTURE_HPP


//GLuint FramebufferName = 0;
//GLuint depthTexture = 0;


GLuint LoadShaders(const char* vertex_file_path, const char * fragment_file_path);

void setUpRenderToFrameBuffer( GLint* light_pos, GLuint depthTexture, GLuint FramebufferName );

void UnsetupRenderToFrameBuffer();

#endif
