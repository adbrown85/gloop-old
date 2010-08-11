/*
 * Outputs.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef OUTPUTS_HPP
#define OUTPUTS_HPP
#include "common.h"
#include <algorithm>                    // Finding attachments
#include "Attachment.hpp"
#include "Configuration.hpp"            // Max draw buffers
using namespace std;


/** @brief Activates framebuffer attachments.
 * @ingroup advanced
 */
class Outputs : public Node, public Applicable {
public:
	Outputs(const Tag &tag);
	virtual ~Outputs();
	virtual GLint addAttachment(Attachment *attachment);
	virtual void apply();
	virtual void remove() {}
	virtual string toString() const;
public: // Utilities
	static Outputs* find(Node *node);
protected:
	virtual void associate();
	virtual void finalize();
private:
	list<Attachment*> attachments;
	Framebuffer *framebuffer;
	GLenum *locations;
	GLsizei n;
};


#endif
