/*
 * GlyphRenderer.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "gloop_common.h"
#include "../Test.h"
#include "GlyphRenderer.hpp"
#include "ErrorChecker.hpp"


class GlyphRendererTest : public Test {
public:
	GlyphRendererTest();
	void testDraw();
	virtual void onCanvasInitEvent(Canvas &canvas);
	virtual void onCanvasDisplayEvent(Canvas &canvas);
private:
	Font *font;
	GlyphRenderer *glyphRenderer;
	GlyphFactory *glyphFactory;
	GlyphTexture *glyphTexture;
	Glyph *glyphs[2];
	GlyphCoords glyphCoords;
};

GlyphRendererTest::GlyphRendererTest() {
	font = new Font("Arial", Font::PLAIN, 72);
	glyphFactory = GlyphFactory::getInstance(*font);
	glyphs[0] = glyphFactory->create('@');
	glyphs[1] = glyphFactory->create('A');
}

void GlyphRendererTest::testDraw() {
	runWindow();
}

void GlyphRendererTest::onCanvasInitEvent(Canvas &canvas) {
	glyphRenderer = new GlyphRenderer();
	glyphTexture = GlyphTexture::getInstance(*font);
}

void GlyphRendererTest::onCanvasDisplayEvent(Canvas &canvas) {
	
	glClearColor(0, 1, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glyphTexture->bind();
	glyphRenderer->beginRendering(512, 512);
	
	glyphCoords = glyphTexture->find(glyphs[0]);
	glyphRenderer->draw(glyphs[0], 200, 50, glyphCoords);
	glyphCoords = glyphTexture->find(glyphs[1]);
	glyphRenderer->draw(glyphs[1], 300, 50, glyphCoords);
	
	glyphRenderer->endRendering();
	
	ErrorChecker::check("After draw");
}

/* Run the test. */
#define HARNESS GlyphRendererTest
#include "../Runner.h"
START_TESTS
ADD_TEST(testDraw)
RUN_TESTS



