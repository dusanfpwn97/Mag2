#include "SpriteBatch.h"
#include <algorithm>

namespace efe
{



SpriteBatch::SpriteBatch() :
	_vbo(0),
	_vao(0)
{

}

SpriteBatch::~SpriteBatch()
{

}

void SpriteBatch::init()
{
	createVertexArray();
}

void SpriteBatch::begin(GlyphSortType sortType/* = GlyphSortType::TEXTURE*/)
{
	_sortType = sortType;
	_renderBatches.clear();
	for (int i = 0; i < _glyphs.size(); i++)
	{
		delete _glyphs[i];
	}

	_glyphs.clear();
}

void SpriteBatch::end()
{
	sortGlyphs();
	createRenderBatches();
}

void SpriteBatch::draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, const Color& color, float depth)
{
	Glyph* newGlyph = new Glyph;

	newGlyph->texture = texture;
	newGlyph->depth = depth;

	newGlyph->topLeft.color = color;
	newGlyph->topLeft.setPosition(destRect.x, destRect.y + destRect.w);
	newGlyph->topLeft.setUV(uvRect.x, uvRect.y + uvRect.w);

	newGlyph->bottomLeft.color = color;
	newGlyph->bottomLeft.setPosition(destRect.x, destRect.y);
	newGlyph->bottomLeft.setUV(uvRect.x, uvRect.y);

	newGlyph->bottomRight.color = color;
	newGlyph->bottomRight.setPosition(destRect.x + destRect.z, destRect.y);
	newGlyph->bottomRight.setUV(uvRect.x + uvRect.z, uvRect.y);

	newGlyph->topRight.color = color;
	newGlyph->topRight.setPosition(destRect.x + destRect.z, destRect.y + destRect.w);
	newGlyph->topRight.setUV(uvRect.x + uvRect.z, uvRect.y + uvRect.w);


	_glyphs.push_back(newGlyph);

}

void SpriteBatch::renderBatch()
{
	glBindVertexArray(_vao);
	for (int i = 0; i < _renderBatches.size(); i++)
	{
		glBindTexture(GL_TEXTURE_2D, _renderBatches[i].texture);
		glDrawArrays(GL_TRIANGLES, _renderBatches[i].offset, _renderBatches[i].numVertices);
	}

	glBindVertexArray(0);
}

void SpriteBatch::createRenderBatches()
{
	if (_glyphs.empty()) return;


	std::vector<Vertex> vertices;
	vertices.resize(_glyphs.size() * 6);

	int currentVertex = 0;
	int offset = 0;

	//RenderBatch* newRenderBatch = new RenderBatch(offset, 6, _glyphs[0]->texture);
	//_renderBatches.push_back(newRenderBatch);
	//delete newRenderBatch;

	// more optimized method but doesnt work for > C++ 11
	//_renderBatches.emplace_back(offset, 6, _glyphs[0]->texture);
	//_renderBatches.push_back(RenderBatch(offset, 6, _glyphs[0]->texture));

	_renderBatches.emplace_back(offset, 6, _glyphs[0]->texture);
	//_renderBatches.emplace_back();
	//_renderBatches.back()->offset = offset;
	//_renderBatches.back()->numVertices = 6;
	//_renderBatches.back()->texture = _glyphs[0]->texture;



	vertices[currentVertex] = _glyphs[0]->topLeft;
	currentVertex++;
	vertices[currentVertex] = _glyphs[0]->bottomLeft;
	currentVertex++;
	vertices[currentVertex] = _glyphs[0]->bottomRight;
	currentVertex++;
	vertices[currentVertex] = _glyphs[0]->bottomRight;
	currentVertex++;
	vertices[currentVertex] = _glyphs[0]->topRight;
	currentVertex++;
	vertices[currentVertex] = _glyphs[0]->topLeft;
	currentVertex++;

	offset += 6;

	for (int currentGlyph = 1; currentGlyph < _glyphs.size(); currentGlyph++)
	{

		if (_glyphs[currentGlyph]->texture != _glyphs[currentGlyph - 1]->texture)
		{
			_renderBatches.emplace_back(offset, 6, _glyphs[currentGlyph]->texture);
			//RenderBatch* newRenderBatch2 = new RenderBatch(offset, 6, _glyphs[currentGlyph]->texture);
			//_renderBatches.push_back(newRenderBatch2);

			//_renderBatches.emplace_back();
			//_renderBatches.back()->offset = offset;
			//_renderBatches.back()->numVertices = 6;
			//_renderBatches.back()->texture = _glyphs[currentGlyph]->texture;
			//delete newRenderBatch2;
		}
		else
		{
			_renderBatches.back().numVertices += 6;
		}

		vertices[currentVertex] = _glyphs[currentGlyph]->topLeft;
		currentVertex++;
		vertices[currentVertex] = _glyphs[currentGlyph]->bottomLeft;
		currentVertex++;
		vertices[currentVertex] = _glyphs[currentGlyph]->bottomRight;
		currentVertex++;
		vertices[currentVertex] = _glyphs[currentGlyph]->bottomRight;
		currentVertex++;
		vertices[currentVertex] = _glyphs[currentGlyph]->topRight;
		currentVertex++;
		vertices[currentVertex] = _glyphs[currentGlyph]->topLeft;
		currentVertex++;

		offset += 6;
	}


	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	// orphan the buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), nullptr, GL_DYNAMIC_DRAW);
	// upload the data
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vertex) * vertices.size(), vertices.data());

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void SpriteBatch::createVertexArray()
{
	if (_vao == 0)
	{
		glGenVertexArrays(1, &_vao);

	}
	
	glBindVertexArray(_vao);


	if (_vbo == 0)
	{
		glGenBuffers(1, &_vbo);

	}

	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

	glBindVertexArray(0);



}

void SpriteBatch::sortGlyphs()
{
	switch (_sortType)
	{
		case GlyphSortType::BACK_TO_FRONT:
			std::stable_sort(_glyphs.begin(), _glyphs.end(), compareFrontToBack);
			break;
		case GlyphSortType::FRONT_TO_BACK:
			std::stable_sort(_glyphs.begin(), _glyphs.end(), compareBackToFront);
			break;
		case GlyphSortType::TEXTURE:
			std::stable_sort(_glyphs.begin(), _glyphs.end(), compareTexture);
			break;

	}
	
}

bool SpriteBatch::compareFrontToBack(Glyph* A, Glyph* B)
{
	return (A->depth < B->depth);
}

bool SpriteBatch::compareBackToFront(Glyph* A, Glyph* B)
{
	return (A->depth > B->depth);
}

bool SpriteBatch::compareTexture(Glyph* A, Glyph* B)
{
	return (A->texture < B->texture);
}



}