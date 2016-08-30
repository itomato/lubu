#ident "@(#) TerminalDOProtocol.h, Rev 1.5, 97/03/17"
//
//      Copyright (c) 1995-1996, Sun Microsystems, Inc.
//      portions (c) Copyright 1994, NeXT Computer, Inc.
//      All rights reserved.

/*
	This protocol allows applications to request that the Terminal
application perform commands on their behalf.  This is useful if
a program wants to open up a shell window for the user to interact
with, and it may be easier than setting up pipes and doing a 
fork/exec of a program yourself.  The commands may be run in a window,
in which case a window handle is returned to allow a window to be
reused for subsequent commands, or they may be performed in the
background.  Additionally, you can pass in an NSData object whose
data will be fed to the command's stdin, and if you pass in a pointer
to an NSData, Terminal can hand you back the output of the commands
stdout and/or stderr.

	Terminal cannot provide services if it is not running.  It may
be necessary to use the workspace request protocol to launch
Terminal if the connection to Terminal fails.

	The following protocol is accessed through distributed objects.

Terminal's distributed service may be disabled as follows:
	dwrite Terminal DisableDOServices YES

You can only get the stdout and stderr of a command if it is run in
the background.  If you pass a pointer to get these back, the data
at the pointer should be nil before invoking the command.  Upon
completion, the pointer will point to an newly created
NSData containing the output.
*/

#import <Foundation/NSObject.h>

typedef enum {
	TSWindowNone = 0,
	TSWindowIdle = 2,
	TSWindowNew = 4,
	TSWindowDedicated = 8
	} TSWindowType;

typedef enum {
	TSShellNone = 1,
	TSShellBourne = 2,
	TSShellDefault = 4,
	TSShellFastC = 8
	} TSShellType;

typedef enum {
	TSCloseOnExit = 0,
	TSCloseUnlessError = 1,
	TSDontCloseOnExit = 2
	} TSExitAction;

@protocol TSTerminalDOServices

// indicates the version implemented
- (int) protocolVersion;

// run in a new window, using fast c shell
- runCommand:(const char *)cmdString
	windowTitle:(const char *)winTitle;

// run command in a specified window
- runCommand:(const char *)cmdString
	windowType: (TSWindowType)winType
	windowHandle: (inout int *)myHandle
	shellType:(TSShellType)shellType
	windowTitle:(const char *)winTitle
	returnCode:(out int *)retCode;

// run in background using fast c shell, return stdout
- runCommand:(const char *)cmdString
	inputData:inputData					// an NSData object for stdin
	outputData:(id *)outputData			// a pointer to an NSData object
	waitForReturn:(int)shouldWait		// synchronous even if no out data?
	directory:(const char *)workingDir	// where to cd before execution
	returnCode:(out int *)retCode;

// the full form, all others invoke this
- runCommand:(const char *)cmdString
	inputData:(id)inputData
	outputData:(id *)outputData
	errorData:(id *)errorData
	waitForReturn:(int)shouldWait		// synchronous even if no out data?
	windowType: (TSWindowType)winType
	windowHandle: (inout int *)myHandle
	exitAction: (TSExitAction)exitAction
	shellType:(TSShellType)shellType
	windowTitle:(const char *)winTitle
	directory:(const char *)workingDir
	environment:(id)environmentData		// null separated in an NSData
	returnCode:(out int *)retCode;

@end
