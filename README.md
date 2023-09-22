# TIOSDKSwift

A description of this package.
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
## Delegate TIOchat
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
**- TIOSystemDelegate**
```sh
- (void)onRecieveSystemNotification:(TIOSystemNotification *)notification;
- (void)onServerConnectChanged:(BOOL)connected;
- (void)onRecieveCustomNotification:(TIOSocketPackage *)object;
```
## TIOLoginManager
**USE: TIOChat.shareSDK().loginManager** 
**FUNCTION**
```sh
- (void)login:(NSString *)account password:(NSString* _Nullable)password authcode:(NSString * _Nullable)authcode completion:(TIOLoginHandler2)completion;
- (void)logout:(nullable TIOLoginHandler)completion;
- (void)loginFQA:(NSString *)token handler:(TIOLoginHandler2)handler;
```
## TIOConversationManager
**USE: TIOChat.shareSDK().conversationManager** 
**FUNCTION**
```sh
- (void)login:(NSString *)account password:(NSString* _Nullable)password authcode:(NSString * _Nullable)authcode completion:(TIOLoginHandler2)completion;
- (void)logout:(nullable TIOLoginHandler)completion;
- (void)loginFQA:(NSString *)token handler:(TIOLoginHandler2)handler;
```
