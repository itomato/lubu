#import <appkit/appkit.h>

#import <Template.h>

@implementation Template

+ new
/*
    Called first time this section's button is clicked.
*/
{
    self = [super new];
    
    if( ![NXApp loadNibForLayout: "Template" owner: self] )
	return 0;
	
    // 'window' is an interface builder outlet.
    view = [window contentView];	// 'view' MUST be initialized
    [view removeFromSuperview];
    [window setContentView: 0];		// Don't need the window for anything
    [window free];			// So free it.
    
    // Do any other set up here.
    
    return self;
}

- willSelect: sender
/*
    Before the view is added via addSubview
*/
{
    return self;
}

- didSelect: sender
/*
    After the view is added via addSubview
*/
{
    /*
    Enable all of the edit and window menu items, just for the heck of it.
    */
    [NXApp enableEdit: CUT_ITEM|COPY_ITEM|PASTE_ITEM|SELECTALL_ITEM];
    [NXApp enableWindow: MINIATURIZE_ITEM|CLOSE_ITEM];
    return self;
}


- willUnselect: sender
/*
    Before removeFromSuperview
*/
{
    /* Make sure that we aren't editing any text fields. */
    [[NXApp appWindow] endEditingFor: self];  
    return self;
}

- didUnselect: sender
/*
    Before removeFromSuperview
*/
{
    /*
    Disable all of the edit and window menu items, just for the heck of it.
    */
    [NXApp enableEdit: NO];
    [NXApp enableWindow: NO];
    return self;
}

- didHide: sender
/*
    Application was just hidden.
*/
{
    return self;
}

- didUnhide: sender
/*
    Application was just unhidden.
*/
{
    return self;
}

- button1Clicked: sender
{
    printf( "button1Clicked:\n" );
    return self;
}

- button2Clicked: sender
{
    printf( "button2Clicked:\n" );
    return self;
}


@end

