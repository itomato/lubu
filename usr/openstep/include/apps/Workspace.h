#ident "@(#)Workspace.h 2.4 96/07/09 workspace SMI"
//
//      Copyright (c) 1995-1996, Sun Microsystems, Inc.
//      portions (c) Copyright 1994, NeXT Computer, Inc.
//      All rights reserved.

/* Subclass WMInspector for your own auto-loadable bundle */

@interface WMInspector: NSObject {
    /* private UI elements */
    id		window;
    id		okButton;
    id		revertButton;
    id		dirNameField;
    id		dirTitleField;
    id		fileNameField;
    id		fileIconButton;
}

+ new;

/* Required in subclass
 * Responsible for loading the nib file;
 * Clone an existing inspector nib file, e.g:
 *
 * /usr/openstep/Apps/WM.app/inspectors.bundle/English.lproj/SoundInspector.nib
 *
 * for making new inspectors.
 */

/*****************	Access to UI elements	**************************/

- window;
- okButton;
- revertButton;

/*****************	Access to Workspace selection	**********************/

- (unsigned)selectionCount;
    /* Number of selected items */
- selectionPathsInto:(char *)paths separator:(char)ch;
    /* Each selected item goes into paths, separated by specified separator;
    paths must be dimensioned to selectionCount * (MAXPATHLEN + 1)*/
    
/*****************	Access to Workspace selection	**********************/

- revert:sender;
    /* Required in subclass */
    /* This is the main point of functionality: this method is called when the inspector is activited; must call [super revert:sender] */
    
- ok:sender;
    /* Optional, required if the inspector allows changing attributes of the selection */
    /* When present must call [super ok:sender] */

- touch:sender;
    /* Optional */
    /* marks the window as edited; 
    When defined lets subclass reject touch: */ 
    
- textDidChange:sender;
    /* Optional */
    /* calls touch; facilitates NIB connections of the textDelegates */
    
@end
