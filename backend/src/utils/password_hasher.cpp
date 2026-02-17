#include "password_hasher.h"

#include <functional>
#include <sstream>

std::string PasswordHasher::hashPassword(const std::string &plainText) {
    std::hash<std::string> hasher;
    size_t value = hasher("erp_salt_" + plainText);
    std::ostringstream oss;
    oss << value;
    return oss.str();
}

bool PasswordHasher::verifyPassword(const std::string &plainText, const std::string &hashedPassword) {
    return hashPassword(plainText) == hashedPassword;
}
