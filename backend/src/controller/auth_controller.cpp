#include "auth_controller.h"

#include <sstream>

AuthController::AuthController(AuthService &authService) : authService(authService) {}

std::string AuthController::login(const std::string &username, const std::string &password) const {
    User user{};
    std::string errorMessage;
    bool ok = authService.login(username, password, user, errorMessage);

    std::ostringstream oss;
    if (!ok) {
        oss << "{\"success\":false,\"message\":\"" << errorMessage << "\"}";
        return oss.str();
    }

    oss << "{\"success\":true,\"userId\":" << user.userId
        << ",\"username\":\"" << user.username << "\",\"isAdmin\":"
        << (user.isAdmin ? "true" : "false") << "}";
    return oss.str();
}

std::string AuthController::changePassword(int userId, const std::string &newPassword) {
    std::string errorMessage;
    bool ok = authService.changePassword(userId, newPassword, errorMessage);

    if (!ok) {
        return "{\"success\":false,\"message\":\"" + errorMessage + "\"}";
    }
    return "{\"success\":true,\"message\":\"密码修改成功\"}";
}
