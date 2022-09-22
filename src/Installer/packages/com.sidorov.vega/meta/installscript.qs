function Component()
{
    // default constructor
}

Component.prototype.createOperations = function()
{
    component.createOperations();

    if (systemInfo.productType === "windows") 
    {
        component.addOperation("CreateShortcut", "@TargetDir@/Vega.exe", "@StartMenuDir@/Vega.lnk",
            "workingDirectory=@TargetDir@", "description=Run Vega");
    }
    else if (systemInfo.productType === "osx")
    {}
	else
	{
	
        component.addOperation("CreateDesktopEntry", 
                              "/usr/share/applications/vega.desktop", "Encoding=UTF-8\nType=Application\nName=Vega\nExec=@TargetDir@/Vega\nIcon=/usr/share/icons/hicolor/scalable/apps/Vega.svg\nTerminal=false\nCategories=GNOME;Application;\nStartupNotify=true")
							  
	  	component.addOperation("Copy", "@TargetDir@/Icon/Vega.svg", "/usr/share/icons/hicolor/scalable/apps/Vega.svg")
    }
}
