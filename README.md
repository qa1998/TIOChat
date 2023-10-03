# TIOCHAT

## ConfigTIOChat
## In Appdelegate

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
- (void)didSendMessage:(TIOMessage *)message completion:(NSError * _Nullable)error;
- (void)didUploadFile:(TIOMessage *)message completion:(NSError * _Nullable)error;
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
