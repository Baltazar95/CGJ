#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture(std::string &sin) {

	std::string last_element(sin.substr(sin.rfind("/") + 1));
	std::string no_extension(last_element.substr(0, last_element.rfind(".")));

	_texture_name = no_extension;

	const char* cstr = sin.c_str();


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
}

Texture::Texture(std::string frontfile, std::string backfile, std::string topfile, std::string bottomfile, std::string leftfile, std::string rightfile) {

	std::string myFiles[] = {frontfile, backfile, topfile, bottomfile, leftfile, rightfile };

	for each (std::string file in myFiles)
	{
		std::string last_element(file.substr(file.rfind("/") + 1));
		std::string no_extension(last_element.substr(0, last_element.rfind(".")));

		_texture_name = no_extension;

		if (_texture_name.compare("skyfront")==0) {

			front = file;

		}
		else if (_texture_name.compare("skyback") == 0) {

			back = file;

		}
		else if (_texture_name.compare("skyright") == 0) {

			right = file;

		}
		else if (_texture_name.compare("skyleft") == 0) {

			left = file;

		}
		else if (_texture_name.compare("skydown") == 0) {

			bottom = file;

		}
		else if (_texture_name.compare("skyup") == 0) {

			top = file;

		}

	}

	_texture_name = "sky";

	// generate a cube-map texture to hold all the sides
	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &tex_cube);

	// load each image and copy into a side of the cube-map texture
	load_cube_map_side(tex_cube, GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, front);
	load_cube_map_side(tex_cube, GL_TEXTURE_CUBE_MAP_POSITIVE_Z, back);
	load_cube_map_side(tex_cube, GL_TEXTURE_CUBE_MAP_POSITIVE_Y, top);
	load_cube_map_side(tex_cube, GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, bottom);
	load_cube_map_side(tex_cube, GL_TEXTURE_CUBE_MAP_NEGATIVE_X, left);
	load_cube_map_side(tex_cube, GL_TEXTURE_CUBE_MAP_POSITIVE_X, right);

	// format cube map texture
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

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

std::string Texture::getName() {

	return _texture_name;
}

bool Texture::load_cube_map_side(GLuint tex_cube, GLenum side_target, std::string file_name) {

	glBindTexture(GL_TEXTURE_CUBE_MAP, tex_cube);
	int x, y, n;
	int force_channels = 4;
	//stbi_set_flip_vertically_on_load(true);
	data = stbi_load(file_name.c_str(), &x, &y, &n, force_channels);
	//data = stbi_load(file_name, &width, &height, &nrChannels, 0);
	if (!data) {
		fprintf(stderr, "ERROR: could not load %s\n", file_name);
		printf(stbi_failure_reason());
		return false;
	}

	// non-power-of-2 dimensions check
	if ((x & (x - 1)) != 0 || (y & (y - 1)) != 0) {

		fprintf(stderr, "WARNING: image %s is not power-of-2 dimensions\n", file_name);
	}

	// copy image data into 'target' side of cube map
	glTexImage2D(side_target, 0, GL_RGBA, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	free(data);
	return true;

}


