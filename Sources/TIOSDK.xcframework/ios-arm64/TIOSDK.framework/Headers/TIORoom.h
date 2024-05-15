//
//  TIORoom.h
//  tio-chat-ios
//
//  Created by QuangAnh on 28/08/2023.
//  Copyright © 2023 刘宇. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <TIOSDK/TIODefines.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSUInteger, TIORoomJoinType) {
    TIORoomJoinTypeReview = 1,
    TIORoomJoinTypeNotReview = 2,
};

typedef NS_ENUM(NSUInteger, TIORoomStatus) {
    TIORoomStatusNormal = 1,
    TIORoomStatusDissolved = 3,
};

@interface TIORoom : NSObject

@property (copy, nonatomic) NSString *roomId;

@property (copy, nonatomic) NSString *intro;

@property (copy, nonatomic) NSString *name;

@property (copy, nonatomic) NSString *avatar;

@property (copy, nonatomic) NSString *notice;

@property (copy,    nonatomic) NSString *createtime;

@property (copy,    nonatomic) NSString *managerId;

@property (assign,  nonatomic) NSInteger    memberNumber;

@property (assign,  nonatomic) TIORoomJoinType joinType;

@property (assign,  nonatomic) TIORoomStatus status;

@property (assign,  nonatomic) BOOL applyFlag;

@property (assign,  nonatomic) NSInteger forbiddenflag;

@property (assign, nonatomic) TIORoomUserRole grouprole;

@property (assign,  nonatomic) NSInteger friendflag;

@end

NS_ASSUME_NONNULL_END
