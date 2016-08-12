// Render to depth texture
// Author: Julio Medina
// jamedina@hmc.edu

#define GLM_FORCE_RADIANS

#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <map>

using namespace std;

#include <stdlib.h>
#include <string.h>

// Glew Extension Wrangler
#include <GL/glew.h>

// GL Math
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include "renderToTexture.hpp"


/* Pass in the light position,  pass in GLuint for depthTexture*/
void setUpRenderToFrameBuffer(GLint* light_pos, GLuint depthTexture, GLuint FramebufferName)
{
	if ( FramebufferName != 0 ){
		glDeleteFramebuffers(1, &FramebufferName);
		glDeleteTextures(1, &depthTexture);
	}


	GLuint depthProgramID = LoadShaders( "depthShader.vertexshader", "depthShader.fragmentshader" );
	GLuint depthMatrixID = glGetUniformLocation(depthProgramID, "depthMVP");

	
	glGenFramebuffers(1, &FramebufferName);
	glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);


	// Depth texture. Slower than a depth buffer, but you can sample it later in your shader
	glGenTextures(1, &depthTexture);
	glBindTexture(GL_TEXTURE_2D, depthTexture);
	glTexImage2D(GL_TEXTURE_2D, 0,GL_DEPTH_COMPONENT16, 1024, 1024, 0,GL_DEPTH_COMPONENT, GL_FLOAT, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE);

	//glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTexture, 0);

	/* Tell open gl to render to the frame buffer */
	// No color output in the bound framebuffer, only depth.
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);

	glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);
	glViewport(0,0,1024,1024); // Render on the whole framebuffer, complete from the lower left corner to the upper right


	//glPushAttrib();
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK); // Cull back-facing triangles -> draw only front-facing triangles
	glDisable(GL_LIGHTING);

	/* Set the camera to be the light position */
	glm::vec3 lightPosition = glm::vec3(0.5f,2,2);


	glm::mat4 depthProjectionMatrix = glm::ortho<float>(-10,10,-10,10,-10,20);
	glm::mat4 depthViewMatrix = glm::lookAt( lightPosition,   //Camera position should == light position
 											 glm::vec3(0,0,0),   //Look at origin
											 glm::vec3(0,1,0));  //Up vector

	glm::mat4 depthModelMatrix = glm::mat4(1.0);
	glm::mat4 depthMVP = depthProjectionMatrix * depthViewMatrix * depthModelMatrix;

	// Send our transformation to the currently bound shader, 
	// in the "MVP" uniform
	glUniformMatrix4fv(depthMatrixID, 1, GL_FALSE, &depthMVP[0][0]);

}
void UnsetupRenderToFrameBuffer()
{
	//glPopAttrib();
	glDrawBuffer(GL_NONE); //<- Set these variables to be what they were before
	glReadBuffer(GL_NONE); //<- Set these variables to be what they were before
}

//void ReleaseDepthTexture()


void GetRidOfFrameBuffer(GLuint depthTexture, GLuint FramebufferName)
{
	glDeleteFramebuffers(1, &FramebufferName);
	glDeleteTextures(1, &depthTexture);

}






















/*
struct PackedVertex{
	glm::vec3 position;
	glm::vec2 uv;
	glm::vec3 normal;
	bool operator<(const PackedVertex that) const{
		return memcmp((void*)this, (void*)&that, sizeof(PackedVertex))>0;
	};
};

bool getSimilarVertexIndex_fast( 
	PackedVertex & packed, 
	std::map<PackedVertex,unsigned short> & VertexToOutIndex,
	unsigned short & result
){
	std::map<PackedVertex,unsigned short>::iterator it = VertexToOutIndex.find(packed);
	if ( it == VertexToOutIndex.end() ){
		return false;
	}else{
		result = it->second;
		return true;
	}
}

*/


/*
void loadOBJ( const char * path,
                        std::vector<glm::vec3> & out_vertices,
                        std::vector<glm::vec2> & out_uvs,
                        std::vector<glm::vec3> & out_normals )
{
    printf("Loading OBJ file %s...\n", path);

    std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
    std::vector<glm::vec3> temp_vertices;
    std::vector<glm::vec2> temp_uvs;
    std::vector<glm::vec3> temp_normals;


    FILE * file = fopen(path, "r");
    if( file == NULL ){
        printf("Impossible to open the file ! Are you in the right path ? See Tutorial 1 for details\n");
        getchar();
    }

    while(!out_vertices.empty()){
        out_vertices.pop_back();
    }

    while( 1 ){

        char lineHeader[128];
        // read the first word of the line
        int res = fscanf(file, "%s", lineHeader);
        if (res == EOF)
            break; // EOF = End Of File. Quit the loop.

        // else : parse lineHeader

        if ( strcmp( lineHeader, "v" ) == 0 ){
            glm::vec3 vertex;
            fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z );
            temp_vertices.push_back(vertex);
        }else if ( strcmp( lineHeader, "vt" ) == 0 ){
            glm::vec2 uv;
            fscanf(file, "%f %f\n", &uv.x, &uv.y );
            uv.y = -uv.y; // Invert V coordinate since we will only use DDS texture, which are inverted. Remove if you want to use TGA or BMP loaders.
            temp_uvs.push_back(uv);
        }else if ( strcmp( lineHeader, "vn" ) == 0 ){
            glm::vec3 normal;
            fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z );
            temp_normals.push_back(normal);
        }else if ( strcmp( lineHeader, "f" ) == 0 ){
            std::string vertex1, vertex2, vertex3;
            unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
            int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2] );
            if (matches != 9){
                printf("File can't be read by our simple parser :-( Try exporting with other options\n");
            }
            vertexIndices.push_back(vertexIndex[0]);
            vertexIndices.push_back(vertexIndex[1]);
            vertexIndices.push_back(vertexIndex[2]);
            uvIndices    .push_back(uvIndex[0]);
            uvIndices    .push_back(uvIndex[1]);
            uvIndices    .push_back(uvIndex[2]);
            normalIndices.push_back(normalIndex[0]);
            normalIndices.push_back(normalIndex[1]);
            normalIndices.push_back(normalIndex[2]);
        }else{
            // Probably a comment, eat up the rest of the line
            char stupidBuffer[1000];
            fgets(stupidBuffer, 1000, file);
        }

}
    // For each vertex of each triangle
    for( unsigned int i=0; i<vertexIndices.size(); i++ ){

        // Get the indices of its attributes
        unsigned int vertexIndex = vertexIndices[i];
        unsigned int uvIndex = uvIndices[i];
        unsigned int normalIndex = normalIndices[i];

        // Get the attributes thanks to the index
        glm::vec3 vertex;
        vertex.x = temp_vertices[ vertexIndex-1 ].x;
        vertex.y = temp_vertices[ vertexIndex-1 ].y;
        vertex.z = temp_vertices[ vertexIndex-1 ].z;

        glm::vec2 uv;
        uv.x = temp_uvs[ uvIndex-1 ].x;
        uv.y = temp_uvs[ uvIndex-1 ].y;

        glm::vec3 normal;
        normal.x = temp_normals[ normalIndex-1 ].x;
        normal.y = temp_normals[ normalIndex-1 ].y;
        normal.z = temp_normals[ normalIndex-1 ].z;

        // Put the attributes in buffers
        out_vertices.push_back(vertex);
        out_uvs     .push_back(uv);
        out_normals .push_back(normal);
    }

}
*/
/*
void indexVBO(
	std::vector<glm::vec3> & in_vertices,
	std::vector<glm::vec2> & in_uvs,
	std::vector<glm::vec3> & in_normals,

	std::vector<unsigned short> & out_indices,
	std::vector<glm::vec3> & out_vertices,
	std::vector<glm::vec2> & out_uvs,
	std::vector<glm::vec3> & out_normals
){
	std::map<PackedVertex,unsigned short> VertexToOutIndex;

	// For each input vertex
	for ( unsigned int i=0; i<in_vertices.size(); i++ ){

		PackedVertex packed = {in_vertices[i], in_uvs[i], in_normals[i]};
		

		// Try to find a similar vertex in out_XXXX
		unsigned short index;
		bool found = getSimilarVertexIndex_fast( packed, VertexToOutIndex, index);

		if ( found ){ // A similar vertex is already in the VBO, use it instead !
			out_indices.push_back( index );
		}else{ // If not, it needs to be added in the output data.
			out_vertices.push_back( in_vertices[i]);
			out_uvs     .push_back( in_uvs[i]);
			out_normals .push_back( in_normals[i]);
			unsigned short newindex = (unsigned short)out_vertices.size() - 1;
			out_indices .push_back( newindex );
			VertexToOutIndex[ packed ] = newindex;
		}
	}
}
*/

/*
void renderToTexture( )
{


	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);

	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS); 

	// Cull triangles which normal is not towards the camera
	glEnable(GL_CULL_FACE);




    GLuint depthProgramID = LoadShaders( "/home/mcqueen/openrave/plugins/qtcoinrave/shadowVert.glsl",
                     					 "/home/mcqueen/openrave/plugins/qtcoinrave/shadowFrag.glsl");

	// Get a handle for our "MVP" uniform
	GLuint depthMatrixID = glGetUniformLocation(depthProgramID, "depthMVP");

	// Get a handle for our buffers
	GLuint depth_vertexPosition_modelspaceID = glGetAttribLocation(depthProgramID, "vertexPosition_modelspace");

////////////////////////////////////////////////////////////////
  //LOAD THE MESH SOMEHOW AND PUT THAT DATA HERE
//

	// Read our .obj file
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;
	loadOBJ("/home/mcqueen/openrave/plugins/qtcoinrave/suzanne.obj", vertices, uvs, normals);

	std::vector<unsigned short> indices;
	std::vector<glm::vec3> indexed_vertices;
	std::vector<glm::vec2> indexed_uvs;
	std::vector<glm::vec3> indexed_normals;
	indexVBO(vertices, uvs, normals, indices, indexed_vertices, indexed_uvs, indexed_normals);

	// Load it into a VBO

	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, indexed_vertices.size() * sizeof(glm::vec3), &indexed_vertices[0], GL_STATIC_DRAW);

	GLuint uvbuffer;
	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, indexed_uvs.size() * sizeof(glm::vec2), &indexed_uvs[0], GL_STATIC_DRAW);

	// Generate a buffer for the indices as well
	GLuint elementbuffer;
	glGenBuffers(1, &elementbuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned short), &indices[0], GL_STATIC_DRAW);

////////////////////////////////////////////////////////////////

	// ---------------------------------------------
	// Render to Texture - specific code begins here
	// ---------------------------------------------

	// The framebuffer, which regroups 0, 1, or more textures, and 0 or 1 depth buffer.
	GLuint FramebufferName = 0;
	glGenFramebuffers(1, &FramebufferName);
	glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);


	// Depth texture. Slower than a depth buffer, but you can sample it later in your shader
	GLuint depthTexture;
	glGenTextures(1, &depthTexture);
	glBindTexture(GL_TEXTURE_2D, depthTexture);
	glTexImage2D(GL_TEXTURE_2D, 0,GL_DEPTH_COMPONENT16, 1024, 1024, 0,GL_DEPTH_COMPONENT, GL_FLOAT, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTexture, 0);

	// No color output in the bound framebuffer, only depth.
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);

	// Get a handle for our "MVP" uniform
	GLuint MatrixID = glGetUniformLocation(depthProgramID, "MVP");
	GLuint DepthBiasID = glGetUniformLocation(depthProgramID, "DepthBiasMVP");
	GLuint ShadowMapID = glGetUniformLocation(depthProgramID, "shadowMap");

	// Get a handle for our buffers
	GLuint vertexPosition_modelspaceID = glGetAttribLocation(depthProgramID, "vertexPosition_modelspace");
	GLuint vertexUVID = glGetAttribLocation(depthProgramID, "vertexUV");

	// Get a handle for our "LightPosition" uniform
	GLuint lightInvDirID = glGetUniformLocation(depthProgramID, "LightInvDirection_worldspace");


//////////////////////////////////
//Do loop starts here

// Render to our framebuffer
	glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);
	glViewport(0,0,1024,1024); // Render on the whole framebuffer, complete from the lower left corner to the upper right


	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK); // Cull back-facing triangles -> draw only front-facing triangles

	// Clear the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Use our shader
	glUseProgram(depthProgramID);

	glm::vec3 lightPosition = glm::vec3(0.5f,2,2);


	glm::mat4 depthProjectionMatrix = glm::ortho<float>(-10,10,-10,10,-10,20);
	glm::mat4 depthViewMatrix = glm::lookAt( glm::vec3(0,0,0),        //Camera position should == light position
 												 glm::vec3(0,0,0),   //Look at origin
												 glm::vec3(0,1,0));  //Up vector

	glm::mat4 depthModelMatrix = glm::mat4(1.0);
	glm::mat4 depthMVP = depthProjectionMatrix * depthViewMatrix * depthModelMatrix;

	// Send our transformation to the currently bound shader, 
	// in the "MVP" uniform
	glUniformMatrix4fv(depthMatrixID, 1, GL_FALSE, &depthMVP[0][0]);


	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(depth_vertexPosition_modelspaceID);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(
		depth_vertexPosition_modelspaceID,  // The attribute we want to configure
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);

	// Index buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);

	// Draw the triangles !
	glDrawElements(
		GL_TRIANGLES,      // mode
		indices.size(),    // count
		GL_UNSIGNED_SHORT, // type
		(void*)0           // element array buffer offset
	);

	glDisableVertexAttribArray(depth_vertexPosition_modelspaceID);

/*
		//TODO: Compute the MVP matrix from the light's point of view. 
		GLint* lightPositionID;
		glGetLightiv(GL_LIGHT0, GL_POSITION, lightPositionID);
		std::cout << "light params:" << *lightPositionID << std::endl;



		glm::mat4 depthProjectionMatrix = glm::ortho<float>(-10,10,-10,10,-10,20);
		glm::mat4 depthViewMatrix = glm::lookAt( glm::vec3(0,0,0),        //Camera position should == light position
 												 glm::vec3(0,0,0),   //Look at origin
												 glm::vec3(0,1,0));  //Up vector

		glm::mat4 depthModelMatrix = glm::mat4(1.0);
		glm::mat4 depthMVP = depthProjectionMatrix * depthViewMatrix * depthModelMatrix;

		// Send our transformation to the currently bound shader, 
		// in the "MVP" uniform
		glUniformMatrix4fv(depthMatrixID, 1, GL_FALSE, &depthMVP[0][0]);

		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(depth_vertexPosition_modelspaceID);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(
			depth_vertexPosition_modelspaceID,  // The attribute we want to configure
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

		// Index buffer
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);

		// Draw the triangles !
		glDrawElements(
			GL_TRIANGLES,      // mode
			indices.size(),    // count
			GL_UNSIGNED_SHORT, // type
			(void*)0           // element array buffer offset
		);

		glDisableVertexAttribArray(depth_vertexPosition_modelspaceID);


		//TODO: How to return the texture in a way that coin can understand and use?
	*/

//}  

