# Fireball_v5

<B>Compiling the Code</B>
<p>The Arduino IDE to compile and upload the code to the Fireball.  I've used the older v1.0.6 and latest
(current as of today) v1.6.8 IDE.  You will need to add the following board manager URL in the Arduino IDE Preferences, 
in order to successfully compile for the Atmel ATtiny85 processor:
https://raw.githubusercontent.com/damellis/attiny/ide-1.6.x-boards-manager/package_damellis_attiny_index.json

After you have added this to the board manager, goto Tools -> Board:, and select ATtiny at the bottom of the pulldown.
Then select the Tools menu again and you'll see additional options for Processor & Clock.
  Under the Tools -> Processor:, select ATtiny85.
  Under the Tools -> Clock:, select 8 MHz (internal)

Click the Verify button to confirm the code will compile.  If it does, you're ready to connect your AVR Programmer and
compile/upload the code.  I'm using an AVRISP mkII programmer, but I've also found my cheaper USBtinyISP purchased off
ebay worked just fine.  Sometimes you might have to select the Upload Using Programmer method, if the normal method fails.

DON'T FORGET TO BURN THE BOOTLOADER <B>BEFORE</B> UPLOADING THE CODE.</p>

<b>Config.h Settings</b>

<p>There are 3 lines in the config.h file that should be set based on user preference.</p>
<p>#define IDLE_BEEPS       true  // Enable short beeps on the second during idle time.  Set to either true or false. </p>
<p>#define SEND_CALL        true  // Enables sending of your callsign.  Set to either true or false. </p>
<p>#define CALLSIGN        "FB5"  // Operator's callsign.  Self explanatory, but can be anything less than 15 characters. </p>

<p> Have Fun with it!!!<p/>


John
AB5SS

