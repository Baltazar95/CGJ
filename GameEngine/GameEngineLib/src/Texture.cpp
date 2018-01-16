#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

//#define _SCL_SECURE_NO_WARNINGS

#pragma warning(disable:4996)

Texture::Texture(std::string &sin) {


	std::string substring = "sky";
	std::string last_element(sin.substr(sin.rfind("/") + 1));
	std::string no_extension(last_element.substr(0, last_element.rfind(".")));

	_texture_name = no_extension;

	const char* cstr = sin.c_str();

	if (!strncmp(_texture_name.c_str(), substring.c_str(), substring.size())) {

		if (_texture_name.compare("skyfront")) {
			
			Texture::front = cstr;

		}else if (_texture_name.compare("skyback")) {

			Texture::back = cstr;
		
		}else if (_texture_name.compare("skyright")) {

			Texture::right = cstr;
		
		}else if (_texture_name.compare("skyback")) {

			Texture::back = cstr;

		}else if (_texture_name.compare("skydown")) {

			Texture::bottom = cstr;

		}else if (_texture_name.compare("skyup")) {

			Texture::top = cstr;

		}

		if (front != "" && back != "" && top != "" &&  bottom != "" &&  left != "" &&  right != "") {
			create_cube_map(front, back, top, bottom, left, right, tex_cube);
		}

		/*
		std::cout << _texture_name << std::endl;
		glGenTextures(1, &texture);
		std::cout << "passei por aqui" << std::endl;

		glBindTexture(GL_TEXTURE_2D, texture);
		std::cout << "passei por aqui 2" << std::endl;

		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		std::cout << "passei por aqui 3" << std::endl; 

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);

		std::cout << "passei por aqui 4" << std::endl;

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		std::cout << "passei por aqui 5" << std::endl;

		//stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
												// The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
		
		std::cout << "passei por aqui 6" << std::endl;

		data = stbi_load(cstr, &width, &height, &nrChannels, 0);

		std::cout << "passei por aqui 7" << std::endl;

		if (data)
		{
			gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);

			//3
			std::cout << "passei por aqui 8" << std::endl;
			//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			//glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::cout << "Failed to load texture" << std::endl;
		}
		//stbi_image_free(data);
		std::cout << "passei por aqui 9" << std::endl;
		free(data);
		*/

		GlUtils::checkOpenGLError("ERROR: Could not create texture sky");
	}
	else {

		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);


		// set the texture wrapping parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		// set texture filtering parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
												// The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
		data = stbi_load(cstr, &width, &height, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::cout << "Failed to load texture" << std::endl;
		}
		stbi_image_free(data);

		GlUtils::checkOpenGLError("ERROR: Could not create normal texture");
	}

}


Texture::Texture(std::string name, char* data) {

	_texture_name = name;

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 640, 480, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
	//glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
	
}


bool Texture::load_cube_map_side(GLuint texture, GLenum side_target, const char* file_name) {
	
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture);
	int x, y, n;
	int force_channels = 4;
	unsigned char*  image_data = stbi_load(file_name, &x, &y, &n, force_channels);
	if (!image_data) {
		fprintf(stderr, "ERROR: could not load %s\n", file_name);
		return false;
	}

	// non-power-of-2 dimensions check
	if ((x & (x - 1)) != 0 || (y & (y - 1)) != 0) {
		
		fprintf(stderr, "WARNING: image %s is not power-of-2 dimensions\n",file_name);
	}

	// copy image data into 'target' side of cube map
	glTexImage2D(side_target,0,GL_RGBA,x,y,0,GL_RGBA,GL_UNSIGNED_BYTE,image_data);
	free(image_data);
	return true;
}


void Texture::create_cube_map(const char* front, const char* back, const char* top, const char* bottom, const char* left, const char* right, GLuint* tex_cube) {

	// generate a cube-map texture to hold all the sides
	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, tex_cube);

	// load each image and copy into a side of the cube-map texture
	load_cube_map_side(*tex_cube, GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, front);
	load_cube_map_side(*tex_cube, GL_TEXTURE_CUBE_MAP_POSITIVE_Z, back);
	load_cube_map_side(*tex_cube, GL_TEXTURE_CUBE_MAP_POSITIVE_Y, top);
	load_cube_map_side(*tex_cube, GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, bottom);
	load_cube_map_side(*tex_cube, GL_TEXTURE_CUBE_MAP_NEGATIVE_X, left);
	load_cube_map_side(*tex_cube, GL_TEXTURE_CUBE_MAP_POSITIVE_X, right);
	// format cube map texture
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

}


std::string Texture::getName() {

	return _texture_name;
}