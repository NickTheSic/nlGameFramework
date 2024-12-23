#include "nl_lib.h"
#import <Foundation/Foundation.h>
#import <Cocoa/Cocoa.h>

extern void app_specific_init(void);
extern void app_specific_update(double dt);
extern void app_specific_render(void);
extern void app_specific_cleanup(void);

@interface AppDelegate : NSObject<NSApplicationDelegate>

@end

int main (int argc, const char * argv[])
{
    NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
    {
        NSLog (@"C include okay");
	
	platform_init();       
        app_specific_init();
	
	while (true)
	{
		app_specific_update(0.01);
		app_specific_render();
	}

	app_specific_cleanup();
	platform_cleanup();
	[pool drain];
    }
    return 0;
}
