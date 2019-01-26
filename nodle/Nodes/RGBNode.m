#import "RGBNode.h"
#import <CoreGraphics/CGBase.h>

@implementation RGBNode

@synthesize inputs = _inputs;
@synthesize outputs = _outputs;;

- (instancetype)init {
    self = [super init];
    if (self) {
        _inputs = @{
                    @"R": [[NodeInput alloc] initWithType:[NSNumber class]],
                    @"G": [[NodeInput alloc] initWithType:[NSNumber class]],
                    @"B": [[NodeInput alloc] initWithType:[NSNumber class]]
                    };
        
        _outputs = @{
                     @"R": [[NodeOutputCollection alloc] initWithKey:@"R"],
                     @"G": [[NodeOutputCollection alloc] initWithKey:@"G"],
                     @"B": [[NodeOutputCollection alloc] initWithKey:@"B"]
                     };
    }
    
    return self;
}

- (void)performForInput:(NSString *)inputKey withValue:(id)value {
    if (![self.inputs.allKeys containsObject:inputKey] ||
        ![[self.inputs objectForKey:inputKey] isValueValid:value]) {
        return;
    }
    
    [self.inputs objectForKey:inputKey].value = value;
    
    if ([self canRun]) {
        [self superSeriousBusinessLogicFunc];
        [super distributeToSubNodes];
    }
}

- (void)superSeriousBusinessLogicFunc {
    CGFloat r = [((NSNumber *)self.inputs[@"R"].value) floatValue],
            g = [((NSNumber *)self.inputs[@"G"].value) floatValue],
            b = [((NSNumber *)self.inputs[@"B"].value) floatValue];
    
    self.outputs[@"R"].value = @(r + 0.1);
    self.outputs[@"G"].value = @(g + 0.1);
    self.outputs[@"B"].value = @(b + 0.1);
}

@end
