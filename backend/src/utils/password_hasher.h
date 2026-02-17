#ifndef UTILS_PASSWORD_HASHER_H
#define UTILS_PASSWORD_HASHER_H

#include <string>

// 密码哈希工具（演示版）
// 注意：生产环境必须替换为 bcrypt/argon2。
class PasswordHasher {
public:
    static std::string hashPassword(const std::string &plainText);
    static bool verifyPassword(const std::string &plainText, const std::string &hashedPassword);
};

#endif
