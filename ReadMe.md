## VirtualInput

A HID driver that includes a virtual mouse, keyboard, and an additional mouse with absolute coordinates, for Windows 10/11. Based on [loki-hidriver](https://github.com/hedgar2017/loki-hidriver).

## Installation 

1. Run `bcdedit /set testsigning on` to enable test mode, then reboot your system.  
2. Build the project in Debug mode.  
3. Open the output folder and run `devcon install VirtualInput.inf HID\VirtualInput` to install the driver.  
   `devcon.exe` can be found in the WDK installation directory, such as:  
   `C:\Program Files (x86)\Windows Kits\10\Tools\10.0.26100.0\x64`  

## Usage

Use the driver just like it is used in [the example](https://github.com/koharubiyori/VirtualInput-Interface).

## Development

To view the logs sent by `TraceEvents()`, you can use `traceview.exe` to create a new log session using the tracing GUID `53814163-f190-47fb-9aa6-4e15e43b4e3e` (defined in `Trace.h`).

