#pragma once

#include <QByteArray>
#include <QHash>
#include <QSharedPointer>

#include "NetUtil.h"

#define HashType QHash<int,QByteArray>
Container(HashType)

using Hash = NetHashTypeContainer*;