# TIOCHAT
## Example 
## Config in appdelegate
```sh
let tioConfig = TIOConfig()
tioConfig.httpsAddress = "https://tio-chat.dev.ftech.ai"
tioConfig.resourceAddress = "https://minio.dev.ftech.ai"
tioConfig.secrectKey = "FY0xOa"
tioConfig.cookieName = "tio_session"
TIOChat.shareSDK().config = tioConfig

let option = TIOSDKOption()
option.isOpenSSL = true

TIOChat.shareSDK().register(with: option)
```
## isLogined
```sh
TIOChat.shareSDK().loginManager.isLogined
```

## Login
```sh
## login usser name, password
## let account = "" 
## let password = ""
TIOChat.shareSDK().loginManager.login(account, password: password, authcode: nil) { user, err in }
## login fqa
## let fqaToken = ""
TIOChat.shareSDK().loginManager.loginFQA(fqaToken) { user, err in }
```
## Logout
```sh
TIOChat.shareSDK().loginManager.logout {err in }
```
## After login success
```sh
# call function
TIOChat.shareSDK().lunch()

# example in AppDelegate
 if TIOChat.shareSDK().loginManager.isLogined { 
     TIOChat.shareSDK().lunch()
 }
 # example in API
 TIOChat.shareSDK().loginManager.loginFQA(fqaToken) { user, err in 
     if err == nil {
         TIOChat.shareSDK().lunch()
     }
 }
```
## List Conversation 
```sh
## Get List
TIOChat.shareSDK().conversationManager.fetchServerSessions { listConversation, error in }

## Add delegate
TIOChat.shareSDK().conversationManager.add(self)

## Remove Delegate
TIOChat.shareSDK().conversationManager.remove(self)

## Delegate Callback
+ ConversationManager
    # start a new chat
  - func didAdd(_ recentSession: TIORecentSession) {} 
    # update chat in session
  - func didUpdate(_ recentSession: TIORecentSession) {} 
    # Delete session. Note the trigger conditions:
    #1. When the machine executes deleteSession to delete the session
    #2. When the remote device executes deleteSession to delete the session
  - func didDeleteSession(_ session: String) {} 
    # The unread messages of a session have changed
  - func didChangeUnreadCount(_ total: Int, in session: TIORecentSession) {} 
    # The total number of unread messages across all conversations changed
  - func didChangeTotalUnreadCount(_ total: Int) {} 
    # All chat history in a conversation has been cleared
  - func didClearAllMessages(in session: TIOSession) {} 
```
## Public Chat
```sh
## Get List Public Chat Is Active
TIOChat.shareSDK().roomManager.fetchAllRooms { rooms, error in}

## Join Public Chat
TIOChat.shareSDK().conversationManager.joinPublicRoom(#Id Public Chat) { err in }
# Enter private chat session
# Note: When executing this method, the conversation in the external chat list will not be marked with the number of unread messages.
TIOChat.shareSDK().conversationManager.enterConversation(with: #TIOSession, uid: #UserId) { err, recentSession in }

## Load history chat
## param startMsgId, endMsgId use for load more messages
TIOChat.shareSDK().conversationManager.fetchMessagesHistory(session: #TIOSession, startMsgId: nil, endMsgId: nil) { err, messages in }

## Check Info PublicChat
## Get public chatId: session.toUId
TIOChat.shareSDK().roomManager.fetchRoomInfo(withRoomId: #PuclicChatId) { room, member, err in }

# Check Session Info
TIOChat.shareSDK().conversationManager.fetchSessionInfo(withSessionId: #SessionId) { err, session in}

# Set Notification Chat
# 1: On
# 2: Off
TIOChat.shareSDK().conversationManager.answerMessageNotification(forRoomid: id, flag: isMute == true ? 1 : 2) { err, data in}

# Get member in PublicChat
TIOChat.shareSDK().roomManager.fetchMembers(inRoom: #PublicChat Id, searchKey: nil, pageNumber: 1) { users, first, last, total, errr in }

# Clear chat History
# Use for public chat
let session = TIOSession(sessionId(), toUId: "", type: .sectionTypePublicChat) 
TIOChat.shareSDK().conversationManager.clearAllMessages(in: session) { err in}

# Public Chat Admin
TIORoomMember.role == TIOTeamUserRoleOwner

# Delete Public Chat (use for admin)
# param: id = roomId
TIOChat.shareSDK().roomManager.deleteRoom(id) { err in}

# Transfer Public Chat
TIOChat.shareSDK().roomManager.transferRoom(#Public Chat Id , toUser: #id member in members in public chat) { err in }
```
## Example Chat
```sh
# Public Chat
# Send Text
let message = TIOMessage()
message.session = session
message.messageType = .text
message.text = text

TIOChat.shareSDK().chatManager.send(message) { err in }

## Add delegate
TIOChat.shareSDK().chatManager.add(self)

## Remove delegate
TIOChat.shareSDK().chatManager.remove(self)

## Delegate Callback
    # The message has been sent (not available yet)
  - func didSend(_ message: TIOMessage, completion error: Error?) {}
    # Callback when receiving message
  - func onRecvMessages(_ messages: [TIOMessage]) {}
    # Friends have read all messages
  - func didReadedAllMessage() {}
```



## TIOchat Delegation
**- TIOLoginDelegate**
```sh
- (void)onLogin:(NSError* __nullable)error;
- (void)onLogout;
- (void)onKick:(TIOKickReason *)resaon;
- (void)didUpdateCurrentUserInfo:(TIOLoginUser *)user;
- (void)onThirdAccountDidBindToOldMobilephone:(NSString *)mobilePhone;
```
**- TIOConversationDelegate**
```sh
- (void)didAddSession:(TIORecentSession *)recentSession;
- (void)didUpdateSession:(TIORecentSession *)recentSession;
- (void)didDeleteSession:(NSString *)session;
- (void)shouldUpdateLocalFromRemote;
- (void)didUpdateLocalFromRemote:(BOOL)isUpdate;
- (void)didClearAllMessagesInSession:(TIOSession *)session;
- (void)didTopSession:(TIOSession *)session;
- (void)didCancelTopSession:(TIOSession *)session;
- (void)friendDidReadMyMessageInSession:(TIOSession *)session;
- (void)didChangeTotalUnreadCount:(NSInteger)total;
- (void)didChangeUnreadCount:(NSInteger)total inSession:(TIORecentSession *)session;
```
**- TIOChatLinkDelegate**
```sh
- (void)tio_linkConnected;
- (void)tio_linkDisconnected:(TIOSocketOfflineType)offlineType;
```
**- TIORoomDelegate**
```sh
- (void)didDeleteRoom:(TIORoom  * _Nullable )room;
- (void)didTransferedRoom:(TIORoom  * _Nullable )room;
- (void)didExitFromRoom:(TIORoom  * _Nullable )room;
- (void)didUpdateRoomInfo:(TIORoom * _Nullable )room;
- (void)didKickedOut:(TIOSystemNotification *)notification;
- (void)didRejoin:(TIOSystemNotification *)notification;
- (void)didUpdateMemebersCount:(NSInteger)count;
```
**- TIOTeamDelegate**
```sh
- (void)didDeleteTeam:(TIOTeam  * _Nullable )team;
- (void)didTransferedTeam:(TIOTeam  * _Nullable )team;
- (void)didExitFromTeam:(TIOTeam  * _Nullable )team;
- (void)didUpdateTeamInfo:(TIOTeam * _Nullable )team;
- (void)didKickedOut:(TIOSystemNotification *)notification;
- (void)didRejoin:(TIOSystemNotification *)notification;
- (void)didUpdateMemebersCount:(NSInteger)count;
```
**- TIOChatDelegate**
```sh
- (void)onRecvMessages:(NSArray<TIOMessage *> *)messages;
- (void)didDeleteMessage:(TIOMessage *)message;
- (void)didRevokeMessage:(TIOMessage *)message;
- (void)didReadedAllMessage;
```
**- TIOSystemDelegate**
```sh
- (void)onRecieveSystemNotification:(TIOSystemNotification *)notification;
- (void)onServerConnectChanged:(BOOL)connected;
- (void)onRecieveCustomNotification:(TIOSocketPackage *)object;
```
## TIOLoginManager
**USE: TIOChat.shareSDK().loginManager** 
## completion
```sh
typedef void(^TIOLoginHandler)(NSError * __nullable error);
typedef void(^TIOLoginHandler2)(TIOLoginUser * __nullable userData, NSError * __nullable error);
typedef void(^TIORegisterHandler)(NSError * __nullable error, NSString * __nullable msg);
```
```sh
- (void)login:(NSString *)account password:(NSString* _Nullable)password authcode:(NSString * _Nullable)authcode completion:(TIOLoginHandler2)completion;
- (void)logout:(nullable TIOLoginHandler)completion;
- (void)loginFQA:(NSString *)token handler:(TIOLoginHandler2)handler;
```
## TIOConversationManager
**USE: TIOChat.shareSDK().conversationManager** 
## completion
```sh
typedef void (^TIOFetchRecentSessionsBlock)(NSArray<TIORecentSession *> * __nullable recentSessions , NSError * __nullable error);
typedef void (^TIOFetchMessageHistoryHandler)(NSError * __nullable error,NSArray<TIOMessage *> * __nullable messages);
typedef void (^TIOEnterConversationHandler)(NSError * __nullable error, TIORecentSession * __nullable session);
typedef void (^TIOConversationError)(NSError * __nullable error);
typedef void (^TIOConversationOperHandler)(NSError * __nullable error, id data);
```
```sh
- (void)enterConversationWithSession:(TIOSession *)session uid:(NSString *)uid completion:(nonnull TIOEnterConversationHandler)completion;
- (void)leaveConversationWithSessionId:(NSString *)sessionId completion:(TIOConversationError)completion;
- (void)fetchServerSessions:(TIOFetchRecentSessionsBlock)completion;
- (nullable NSArray<TIORecentSession *> *)allRecentSessions;
- (void)fetchAllRecentSessions:(TIOFetchRecentSessionsBlock)completion;
- (void)findSession:(NSString *)sessionId complete:(void(^_Nullable)(TIORecentSession * _Nullable session))complete;
- (void)updateLocalFromRemote:(void(^ _Nullable)(BOOL isSuccess, NSInteger all))completion retryCount:(NSInteger)retryCount;
- (void)clearLocal:(void(^)(BOOL isSuccess))completion;
- (void)fetchMessagesHistory:(TIOSession *)session startMsgId:(NSString * __nullable)startMsgId endMsgId:(NSString * __nullable)endMsgId completion:(TIOFetchMessageHistoryHandler)completion;
- (void)fetchSessionId:(TIOSessionType)sessionType friendId:(NSString *)friendId completion:(TIOEnterConversationHandler)completion;
- (void)fetchSessionInfoWithSessionId:(NSString *)sessionId completion:(TIOEnterConversationHandler)completion;
- (void)joinPublicRoom:(NSString *) roomId completion: (TIOConversationError) completion;
- (void)topSession:(TIOSession *)session isTop:(BOOL)top completon:(TIOConversationError)completion;
- (void)deleteSession:(TIOSession *)session isClearMessage:(BOOL)clearMessage completion:(TIOConversationError)completion;
- (void)deleteAllMessagesInSession:(TIOSession *)session complrtion:(TIOConversationError)completion;
- (void)tipoffSession:(NSString *)sessionId complrtion:(TIOConversationOperHandler)completion
- (void)clearAllMessagesInSession:(TIOSession *)session completion:(TIOConversationError)completion;
- (void)answerMessageNotificationForUid:(NSString *__nullable)uid orTeamid:(NSString *__nullable)teamid flag:(NSInteger)flag completion:(TIOConversationOperHandler)completion;
```
## TIOChatManager
## completion
```sh
typedef void (^TIOFetchRecentSessionsBlock)(NSArray<TIORecentSession *> * __nullable recentSessions , NSError * __nullable error);
typedef void (^TIOFetchMessageHistoryHandler)(NSError * __nullable error,NSArray<TIOMessage *> * __nullable messages);
typedef void (^TIOEnterConversationHandler)(NSError * __nullable error, TIORecentSession * __nullable session);
typedef void (^TIOConversationError)(NSError * __nullable error);
typedef void (^TIOConversationOperHandler)(NSError * __nullable error, id data);

```
```sh
- (void)sendMessage:(TIOMessage *)message completionHandler:(nonnull void (^)(NSError * _Nullable error))completionHandler;
- (void)revokeMessage:(TIOMessage *)message inSession:(TIOSession *)session completionHandler:(nonnull void (^)(NSError * _Nullable error))completionHandler;
- (void)deleteMessage:(TIOMessage *)message inSession:(TIOSession *)session completionHandler:(nonnull void (^)(NSError * _Nullable error))completionHandler;
- (void)repostMessages:(NSArray *)messageIds toUsers:(NSArray * _Nullable)uIds teams:(NSArray * _Nullable)teamIds inSession:(TIOSession *)session completionHandler:(nonnull void (^)(NSError * _Nullable error))completionHandler;
- (void)tipoffMessage:(TIOMessage *)message inSession:(TIOSession *)session completionHandler:(nonnull void (^)(NSError * _Nullable error))completionHandler 
```
## TIOTeamManager
## completion
```sh
- (void)didDeleteTeam:(TIOTeam  * _Nullable )team;
- (void)didTransferedTeam:(TIOTeam  * _Nullable )team;
- (void)didExitFromTeam:(TIOTeam  * _Nullable )team;
- (void)didUpdateTeamInfo:(TIOTeam * _Nullable )team;
- (void)didKickedOut:(TIOSystemNotification *)notification;
- (void)didRejoin:(TIOSystemNotification *)notification;
- (void)didUpdateMemebersCount:(NSInteger)count;
```

```sh
- (void)createTeamName:(NSString * _Nullable)name
          introduction:(NSString *)intro
                 users:(NSArray<NSString *> *)userIds
            completion:(TIOCreateTeamHandler)completion;
- (void)addUser:(NSArray<NSString *> *)userIds toTeam:(NSString *)teamId sharerUid:(NSString * _Nullable)sharerUid completion:(TIOTeamError)completion;
- (void)applyToAddUsers:(NSArray *)userIds toTeam:(NSString *)teamId msg:(NSString *)msg completion:(TIOTeamError)completion;
- (void)removeUser:(NSArray<NSString *> *)userIds
          fromTeam:(NSString *)teamId
        completion:(TIOTeamError)completion;
- (void)fetchTeamInfoWithTeamId:(NSString *)groupId
                     completion:(TIOTeamInfoHandler)completion;
- (void)fetchUserInfoInTeam:(NSString *)teamId
                 completion:(TIOTeamUserHandler)completion;
- (void)searchMember:(NSString * _Nullable)key
              inTeam:(NSString *)teamId
          completion:(TIOUsersNotInTeamHandler)completion;
- (void)searchFriends:(NSString *)searchKey
            notInTeam:(NSString *)teamId
           completion:(TIOUsersNotInTeamHandler)completion;
- (void)fetchMembersInTeam:(NSString *)teamId
                 searchKey:(NSString * _Nullable)key
                pageNumber:(NSInteger)pageNumber
                completion:(TIOTeamUsersHandler)completion;
- (void)searchMyTeamsWithKey:(NSString *)key
                  completion:(TIOTeamsHandler)completion;
- (void)checkTeam:(NSString *)teamId canSendCardWithCompletion:(TIOTeamError)completion;
- (void)checkTeamShareCard:(NSString *)teamId fromUser:(NSString *)fromUserId completion:(TIOCheckCardJoinToTeamError)completion;
- (void)shareTeam:(NSString *)teamId toUids:(NSArray<NSString *> * _Nullable )uids toTeamIds:(NSArray<NSString *> * _Nullable )teamIds completion:(TIOTeamError)completion;
- (void)checkMember:(NSString *)memberId isInTeam:(NSString *)teamId completion:(TIOCheckMemberHandler)completion;
- (void)updateUserNick:(NSString *)newNick
                inTeam:(NSString *)teamId
            completion:(TIOTeamError)completion;
- (void)updateTeamName:(NSString *)newNick
                inTeam:(NSString *)teamId
            completion:(TIOTeamError)completion;
- (void)updateTeamNotice:(NSString *)newNotice
                  inTeam:(NSString *)teamId
              completion:(TIOTeamError)completion;
- (void)updateTeamIntro:(NSString *)newIntro
                 inTeam:(NSString *)teamId
             completion:(TIOTeamError)completion;
- (void)exitFromTeam:(NSString *)teamId
          completion:(TIOTeamError)completion;
- (void)deleteTeam:(NSString *)teamId
        completion:(TIOTeamError)completion;
- (void)transferTeam:(NSString *)teamId
              toUser:(NSString *)uid
          completion:(TIOTeamError)completion;
- (void)updateJoiningPermissionForTeam:(NSString *)teamId isAllowJoin:(BOOL)allow completion:(TIOTeamError)completion;
- (void)updateReviewingPermissionForTeam:(NSString *)teamId isReview:(BOOL)isReview completion:(TIOTeamError)completion;
- (void)fetchAllTeams:(TIOTeamsHandler)completion;
- (void)changeMemberRole:(TIOTeamUserRole)role uid:(NSString *)uid inTeam:(NSString *)teamid completion:(TIOTeamError)completion;
- (void)fetchApplyInfoForInviting:(NSString *)applyId completion:(void(^)(TIOInvitationApply  * _Nullable applyInfor, NSArray <TIOUser *>  * _Nullable users, NSError * __nullable error))completion;
- (void)dealApplyForInviting:(NSString *)applyId messageId:(NSString *)mid completion:(TIOTeamError)completion;
- (void)updateAddingFriendPermissionInTeam:(NSString *)teamId flag:(NSInteger)flag completion:(TIOTeamError)completion;
- (void)forbiddenSpeakInTeam:(NSString *)teamid oper:(NSInteger)oper mode:(NSInteger)mode duration:(NSInteger)duration uid:(NSString *_Nullable)uid completion:(TIOTeamError)completion;
- (void)fetchForbiddenUserListInTeamId:(NSString *)teamid
                             searchKey:(NSString * _Nullable)key
                            pageNumber:(NSInteger)pageNumber
                            completion:(TIOTeamUsersHandler)completion;
- (void)checkStatusForUser:(NSString *)uid inTeam:(NSString *)teamid completion:(void(^)(NSError * _Nullable error, NSDictionary * _Nullable result))completion;
```
## TIOTRoomManager
## completion
```sh
typedef void(^TIORoomsHandler)(NSArray<TIORoom *> * __nullable room,NSError * __nullable error);
typedef void(^TIORoomInfoHandler)(TIORoom * __nullable room, TIORoomMember * __nullable roomUser ,NSError * __nullable error);
typedef void(^TIORoomUserHandler)(TIORoomMember * __nullable roomUser,NSError * __nullable error);
typedef void(^TIORoomUsersHandler)(NSArray<TIORoomMember *> * __nullable roomUsers,BOOL first,BOOL last, NSInteger total, NSError * __nullable error);
typedef void(^TIOUsersNotInRoomHandler)(NSArray<TIOUser *> * __nullable users,NSError * __nullable error);
typedef void(^TIORoomError)(NSError * __nullable error);
typedef void(^TIOCreateRoomHandler)(NSError * __nullable error, NSString * __nullable roomId);
typedef void(^TIOCheckCardJoinToRoomError)(NSError * __nullable error, TIORoomCardStatus status);
typedef void(^TIOCheckMemberHandler)(NSError * __nullable error, BOOL isInRoom);
```
```sh
- (void)createRoomName:(NSString * _Nullable)name
          introduction:(NSString *)intro
                 users:(NSArray<NSString *> *)userIds
            completion:(TIOCreateRoomHandler)completion;
            
- (void)addUser:(NSArray<NSString *> *)userIds
         toRoom:(NSString *)roomId
      sharerUid:(NSString * _Nullable)sharerUid
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
```
