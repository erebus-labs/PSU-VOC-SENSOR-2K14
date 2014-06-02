<?xml version="1.0"?>
<dpInst>	
	<suppressWizard/>
    <language code="0x0409">
        <dpinstTitle>Cypress USB-Serial Driver Installer</dpinstTitle>
    
        <welcomeTitle>Welcome to the Cypress USB-Serial Installer!</welcomeTitle>
        <welcomeIntro>This wizard will walk you through updating the drivers for your Cypress USB-Serial devices.</welcomeIntro>
    
		<suppressEulaPage/>
        <installHeaderTitle>Installing the driver for your USB-Serial device...</installHeaderTitle>        
    </language>
	<group>
		<package path="__LOC__\CypressUsbAndBus.inf"/>
		<package path="__LOC__\CypressSerial.inf"/>
		<suppressAddRemovePrograms/>
	</group>
</dpInst>

