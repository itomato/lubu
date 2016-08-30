;GIL-3
(
(
	:type                   :menu
	:name                   menu1
	:help                   ""
	:columns                1
	:menu-type              :command
	:menu-handler           exit
	:menu-title             "File"
	:menu-item-labels       ("Quit .." )
	:menu-item-label-types  (:string )
	:menu-item-states       (:active )
	:menu-item-defaults     (nil )
	:initial-selections     (nil )
	:menu-item-handlers     (nil )
	:menu-item-menus        (nil )
	:menu-item-colors       ("" )
	:pinnable               t
	:user-data              ()
	:actions                (
		(
		:from                   (menu1)
		:when                   (Notify )
		:to                     (menu1)
		:function_type          CallFunction
		:arg_type               ()
		:action                 (exit)
		)
	)
)
(
	:type                   :popup-window
	:name                   popup1
	:owner                  nil
	:width                  400
	:height                 150
	:background-color       ""
	:foreground-color       ""
	:label                  "Popup Window"
	:label-type             :string
	:initial-state          :invisible
	:show-footer            t
	:resizable              t
	:pinned                 nil
	:done-handler           nil
	:event-handler          nil
	:user-data              ()
	:actions                ()
)
(
	:type                   :canvas-pane
	:name                   canvas1
	:owner                  popup1
	:help                   ""
	:x                      0
	:y                      0
	:width                  400
	:height                 150
	:background-color       ""
	:foreground-color       ""
	:initial-state          :visible
	:draggable              nil
	:droppable              nil
	:default-drop-site      nil
	:menu                   nil
	:horizontal-scrollbar   nil
	:scrollable-width       400
	:vertical-scrollbar     nil
	:scrollable-height      150
	:repaint-proc           nil
	:event-handler          nil
	:drawing-model          :xwindows
	:user-data              ()
	:actions                (
		(
		:from                   (popup1 canvas1)
		:when                   (AnyEvent )
		:to                     (popup1 canvas1)
		:function_type          :user_defined
		:arg_type               ()
		:action                 (Show)
		)
	)
)
)
