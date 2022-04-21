// interface
#include "oled.h"


// arduino includes
#include <Arduino.h>
//
#include <Adafruit_SSD1306.h>
#include <SPI.h>
#include <stdint.h>

Adafruit_SSD1306 display(128, 64, &Wire, 4);

namespace oled {
// -- prototypes --
void refresh(int total_count, int unsafe_count, inches_t* distances, int len);

// -- impls --

void init() {
    // /*noInterrupts();*/
    debug_println("oled::init()... ");

    oled_delay("\t1");
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // setting up OLED display

    oled_delay("\t2.a");
    display.clearDisplay();

    oled_delay("\t2.b");
    display.setTextSize(1);

    oled_delay("\t2.c");
    display.setTextColor(SSD1306_WHITE);

    oled_delay("\t2.d");
    display.fillRect(0, 0, 128, 64, SSD1306_WHITE);

    oled_delay("\t3");
    display.display();

    oled_delay("\t4");
    display.clearDisplay();

    oled_delay("\t5");
    display.display();

    oled_delay("\t6");
    debug_println("... done (oled::init)");
}

void update(track::tracker_t* tracker) {
    static const inches_t ls[] = {1, 2, 3, 4};
    refresh(tracker->total_event_count, tracker->unsafe_event_count, tracker->closest_events, 4);
}

void refresh(int total_count, int unsafe_count, inches_t* distances, int len) {
    display.clearDisplay();

    display.setCursor(0, 0);
    display.print("# of Patrons: ");  // good 1
    display.println(total_count);     // good 2
    display.print("# of unsafe: ");   // bad 1 ? or maybe good 2.5
    display.println(unsafe_count);    // good 3

    // clang-format off
    if (distances[0] != TOMBSTONE_DIST) display.println(distances[0] / 12);
    else display.println("-");

    if (distances[1] != TOMBSTONE_DIST) display.println(distances[1] / 12);
    else display.println("-");

    if (distances[2] != TOMBSTONE_DIST) display.println(distances[2] / 12);
    else display.println("-");

    if (distances[3] != TOMBSTONE_DIST) display.println(distances[3] / 12);
    else display.println("-");
    // clang-format on


    // display.print((distances[0] / 12));
    // display.print(", ");
    // display.print((distances[1] / 12));
    // display.print(", ");
    // display.print((distances[2] / 12));
    // display.print(", ");
    // display.print((distances[3] / 12));

    oled_delay("...");
    display.display();
    oled_delay("...");
}

}  // namespace oled
