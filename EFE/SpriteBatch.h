#pragma once
#include <GL/glew.h>
#include "Vertex.h"
#include <glm/glm.hpp>
#include <vector>

namespace efe
{


enum class GlyphSortType
{
	NONE,
	FRONT_TO_BACK,
	BACK_TO_FRONT,
	TEXTURE
};


struct Glyph
{
	GLuint texture;
	float depth;

	Vertex topLeft;
	Vertex bottomLeft;
	Vertex topRight;
	Vertex bottomRight;
};


struct RenderBatch
{
public:
	RenderBatch(GLuint offsetC, GLuint numVerticesC, GLuint textureC) :
		offset(offsetC),
		numVertices(numVerticesC),
		texture(textureC)
	{}

	GLuint offset;
	GLuint numVertices;
	GLuint texture;
};


class SpriteBatch
{
public:
	SpriteBatch();
	~SpriteBatch();

	void init();

	void begin(GlyphSortType sortType = GlyphSortType::TEXTURE);
	void end();


	void draw(const glm::vec4 &destRect, const glm::vec4 &uvRect, GLuint texture, const Color &color, float depth);

	void renderBatch();


private:
	void createRenderBatches();
	void createVertexArray();
	void sortGlyphs();


	GlyphSortType _sortType;

	GLint _vbo;
	GLint _vao;

	static bool compareFrontToBack(Glyph* A, Glyph* B);
	static bool compareBackToFront(Glyph* A, Glyph* B);
	static bool compareTexture(Glyph* A, Glyph* B);

	std::vector<Glyph*> _glyphs;
	std::vector<RenderBatch> _renderBatches;
};

}