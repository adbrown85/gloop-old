/*
 * AdvancedFactory.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "AdvancedFactory.hpp"
bool AdvancedFactory::installed=false;


void AdvancedFactory::install() {
	
	// Check if already called
	if (installed)
		return;
	installed = true;
	
	// Make sure basic factory is already installed
	BasicFactory::install();
	
	// Tags
	Factory::install("boolean", &createBoolean);
	Factory::install("blend", &createBlend);
	Factory::install("bind", &createBind);
	Factory::install("branch", &createBranch);
	Factory::install("choose", &createChoose);
	Factory::install("clear", &createClear);
	Factory::install("clone", &createClone);
	Factory::install("cull", &createCull);
	Factory::install("depth", &createDepth);
	Factory::install("framebuffer", &createFramebuffer);
	Factory::install("fullscreen", &createFullscreen);
	//Factory::install("octree", &createOctree);
	Factory::install("outputs", &createOutputs);
	Factory::install("placeholder", &createPlaceholder);
	Factory::install("renderbuffer", &createRenderbuffer);
	Factory::install("replacement", &createReplacement);
	Factory::install("replica", &createReplica);
	Factory::install("screen", &createScreen);
	Factory::install("shadow", &createShadow);
	Factory::install("sort", &createSort);
	Factory::install("target", &createTarget);
	Factory::install("uniform", &createUniform);
}


Node* AdvancedFactory::createBind(const Tag &t) {return new Bind(t);}

Node* AdvancedFactory::createBlend(const Tag &t) {return new Blend(t);}


/** @throw NodeException if boolean operation not supported. */
Node* AdvancedFactory::createBoolean(const Tag &tag) {
	
	string operation;
	
	tag.get("operation", operation);
	if (operation == "and") {
		return new BooleanAnd(tag);
	} else if (operation == "xor") {
		return new BooleanXor(tag);
	} else {
		NodeException e(tag);
		e << "[AdvancedFactory] Boolean operation not supported.";
		throw e;
	}
}

Node* AdvancedFactory::createBranch(const Tag &t) {return new Branch(t);}

Node* AdvancedFactory::createCull(const Tag &t) {return new Cull(t);}

Node* AdvancedFactory::createChoose(const Tag &t) {return new Choose(t);}

Node* AdvancedFactory::createClear(const Tag &t) {return new Clear(t);}

Node* AdvancedFactory::createClone(const Tag &tag) {return new Clone(tag);}

Node* AdvancedFactory::createDepth(const Tag &t) {return new Depth(t);}

Node* AdvancedFactory::createFramebuffer(const Tag &t) {return new Framebuffer(t);}

Node* AdvancedFactory::createFullscreen(const Tag &t) {return new Fullscreen(t);}

/*
Node* AdvancedFactory::createOctree(const Tag &t) {return new Octree(t);}
*/

Node* AdvancedFactory::createOutputs(const Tag &t) {return new Outputs(t);}

Node* AdvancedFactory::createPlaceholder(const Tag &t) {return new Placeholder(t);}

Node* AdvancedFactory::createRenderbuffer(const Tag &t) {return new Renderbuffer(t);}

Node* AdvancedFactory::createReplacement(const Tag &t) {return new Replacement(t);}

Node* AdvancedFactory::createReplica(const Tag &t) {return new Replica(t);}

Node* AdvancedFactory::createScreen(const Tag &t) {return new Screen(t);}

Node* AdvancedFactory::createShadow(const Tag &t) {return new Shadow(t);}

Node* AdvancedFactory::createSort(const Tag &t) {return new Sort(t);}

Node* AdvancedFactory::createTarget(const Tag &t) {return new Target(t);}

Node* AdvancedFactory::createUniform(const Tag &tag) {
	
	string type;
	
	// Get type
	tag.get("type", type);
	
	// Create based on type
	if (type == "float[]") {
		return new UniformFloatArray(tag);
	} else {
		return BasicFactory::createUniform(tag);
	}
}
