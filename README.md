# LedControl

## About
LedControl creates programmable, non-blocking, fast and low-footprint effects for LED strip control with Arduino. Can be used with Arduino Mini.
It allows you to schedule a sequence of desired LED effects and then get current color at any point of time, to be output to pins.
I never learned C++ so the code may seem hacky.

### Simplified example:
<pre><code>
	uint actionCount = 3;
    lazyActionInitializer ** actionTable = new lazyActionInitializer *[actionCount];
    int i=0; 
    //                                                                          Action type  Start time      Duration     ColorFrom    ColorTo     Delay afterwards
    arr[i++]  = new lazyActionInitializer([] ()->BaseLedAction* { return new ColorChangeAction(  0,           1000,       COLOR_BLACK, COLOR_WHITE, 0); });
    arr[i++]  = new lazyActionInitializer([] ()->BaseLedAction* { return new StrobeAction(1000, 1000, COLOR_RED, COLOR_GREEN, 0); });
    arr[i++]  = new lazyActionInitializer([] ()->BaseLedAction* { return new StrobeUnevenAction(2000, 1000, COLOR_HBLUE, COLOR_MAGENTA, 0, 0.3f,0); });

    ActionWalker walker = ActionWalker(actionTable, actionCount);

	// call walker.GetCurrentColor(time) at any point to get color which should be displayed
    long currentTime = 0;
    long endTime = 3000;
    while (currentTime < endTime) {
        RGB color = walker.GetCurrentColor(currentTime);
        cout << (int)color.r << "/" << (int)color.g << "/" << (int)color.b << endl;
        currentTime += 10;
    }
</code></pre>

## License
GPL v3, see LICENSE for details.

## Supported effects: 
### COLOR CHANGE
Evenly change from &lt;colorFrom&gt; to &lt;colorTo&gt;.

### STROBE
Change from &lt;colorFrom&gt; to &lt;colorTo&gt; and back.

### UNEVEN STROBE
Change from &lt;colorFrom&gt; to &lt;colorTo&gt; in &lt;upPercent&gt; time of &lt;total duration&gt;; wait for &lt;maxBrightnessPercent&gt; of time; change back to initial color

### STROBE CYCLE
Strobe several times

### STROBE RAINBOW
Strobe from black to &lt;color&gt; and back to black for all colors in rainbow table.

### FULL RAINBOW
Change rainbow colors from one to another without black in between.

## Using in your sketch
See exampleSketch.ino. Make sure to comment EXECUTABLE and DEBUG defines - they are used only to test the schedule on PC.  EXAMPLE define provides example BuildActionTable function.
<p><b>You will need C++11 to use LedControl. If you use inotool, use 'ino build -f="-std=gnu++11"' command.</b>

## Project structure
* TBD

## Unit tests
Project is partially covered by C#/NUnit unit tests - see LedControl.Test.
Memory leaks were mostly fixed, see Known Issues. 
Project has been tested with Valgrind for memory leaks (see valgrind-memory-leak-check.sh).

## Testing/compiling
To test your schedule on PC:
* Place it into LedControl/example.cpp and uncomment EXECUTABLE and DEBUG defines;
* Change LedControl/CMakeLists.txt - uncomment add_executable, comment add_executable;
* Compile/make using LedControl/make.sh, cmake+make, or IDE of your choice;
* Run; you should see output for all schedule with timestamps. 
* All actions in your schedule ideally should be sequential and have start/end times correct (next action should start at the time when previous ended). With DEBUG defined, this is strictly checked.

## Known Issues
* Minor memory leak: with a 8-minute schedule of 50+ complex actions, Arduino Leonardo hangs on 4th consecutive repeat in loop. 
* Actions with high Count (especially Rainbow actions) may require more than 1k memory; split action in several parts if this happen. Use Valgrind to check max-alloc during program lifetime.

## Examples
* TBD

## TODO
* Add examples
* Cover all actions with unit tests
* Fix memory leak
* Add Releases
