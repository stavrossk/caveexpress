#include "GLFrontend.h"
#include "engine/client/ui/UI.h"
#include "engine/client/ClientConsole.h"
#include "engine/client/textures/TextureCoords.h"
#include "engine/common/Logger.h"
#include "engine/common/DateUtil.h"
#include "engine/common/FileSystem.h"
#include "engine/common/ConfigManager.h"
#include <SDL_image.h>

inline TexNum getTexNum (void *textureData)
{
	const intptr_t texnum = reinterpret_cast<intptr_t>(textureData);
	return texnum;
}

GLFrontend::GLFrontend (SharedPtr<IConsole> console) :
		SDLFrontend(console), _maxTextureUnits(0), _currentTextureUnit(nullptr), _rx(1.0f), _ry(1.0f)
{
	_context = nullptr;

	memset(&_viewPort, 0, sizeof(_viewPort));
}

GLFrontend::~GLFrontend ()
{
	if (_context)
		SDL_GL_DeleteContext(_context);
}

inline bool GLFrontend::invalidTexUnit (int textureUnit) const
{
	return textureUnit < 0 || textureUnit >= _maxTextureUnits || textureUnit >= MAX_GL_TEXUNITS;
}

void GLFrontend::setGLAttributes ()
{
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
}

void GLFrontend::setHints ()
{
}

void GLFrontend::enableScissor (int x, int y, int width, int height)
{
#ifdef SDL_VIDEO_OPENGL
	const int lowerLeft = std::max(0, getHeight() - y - height);
	glScissor(x * _rx, lowerLeft * _ry, width * _rx, height * _ry);
	glEnable(GL_SCISSOR_TEST);
#endif
}

float GLFrontend::getWidthScale () const
{
	return _rx;
}

float GLFrontend::getHeightScale () const
{
	return _ry;
}

void GLFrontend::disableScissor ()
{
#ifdef SDL_VIDEO_OPENGL
	glDisable(GL_SCISSOR_TEST);
#endif
}

void GLFrontend::initRenderer ()
{
#ifdef SDL_VIDEO_OPENGL
	info(LOG_CLIENT, "init opengl renderer with shaders: " + ConfigManager::get().getConfigVar("shader")->getValue());

	_context = SDL_GL_CreateContext(_window);

	glGetIntegerv(GL_MAX_TEXTURE_UNITS, &_maxTextureUnits);
	info(LOG_CLIENT, String::format("max texture units: %i", _maxTextureUnits));
	GL_checkError();

	_maxTextureUnits = clamp(_maxTextureUnits, 1, MAX_GL_TEXUNITS);

	for (int i = 0; i < _maxTextureUnits; ++i) {
		_texUnits[i].textureUnit = GL_TEXTURE0 + i;
		enableTextureUnit(_texUnits[i], true);
		selectTextureUnit(_texUnits[i]);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		enableTextureUnit(_texUnits[i], false);
		GL_checkError();
	}
	enableTextureUnit(_texUnits[0], true);

	glClearColor(0, 0, 0, 0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	GL_checkError();
	glDepthMask(GL_FALSE);
	glEnable(GL_BLEND);
	glEnable(GL_ALPHA_TEST);
	GL_checkError();
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	GL_checkError();
	glAlphaFunc(GL_GREATER, 0.1f);
	GL_checkError();
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	GL_checkError();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	GL_checkError();
#endif
}

int GLFrontend::getCoordinateOffsetX () const
{
	return -_viewPort.x;
}

int GLFrontend::getCoordinateOffsetY () const
{
	return -_viewPort.y;
}

void GLFrontend::getViewPort (int* x, int *y, int *w, int *h) const
{
	if (x != nullptr)
		*x = _viewPort.x;
	if (y != nullptr)
		*y = _viewPort.y;
	if (w != nullptr)
		*w = _viewPort.w;
	if (h != nullptr)
		*h = _viewPort.h;
}

void GLFrontend::selectTextureUnit (TexUnit &textureUnit)
{
	if (_currentTextureUnit != nullptr && *_currentTextureUnit == textureUnit)
		return;

	_currentTextureUnit = &textureUnit;
#ifdef SDL_VIDEO_OPENGL
	if (!GLContext::get().isMultiTextureSupported())
		return;
	GLContext::get().ctx_glActiveTexture(textureUnit.textureUnit);
	GLContext::get().ctx_glClientActiveTexture(textureUnit.textureUnit);
#endif
}

void GLFrontend::enableTextureUnit (TexUnit &texunit, bool enable)
{
	if (enable == texunit.active) {
		return;
	}

	texunit.active = enable;
	selectTextureUnit(texunit);
#ifdef SDL_VIDEO_OPENGL
	if (enable) {
		glEnable(GL_TEXTURE_2D);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	} else {
		glDisable(GL_TEXTURE_2D);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	}
#endif
	selectTextureUnit(_texUnits[0]);
}

void GLFrontend::bindTexture (Texture* texture, int textureUnit)
{
	if (invalidTexUnit(textureUnit))
		return;

	selectTextureUnit(_texUnits[textureUnit]);
	const TexNum texnum = getTexNum(texture->getData());
	if (_currentTextureUnit->currentTexture == texnum)
		return;
	_currentTextureUnit->currentTexture = texnum;
#ifdef SDL_VIDEO_OPENGL
	glBindTexture(GL_TEXTURE_2D, _currentTextureUnit->currentTexture);
#endif
}

void GLFrontend::setColorPointer (const Color& color, int amount)
{
#ifdef SDL_VIDEO_OPENGL
	if (amount > MAX_COLOR)
		amount = MAX_COLOR;
	for (int i = 0; i < amount; ++i) {
		for (int c = 0; c < 4; ++c) {
			_colorArray[i * 4 + c] = color[c];
		}
	}
	glColorPointer(4, GL_FLOAT, 0, _colorArray);
#endif
}

void GLFrontend::renderImage (Texture* texture, int x, int y, int w, int h, int16_t angle, float alpha)
{
#ifdef SDL_VIDEO_OPENGL
	if (!texture->isValid())
		return;

	_color[3] = alpha;
	setColorPointer(_color, 4);

	const TextureCoords texCoords(texture);

	getTrimmed(texture, x, y, w, h);

	const float x1 = x * _rx;
	const float y1 = y * _ry;
	const float nw = w * _rx;
	const float nh = h * _ry;
	const float centerx = nw / 2.0f;
	const float centery = nh / 2.0f;
	const float minx = -centerx;
	const float maxx = centerx;
	const float miny = -centery;
	const float maxy = centery;
	const float imageVerts[] = { minx, miny, maxx, miny, maxx, maxy, minx, maxy };

	glPushMatrix();
	glLoadIdentity();
	glTranslatef((GLfloat) (x1 + centerx), (GLfloat) (y1 + centery), (GLfloat) 0.0f);
	glRotated(angle, (GLdouble) 0.0, (GLdouble) 0.0, (GLdouble) 1.0);
	glVertexPointer(2, GL_FLOAT, 0, imageVerts);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glTexCoordPointer(2, GL_FLOAT, 0, texCoords.texCoords);
	bindTexture(texture, 0);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glPopMatrix();
	GL_checkError();
#endif
}

void GLFrontend::renderRect (int x, int y, int w, int h, const Color& color)
{
#ifdef SDL_VIDEO_OPENGL
	if (w <= 0)
		w = getWidth();
	if (h <= 0)
		h = getHeight();

	const float nx = x * _rx;
	const float ny = y * _ry;
	const float nw = w * _rx;
	const float nh = h * _ry;
	const float points[] = { nx, ny, nx + nw, ny, nx + nw, ny + nh, nx, ny + nh };

	setColorPointer(color, 4);
	enableTextureUnit(*_currentTextureUnit, false);
	glVertexPointer(2, GL_FLOAT, 0, points);
	glDrawArrays(GL_LINE_LOOP, 0, 4);
	GL_checkError();
	enableTextureUnit(*_currentTextureUnit, true);
#endif
}

void GLFrontend::renderFilledRect (int x, int y, int w, int h, const Color& fillColor)
{
#ifdef SDL_VIDEO_OPENGL
	if (w <= 0)
		w = getWidth();
	if (h <= 0)
		h = getHeight();

	const float nx = x * _rx;
	const float ny = y * _ry;
	const float nw = w * _rx;
	const float nh = h * _ry;

	setColorPointer(fillColor, 4);
	enableTextureUnit(*_currentTextureUnit, false);
	const float minx = nx;
	const float maxx = nx + nw;
	const float miny = ny;
	const float maxy = ny + nh;
	const float vertices[] = { minx, miny, maxx, miny, minx, maxy, maxx, maxy };
	glVertexPointer(2, GL_FLOAT, 0, vertices);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	GL_checkError();
	enableTextureUnit(*_currentTextureUnit, true);
#endif
}

void GLFrontend::destroyTexture (void *data)
{
#ifdef SDL_VIDEO_OPENGL
	const TexNum texnum = getTexNum(data);
	glDeleteTextures(1, &texnum);
	GL_checkError();
#endif
}

bool GLFrontend::loadTexture (Texture *texture, const std::string& filename)
{
#ifdef SDL_VIDEO_OPENGL
	const std::string file = FS.getFile(FS.getPicsDir() + filename + ".png")->getName();
	SDL_RWops *src = FS.createRWops(file);
	if (src == nullptr) {
		error(LOG_CLIENT, "could not load the file: " + file);
		return false;
	}
	SDL_Surface *surface = IMG_Load_RW(src, 1);
	if (!surface) {
		sdlCheckError();
		error(LOG_CLIENT, "could not load the texture: " + file);
		return false;
	}

	GLuint texnum;
	glGenTextures(1, &texnum);
	glBindTexture(GL_TEXTURE_2D, texnum);
	unsigned char* pixels = static_cast<unsigned char*>(surface->pixels);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	int format;
	if (surface->format->BytesPerPixel == 4)
		format = GL_RGBA;
	else
		format = GL_RGB;
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, format, GL_UNSIGNED_BYTE, pixels);
	glBindTexture(GL_TEXTURE_2D, 0);
	GL_checkError();
	texture->setData(reinterpret_cast<void*>(texnum));
	texture->setRect(0, 0, surface->w, surface->h);
	SDL_FreeSurface(surface);
	return texnum != 0;
#else
	return false;
#endif
}

void GLFrontend::renderLine (int x1, int y1, int x2, int y2, const Color& color)
{
#ifdef SDL_VIDEO_OPENGL
	const float nx1 = x1 * _rx;
	const float ny1 = y1 * _ry;
	const float nx2 = x2 * _rx;
	const float ny2 = y2 * _ry;
	const float verts[] = { nx1, ny1, nx2, ny2 };

	glEnable(GL_LINE_SMOOTH);
	setColorPointer(color, 4);
	enableTextureUnit(*_currentTextureUnit, false);
	glVertexPointer(2, GL_FLOAT, 0, verts);
	glDrawArrays(GL_LINES, 0, 2);
	glDisable(GL_LINE_SMOOTH);
	GL_checkError();
	enableTextureUnit(*_currentTextureUnit, true);
#endif
}

void GLFrontend::makeScreenshot (const std::string& filename)
{
#ifndef EMSCRIPTEN
	const int bytesPerPixel = 3;
	ScopedPtr<GLubyte> pixels(new GLubyte[bytesPerPixel * _width * _height]);
	int rowPack;
	glGetIntegerv(GL_PACK_ALIGNMENT, &rowPack);
	glPixelStorei(GL_PACK_ALIGNMENT, 1);
	glReadPixels(0, 0, _width, _height, GL_RGB, GL_UNSIGNED_BYTE, pixels);
	glPixelStorei(GL_PACK_ALIGNMENT, rowPack);

	ScopedPtr<SDL_Surface> surface(SDL_CreateRGBSurface(SDL_SWSURFACE, _width, _height, 24,
#if SDL_BYTEORDER == SDL_LIL_ENDIAN
			0x000000ff, 0x0000ff00, 0x00ff0000
#else
			0x00ff0000, 0x0000ff00, 0x000000ff
#endif
			, 0));
	if (!surface)
		return;
	const int pitch = _width * bytesPerPixel;
	for (int y = 0; y < _height; ++y)
		memcpy((uint8 *) surface->pixels + surface->pitch * y, (uint8 *) pixels + pitch * (_height - y - 1), pitch);
	const std::string fullFilename = FS.getAbsoluteWritePath() + filename + "-" + dateutil::getDateString() + ".png";
	IMG_SavePNG(surface, fullFilename.c_str());
#endif
}

void GLFrontend::updateViewport (int x, int y, int width, int height)
{
#ifdef SDL_VIDEO_OPENGL
	const float wantAspect = (float)width / height;
	const float realAspect = (float)_width / _height;

	float scale;
	if (fequals(wantAspect, realAspect)) {
		/* The aspect ratios are the same, just scale appropriately */
		scale = (float) _width / width;
		_viewPort.x = 0;
		_viewPort.w = _width;
		_viewPort.h = _height;
		_viewPort.y = 0;
	} else if (wantAspect > realAspect) {
		/* We want a wider aspect ratio than is available - letterbox it */
		scale = (float) _width / width;
		_viewPort.x = 0;
		_viewPort.w = _width;
		_viewPort.h = (int) SDL_ceil(height * scale);
		_viewPort.y = (_height - _viewPort.h) / 2;
	} else {
		/* We want a narrower aspect ratio than is available - use side-bars */
		scale = (float) _height / height;
		_viewPort.y = 0;
		_viewPort.h = _height;
		_viewPort.w = (int) SDL_ceil(width * scale);
		_viewPort.x = (_width - _viewPort.w) / 2;
	}

	_rx = scale;
	_ry = scale;
	glViewport(_viewPort.x, _viewPort.y, _viewPort.w, _viewPort.h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	const GLdouble _w = static_cast<GLdouble>(_viewPort.w);
	const GLdouble _h = static_cast<GLdouble>(_viewPort.h);
	glOrtho(0.0, _w, _h, 0.0, 0.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	GL_checkError();
#endif
}

void GLFrontend::renderBegin ()
{
#ifdef SDL_VIDEO_OPENGL
	SDL_GL_MakeCurrent(_window, _context);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
#endif
}

void GLFrontend::renderEnd ()
{
#ifdef SDL_VIDEO_OPENGL
	SDL_GL_SwapWindow(_window);
	GL_checkError();
#endif
}
