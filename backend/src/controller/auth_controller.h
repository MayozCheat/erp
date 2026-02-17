#ifndef CONTROLLER_AUTH_CONTROLLER_H
#define CONTROLLER_AUTH_CONTROLLER_H

#include "../service/auth_service.h"

#include <string>

// 认证控制器：负责接收参数并返回简单 JSON 字符串
class AuthController {
public:
    explicit AuthController(AuthService &authService);

    std::string login(const std::string &username, const std::string &password) const;
    std::string changePassword(int userId, const std::string &newPassword);

private:
    AuthService &authService;
};

#endif
