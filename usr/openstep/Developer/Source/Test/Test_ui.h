#ifndef	Test_HEADER
#define	Test_HEADER

/*
 * Test_ui.h - User interface object and function declarations.
 * This file was generated by `gxv' from `Test.G'.
 * DO NOT EDIT BY HAND.
 */

extern Attr_attribute	INSTANCE;

extern Xv_opaque	Test_menu1_create(caddr_t, Xv_opaque);

typedef struct {
	Xv_opaque	popup1;
	Xv_opaque	canvas1;
} Test_popup1_objects;

extern Test_popup1_objects	*Test_popup1_objects_initialize(Test_popup1_objects *, Xv_opaque);

extern Xv_opaque	Test_popup1_popup1_create(Test_popup1_objects *, Xv_opaque);
extern Xv_opaque	Test_popup1_canvas1_create(Test_popup1_objects *, Xv_opaque);
#endif
