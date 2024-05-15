//
//  TIORoomManager.h
//  tio-chat-ios
//
//  Created by QuangAnh on 28/08/2023.
//  Copyright © 2023 刘宇. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <TIOSDK/TIODefines.h>
#import <TIOSDK/TIOInvitationApply.h>

NS_ASSUME_NONNULL_BEGIN
@class TIORoom;
@class TIORoomMember;
@class TIOUser;
@class TIOSocketPackage;
@class TIOSystemNotification;


typedef NS_ENUM(NSUInteger, TIORoomCardStatus) {
    TIORoomCardStatusAvailable  =   1, ///< 分享的群名片可用
    TIORoomCardStatusUnavailable=   2,///< 分享的群名片不可用
};

/**
 ---- COMPLETION
 */

typedef void(^TIORoomsHandler)(NSArray<TIORoom *> * __nullable room,NSError * __nullable error);
typedef void(^TIORoomInfoHandler)(TIORoom * __nullable room, TIORoomMember * __nullable roomUser ,NSError * __nullable error);
typedef void(^TIORoomUserHandler)(TIORoomMember * __nullable roomUser,NSError * __nullable error);
typedef void(^TIORoomUsersHandler)(NSArray<TIORoomMember *> * __nullable roomUsers,BOOL first,BOOL last, NSInteger total, NSError * __nullable error);
typedef void(^TIOUsersNotInRoomHandler)(NSArray<TIOUser *> * __nullable users,NSError * __nullable error);
typedef void(^TIORoomError)(NSError * __nullable error);
typedef void(^TIOCreateRoomHandler)(NSError * __nullable error, NSString * __nullable roomId);
typedef void(^TIOCheckCardJoinToRoomError)(NSError * __nullable error, TIORoomCardStatus status);
typedef void(^TIOCheckMemberHandler)(NSError * __nullable error, BOOL isInRoom);


/** TIORoomName
 
 */
@interface TIORoomName : NSObject
@property (nonatomic, strong) NSString *name;

@property (nonatomic, assign) BOOL allowServerToUpdateAutomatically;
@end

/** TIORoomDelegate
 
 */
@protocol TIORoomDelegate <NSObject>
@optional
/// 已删除解散群
- (void)didDeleteRoom:(TIORoom  * _Nullable )room;
/// 已转让群
- (void)didTransferedRoom:(TIORoom  * _Nullable )room;
/// 已退群
- (void)didExitFromRoom:(TIORoom  * _Nullable )room;

- (void)didUpdateRoomInfo:(TIORoom * _Nullable )room;
/// 被踢出群
- (void)didKickedOut:(TIOSystemNotification *)notification;
/// 重新加入群聊
- (void)didRejoin:(TIOSystemNotification *)notification;
/// 群成员数量变更
- (void)didUpdateMemebersCount:(NSInteger)count;

@end

/** TIORoomManager
 
 */
@interface TIORoomManager : NSObject

- (void)createRoomName:(NSString * _Nullable)name
          introduction:(NSString *)intro
                 users:(NSArray<NSString *> *)userIds
            completion:(TIOCreateRoomHandler)completion;

- (void)addUser:(NSArray<NSString *> *)userIds
         toRoom:(NSString *)roomId
      sharerUid:(NSString * _Nullable)sharerUid
     completion:(TIORoomError)completion;

- (void)applyToAddUsers:(NSArray *)userIds
                 toRoom:(NSString *)roomId
                    msg:(NSString *)msg
             completion:(TIORoomError)completion;

- (void)removeUser:(NSArray<NSString *> *)userIds
          fromRoom:(NSString *)roomId
        completion:(TIORoomError)completion;

- (void)fetchRoomInfoWithRoomId:(NSString *)roomId
                     completion:(TIORoomInfoHandler)completion;

- (void)fetchUserInfoInRoom:(NSString *)roomId
                 completion:(TIORoomUserHandler)completion;

- (void)searchMember:(NSString * _Nullable)key
              inRoom:(NSString *)roomId
          completion:(TIOUsersNotInRoomHandler)completion;

- (void)searchFriends:(NSString *)searchKey
            notInRoom:(NSString *)roomId
           completion:(TIOUsersNotInRoomHandler)completion;

- (void)fetchMembersInRoom:(NSString *)roomId
                 searchKey:(NSString * _Nullable)key
                pageNumber:(NSInteger)pageNumber
                completion:(TIORoomUsersHandler)completion;

- (void)searchMyRoomsWithKey:(NSString *)key
                  completion:(TIORoomsHandler)completion;

- (void)checkRoom:(NSString *)roomId canSendCardWithCompletion:(TIORoomError)completion;

- (void)checkRoomShareCard:(NSString *)roomId fromUser:(NSString *)fromUserId completion:(TIOCheckCardJoinToRoomError)completion;

- (void)shareRoom:(NSString *)roomId
           toUids:(NSArray<NSString *> * _Nullable )uids
        toRoomIds:(NSArray<NSString *> * _Nullable )roomIds completion:(TIORoomError)completion;

- (void)checkMember:(NSString *)memberId
           isInRoom:(NSString *)roomId
         completion:(TIOCheckMemberHandler)completion;

#pragma mark - 用户更新修改操作
// User update modification operation

- (void)updateUserNick:(NSString *)newNick
                inRoom:(NSString *)roomId
            completion:(TIORoomError)completion;

- (void)updateRoomName:(NSString *)newNick
                inRoom:(NSString *)roomId
            completion:(TIORoomError)completion;

- (void)updateRoomNotice:(NSString *)newNotice
                  inRoom:(NSString *)roomId
              completion:(TIORoomError)completion;

- (void)updateRoomIntro:(NSString *)newIntro
                 inRoom:(NSString *)roomId
             completion:(TIORoomError)completion;

#pragma mark - 群操作
//group operation

- (void)exitFromRoom:(NSString *)roomId
          completion:(TIORoomError)completion;

- (void)deleteRoom:(NSString *)roomId
        completion:(TIORoomError)completion;

- (void)transferRoom:(NSString *)roomId
              toUser:(NSString *)uid
          completion:(TIORoomError)completion;

- (void)updateJoiningPermissionForRoom:(NSString *)roomId
                           isAllowJoin:(BOOL)allow
                            completion:(TIORoomError)completion;

- (void)updateReviewingPermissionForRoom:(NSString *)roomId
                                isReview:(BOOL)isReview
                              completion:(TIORoomError)completion;

- (void)fetchAllRooms:(TIORoomsHandler)completion;

- (void)changeMemberRole:(TIORoomUserRole)role
                     uid:(NSString *)uid
                  inRoom:(NSString *)roomid
              completion:(TIORoomError)completion;

- (void)fetchApplyInfoForInviting:(NSString *)applyId
                       completion:(void(^)(TIOInvitationApply  * _Nullable applyInfor, NSArray <TIOUser *>  * _Nullable users, NSError * __nullable error))completion;

- (void)dealApplyForInviting:(NSString *)applyId
                   messageId:(NSString *)mid
                  completion:(TIORoomError)completion;

- (void)updateAddingFriendPermissionInRoom:(NSString *)roomId
                                      flag:(NSInteger)flag
                                completion:(TIORoomError)completion;

- (void)forbiddenSpeakInRoom:(NSString *)roomid
                        oper:(NSInteger)oper
                        mode:(NSInteger)mode
                    duration:(NSInteger)duration
                         uid:(NSString *_Nullable)uid
                  completion:(TIORoomError)completion;

- (void)fetchForbiddenUserListInRoomId:(NSString *)roomid
                             searchKey:(NSString * _Nullable)key
                            pageNumber:(NSInteger)pageNumber
                            completion:(TIORoomUsersHandler)completion;

- (void)checkStatusForUser:(NSString *)uid
                    inRoom:(NSString *)roomid
                completion:(void(^)(NSError * _Nullable error, NSDictionary * _Nullable result))completion;

- (void)addDelegate:(id<TIORoomDelegate>)delegate;

- (void)removeDelegate:(id<TIORoomDelegate>)delegate;

- (void)handler:(TIOSocketPackage *)data;

@end

NS_ASSUME_NONNULL_END
