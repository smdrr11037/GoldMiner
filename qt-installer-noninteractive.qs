// qt-installer-noninteractive.qs

function Controller() {
    installer.autoAcceptLicense = true;
}

function Component() {
    // Specify Qt components to install
    installer.addPage(installer.targetPage);
    installer.addPage(installer.componentSelectionPage);
    installer.addPage(installer.installationPage);
    installer.addPage(installer.finishedPage);
}

function TargetDirectoryPageCallback() {
    // Set installation path
    var widget = gui.pageWidgetByObjectName("TargetDirectoryPage");
    widget.TargetDirectoryLineEdit.setText("C:\\Qt\\5.15.2");
}

function ComponentSelectionPageCallback() {
    // Select components to install
    var widget = gui.pageWidgetByObjectName("ComponentSelectionPage");
    widget.deselectAll();
    widget.selectComponent("qt.qt5.5152.win64_msvc2019_64");
}
