;GIL-3
(
(
	:type                   :popup-window
	:name                   popup1
	:owner                  nil
	:width                  597
	:height                 390
	:background-color       ""
	:foreground-color       ""
	:label                  "Lubu OpenMagic 1.0 Copyright Notice"
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
	:type                   :text-pane
	:name                   textpane1
	:owner                  popup1
	:help                   ""
	:x                      0
	:y                      0
	:width                  597
	:height                 390
	:background-color       ""
	:foreground-color       ""
	:initial-state          :visible
	:show-border            nil
	:read-only              t
	:event-handler          nil
	:user-data              ()
	:actions                (
		(
		:from                   (popup1 textpane1)
		:when                   (AnyEvent )
		:to                     (popup1 textpane1)
		:function_type          :user_defined
		:arg_type               (:string)
		:action                 (LoadTextFile "Copyright.txt")
		)
	)
)
)
