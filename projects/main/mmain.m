#include "nl_lib.h"
#import <Foundation/Foundation.h>

extern void app_specific_init(void);
extern void app_specific_update(double dt);
extern void app_specific_render(void);
extern void app_specific_cleanup(void);

int main (int argc, const char * argv[])
{
    NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
    {
        NSLog (@"C include okay");
       
        app_specific_init();
	app_specific_update(0.01);
	app_specific_render();
	app_specific_cleanup();

	[pool drain];
    }
    return 0;
}
