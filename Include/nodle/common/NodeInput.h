#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class NodeInput;
@protocol Node;

/**
 Defines how a node input communicates changes.
 */
@protocol NodeInputDelegate
@required

/**
 The input value was changed
 */
- (void)nodeInput:(NodeInput *)nodeInput didUpdateValue:(id)value;

@end

/**
 A type of input for a \c Node. This decides what type of input a node can accept.
 A node can accept more than one input by defining more of these.
 
 This class is well suited for subclassing so you can implement inputs for specific types.
 */
@interface NodeInput : NSObject

/**
 The current value of the input. The setter will run the validationBlock before
 trying to store the value.
 */
@property (nonatomic, strong, nullable) id value;

/**
 The node that this input beloongs to. Receives events regarding input changes.
 */
@property (nonatomic, assign, nullable) id<NodeInputDelegate, Node> node;

/**
 The optional key of this input for the node.
 */
@property (nonatomic, strong, nullable, readonly) NSString *key;

/**
 The block that validates incoming values.
 */
@property (nonatomic, copy, nullable, readonly) BOOL (^validationBlock)(id _Nullable value);

/**
 Create a new input without a key.
 This method is very good for instantiating subclasses of NodeInput since the
 validation block would be handled by the subclass
 */
+ (instancetype)inputWithKey:(nullable NSString *)key
                        node:(nullable id<NodeInputDelegate, Node>)node;

/**
 Create a new input.
 */
+ (instancetype)inputWithKey:(nullable NSString *)key
                  validation:(nullable BOOL (^)(_Nullable id value))validationBlock
                        node:(nullable id<NodeInputDelegate, Node>)node;

/**
 Create a new input without a key.
 This method is very good for instantiating subclasses of NodeInput since the
 validation block would be handled by the subclass
 */
- (instancetype)initWithKey:(nullable NSString *)key
                       node:(nullable id<NodeInputDelegate, Node>)node;

/**
 Create a new input.
 */
- (instancetype)initWithKey:(nullable NSString *)key
                 validation:(nullable BOOL (^)(id _Nullable value))validationBlock
                       node:(nullable id<NodeInputDelegate, Node>)node;

/**
 Checks if value is valid or not.
 */
- (BOOL)valueIsValid:(id _Nullable)value;

@end

NS_ASSUME_NONNULL_END