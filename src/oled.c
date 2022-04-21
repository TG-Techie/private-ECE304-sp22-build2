// interface
#include "oled.h"


#include "config.h"

#include "SSD1306.h"

// -- prototypes --
void oled__refresh(int total_count, int unsafe_count, inches_t* distances, int len);

// -- impls --

void oled__init() {
#if ENABLE_OLED == ON
    // /*noInterrupts();*/

    OLED_Init();
    OLED_DisplayString("---------------------");
    OLED_Clear();
    debug_println("... done (oled::init)");
#endif
}

// void update(track__tracker_t* tracker) {
//     static const inches_t ls[] = {1, 2, 3, 4};
//     refresh(tracker->total_event_count, tracker->unsafe_event_count, tracker->closest_events,
//     4);
// }

void oled__refresh(int total_count, int unsafe_count, inches_t* distances, int len) {
#if ENABLE_OLED == ON
    // OLED_Clear();
    OLED_SetCursor(0, 0);
    OLED_DisplayString("# of Patrons: ");
    OLED_DisplayNumber(10, total_count, 2);
    OLED_GoToLine(2);
    OLED_DisplayString("# of Unsafe: ");
    OLED_DisplayNumber(10, unsafe_count, 2);

    // // clang-format off
    // if (distances[0] != TOMBSTONE_DIST) display.println(distances[0] / 12);
    // else display.println("-");

    // if (distances[1] != TOMBSTONE_DIST) display.println(distances[1] / 12);
    // else display.println("-");

    // if (distances[2] != TOMBSTONE_DIST) display.println(distances[2] / 12);
    // else display.println("-");

    // if (distances[3] != TOMBSTONE_DIST) display.println(distances[3] / 12);
    // else display.println("-");
    // // clang-format on


    // display.print((distances[0] / 12));
    // display.print(", ");
    // display.print((distances[1] / 12));
    // display.print(", ");
    // display.print((distances[2] / 12));
    // display.print(", ");
    // display.print((distances[3] / 12));

#endif
}
