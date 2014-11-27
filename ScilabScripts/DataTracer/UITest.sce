 f1=figure('position',[50 50 100 100]);
a = uicontrol(f1, 'units','normalized', 'style', 'pushbutton','string','Pushbutton','position',[0.1 0.1 0.5 0.5],'tag','mybutton');

// Get the string for the uicontrol construction
uistring = guicontrolcreate(a);

// Create a figure and use the contructed string to create an uicontrol on the figure
// Due to the default string is generated for guibuilder, some string manupulation need to be done before using it
//f=figure('position',[50 50 100 100]);
//temp_str = strsplit(uistring);
//eval(strcat(temp_str(18:$)'));
