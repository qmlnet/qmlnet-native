#include "NetAbstractItemModelRoleNames.h"

Creator(HashType, qmodelhash)
Deleter(HashType, qmodelhash)

void net_qmodelhash_insert(Hash hash, int num, const char* data) {
    hash->data->insert(num, QString::fromLocal8Bit(data).toLocal8Bit());
}