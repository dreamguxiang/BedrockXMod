#pragma once
#include "eventBase.h"
class PostInitEvent : public INotifyEvent<PostInitEvent> {};
class ServerStartedEvent : public INotifyEvent<ServerStartedEvent> {};
class RegisterCommandEvent : public INotifyEvent<RegisterCommandEvent> {};