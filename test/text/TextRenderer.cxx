/*
 * TextRenderer.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "gloop_common.h"
#include "../Test.h"
#include "TextRenderer.hpp"


/** @brief Test for %TextRenderer. */
class TextRendererTest : public Test {
public:
	TextRendererTest();
	void testDraw();
	virtual void onCanvasInitEvent(Canvas &canvas);
	virtual void onCanvasDisplayEvent(Canvas &canvas);
private:
	Font *font;
	TextRenderer *textRenderer;
};

/** Creates a test. */
TextRendererTest::TextRendererTest() {
	font = new Font("Arial", Font::PLAIN, 72);
	textRenderer = NULL;
}

/** Runs the test. */
void TextRendererTest::testDraw() {
	runWindow();
}

void TextRendererTest::onCanvasInitEvent(Canvas &canvas) {
	textRenderer = new TextRenderer(*font);
}

void TextRendererTest::onCanvasDisplayEvent(Canvas & canvas) {
	
	glClearColor(0, 1, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	textRenderer->begin(512, 512);
	textRenderer->draw("Text Renderer", 50, 50);
	textRenderer->end();
}

#define HARNESS TextRendererTest
#include "../Runner.h"
START_TESTS
ADD_TEST(testDraw)
RUN_TESTS

