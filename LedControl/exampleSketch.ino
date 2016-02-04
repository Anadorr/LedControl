#include "ColorChangeScheduler.cpp"
#include "LedActions/BaseLedAction.cpp"
#include "main.cpp"

int freeRam () 
{
  extern int __heap_start, *__brkval; 
  int v; 
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval); 
}


void setup() {
  Serial.begin(57600);
}


void loop() {
    int runCount = 0;
    while(true) {
        uint actionCount = 0;
        long endTime = 0;
        lazyActionInitializer ** actionTable = BuildActionTable(actionCount, endTime);

        long currentTime = 0;
        ActionWalker walker = ActionWalker(actionTable, actionCount);

        while (currentTime < endTime) {
            RGB color = walker.GetCurrentColor(currentTime);
            
            if (currentTime % 100 == 0) {
                Serial.println((String)"RUN: " + runCount + " RAM: " + freeRam());
                Serial.println((String)"time:" + currentTime);
                Serial.println((String)"color:" + color.r + " " + color.g + " " + color.b);
            }
            currentTime += 10;
        }

        walker.DestroyTable();
        runCount++;
    }
}
