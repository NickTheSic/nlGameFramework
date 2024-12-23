#include "private/nl_platform.h"

#import <Foundation/Foundation.h>
#import <Cocoa/Cocoa.h>

int platform_init(void)
{
    NSLog (@"Mac Build-PlatformInit");
    return 0;
}

void platform_cleanup(void)
{
    NL_UNIMPLEMENTED_FUNC
}
